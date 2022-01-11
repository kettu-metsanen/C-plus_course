#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>

class Player
{
public:
    Player(std::string nimi);
    std::string get_name();
    void add_points(int pts);
    bool has_won();
    int get_points();
private:
    std::string nimi_;
    int pts_;
};

#endif // PLAYER_HH
