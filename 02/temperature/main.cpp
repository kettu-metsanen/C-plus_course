#include <iostream>

using namespace std;

int main()
{
    double temperatur = 0;
    cout << "Enter a temperature: ";
    cin >> temperatur;
    cout << temperatur << " degrees Celsius is " << temperatur*1.8+32 <<  " degrees Fahrenheit" << endl;
    cout << temperatur << " degrees Fahrenheit is " << (temperatur-32)/1.8 <<  " degrees Celsius" << endl;

    return 0;
}
