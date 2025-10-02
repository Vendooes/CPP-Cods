#include <iostream>
using namespace std;

unsigned long long int get_a_hexadecimal(){
        unsigned long long int fin = 0;
    char c;
    while (cin.get(c)) {
        if (c == ' '|| c == '\n') {
            break;}
        if (c >='0'&& c <='9') 
        {
            fin = fin *16 + (c -'0');} 
        else if (c >='A' && c <= 'F') 
        {
            fin = fin *16 +(c -'A' +10);} 
        else if (c >='a' && c <= 'f') 
        {
            fin = fin* 16 +(c -'a'+ 10);}
    }
    return fin;
}
int main()
{
    cout << get_a_hexadecimal() << endl;
    return 0;
}