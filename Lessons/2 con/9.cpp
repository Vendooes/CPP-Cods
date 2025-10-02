#include <iostream>
using std::cout;
using std::endl;
using std::cin;
unsigned int result_ternary(unsigned int a){
    unsigned int result =0;
    while (a> 0) {
        result +=a %3;
        a/=3;
    }
    return result;
}
int main()
{
    unsigned int n, s = 0, tmp;
    cin >> n;
    for (unsigned int i = 0; i < n; i++)
    {
        cin >> tmp;
        s += result_ternary(tmp);
    }
    cout << result_ternary(s) << endl;
    return 0;
}