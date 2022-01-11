#include <iostream>

using namespace std;

int main()
{
    int num;
    int numCube;
    cout << "Enter a number: " ;
    cin >> num;
    numCube = num * num * num;
    if (num <= numCube) {
        cout << "The cube of " << num << " is " << numCube << "." << endl;
    }
    else {
        cout << "Error! The cube of "<< num <<" is not " << numCube << "." << endl;
    }
    return 0;
}
