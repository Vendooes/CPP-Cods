#include <iostream>
using namespace std;

int main(){
    int n;
    cin>>n;
    int arr[1000];
    
    for (int i = 0; i< n;i++) {
        cin >> arr[i];}
    int summ = 0;
    for (int i = 0; i<n; i++){
        summ+=arr[i];
    }

    for(int i = 0; i<n; i++){
        if (arr[i]*n>summ){
            cout<< arr[i];
            cout<< ' ';
        }
    }

    return 0;
}