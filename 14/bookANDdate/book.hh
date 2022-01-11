#ifndef BOOK_HH
#define BOOK_HH
#include <iostream>

class Book
{
public:
    Book(std::string name, std::string avtor, int vuosi, bool vidana = false);

private:
    std::string name_;
    std::string avtor_;
    int vuosi_;
};

#endif // BOOK_HH
