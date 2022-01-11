#include "cards.hh"

// TODO: Implement the methods here
Cards::Cards(): top_(nullptr), last_(nullptr), length_(0){
}
Cards::~Cards() {
   while ( top_ != nullptr ) {
      Card_data* item_to_be_released = top_;
      top_ = top_->next;

      delete item_to_be_released;
   }
}
void Cards::add(int id){
    Card_data* new_item = new Card_data{id, nullptr};
    if(top_ == nullptr)
    {
        top_ = new_item;

    }
    else
    {
        Card_data* tptr = top_;
        top_ = new_item;
        top_->next = tptr;
        last_ = top_;
        while(last_->next != nullptr)
        {
            last_ = last_->next;
        }
    }
    length_++;
    return;
}

void Cards::print_from_top_to_bottom(std::ostream& s)
{
    int number = 1;
    if(length_ == 1)
    {
        s << number << ": " << top_->data << std::endl;
    }
    else
    {
        Card_data *tptr = top_;
        while(tptr != nullptr)
        {
                s << number << ": " << tptr->data << std::endl;
                tptr = tptr->next;
                number++;

        }
    }
    //delete tptr;
}

bool Cards::bottom_to_top()
{
    if(length_ == 0)
    {
        return false;
    }
    if(length_ == 1)
    {
        return true;
    }
    Card_data* second_last = top_;
    while(second_last->next->next != nullptr)
    {
        second_last = second_last->next;
    }
    Card_data* temp = top_; // save top to temporary variable
    top_ = last_; // now top is the last element
    top_->next = temp; // and new top refers to the previous top
    last_ = second_last; // the last element is now the second_last
    second_last->next = nullptr; // and the new last element has nullptr for the next property
    return true;
    //TODO
    //define returning either True or False depending on the data structure

}

bool Cards::top_to_bottom()
{
    if(length_ == 0)
    {
        return false;
    }
    if(length_ == 1)
    {
        return true;
    }

    Card_data* temp = top_; // save top_ to temporary variable
    top_ = top_->next; // new top_ is the next value after the top_
    last_->next = temp; // last refers to the old top_
    last_ = last_->next; // the old top_ becomes last
    last_->next = nullptr; // last refers to null
    return true;

}

int Cards::recursive_print(Card_data *top, std::ostream &s, int counter)
{

    if(top->next == nullptr)

    {
         s <<  --counter << ": "  << top->data << std::endl;
         return 0;
    }
    counter--;
    recursive_print(top->next, s, counter);
    s << counter << ": "  << top->data << std::endl;
    return 0;


}

void Cards::print_from_bottom_to_top(std::ostream &s)
{
    /*if(length_ == 1)
    {
        s << "1: " << top_->data << std::endl;
    }
    else
    {
        recursive_print(top_, s, ++length_);
    }*/
    int counter = length_ + 1;
    recursive_print(top_, s, counter);
}

bool Cards::remove(int& id)
{
    if(top_ == nullptr)
    {
        return false;
    }
    Card_data* item_to_be_removed = top_;

    id = item_to_be_removed->data;

    if ( top_ == last_ ) {
       top_ = nullptr;
       last_ = nullptr;
    } else {
       top_ = top_->next;
    }

    delete item_to_be_removed;
    length_--;

    return true;
}
