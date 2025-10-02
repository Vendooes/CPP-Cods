#include <iostream>
#include <cmath>

bool First(int sim) {
    if (sim<= 1) {
        return false;}
        if (sim== 2) {
            return true;}
        if (sim%2== 0) {
            return false;}
    
    for (int i= 3; i<= sqrt(sim);i += 2)
    {
        if (sim%i == 0) {
            return false;}
    }
    return true;
}
 
int Second(int n) {
    if (n<= 0) {
        return -1;}
    int count = 0;
    int sim= 1;
    
    while (count<n) {
        sim++;
        if (First(sim)) count++;
    }
    return sim;
}

int main() {
    int n;
    std::cin >> n;
    std::cout<<Second(n)<<std::endl;
    return 0;
}