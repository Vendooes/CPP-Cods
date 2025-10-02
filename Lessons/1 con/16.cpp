#include <iostream>
#include <cmath>
int main() {
    int N,number;
    number =0;
    std::cin>>N;
    float r,h,p,max;
    max=0;
    for (int i=0; i<N; i++){
    r=0;
    h=0;
    p=0;
    std:: cin>>r>>h>>p;
    float M;
    M=0;
    M = 3.14*std::pow(r,2)*h*p;
    if (M>max){
        max=M;
        number = i;
    }
    }
std::cout<< number<<std::endl;
return 0;
}