//--------------------------------------------------
//  COMP.CS.110 Ohjelmointi 2: Rakenteet -pohjakoodi
//  Copyright © 2021
//--------------------------------------------------

/*
 * Ohjelma lukee tiedostosta kurssit ja paikkakunnat, joissa kurseihin voi ilmoittautua.
 * Tällä ohjelmalla on yksinkertainen käyttöliittymä, joka pohjautuu komentoihin.
 * Ohjelman avulla käyttäjä voi:
 * - Tulostaa aiheet
 * - Hakea annetun paikkakunn kurssit
 * - Tulostaa kurssit, joissa on tilaa
 * - Tulostaa kurssit aiheittain
 * - Katsoa suosituimmat kurssit
 * - Poista tietty kurssi datarakenteesta
 * Ohjelman toiminta päättyy komennolla "quit".
 * Tietojen tallentamiseen ohjelmassa käytettiin rakennetta map<string,map<string,vector<Course>>>.
 * Ylin map: <aihe,map...>, seuraava taso: map<paikkakunta, vector<Course>>.
 * Ohjelman kirjoittaja
 * Nimi: Anna Rumiantseva
 * Opiskelijanumero: 50309159
 * Käyttäjätunnus: rdanru
 * E-Mail: anna.rumiantseva@tuni.fi
 * */

#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

// Jakaa annetun merkkijonon str annetun merkin delimiter erottelemiin osiin
// ja palauttaa osat vektorissa.
// Jos erotinmerkki on lainausmerkkien sisällä, erotinmerkistä ei välitetä,
// eli osaa olla erottelematta lainausmerkkien sisällä olevan tekstin.
//
// Splits the given string str into parts separated by the given delimiter
// and returns the parts in a vector.
// If the delimiter appears inside quatation, ignores delimiter,
// i.e. does not split quoted text.
std::vector<std::string> split_ignoring_quoted_delim(const std::string& str,
                                                     char delimiter)
{
    std::vector<std::string> result = {""};
    bool inside_quotation = false;
    for(char current_char : str)
    {
        if(current_char == '"')
        {
            inside_quotation = not inside_quotation;
        }
        else if(current_char == delimiter and not inside_quotation)
        {
            result.push_back("");
        }
        else
        {
            result.back().push_back(current_char);
        }
    }
    if(result.back() == "")
    {
        result.erase(--result.end());
    }
    return result;
}


struct Course {
    string name;
    string location;
    int enrollments;
};

//Tässä funktiossä jäsentetaan rivit tiedosta, tarkistetaan tuplasti rivit ja poistetaan se,
//tarkistetaan tiedoston avamisaen kanssa, tarkistetaan värin parametrit tiedostossa
//ja laitetaan oikein tiedot uudeen rakenteelliseen(map(map(vector(struct)))
//
//Syöttää tiedoston nimi ja takenteellinen
void parsing_and_struct(const string fname, map<string,map<string,vector<Course>>>& ds)
{
    ifstream reader(fname);//avataan tiedosto
    if(not reader){ // tarkistetaan etta tiedosto on mahdolista avata, jos ei tulee virhe
        cout << "Error: the input file cannot be opened" << endl;
        exit(EXIT_FAILURE);
    }
    vector<string> rows;
    string row;
    while(getline(reader, row))//kaikki rivit tiedostosta laitetaan vektoriin
    {
        rows.push_back(row);
    }
    reader.close();//kiini tiedosto

    for(unsigned int i=0; i < rows.size(); i++)//tarkistetaan tuplasti rivit
    {
        vector<string> frow = split_ignoring_quoted_delim(rows[i],';');
        for(unsigned int j=i+1; j < rows.size(); j++)
        {
            vector<string> srow = split_ignoring_quoted_delim(rows[j],';');
            if((frow[1] == srow[1]) & (frow[2] == srow[2]))
            {
                rows.erase(rows.begin() + i);//poistetaan sama rivi
                break;

            }
        }
    }


    for(unsigned int i=0; i < rows.size(); i++)//täytetään rakenteelliseen
    {
        Course temp;
        vector<string> parsed = split_ignoring_quoted_delim(rows[i],';');
        for(auto i = parsed.begin(); i != parsed.end(); i++)//tarkistetaan jos rivissa oli tyhjä parametri
        {
            if(*i == "")
            {
                cout << "Error: empty field" << endl;
                exit(EXIT_FAILURE);
            }
        }
        if(parsed.size() != 4)//tarkistetaan jos rivis ale tai yle 4 parametria
        {
            cout << "Error: empty field" << endl;
            exit(EXIT_FAILURE);
        }

        else//täytetään struct
        {
            temp.name = parsed[1];
            temp.location = parsed[2];
            if(parsed[3] == "full"){
                temp.enrollments=50;
            }
            else{
                temp.enrollments = stoi(parsed[3]);
            }

            ds[parsed[0]][parsed[2]].push_back(temp);//täytetään rakeneelliseen
        }

    }



}

//Tämä on apufunktio, joka on tarkoitettu map<Course>-rakenteen lajitteluun
bool course_name_compare(const Course& nem1, const Course& nem2)
{
    return nem1.name < nem2.name;
}

