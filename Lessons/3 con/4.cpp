#include <iostream>
using namespace std;
int main() {
    int n;
    cin >> n;

    int arr[1000];
    
    for (int i = 0; i< n;i++) {
        cin >> arr[i];}
    int m;
    cin >> m;
    
    int second[1000];
    for (int i =0; i <n; i++) {
        second[i] = arr[i];
    }
    
    for (int i= 0;i <n -1; i++) {
        for (int j =0; j <n -i -1; j++) {
            if (second[j] <second[j +1]) {
                int t =second[j];
                second[j] =second[j +1];
                second[j +1] = t;}
        }
    }
    
    int lim = second[m - 1];
    int count_lim = 0;
    for (int i =0; i <m; i++) {
        if (second[i] ==lim) {
            count_lim++;
        }
    }
    
    int res = 0;
    for (int i = 0; i < n && res < m; i++) {
        if (arr[i] > lim) {
            cout<< arr[i] << " ";
            res++;}
        else if (arr[i] ==lim && count_lim> 0) {
            cout << arr[i]<< " ";
            res++;
            count_lim--;}
    }
    return 0;
}