#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main() {
    string tiedoston_nimi = "";
    string output_nimi = "";
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);
    cout << "Output file: ";
    cin >> output_nimi;

    ifstream tiedosto_olio(tiedoston_nimi);

    if ( not tiedosto_olio ) {
        cout << "Error! The file " << tiedoston_nimi << " cannot be opened." << endl;
        return EXIT_FAILURE;
    } else {
        ofstream tiedosto_output(output_nimi);
        int schetchk = 1;
        string rivi;
        while ( getline(tiedosto_olio, rivi) ) {
           //cout << schetchk << " " << rivi;
           tiedosto_output << schetchk << " " << rivi << endl;
           schetchk += 1;
        }

        tiedosto_olio.close();
        tiedosto_output.close();
    }

    return EXIT_SUCCESS;
}
