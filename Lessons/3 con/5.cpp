#include <iostream>
using namespace std;
int main() {
    int n;
    cin >>n;
    int arr[1000];

    for (int i = 0; i< n;i++) {
        cin >> arr[i];}

    int average = n /2;
    cout << arr[average];
    
    for (int i =1; i<= average; i++) {
        cout << " "<< arr[average- i];
        cout << " " << arr[average+ i];
    }
    return 0;
}