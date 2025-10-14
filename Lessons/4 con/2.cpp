#include <iostream>
using std::cout;
using std::cin;
using std::endl;

int main()
{
    unsigned int u, u2;
    cin >> u >> u2;

    unsigned int *p = &u, *p2 = &u2;
    
    cout <<*p + *p2 <<endl;
    
    return 0;
}