//Funktio tulostaa aiheet
void print_themes(map<string,map<string,vector<Course>>>& ds)
{
    //käydään läpi kaikki map ylimmän tason avaimet
    for(auto it=ds.begin(); it != ds.end(); it++)
    {
            cout << it->first << endl;
    }
}

//Funktio tulostaa kurssin nimen mukaisessa aakkosjärjestyksessä kaikki kurssit,
//jotka löytyvät kyseiseltä paikkakunnalta ja kyseisestä teemasta sekä osallistujamäärät
void print_courses(vector<string>& command, map<string,map<string,vector<Course>>> ds)
{
    bool non_existing_paikkakunta = 0; //muuttuja, joka tarkistaa syötetyn paikkakunnan
    bool non_existing_teema = 0; //muuttuja, joka tarkistaa syötetyn aiheen
    if(command.size() != 3)//tarkistetaan että on kaikki parametrit
    {
        cout << "Error: error in command courses" << endl;
        return;
    }
    //map<string,map<string,vector<Course>>> temp = ds;
    for(auto it=ds.begin(); it != ds.end(); it++) //käydään aihe-avaimet läpi
    {

        if(it->first == command[2]) // jos aihe-avain on sama kuin annettu aihe
        {

            non_existing_teema = true; // jos ohjelma on täällä, niin aihe on olemassa = true
            for(auto it1=it->second.begin(); it1 != it->second.end(); it1++) // käydään läpi aiheen kurssit
            {
                if(it1->first == command[1]) // jos kurssi on sama kuin komennossa
                {
                    non_existing_paikkakunta = true; // jos ohjelma on täällä, niin paikkakunta on olemassa
                    sort(it1->second.begin(), it1->second.end(), course_name_compare);//lajitelaan tiedoston vektori aakkosjärjestykseen
                    for(auto it2=it1->second.begin(); it2 != it1->second.end(); it2++){
                        if(it2->enrollments == 50) // jos kurssi on täynnä
                        {
                            cout << it2->name << " --- " << "full" << endl; //tulostaa "full"

                        }
                        else
                        {
                            cout << it2->name << " --- " << it2->enrollments << " enrollments" << endl;

                        }

                    }
                }
            }
        }

    }
    if(non_existing_teema == false)//tarkistetaan oliko aihe oikein
    {
        cout << "Error: unknown theme" << endl;
        return;
    }
    if(non_existing_paikkakunta == false)//tarkistetaan oliko paikkakunta oikein
    {
        cout << "Error: unknown location" << endl;
        return;
    }
}


/*
 * Tämä funktio tulostaa kaikki olemassa olevat kurssit
 */
void print_available(map<string,map<string,vector<Course>>> ds)
{
    //map<string,map<string,vector<Course>>> temp = ds;
    for(auto it=ds.begin(); it != ds.end(); it++) // käydään läpi aiheen avaimet
    {
        for(auto it1=it->second.begin(); it1 != it->second.end(); it1++) // käydään läpi paikkakunnan avaimet
        {
            sort(it1->second.begin(), it1->second.end(), course_name_compare);// lajitellaan aakkojärjestykseen
            for(auto it2=it1->second.begin(); it2 != it1->second.end(); it2++) // käydään läpi vektorissa olevat kurssit
            {
                if(it2->enrollments != 50) // jos kurssilla on tilaa, tulostetaan
                {
                    cout << it->first << " : " << it1->first << " : " << it2->name << endl;
                }
            }

        }
    }
}

/*
 * Ohjelma tulostaa kurssit annetulla aiheella
 */
void print_courses_in_theme(map<string,map<string,vector<Course>>>& ds, vector<string>& command)
{
    bool tarkastus = false; // muuttuja, joka seuraa annetun aiheen olemassaolon
    for(auto it=ds.begin(); it != ds.end(); it++) // käydään läpi kaikki aiheet
    {
        if(it->first == command[1]) // jos aihe on sama kuin komennossa
        {
            for(auto it1=it->second.begin(); it1 != it->second.end(); it1++) // käydään läpi kaikki tämän aiheen kurssit jokaisessa paikkakunnassa
            {

                for(auto it2=it1->second.begin(); it2 != it1->second.end(); it2++)
                {
                    cout << it1->first << " : " << it2->name << endl;
                    tarkastus = true;
                }
            }
        }
    }
    if(tarkastus == false)
    {
        cout << "Error: unknown theme" << endl;
        return;
    }
}

/*
 * Funktio tulostaa kaikki kurssit annetussa paikkakunnassa
 */
