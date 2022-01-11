#ifndef BOOK_HH
#define BOOK_HH
#include <iostream>
#include <string>
#include <date.hh>

class Book
{
public:
    Book(std::string avtor, std::string nazvanie, bool loan = true);
    void print();
    void loan(class Date day);
    void renew();
    void give_back();
private:
    std::string avtorName_;
    std::string nazvanieKnigi_;
    bool loan_;
    Date loanDay_;
    Date returnDay_;

};

#endif // BOOK_HH
