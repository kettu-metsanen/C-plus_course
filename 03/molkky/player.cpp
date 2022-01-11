#include "player.hh"

Player::Player(std::string nimi)
{
    nimi_ = nimi;
    pts_ = 0;
}

std::string Player::get_name()
{
    return nimi_;
}

void Player::add_points(int pts)
{
    int tar = pts_+pts;
    if(tar > 50)
    {
        std::cout << nimi_ << " gets penalty points!" << std::endl;
        pts_ = 25;
    }
    else
    {
        pts_+= pts;
    }
}

bool Player::has_won()
{
    if(pts_ == 50)
    {
        return true;
    }
    return false;
}

int Player::get_points()
{
    return pts_;
}
