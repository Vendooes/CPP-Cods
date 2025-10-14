#include <iostream>
#include <algorithm>
#include <climits>
using namespace std;

int main() {
    int n;
    cin >> n;
    const int achiev =1000;
    int list_ach[achiev];
    float low_ach[achiev];

    float m_act[achiev];
    int counts[achiev];
    int unussiul = 0;

    for (int i = 0; i<n; i++) {
        int t_k, id;
        float mmm,second,nnn,arb,aaa;
        cin>> t_k;
        cin >> id;
        cin >> mmm; 
        cin>> second;
        cin >> nnn;
        cin>> arb;
        cin >> aaa;

        int index = -1;
        for (int j =0;j <unussiul; j++) {
            if (list_ach[j] ==id) {
                index =j;
                break;}
        }

        if (index ==-1) {
            list_ach[unussiul] =id;
            low_ach[unussiul] =arb;
            m_act[unussiul] =arb;
            counts[unussiul] =1;
            unussiul++;
        } else {
            low_ach[index] =min(low_ach[index],arb);
            m_act[index] =max(m_act[index],arb);
            counts[index]++;}
    }

    int c_i =-1;
    float mini =INT_MAX;
    float maxi =-1;
    for (int i =0; i <unussiul; i++) {
        if (counts[i] < 2) {continue;}

        float df =m_act[i] -low_ach[i];
        if (df < mini ||(df ==mini && m_act[i]>maxi)) {
            mini = df;
            c_i =list_ach[i];
            maxi =m_act[i];}
    }
    cout << c_i;
    return 0;
}