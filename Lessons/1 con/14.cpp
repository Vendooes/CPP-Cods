#include <iostream>

int main() {
    int a,b,c;
    std::cin>> a>> b>>c;
    int maximum = a;
    if (b > maximum) maximum =b;
    if (c > maximum) maximum =c;
    int NOK = maximum;
    while (true) {
        if (NOK % a == 0 && NOK % b == 0 && NOK % c == 0) {
            break;
        }
        NOK +=maximum;
    }
    std::cout << NOK << std::endl;
    return 0;
}