#include <iostream>
int main() {
    int n;
    std::cin >> n;
    int value =0;
    int maximum;
    
    for (int i =0; i<n; i++) {
        int val;
        std::cin >>val;
        if (i == 0) {
            maximum =val;
            value =1;
        }

        else {
            if (val >maximum) {
                maximum =val;
                value= 1;
            } 
        else if (val ==maximum) {
                value++;
            }
        }
    }
    std::cout<<value <<std::endl;
    return 0;
}