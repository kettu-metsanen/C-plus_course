/*
 * Ohjelman kirjoittaja
 * Nimi: Anna Rumiantseva
 * Opiskelijanumero: 50309159
 * Käyttäjätunnus: rdanru
 * E-Mail: anna.rumiantseva@tuni.fi
 *
 * Huomioita ohjelmasta ja sen toteutuksesta:
 *
 */




#include "help_functions.hh"
#include <iostream>
#include <vector>
#include <string>
#include <cstring>


using namespace std;
//Tämä funktio tulostaa ruudukon
void print_board(vector<vector<char>>& board)
{
    cout << "  "; //tulostetaan tyhjä vasen ylänurkka
    // tulostetaan ylävaakarivi. Tämä rivi sisältää 1,2,3...
    for(unsigned int i=1; i<=board[0].size(); i++)
    {
        cout << i % 10 << " ";
    }
    cout << endl;
    // tulostetaan vasen pystyrivi. Tämä rivi sisältää 1,2,3...
    for(unsigned int i=0; i<board.size(); i++)
    {
        cout << (i+1) % 10 << " ";
        for(unsigned int j=0; j<board[i].size(); j++)
        {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

//Tämä funktio hoitaa ruudukon kasvattamisen, jos koordinaattina on syötetty nolla.
//Tässä tapauksessa täytyy huomioida olemassa olevien ristinollien siirto.
//Ideana on sijoittaa vector<vector<char>> rakenteeseen yksi vector<char> alkuun,
//jolloin kaikki olemassa olevat ristinollat siirtyy automaattisesti.
//Sama idea on jos sijoittaa jokaiseen alimmaiseen vector<char> rakenteeseen yksi ylimääräinen "."-char
void enlarge_board_zero(vector<vector<char>>& board)
{
    board.insert(board.begin(), vector<char>(board.size(), '.')); //lisätään vaakarivi alkuun
    for(unsigned int i=0; i<board.size(); i++)//lisätään solut alkuun
    {
        board[i].insert(board[i].begin(), '.');
    }
}
//Tämä funktio hoitaa ruudukon kasvattamisen jos koordinaattina on syötetty luku, joka
//1 yksikkö suurempi kuin ruudukon koko. Tässä tapauksessa olemassa olevia ristinollia ei tarvitse huomioida.
void enlarge_board_end(vector<vector<char>>& board)
{
    board.insert(board.end(), vector<char>(board.size(), '.')); //lisää vector<char> loppuun
    for(unsigned int i=0; i<board.size(); i++) // lisää char-solut jokaisen rivin loppuun
    {
        board[i].insert(board[i].end(), '.');
    }
}


//Tämä funktio tarkistaa kaikki koordinaateille asetetut ehdot
//ja jos nämä ehdot toteutuvat sijoittaa pelaajan merkin ruudukolle palauttaen TRUE
//muussa tapauksessa palauta FALSE
bool hit(char symbol, unsigned int x, unsigned int y, vector<vector<char>>& board)
{
    unsigned int height = board.size();
    unsigned int width = board[0].size();
    if(abs(static_cast<int>(x) - static_cast<int>(y)) > static_cast<int>(board.size())) //jos koordinaattien x ja y ero on
        //isompi kuin ruudukon koko tulostetaan virheilmoitus ja palautetaan FALSE

    {
        cout << "Coordinate outside the board" << endl;
        return false;
    }

    // Jos koordinaatti x tai y on isompi kuin ruudukon koko+1 tulostetaan virheilmoitus
    // ja palautetaan FALSE
    if(x > width+1 || y > height+1)
    {
        cout << "Coordinate outside the board" << endl;
        return false;
    }
    if((x == 0) || (y==0)) // jos koordinaatti x tai y on nolla muutetaan ruudukon koko.
    {
        enlarge_board_zero(board);
        board[y++][x++] = symbol; // korjataan syötetyt koordinaatit
                                //(koordinaatisto kasvoi ykkösellä, lisätään tämä ykkönen syötetyille koordinaateille
                                // ja lisätään pelaajan merkki ruudukolle
        return true;
    }
    else if((x == board[0].size() + 1) || (y == board.size() + 1)) // jos koordinaatti x tai y
        // on isompi kuin ruudukon koko + 1 muutetaan ruudukon koko.
    {
        enlarge_board_end(board);
        board[y-1][x-1] = symbol; // koordinaatit täytyy siirtää, koska indeksointi alkaa nollasta
                                    // ja ruudukon numerot ykkösestä
        return true;
    }
    if(board[y-1][x-1] != '.') // tarkistetaan onko solu tyhjä. Jos ei ole tulostetaan virheilmoitus ja palautetaan FALSE
    {
        cout << "The given place is already occupied" << endl;
        return false;
    }
    board[y-1][x-1] = symbol; // sijoitetaan syötettyjen koordinaattien mukaan pelaajan merkki
    return true;
}
// Tämä funktio tarkistaa syötetyt koordinaatit ja yrittää muuttaa ne luvuiksi.
bool parse_commands(string cmd1, string cmd2, char player, vector<vector<char>>& board)
{
    int x=0; int y=0;
    try // jos x tai y eivät sisällä lukua, siirrytään "catch" osiolle
    {
        x = stoi(cmd1); // muuttaa "string"-muuttujan luvuksi
        y = stoi(cmd2); // - || - || -
    }
    catch(...) // jos ei onnistunut muuttaa luvuksi tulostetaan virheilmoitus ja palautetaan FALSE
    {
        cout << "Coordinate outside the board" << endl;
        return false;
    }
    // Jos kaikki muunnokset onnistuivat hyvin, kutsutaan hit-funktio
    bool result = hit(player, x, y, board);
    return result;
}
// Tämä funktio tarkistaa pelaajan voiton
bool if_won(vector<vector<char>>& board, char player)
{
    string participant = ""; // tallennetaan pelaajan merkki
    player == 'X' ? participant = "Cross" : participant="Nought"; // какая из диаоналей вирал
    int width = board[0].size();
    int height = board.size();
    // Tarkistetaan vaakarivit
    for(unsigned int i=0; i<board.size(); i++)
    {
        char comparable = board[i][0]; // tallennetaan jokaisen rivin ensimmäinen merkki (X tai 0)
        int counter = 1; // asetetaan laskuri
        if(comparable == '.') // jos ensimmäinen merkki on ".", siirrytään välittömästi seuraavalle riville
        {
            continue;
        }
        for(unsigned int j=1; j<=board[i].size(); j++) // käydään läpi rivin jokainen alkio
        {
            if(board[i][j] == comparable) // jos toinen alkio == comparable, kolmas alkio == comparable jne.
            {
                counter++; // kasvatetaan laskuri
            }
        }
        if(counter == width) // jos laskurin arvo on sama kuin ruudukon koko juhlitaan voitto
        {
            cout << participant << " won horizontally" << endl << "Game over!"<< endl;
            return true;
        }
    }
    // Tarkistetaan pystyrivit
    for(unsigned int i=0; i<board.size(); i++)
    {
        char comparable = board[0][i]; // tallennetaan jokaisen pystyrivin ensimmäinen alkio
        if(comparable == '.') // jos tämä alkio on ".", välittömästi siirrytään seuraavalle sarakkeelle
        {
            continue;
        }
        int counter = 1; // asetetaan laskuri
        for(unsigned int j=1; j<board[i].size(); j++) // käydään pystyrivin jokainen alkio läpi
        {
            if(board[j][i] == comparable) // jos jokainen alkio on sama kuin comparable
            {
                counter++; // kasvatetaan laskuri
            }
        }
        if(counter == height) // jos laskurin arvo on sama kuin ruudukon koko juhlitaan voitto
        {
            cout << participant << " won vertically" << endl << "Game over!"<< endl;
            return true;
        }
    }
    // Tarkistetaan diagonaalit
    // päälävistäjä
    char comparable = board[0][0]; // tallennetaan vasemman ylänurkan arvo
    int counter = 1; // asetetaan laskuri
    if(comparable != '.') // jos ensimmäinen alkio on "." lopetetaan silmukka
    {
        for(unsigned int i=1; i<board[0].size(); i++) // käydään päälävistäjän jokainen arvo läpi ja verrataan
        {
            if(comparable == board[i][i]) // jo on sama kuin comparable
            {
                counter++; // kasvatetaan laskuri
            }
        }
    }
    if(counter == width) // juhlitaan jos laskurin arvo on sama kuin ruudukon koko
    {
        cout << participant << " won diagonally" << endl << "Game over!"<< endl;
        return true;
    }
    // Tarkistetaan toinen lävistäjä
    comparable = board[height-1][0];
    if(comparable == '.')
    {
        return false;
    }
    counter = 1;
    for(int i=height-2; i>=0; i--)
    {
        for(int j=2; j<width; j++)
        {
            if(comparable == board[i][j])
            {
                counter++;
            }
        }
    }
    if(counter == width)
    {
        cout << participant << " won diagonally" << endl << "Game over!" << endl;
        return true;
    }
    return false;
}
// Tarkistetaan onko ruudukko täynnä
bool ifempty(vector<vector<char>>& board)
{
    for(unsigned int i=0; i<board.size(); i++)
    {
        for(unsigned int j=0; j<board[i].size(); j++)
        {
            if(board[i][j] == '.')
            {
                return false;
            }
        }
    }
    return true;
}
