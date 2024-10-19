#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono>
#include <thread>
#include <algorithm> // std::shuffle
#include <random>    // std::default_random_engine

using namespace std;

// Gaming desk function
void vykresliDesku(const vector< vector<string> >& deska, const vector< vector<bool> >& odkryte) {
    cout << "   ";
    for (int i = 0; i < deska[0].size(); i++) {
        cout << setw(3) << i + 1;
    }
    cout << endl;

    for (int i = 0; i < deska.size(); i++) {
        cout << setw(3) << i + 1;
        for (int j = 0; j < deska[i].size(); j++) {
            if (odkryte[i][j]) {
                cout << setw(3) << deska[i][j];
            } else {
                cout << setw(3) << "*";
            }
        }
        cout << endl;
    }
}

// Cards shuffle
void zamichejKarty(vector< vector<string> >& deska) {
    vector<string> hodnoty;
    hodnoty.push_back("A"); hodnoty.push_back("A");
    hodnoty.push_back("B"); hodnoty.push_back("B");
    hodnoty.push_back("C"); hodnoty.push_back("C");
    hodnoty.push_back("D"); hodnoty.push_back("D");
    hodnoty.push_back("E"); hodnoty.push_back("E");
    hodnoty.push_back("F"); hodnoty.push_back("F");
    hodnoty.push_back("G"); hodnoty.push_back("G");
    hodnoty.push_back("H"); hodnoty.push_back("H");

    
    random_device rd;
    mt19937 g(rd());

    
    shuffle(hodnoty.begin(), hodnoty.end(), g);

    int index = 0;
    for (int i = 0; i < deska.size(); i++) {
        for (int j = 0; j < deska[i].size(); j++) {
            deska[i][j] = hodnoty[index++];
        }
    }
}

// User login
bool zadejSouradnice(int& radek, int& sloupec, int velikost) {
    cout << "Zadejte souřadnice (radek a sloupec, např. 2 3): ";
    cin >> radek >> sloupec;

    if (cin.fail() || radek < 1 || radek > velikost || sloupec < 1 || sloupec > velikost) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
        cout << "Neplatné souřadnice, zkuste znovu." << endl;
        return false;
    }

    radek--; 
    sloupec--; 
    return true;
}

void zobrazNaChvili(vector< vector<bool> >& odkryte, const vector< vector<string> >& deska, int r1, int s1, int r2, int s2) {
    odkryte[r1][s1] = true;
    odkryte[r2][s2] = true;
    vykresliDesku(deska, odkryte);
    this_thread::sleep_for(chrono::seconds(2));
    odkryte[r1][s1] = false;
    odkryte[r2][s2] = false;
}

// Main
void hrajHru() {
    vector< vector<string> > deska(4, vector<string>(4));
    vector< vector<bool> > odkryte(4, vector<bool>(4, false));

    zamichejKarty(deska);
    int nalezenePary = 0;

    while (nalezenePary < 8) {
        vykresliDesku(deska, odkryte);

        int r1, s1, r2, s2;
        do {
            cout << "Vyberte první kartu:" << endl;
        } while (!zadejSouradnice(r1, s1, 4) || odkryte[r1][s1]);

        odkryte[r1][s1] = true;
        vykresliDesku(deska, odkryte);

        do {
            cout << "Vyberte druhou kartu:" << endl;
        } while (!zadejSouradnice(r2, s2, 4) || odkryte[r2][s2] || (r1 == r2 && s1 == s2));

        odkryte[r2][s2] = true;
        vykresliDesku(deska, odkryte);

        if (deska[r1][s1] == deska[r2][s2]) {
            cout << "Správná dvojice!" << endl;
            nalezenePary++;
        } else {
            cout << "Nesprávná dvojice, znovu zakrývám karty..." << endl;
            zobrazNaChvili(odkryte, deska, r1, s1, r2, s2);
        }
    }

    cout << "Gratulujeme, našli jste všechny páry!" << endl;
}

int main() {
    char volba;
    do {
        cout << "Vítejte v Pexesu!" << endl;
        cout << "Vaším úkolem je najít všechny dvojice stejných karet." << endl;

        hrajHru();

        cout << "Chcete hrát znovu? (y/n): ";
        cin >> volba;

    } while (volba == 'y' || volba == 'Y');

    cout << "Děkujeme za hraní!" << endl;
    return 0;
}
