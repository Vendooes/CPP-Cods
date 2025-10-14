#include <iostream>
using namespace std;

int main() {
    int n, m;
    cin >>n >> m;
    int summa[100] = {0};

    for (int i =0; i< n;i++) {
        for (int j =0; j< m; j++) {
            int num;
            cin >>num;
            summa[j]+= num;}
    }
    int max_sum = summa[0];
    int number =0;
    for (int j =1; j <m; j++) {
        if (summa[j] >max_sum) {
            max_sum =summa[j];
           number =j;}
    }
    cout <<number<< endl;
    return 0;
}