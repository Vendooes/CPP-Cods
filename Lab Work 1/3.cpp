#include <iostream>
#include <bitset>
#include <cstdint>
#include <cmath>

void printFloatBinary(float f) {
    uint32_t bits = *reinterpret_cast<uint32_t*>(&f);
    std::bitset<32> b(bits);
    
    std::cout << "Число: " << f << std::endl;
    std::cout << "Битовое представление: " << b << std::endl;
    std::cout << "Знак (1 бит): " << b[31] << std::endl;
    std::cout << "Экспонента (8 бит): ";
    for (int i = 30; i >= 23; --i) std::cout << b[i];
    std::cout << std::endl;
    std::cout << "Мантисса (23 бита): ";
    for (int i = 22; i >= 0; --i) std::cout << b[i];
    std::cout << std::endl;
}

int main() {
    float f = 5.0f;
    printFloatBinary(f);
}