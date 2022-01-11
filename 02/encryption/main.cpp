#include <iostream>
#include <string>
using namespace std;

int tarkastus(string text){
    string abc = "abcdefghijklmnopqrstuvwxyz";
    if(text.length() != 26){
        cout << "Error! The encryption key must contain 26 characters." << endl;
        exit(EXIT_FAILURE);
    }
    for(int i = 0; i < 26; i++){
        //cout << text.at(i) << " " << islower(text.at(i)) << endl;
        if (islower(text.at(i)) == 0){
            //cout << "Error! The encryption key must contain only lower case characters." << endl; HERE WAS THE LAST ERROR!!!
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            exit(EXIT_FAILURE);
        }
    }

    for(int i = 0; i < 26; i++){
        string::size_type n;
        n = text.find(abc.at(i));

        if ( n == string::npos ) {
            cout << "Error! The encryption key must contain all alphabets a-z." << endl;
            exit(EXIT_FAILURE);
        }
        }
    return 0;
    }
int tarkastusText(string text){

    for(int i = 0; static_cast<string::size_type>(i) < text.length(); i++){
        //cout << text.at(i) << " " << islower(text.at(i)) << endl;
        if (islower(text.at(i)) == 0){
            cout << "Error! The text to be encrypted must contain only lower case characters." << endl;
            exit(EXIT_FAILURE);
        }
    }
    return 0;
}

string kod(string key, string text){
     string newText(text.length(), 42);

     string abc = "abcdefghijklmnopqrstuvwxyz";
     for(int i = 0; i < 26; i++){
         string::size_type n;
         n = text.find(abc.at(i));
         while(n != string::npos){
             char merk = key.at(i);
             newText.replace(n, 1, 1, merk);
             text.replace(n, 1, 1, 42);
             n = text.find(abc.at(i));
         }


     }

     return newText;
}
int main()
{
    string key;
    string text;
    string result;
    cout << "Enter the encryption key: ";
    cin >> key;
    if(tarkastus(key) == EXIT_FAILURE){
        return 0;
    }

    cout << "Enter the text to be encrypted: ";
    cin >> text;
    if(tarkastusText(text) == EXIT_FAILURE){
        return 0;
    }
    result = kod(key, text);
    cout << "Encrypted text: " << result << endl;

    return 0;
}
