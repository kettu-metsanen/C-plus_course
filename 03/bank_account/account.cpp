#include "account.hh"
#include <iostream>

Account::Account(const std::string& owner, bool has_credit): owner_(owner), has_credit_(has_credit)
{

    generate_iban();
}

// Setting initial value for the static attribute running_number_
int Account::running_number_ = 0;

void Account::generate_iban()
{
    ++running_number_;
    std::string suffix = "";
    if(running_number_ < 10)
    {
        suffix.append("0");
    }
    else if(running_number_ > 99)
    {
        std::cout << "Too many accounts" << std::endl;
    }
    suffix.append(std::to_string(running_number_));

    iban_ = "FI00 1234 ";
    iban_.append(suffix);
}
void Account::print() const{
    std::cout << owner_ << " : " << iban_ << " : " << balance_  << " euros"<< std::endl;
}

void Account::set_credit_limit(int lim){
    if(has_credit_ != 1){
        std::cout << "Cannot set credit limit: the account has no credit card" << std::endl;
        return;
    }
    limit_ = lim;

}

void Account::save_money(int amount){
    balance_ += amount;
}

void Account::take_money(int amount){
    int sum = balance_ - amount;
    if (sum < 0) {
        sum = sum * (-1);
    }

    if(has_credit_ != 1 and amount>balance_){

        std::cout << "Cannot take money: balance underflow" << std::endl;
        return;
    }
    if(has_credit_ ==1 and limit_ < sum){
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
        return;
    }
    else{
        balance_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
    }
}

void Account::transfer_to(Account& where, int amount){
    int sum = balance_ - amount;
    if (sum < 0) {
        sum = sum * (-1);
    }
    if (amount > balance_ and has_credit_ != 1){
        std::cout << "Cannot take money: balance underflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        return;
    }
    if (has_credit_ == 1 and limit_ < sum){
        std::cout << "Cannot take money: credit limit overflow" << std::endl;
        std::cout << "Transfer from " << iban_ << " failed" << std::endl;
        return;
    }
    else{
        where.save_money(amount);
        balance_ -= amount;
        std::cout << amount << " euros taken: new balance of " << iban_ << " is " << balance_ << " euros" << std::endl;
    }
}
