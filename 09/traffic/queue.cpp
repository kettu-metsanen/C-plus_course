#include "queue.hh"
#include <iostream>

// Implement the member functions of Queue here
Queue::Queue(unsigned int cycle){
    cycle_ = cycle;
    length_ = 0;

}
Queue::~Queue() {

}
void Queue::enqueue(string const& reg)
{
    if(is_green_ == false)
    {
        Vehicle* new_item = new Vehicle{reg, nullptr};
        if(first_ == nullptr)
        {
            first_ = new_item;
            last_ = new_item;

        }
        else
        {
            Vehicle* tptr = last_;
            last_ = new_item;
            tptr->next = last_;
        }
        length_++;

    }
    else
    {
        std::cout << "GREEN: The vehicle "<< reg <<" need not stop to wait" << endl;
    }
}
void Queue::dequeue()
{

    unsigned i = 0;
    if(length_ < cycle_)
    {
        //std::cout << "lenght = " << length_ << "cycle_" << cycle_ << endl;
        while (length_ != 0)
        {
            //std::cout << "I am here i =" << i << << "lengh"  endl;
            Vehicle* item_to_be_removed = first_;
            if ( first_ == last_ ) {
               first_ = nullptr;
               last_ = nullptr;
            } else {
               first_ = first_->next;
            }

            delete item_to_be_removed;
            i++;
            length_--;
        }
    }
    else
    {
        while (i != cycle_)
        {

            Vehicle* item_to_be_removed = first_;
            if ( first_ == last_ ) {
               first_ = nullptr;
               last_ = nullptr;
            } else {
               first_ = first_->next;
            }

            delete item_to_be_removed;
            i++;
            length_--;
        }
    }
    is_green_ = false;
}
void Queue::print() const
{
    if(is_green_ == false)
    {
        //std::cout << "lenght = " << length_ << endl;
        if(length_ == 0)
        {
            std::cout << "RED: No vehicles waiting in traffic lights" << endl;
        }
        else
        {
            std::cout << "RED: Vehicle(s) ";
            Vehicle*tptr = first_;
            while(tptr != nullptr)
            {
                    std::cout << tptr->reg_num << " ";
                    tptr = tptr->next;
            }
            std::cout << "waiting in traffic lights" << endl;
        }
    }
    else
    {
        //std::cout << "lenght = " << length_ << endl;
        if(length_ == 0)
        {
            std::cout << "GREEN: No vehicles waiting in traffic lights" << endl;
        }
        else
        {
            std::cout << "GREEN: Vehicle(s) ";
            unsigned int i=0;
            Vehicle*tptr = first_;
            while(i != cycle_)
            {
                if(tptr->next == nullptr)
                {
                    std::cout << tptr->reg_num << " ";
                    break;
                }
                else
                {
                    std::cout << tptr->reg_num << " ";
                    tptr = tptr->next;
                    i++;
                }
            }
            std::cout << "can go on" << endl;
        }
    }
}
void Queue::switch_light()
{
    //std::cout << is_green_ << endl;
    if(is_green_ == false)
    {
        is_green_ = true;
        print();
        if(length_ != 0)
        {
            dequeue();
        }
    }
    else
    {
        is_green_ = false;
        print();
    }
}
void Queue::reset_cycle(unsigned int cycle)
{
    cycle_ = cycle;
}
