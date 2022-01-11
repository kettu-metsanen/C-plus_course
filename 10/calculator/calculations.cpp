// Note that there is no need for "using namespace std",
// since no C++ standard libraries are used.

double addition(double left, double right) {
    return left + right;
}


double subtraction(double left, double right) {
    return left - right;
}


double multiplication(double left, double right) {
    return left * right;
}


double division(double left, double right) {
    return left / right;
}
double power(double left, double right){
    double result = left;
    for(int i = 0; i < right-1; i++ )
    {
        result = result * left;
    }
    return result;
}
