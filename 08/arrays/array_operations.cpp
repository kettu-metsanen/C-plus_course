#include "array_operations.hh"
#include <iostream>
int greatest_v1(int* itemptr, int size){
    int maximum = *itemptr;
    for(int *p = itemptr; p < itemptr + size; ++p)
    {
        if(*p > maximum){
            maximum = *p;
        }
    }
    return maximum;
}

int greatest_v2(int* itemptr, int* endptr)
{
    int maximum = *itemptr;
    for(int *p = itemptr; p < endptr; ++p)
    {
        if(*p > maximum)
            maximum = *p;
    }
    return maximum;
}

void copy(int* itemptr, int* endptr, int* targetptr)
{
    for(int* p = itemptr; p < endptr; ++p)
    {
        *targetptr = *p;
        targetptr++;
    }
}

void reverse(int* leftptr, int* rightptr)
{
    float size=static_cast<int>((rightptr - leftptr)/2);
    for(int i=0; i < size; i++)
    {
        --rightptr;
        int temp = *leftptr;
        *leftptr = *rightptr;
        *rightptr = temp;
        leftptr++;
    }
}
