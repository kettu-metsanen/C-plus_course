#include <iostream>

using namespace std;

// Before passing automated tests, do not touch the values of the following
// constants, even if they differ from those you see in Plussa.
// At the end of the course, if you use this program to count your final grade,
// you should update the constants to make them identical with those in Plussa.
unsigned int MAX_N_POINTS = 780;
unsigned int MAX_G_POINTS = 100;


// Add functions if you feel it necessary

int main()
{
    unsigned int n = 0;
    unsigned int g = 0;
    unsigned int p = 0;
    unsigned int e = 0;
    int tulos = 0;
    double summ = 0;
    int tulosN = 0;
    int tulosP = 0;
    cout << "Enter N points, G points, P points: ";
    cin >> n;
    cin >> g;
    cin >> p;
    cout << "Enter exam grade (if no exam, enter zero): ";
    cin >> e;
    if (g>0){
        summ = ((n+g)*100)/880;

    }
    else {
        summ = n*100/780;

    }

    if (summ >=50 and summ <60){
        tulosN = 1;
    }
    if (summ >=60 and summ <70){
        tulosN = 2;
    }
    if (summ >=70 and summ <80){
        tulosN = 3;
    }
    if (summ >=80 and summ <90){
        tulosN = 4;
    }
    if (summ >=90){
        tulosN = 5;
    }

    if (p >=51 and p <75){
        tulosP = 1;
    }
    if (p >=75 and p <125){
        tulosP = 2;
    }
    if (p >=125 and p <150){
        tulosP = 3;
    }
    if (p >=150 and p <175){
        tulosP = 4;
    }
    if (p >=175){
        tulosP = 5;
    }
    tulos = (tulosP + tulosN + e) / 3 ;
    if((tulosP + tulosN + e) % 3 >=2){
        tulos+=1;

    }
    if (p < 51 or summ < 50) {
        tulos = 0;
    }
    if (g < 30){
        if(tulos>2){
            tulos =2;
        }
    }
    if (g >= 30 and g < 40){
        if(tulos>3){
            tulos =3;
        }
    }
    if (g >= 40 and g < 50){
        if(tulos>4){
            tulos =4;
        }
    }
    if (e == 0){
        tulos = (tulosP + tulosN) / 2  - 2;
        if((tulosP + tulosN) % 2 >=1){
            tulos+=1;
        }
    }
    //cout << "Tulospiste N+G on " << tulosN << endl;
    //cout << "Tulospiste P on " << tulosP << endl;
    cout << "The final grade is " << tulos << endl;
    return 0;
}
