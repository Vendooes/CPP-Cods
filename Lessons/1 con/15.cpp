#include <iostream>

int main() {
    int a;
    std::cin>> a;
    if (a ==0) {
        std::cout <<0;
        return 0;
    }
    int one =0;
    int zero =0;
    while (a >0) {
        if (a %2 == 1) {
            one++;
        } else {
            zero++;
        }
        a /= 2;
    }
    for (int i =0; i<one;i++) {
        std::cout << 1;
    }
    for (int i =0;i <zero;i++) {
        std::cout << 0;
    }
    return 0;
}