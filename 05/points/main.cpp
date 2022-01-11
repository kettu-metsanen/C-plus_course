#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
using namespace std;


int main()
{
    string tiedoston_nimi = "";

    cout << "Input file: ";
    getline(cin, tiedoston_nimi);

    ifstream tiedosto_olio(tiedoston_nimi);
    map<string, int> pistet;
    if ( not tiedosto_olio ) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else{

        string rivi;
        string luku;
        string nimi;
        int ind;
        int znach;
        while ( getline(tiedosto_olio, rivi)) {
            ind = rivi.find(":", 0);
            luku = rivi.substr(ind+1, rivi.size());
            nimi = rivi.substr(0, ind);
            if(pistet.find(nimi) == pistet.end()){
                pistet[nimi] = atoi(luku.c_str());
            }
            else{
                znach = pistet[nimi];
                pistet[nimi] = znach + atoi(luku.c_str());
            }



        }
    }
    cout << "Final scores:" << endl;
    for(auto pari : pistet ){
        cout << pari.first << ": " << pari.second << endl;
    }
    tiedosto_olio.close();
}
