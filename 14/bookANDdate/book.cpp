#include "book.hh"

Book::Book(std::string name, std::string avtor, int vuosi, bool vidana)
{
    name_ = name;
    avtor_ = avtor;
    vuosi_ = vuosi;
    vidana_ = vidana;
}
