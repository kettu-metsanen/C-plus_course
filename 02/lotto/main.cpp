#include <iostream>

using namespace std;

int faktorial(int all, int ballnum){
    int n = all - (all - ballnum);
    int tulosA = 1;
    int tulosB = 1;
    int tulos;
    for(int i= 1; i < n; i++ ){
        tulosA = tulosA * (all - i);

    }
    tulosA = tulosA * all;

    for(int i= 1; i < ballnum; i++ ){
        tulosB = tulosB * (ballnum - i);

    }
    tulosB = tulosB * ballnum;

    tulos = tulosA / tulosB;
    return tulos;
}


int main()
{
    int allbols;
    int needbals;
    int result;
    cout << "Enter the total number of lottery balls: ";
    cin >> allbols;
    cout << "Enter the number of drawn balls: ";
    cin >> needbals;
    if (allbols < 0){
        cout << "The number of balls must be a positive number." << endl;
        return 0;
    }
    if (needbals > allbols){
        cout << "The maximum number of drawn balls is the total amount of balls." << endl;
        return 0;
    }
    else {
        result = faktorial(allbols, needbals);
        cout << "The probability of guessing all " << needbals << " balls correctly is 1/" <<result << endl;
        return 0;
    }

}
