#include "calculations.hh"
#include <iostream>
#include <iomanip>
#include <sstream>  // for implementing function string_to_double
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const string GREETING_AT_END = "Thanks and see you later!";

// Utility function to sections a string at delimiters
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty = false);

// Function string_to_double changes a string comprising a real number
// into a float type value for calculations.
// It returns true, if parameter s comprised a real.
// It returns false, if s was not a valid real number.
// The converted float will be assigned into reference parameter result.
// The implementation of the function uses stringstream for the sake of example.
bool string_to_double(const string& s, double& result);


// TODO: Explore the following data structures!
struct Command {
    string str;
    vector<string>::size_type parameter_number;
    bool is_exit;
    double(*action)(double, double);
};

const vector<Command> COMMANDS = {
    {"+", 2, false, addition},
    {"-", 2, false, subtraction},
    {"*", 2, false, multiplication},
    {"/", 2, false, division},
    {"^", 2, false, power},
    {"POWER", 2, false, power},
    {"EXP", 2, false, power},
    {"PLUS", 2, false, addition},
    {"MINUS", 2, false, subtraction},
    {"TIMES", 2, false, multiplication},
    {"DIVIDED", 2, false, division},
    {"ADDITION", 2, false, addition},
    {"SUBTRACTION", 2, false, subtraction},
    {"MULTIPLICATION", 2, false, multiplication},
    {"DIVISION", 2, false, division},
    {"SUM", 2, false, addition},
    {"DIFFERENCE", 2, false, subtraction},
    {"PRODUCT", 2, false, multiplication},
    {"QUOTIENT", 2, false, division},
    {"ADD", 2, false, addition},
    {"INCREASE", 2, false, addition},
    {"SUBTRACT", 2, false, subtraction},
    {"DECREASE", 2, false, subtraction},
    {"MULTIPLY", 2, false, multiplication},
    {"DIVIDE", 2, false, division},
    {"STOP", 0, true, nullptr},
    {"QUIT", 0, true, nullptr},
    {"EXIT", 0, true, nullptr},
    {"Q", 0, true, nullptr}
};

bool is_digits(const std::string &str)
{
    return str.find_first_not_of("0123456789.-") == std::string::npos;
}

int main() {

    // Using precision of two decimals in printing
    cout.precision(2);
    cout << fixed;

    while ( true ) {
        cout << "calculator> ";

        string line = "";
        getline(cin, line);

        if ( line.empty() ) {
            // By inputting an empty line, the user can make the program end.
            cout << GREETING_AT_END << endl;
            break;
        }

        vector<string> pieces = split(line, ' ', true);

        if(pieces.size() == 0){
            continue;
        }

        string command_to_be_executed = pieces.at(0);
        for (auto & c: command_to_be_executed) c = toupper(c);
        // TODO: Implement command execution here!

        /*for(auto s: COMMANDS)
        {
            if(command_to_be_executed == s.str)
            {
                if(pieces.size() != 3)
                {
                    if(pieces.size() == 1)
                    {
                        if(s.is_exit)
                        {
                            cout << GREETING_AT_END << endl;
                            exit(EXIT_SUCCESS);
                        }
                    }
                }
                else
                {
                    cout << "Error: wrong number of parameters." << endl;

                }

                if(pieces.at(1).size()>1 or pieces.at(2).size()>1)
                {
                    cout << "Error: a non-number operand." << endl;

                }
                else
                {
                    cout << s.action(stoi(pieces.at(1)), stoi(pieces.at(2))) << endl;

                }
            }

        }
        cout << "Error: unknown command." << endl;*/
        bool chois = true;
        for(auto s: COMMANDS)
        {
            if(command_to_be_executed == s.str)
            {
                chois = true;
                break;
            }
            else
            {
                chois = false;
            }
        }
        if(chois == true)
        {
            if(pieces.size() != 3)
            {

                if(pieces.size() == 1)
                {
                    for(auto s: COMMANDS)
                    {
                        if(command_to_be_executed == s.str)
                        {
                            if(s.is_exit)
                            {
                                cout << GREETING_AT_END << endl;
                                exit(EXIT_SUCCESS);
                            }
                            else
                            {
                                cout << "Error: wrong number of parameters." << endl;
                            }
                        }

                    }

                }
                else
                {
                    cout << "Error: wrong number of parameters." << endl;

                }
            }
            else
            {
                for(auto s: COMMANDS)
                {
                    if(command_to_be_executed == s.str)
                    {
                        //cout << std::all_of(pieces.at(1).begin(), pieces.at(1).end(), ::isdigit) << endl;
                        if(is_digits(pieces.at(1)) == 0 or is_digits(pieces.at(2)) == 0)
                        {
                            cout << "Error: a non-number operand." << endl;
                        }
                        else
                        {
                            cout << s.action(atof(pieces.at(1).c_str()), atof(pieces.at(2).c_str())) << endl;
                        }
                    }
                }
            }
        }
        else
        {
            cout << "Error: unknown command." << endl;
        }
    }
}


// This function exemplifies istringstreams.
// It would be possible to use function stod of string to convert a string to
// a double, but to recognize all error cases would be more complicated with it
// at this phase of education.
// It is easier to use the boolean type return value that can be
// examined at calling point as done in the implementation below.
bool string_to_double(const string& s, double& result) {
    // Initializing input stream of istringstream type the string that will
    // scanned with ">>" or getline.
    istringstream stream(s);

    double tmp;

    // Reading input value in a normal way with ">>" operator.
    // You can operate istringstreams with the same operations as cin
    // and other ifstreams.
    stream >> tmp;

    if ( not stream ) {
        return false;
    }

    // ws is special operator that skips all the word delimiters (such as spaces)
    // until it meets something else
    stream >> ws;

    // If parameter s is a string comprising a valid real number, it cannot
    // succeed other characters than spaces.
    // Since previous ">> ws" operation threw the spaces away, at this point
    // the input stream should contain nothing.
    // If it does, then it is erroneous.
    // Let's try to read a character from the input stream.
    // If this fails, because the input stream has no characters left,
    // then all is right.
    // If it succeeds, then string s has something that it should not have.
    stream.get();

    if ( stream ) {
        return false;
    } else {
        result = tmp;
        return true;
    }
}

// Model implementation of good old split function
vector< string > split(const string& s,
                       const char delimiter,
                       bool ignore_empty){
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos)
    {
        string word = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and word.empty()))
        {
            result.push_back(word);
        }

    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}
