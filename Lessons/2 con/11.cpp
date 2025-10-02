#include <iostream>
using namespace std;
char leveling(char c){
    char big = c;
    if (big >= 'A' and big <= 'Z') {
        char small = big + 32;
        return small;
    }
    return c;
}

int main()
{
    char c;
    do
    {
        cin.get(c);
        cout << leveling(c);
    } while (c != '\n');
    return 0;
}
