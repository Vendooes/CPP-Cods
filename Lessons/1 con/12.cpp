#include <iostream>
#include <cmath>

int main() {
    int n;
    std::cin>>n;

    for (int i = 0; i < n; ++i) {
        int sp = std::abs(n/2 - i);
        int pl = n- 2 * sp;
        std::cout << std::string(sp, ' '); 
        std::cout << std::string(pl,'+') << std::endl;
    }
    return 0;
}