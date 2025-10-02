#include <iostream>
using namespace std;

bool is_a_number(char c){
    if (c == '0' or c =='1'
    or c =='2' or c=='3' or c=='4'
or c=='5' or c=='6' or c=='7'
 or c=='8' or c=='9'){
    return true;
 }else{
    return false;
 }
}

int main()
{
    char c;
    unsigned int sum = 0;
    do
    {
        cin >> c;
        if (is_a_number(c))
            sum += c - '0';
    } while (c != '$');
    cout << sum << endl;
    return 0;
}