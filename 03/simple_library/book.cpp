#include "book.hh"
#include <date.hh>

Book::Book(std::string avtor, std::string nazvanie, bool loan)
{
    avtorName_ = avtor;
    nazvanieKnigi_ = nazvanie;
    loan_ = loan;
}

void Book::print()
{
    std::cout << avtorName_ << " : " << nazvanieKnigi_ << std::endl;
    if(loan_ == true)
    {
        std::cout << "- available" << std::endl;
    }
    else
    {
        std::cout << "- loaned: ";
        loanDay_.print();
        std::cout << "- to be returned: ";
        returnDay_.print();
    }
}

void Book::loan(Date day)
{
    if(loan_ == true)
    {
        loan_ = false;
        loanDay_ = day;
        day.advance(28);
        returnDay_ = day;
    }
    else
    {
        std::cout << "Already loaned: cannot be loaned" << std::endl;
    }
}

void Book::renew()
{
    if(loan_ == false)
    {
        returnDay_.advance(28);
    }
    else
    {
        std::cout << "Not loaned: cannot be renewed" << std::endl;
    }
}

void Book::give_back()
{
    loan_ = true;
}
