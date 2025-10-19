#include <iostream>
#include <climits> //библиотека для нахождения максимального значения unsigned int
using namespace std;

//т.к нам не нужно передавать значения побитовой операции в код, то используем 'void'
void bits(int val) {
// union -это структура данных, где все члены используют одну и ту же область памяти (размер union равен размеру самого большого члена)
    union {
        int value;
//выделяем область 1 байт и позволяет нам получить доступ к байтам значения
        unsigned char bytt[sizeof(int)];
    } (u);
//записываем значение в value (4 байта)
    u.value = val;

    for (int i = sizeof(int) - 1;i >= 0; --i) {
        for (int j = 7;j >= 0;--j) {
//используем little-endian, те сначала записываются младшие байты, а затем старшие
// "&" побитовое "и", те он извлекает только правый бит
            cout <<((u.bytt[i] >>j)& 1);
        }
        cout << ' ';
    }
    cout << endl;
}

//то же самое делаем для unsigned int
void unbits(unsigned int val) {
    union {
        unsigned int value;
        unsigned char bytt[sizeof(int)];
    } (u);

    u.value = val;

    for (int i = sizeof(int) - 1;i >= 0; --i) {
        for (int j = 7;j >= 0;--j) {
            cout <<((u.bytt[i] >>j)& 1);
        }
        cout << ' ';
    }
    cout << endl;
}


int main(){
    cout<<"1 ----------------------------"<<endl;
    cout<<"Побитовое представление положительных и отрицательных чисел типа int в памяти для числа 96:"<< endl;
    int i = 96;
    bits(i);
    bits(-i);
    cout<<"2 ----------------------------"<<endl;
    cout<<"Побитовое представление для числа unsigned int"<<endl;
    unsigned int u = 96;
    unbits(u);
//проверим сдвиг unsigned int на половину диапазона 
    unsigned int half = UINT_MAX / 2 + 1;
    cout<< "Проверка сдвига на половину диапазона"<<endl;
    unbits(half);
    cout<<"3 ----------------------------"<<endl;
// эксперимент с прибалением 1 к INT_MAX
    int max_int = INT_MAX;
    cout << "прибалением 1 к INT_MAX"<<endl;
    cout << "До"<<endl;
    bits(max_int);

    max_int += 1;
    cout << "После"<<endl;
    bits(max_int);
    cout << "Значение: " << max_int << " (это INT_MIN) !" << endl;
    
// эксперимент с вычитанием 1 из 0 типа unsigned int
    unsigned int zero = 0;
    cout << "До"<<endl;
    unbits(zero);
    
    zero -= 1;
    cout << "После "<<endl;
    unbits(zero);
    cout << "Значение:" << zero << " (это UINT_MAX) !!!" << endl;

    return 0;
}

