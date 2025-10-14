#include <iostream>
using namespace std;

int main() {
    int n;
    cin >>n;
    
    int average[1000];
    int av2[1000];
    int count_average =0;
    int value = 0;
    
    for (int i= 0;i<n; i++) {
        int count;
        cin >>count;
        if (count >=0) {
            average[count_average] =count;
            count_average++;
        } else {
            av2[value] =count;
            value++;}
    }

    for (int i =0; i < count_average -1; i++) {
        for (int j =0; j <count_average -i -1; j++) {
            if (average[j] >average[j +1]) {
                int period =average[j];
                average[j] =average[j +1];
                average[j +1] =period;}
        }
    }
    for (int i = 0; i <value -1; i++) {
        for (int j = 0;j< value -i -1;j++) {
            int ostatok1 = (av2[j]<0)?-av2[j]: av2[j];
            int ostatok2 = (av2[j+1]<0)?-av2[j+ 1]:av2[j+1];
            if (ostatok1 >ostatok2) {
                int period =av2[j];
                av2[j] =av2[j+ 1];
                av2[j +1]= period;}
        }
    }
    for (int i = 0;i <count_average; i++) {
        cout << average[i] <<" ";}
    for (int i = 0;i <value; i++) {
        cout <<av2[i]<< " ";}
    return 0;
}