#include <iostream>
using namespace std;
int* copyarr(int* a, unsigned int size) {
    int* copy = new int[size];
    
    for(unsigned int i = 0; i<size; i++) {
        copy[i] =a[i];}
    return copy;
}
int main()
{
    unsigned int n;
    int* a;
    cin >> n;
    a = new int[n];
    for(unsigned int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int* b = copyarr(a, n);
    for(unsigned int i = 0; i < n; i++) {
        cout << b[i] << " ";
    }
    cout << endl;
    delete[] a;
    delete[] b;
    return 0;
}