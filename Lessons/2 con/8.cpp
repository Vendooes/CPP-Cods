#include <iostream>
using namespace std;

unsigned int sum_of_numbers(unsigned long long int n);
unsigned long long int nonacci(unsigned int n){
    
    if (n ==1) return 0;
    if (n ==2) return 1;
    unsigned long long int first = 0;
    unsigned long long int second = 1;
    unsigned long long int third;
    for (unsigned int i =3; i<= n; ++i) {
        third =first +second;
        first =second;
        second =third;
    }
    return second;
}



unsigned int sum_of_numbers(unsigned long long int n)
{
    unsigned int res = 0;
    while (n)
    {
        res += n % 10;
        n /= 10;
    }
    return res;
}
// ваша реализация функции

int main()
{
    unsigned int n;
    cin >> n;
    cout << sum_of_numbers(nonacci(n)) << endl;
    return 0;
}