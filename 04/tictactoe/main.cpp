/* Ristinolla
 *
 * Kuvaus:
 *   Ohjelma toteuttaa ristinollapelin, jossa pelialuetta pystyy
 * laajentamaan. Alussa peliruudukko on kooltaan 3 x 3. Peliruudukossa
 * on kolmenlaisia merkkejä: risti (X), nolla (0) ja tyhjä (.).
 *   Pelivuorossa ovat vuorotellen risti ja nolla, risti aloittaa.
 * Joka kierroksella vuorossa olevalle merkille kysytään koordinaatteja
 * eli kahta lukua. Vuorossa oleva merkki sijoitetaan peliruudukolla
 * annettuihin koordinaatteihin, ja vuoro siirtyy toiselle merkille.
 *   Pelin voittaa merkki, jolla saadaan ensimmäiseksi täytettyä peliruudukon
 * kokonainen rivi, kokonainen sarake tai kokonainen diagonaali.
 * Peli voi päättyä myös sellaiseen tilanteeseen, että peliruudukko on
 * täynnä merkkejä, mutta kumpikaan merkki ei voittanut.
 *   Ohjelma tarkistaa annetut koordinaatit. Koordinaattien pitää olla
 * peliruudukon sisällä, tai koordinaatit saavat ylittyä tai alittua
 * korkeintaan yhdellä. Jos annettu x- tai y-koordinaatti (rivi tai sarake)
 * ylittyy yhdellä, peliruudukko laajenee oikealle ja alaspäin. Jos taas
 * x- tai y-koordinaatti alittuu yhdelle, peliruudukko laajenee vasemmalle
 * ja alaspäin. Peliruudukko siis pysyy aina neliön muotoisena.
 *   Pelin päättyessä kerrotaan, kumpi voitti, vai voittiko kumpikaan.
 *
 * Ohjelman kirjoittaja
 * Nimi: Anna Rumiantseva
 * Opiskelijanumero: 50309159
 * Käyttäjätunnus: rdanru
 * E-Mail: anna.rumiantseva@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 * Harjoittelun vuoksi laitoin kaikki funktiot toiseen tiedostoon,
 * Toivottavasti en menetä pisteitä sen takia. Tämä parani minun ymmärtämisen
 * miten sijoittaa funktiot ja oliot eri tiedostoihin.
 * */

#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <help_functions.hh>


using namespace std;

int main()
{
    char player = 'X';
    //char player = '0'; // for debugging purposes
    vector<vector<char>> board(3, vector<char>(3, '.')); // aloitetaan ruudukolla 3x3
    //vector<vector<char>> board{{'X','0','.'},{'0','X','X'},{'X','.','.'}}; //for debugging purposes
    cout << "Start game:" << endl;
    print_board(board); // tulostetaan ruudukko
    while(true)
    {
        string cmd1 = "", cmd2 = "";
        cout << "For " << player << ", enter coordinates: x y> ";
        cin >> cmd1;
        if(cmd1 == "q") // lopetetaan ohjelma jo on syötetty "q"
        {
            cout << "Why on earth you are giving up the game?" << endl;
            return 0;
        }
        cin >> cmd2;
        bool res = parse_commands(cmd1, cmd2, player, board); // muutetaan koordinaatit luvuiksi
        if(res == true) // jos muuttaminen onnistui jatketaan
        {
            print_board(board);
            if(if_won(board, player)) // jos on voitto lopetetaan ohjelma
            {
                break;
            }
            if(ifempty(board)) // jos ruudukko on täynnä eikä ole voittoa tulostetaan ilmoitus ja lopetetaan ohjelma
            {
                cout << "No empty places\nGame over!" << endl;
                break;
            }
            if(player == 'X')// vaihdetaan pelaaja jokaisen onnistuneen vuoron jälkeen
            {
                player = '0';
            }
            else
            {
                player='X';
            }

        }
    }
    EXIT_SUCCESS;

}
