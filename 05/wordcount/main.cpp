#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <set>
using namespace std;

int main()
{
    string tiedoston_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);
    ifstream tiedosto_olio(tiedoston_nimi);
    map<string, set<int>> lause;
    if ( not tiedosto_olio ) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else{
        string sana;
        string rivi;
        int ind;
        int pos = 0;
        int schetchik = 1;
        bool chek = true;
        while ( getline(tiedosto_olio, rivi)){
            //cout << rivi<< endl;

            while(chek == true){
                ind = rivi.find(" ", pos);
                if(rivi.find(" ", pos) == string::npos){
                    sana = rivi.substr(pos);
                    lause[sana].insert(schetchik);
                    chek = false;

                }
                else{

                    sana = rivi.substr(pos, ind-pos);
                    lause[sana].insert(schetchik);
                    pos = ind+1;
                    }

                }
            schetchik += 1;
            chek = true;
            pos = 0;
            }
        }

        for( auto pari : lause ){
            cout << pari.first << " " << pari.second.size() << ": ";
            for( auto i :  pari.second){
                if(i == *pari.second.rbegin()){
                    cout << i;
                }
                else{
                    cout << i << ", ";
                }
            }
            cout << endl;
        }


}
