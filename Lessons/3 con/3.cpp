#include <iostream>
#include <algorithm>
using namespace std;
int main(){
    int n;
    std::cin >> n;
    
    int arr[1000];

    for (int i = 0; i< n;i++) {
    cin >> arr[i];}

    int m;
    cin >> m;
    sort(arr, arr + n);

    for (int i= n -m; i< n; ++i) {
    std::cout <<arr[i];

    std::cout << " ";
}
return 0;
}
