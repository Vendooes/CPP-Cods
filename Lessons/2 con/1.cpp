#include <iostream>
using namespace std;
int minus_of_int(int x){
    return -x;
}
int main()
{
    int x;
    cin >> x;
    cout << minus_of_int(x) << std::endl;
    return 0;
}