void print_courses_in_location(map<string,map<string,vector<Course>>> ds, vector<string>& command)
{
    //map<string,map<string,vector<Course>>> temp = ds;
    vector<Course> sort_name = {}; // tähän kerätään kaikki sopivat kurssit tulostusta varten
    for(auto it=ds.begin(); it != ds.end(); it++)
    {
        for(auto it1=it->second.begin(); it1 != it->second.end(); it1++)
        {
            if(it1->first == command[1]) // jos on sopiva paikkakunta
            {
                for(auto it2=it1->second.begin(); it2 != it1->second.end(); it2++) // käydään läpi kaikki tämän paikkakunnan kurssit
                {
                    sort_name.push_back(*it2); // ja lisätään vektoriin

                }
            }

        }
    }
    if(sort_name.size() == 0) //jos vektori on tyhjä, niin silmukassa tätä paikkakuntaa ei tullut vastaan
    {
        cout << "Error: unknown location" << endl;
        return;
    }
    sort(sort_name.begin(), sort_name.end(), course_name_compare);//lajitellaan vektori
    for(auto i = sort_name.begin(); i != sort_name.end(); i++) // ja tulostetaan
    {
        cout << i->name << endl;
    }

}

/*
 * Funktio tulostaa suosituimman teeman
 */
void print_favorite_theme(map<string,map<string,vector<Course>>>& ds)
{
    if(ds.size() == 0) // jos rakenne on tyhjä niin ilmoittautumisia ei ole
    {
        cout << "No enrollments" << endl;
    }
    else
    {
        map<string, int> sum_themes; // map aiheiden laskuun
        for(auto it=ds.begin(); it != ds.end(); it++) // käydään läpi jokainen aihe
        {
            int summa = 0; // jokaisen aiheen "sisällä" alustetaan laskuri
            for(auto it1=it->second.begin(); it1 != it->second.end(); it1++) //käydään läpi jokainen paikkakunta
            {

                    for(auto it2=it1->second.begin(); it2 != it1->second.end(); it2++) // ja jokainen kurssi
                    {

                        summa += it2->enrollments; // ja lasketaan ilmoittautumiset
                    }


            }
            sum_themes[it->first] = summa; // sijoitetaan map rakenteeseen
        }

        // etsitään maksimi
        int max_summ = 0;
        for(auto i = sum_themes.begin(); i != sum_themes.end(); i++)
        {
            if(max_summ < i->second)
            {
                max_summ = i->second;
            }
            //cout << i->first << " : " << i->second << endl;
        }
        cout << max_summ << " enrollments in themes" << endl;
        for(auto i = sum_themes.begin(); i != sum_themes.end(); i++)
        {
            if(max_summ == i->second)
            {
                cout << "--- " << i->first << endl;

            }
        }
    }
}

/*
 * Funktio poistaa annettu kurssi datarakenteesta
 */
void print_cancel(map<string,map<string,vector<Course>>>& ds, vector<string>& command)
{
    bool tarkastus = false;
    for(auto it=ds.begin(); it != ds.end(); it++) // aihe
    {

        for(auto it1=it->second.begin(); it1 != it->second.end(); it1++) //paikkakunta
        {
            vector<Course> tempvec = it1->second; // tallennetaan jokaisen aiheen ja paikkakunnan vector<Course>
            vector<Course> newvec; // luodaan uusi vector<Course>
            for(auto i = tempvec.begin(); i!=tempvec.end(); i++)
            {
                if(i->name != command[1]) // jos avain ei ole sama kuin poistettava kurssi
                {
                    newvec.push_back(*i); // lisätään se uuteen vektoriin

                }
                else
                {
                    tarkastus = true; // jos poistettava kurssi löytyi
                }
            }
            ds[it->first][it1->first] = newvec; // liitetään datarakenteeseen uusi vektori

        }
    }
    if(tarkastus == false)
    {
        cout << "Error: unknown course" << endl;
        return;
    }
    cout << command[1] << " cancelled in all locations" << endl;
}
int main()
{
    string tiedoston_nimi;
    cout << "Input file: ";
    getline(cin, tiedoston_nimi);
    map<string,map<string,vector<Course>>> dstructure;
    parsing_and_struct(tiedoston_nimi, dstructure);

    string command = "";
    while (command != "quit")
    {
        cout << "> ";
        getline(cin, command);
        vector<string> pars_comand = split_ignoring_quoted_delim(command, ' ');

        if (pars_comand[0] == "themes"
                )
        {
            print_themes(dstructure);
            continue;
        }
        if(pars_comand[0] == "courses")
        {
            print_courses(pars_comand, dstructure);
            continue;
        }
        if(pars_comand[0] == "available")
        {
            print_available(dstructure);
            continue;
        }
        if(pars_comand[0] == "courses_in_theme")
        {
            print_courses_in_theme(dstructure, pars_comand);
            continue;
        }
        if(pars_comand[0] == "courses_in_location")
        {
            print_courses_in_location(dstructure, pars_comand);
            continue;
        }
        if(pars_comand[0] == "favorite_theme")
        {
            print_favorite_theme(dstructure);
            continue;
        }
        if(pars_comand[0] == "cancel")
        {
            print_cancel(dstructure, pars_comand);
            continue;
        }
        if(pars_comand[0] == "quit")
        {
            exit(EXIT_SUCCESS);
        }
        else
        {
            cout << "Error: Unknown command: " << pars_comand[0] << endl;
            continue;
        }
     }

    return EXIT_SUCCESS;
}

