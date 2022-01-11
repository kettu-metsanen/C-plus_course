#include <iostream>
using namespace std;
int main()
{
    int numers = 0;
    cout << "How many numbers would you like to have? ";
    cin >> numers;
    int i = 1;
    while (i <= numers) {
        if (i%3 == 0){
            if(i%7 == 0){
                cout << "zip boing" << endl;
            }
            else {
                    cout << "zip" << endl;
                }
        }
        else if(i%7 == 0){
            cout << "boing" << endl;
        }
        else{
            cout << i << endl;
        }

        i++;
    }
}
