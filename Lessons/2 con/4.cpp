#include <iostream>
using namespace std;
unsigned int sum_of_numbers(unsigned int n){
    unsigned int sum =0;
    while(n>0){
    sum+=n%10;
    n/=10;
    }
    return sum;
}
int main()
{
    unsigned int n;
    cin >> n;
    cout << sum_of_numbers(n) << endl;
    return 0;
}