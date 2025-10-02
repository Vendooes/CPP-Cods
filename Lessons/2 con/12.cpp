#include <iostream>
using namespace std;
char unleveling(char c);

char get_a_letter() {
    char c;
    while (true) {
    cin.get(c);
        if ((c >='a'&& c <='z')|| 
(c >='A' &&c<='Z')) {
        return c;
        }}
}
    


char unleveling(char c)
{
    if (c >= 'a' && c <= 'z')
        c += 'A' - 'a';
    return c;
}
// ваша реализация функции
int main()
{
    for (int i = 0; i < 10; i++)
        cout << unleveling(get_a_letter());
    cout << endl;
    return 0;
}