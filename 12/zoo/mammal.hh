#ifndef MAMMAL_HH
#define MAMMAL_HH

#include <iostream>
#include <string>
#include <animal.hh>

class Mammal: public Animal
{
public:
    Mammal();
    void suckle(std::ostream& output);
};

#endif // MAMMAL_HH
