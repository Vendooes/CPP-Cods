#include <iostream>
using namespace std;
int main() {
    int n,m;
    cin >> n>>m;
    
    int matr[10][10];
    for (int i = 0; i < n; i++) {
        for (int j =0; j< m; j++) {
            cin >> matr[i][j];}
    }
    int transp[10][10];
    for (int i = 0; i< n; i++) {
        for (int j = 0; j< m; j++) {
            transp[j][i] =matr[i][j];}
    }
    for (int i =0; i <m; i++) {
        for (int j =0; j<n; j++) {
            cout <<transp[i][j];
            if (j <n-1) {
                cout << " ";
            }
        }
        cout <<endl;
    }
    
    return 0;
}