#include <iostream>
#include <vector>
#include <string>
using namespace std;


int* perform_operation(int* endptr, char operation)
{
    int operand1 = *(endptr - 2);
    int operand2 = *(endptr - 1);
    *(endptr - 1) = 0;
    if(operation == '+'){
        *(endptr - 2) = operand1 + operand2;
    }
    else if(operation == '-')
    {
        *(endptr - 2) = operand1 - operand2;
    }
    else if(operation == '*')
    {
        *(endptr - 2) = operand1 * operand2;
    }
    else if(operation == '/')
    {
        if(operand2 == 0)
        {
            cout << "Error: Division by zero" << endl;
            exit(EXIT_FAILURE);
        }
        *(endptr - 2) = int(operand1 / operand2);
    }
    return --endptr;

}

int main()
{

    std::cout << "Input an expression in reverse Polish notation (end with #):" << endl;
    cout << "EXPR> ";
    string command = "";
    getline(cin,command);
    int operational[80];// = new int[80];
    int* optr = operational;
    //int* start_ptr = operational;
    char *buffer = command.data();
    int schetCifr = 0;
    int schetZnakov = 0;
    for(char* p = buffer; p < buffer + command.size(); ++p)
    {
        if((int)*p >= 48 && (int)*p <= 57)
        {
            *optr = *p - '0';
            optr++;
            schetCifr++;
        }
        else if(*p == '+' || *p == '-' || *p == '/' || *p == '*')
        {
            if(schetCifr == 0)
            {
              cout << "Error: Expression must start with a number" << endl;
              exit(EXIT_FAILURE);
            }
            else
            {
                optr = perform_operation(optr, *p);
                schetZnakov ++;
            }
        }
        else if(*p == '#')
        {
            break;
        }
        else if(*p == ' ')
        {
            continue;
        }
        else
        {
            cout << "Error: Unknown character" << endl;
            exit(EXIT_FAILURE);
        }
    }
    if(schetCifr > schetZnakov+1)
    {
        cout << "Error: Too few operators" << endl;
        exit(EXIT_FAILURE);
    }
    if(schetCifr < schetZnakov+1)
    {
        cout << "Error: Too few operands" << endl;
        exit(EXIT_FAILURE);
    }
    else
    {
        cout << "Correct: "<< *(--optr) << " is the result" << endl;

    }


    return 0;
}
