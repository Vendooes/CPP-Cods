#include <iostream>

int main() {

int count;
std::cin >> count;

if (count==1){
    std::cout << 1;}

if (count == 0){
    std::cout << 0;
    }

int b[32] = {};
int ind = 0;
while (count>=2){
    
    b[ind++] = count % 2;
    count = count/2;
    if (count==1){
        b[ind++] = 1;

    }
    if (count == 0){
        b[ind++] = 0;
    }

}
    for (int i = ind - 1; i >= 0; --i) {
        std::cout << b[i];
    }

return 0;
}