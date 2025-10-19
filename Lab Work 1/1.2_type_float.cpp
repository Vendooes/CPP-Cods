#include <iostream>
#include <cmath>
using namespace std;


//Так же, как и в первом задании делаем двоичное представление числа
union uni {
    float value;
    struct {
//чтобы не допускать арифметического сдвига, задаем тип unsigned int
        unsigned int mantissa : 23;
        unsigned int exponenta : 8;
        unsigned int sign : 1;
    } (p);
    unsigned int bits;
};
//1-----------------------------------------------------------

void flotbits(float val) {
    cout<<"1-------------------------------------------------------------"<<endl;

    uni u; //u - объединение union
    u.value =val;
    cout << "Двоичный вид: "<<endl;
    
// Выводим все 32 бита
    for (int i = 31; i >= 0; i--) {
        cout << ((u.bits >> i) & 1);
//Здесь можно сделать разделение для удобства между знаком и мантиссой
        if (i == 31 or i == 23) {cout << " ";}
    }
    cout << endl;
    
    cout << "Знак (1 бит): " << u.p.sign << endl;
    cout << "Экспонента (8 бит): ";
    for (int i = 7; i >= 0; i--) {
        cout << ((u.p.exponenta >> i) & 1);
    }
    cout << " (в десятичном виде: " ;
    cout<< u.p.exponenta << ")" << endl;//извлекаем из структуры union значение exp
    
    cout << "Мантисса (23 бита): ";
    for (int i = 22; i >= 0; i--) {
        cout << ((u.p.mantissa >> i) & 1);
    }
    cout << endl;

//покажем, как переводится двоичный код в значение действительного числа

//Проверка случая представления 0: здесь проверяем в зависимости от знака sign
if (u.p.exponenta== 0 and u.p.mantissa == 0) {
    cout << "Значение: ";
    if (u.p.sign == 1) {
        cout << "-0";
    } else {
        cout << "+0";
    }
    cout << endl;
}
    else {
//вычисляем реальную экспоненту, т к она изначально хранилась со смещением
        int Rexp = u.p.exponenta - 127;
//Учитываем,что мантисса хранит только дробную часть после запятой
        double mantis =1.0;
        for (int i = 0; i <23; i++) {
            if (u.p.mantissa & (1 << (22 -i))) {
                mantis += pow(2.0,-(i +1));//для сокращения кода воспользуемся функцией возвода в степень из бибилотеки cmath(** видимо здесь не работает)
            }
        }
//вычисление итогового значения числа типа float по формуле value = (-1)^знак * (1 + мантисса) * 2^(экспонента - 127)
        float solve;
if (u.p.sign == 1) {
    solve= -mantis*pow(2.0,Rexp);
} else {
    solve= mantis*pow(2.0,Rexp);
}
//здесь мы записываем финальный вывод в консоль
    cout << "Расчет: ";
    if (u.p.sign == 1) {
        cout << "-";
    }
    cout << mantis;
    cout << " * 2^" ;
    cout<< Rexp;
    cout << "=";
    cout<< solve;
    cout << endl;
    }
    cout << endl;
}

//2-----------------------------------------------------------
void dist() {
    cout<<"2-------------------------------------------------------------"<<endl;

// Поиск чисел с расстоянием 1 через анализ float( 2.0f - преобразуем число в float)
    float a = pow(2.0f, 23);
    float b = a + 1.0f;
    
    cout << "a = 2^23 =" ;
    cout<< a << endl;
    cout << "b = a + 1 = ";
    cout << b << endl;
    cout << "Разность: " ;
    cout<< b - a << endl;
    
// Поиск x_0 через анализ float
    float x0 = pow(2.0f, 24);
    
    cout << "x0 = 2^24 = " ;
    cout<< x0 << endl;
    cout << "Проверяем: " ;
    cout<< x0 << " == " ;
    cout<< x0 ;
    cout<< " + 1 ? " ;
    cout<< (x0 == x0 + 1.0f) << endl;
 
}

//3-------------------------------------------------------
void asso() {
    cout<<"3-------------------------------------------------------------"<<endl;
//Тут важны большие числа больше 6 знаков(на маленьких все работает)
    float a = 1000000000.0f;
    float b = -1000000000.0f;
    float c = 1.0f;
    float res1 = (a + b) +c;
    float res2 = a +(b + c);

    cout<<"При a=1000000000, b=-1000000000,c=1"<<endl;
    cout << "(a + b) + c = ";
    cout << res1 << endl;
    cout << "a + (b + c) = ";
    cout << res2 << endl;
    cout << "Ассоциативность нарушена" << endl;
}

//4-------------------------------------------------------
void ruyd() {
    cout<<"4-------------------------------------------------------------"<<endl;
    
    float sum = 0.0f;
    int k = 1;
    uni u_now;//Текущее знач
    uni u_previous;//Предыдущее знач
    
    while (true) {
        float term = 1.0f / k;//Делаем гармонический ряд
//Делаем проверку суммы чтобы вовремя остановиться
        u_previous.value = sum;
        sum +=term;
        u_now.value = sum;
        
// Проверяем, изменилась ли сумма
        if (u_now.bits == u_previous.bits) {
            cout << "С k = ";
            cout << k ;
            cout<< " сумма не увеличивается" << endl;
            cout << "Остановился на значении 1/" ;
            cout<< k << " = " ;
            cout<< term << endl;
            cout << "Текущая сумма: " ;
            cout<< sum << endl;
            cout << "Следующая сумма: " ;
            cout<< sum +term << endl;
            break;
        }
        k++;
//Если будет бесконечный цикл
        if (k > 10000000) { 
            cout << "Break на k = " ;
            cout<< k << endl;
            break;
        }
    }
    cout << endl;
}
//5-------------------------------------------------------
void harm() {
    cout<<"5-------------------------------------------------------------"<<endl;
//Используем знания из предыдущего пункта и настроим k
    int start = 0;
    int k = 1000000;
    int end = k +100;

// Суммируем от маленьких до больших чисел
    float summa_f = 0.0f;
    for (int i = start; i <= end; ++i) {
        summa_f += 1.0f / i;
    }

// А здесь уже наоборот от больших до маленьких
    float summa_b = 0.0f;
    for (int i = end; i >= start; --i) {
        summa_b += 1.0f / i;
    }

    cout << "Прямое суммирование ";
    cout << summa_f << endl;
    cout << "Обратное суммирование ";
    cout << summa_b << endl;
    cout << "Разница: " ;
    cout<< summa_b - summa_f << endl;
    
// Это происходит из-за разного битового представления
    uni u_ahead;
    uni u_rev;
    u_ahead.value = summa_f;
    u_rev.value = summa_b;
    
    cout << "Представление в битах прямой суммы: ";
// Здесь используем тот же прием, что и в первом задании с int
    for (int i = 31; i >=0; i--) {
        cout <<((u_ahead.bits >> i) & 1);}
    cout << endl;
    
    cout << "Представление в битах обратной суммы: ";
    for (int i = 31; i >= 0; i--) {
        cout << ((u_rev.bits >> i) & 1);}
    cout << endl;
}

//6-------------------------------------------------------
void safe() {
    cout<<"6-------------------------------------------------------------"<<endl;
    
    uni u_a;
    uni u_b;
    u_a.value = 1;
    u_b.value = 0.1;
    cout << "Представление a:";
    for (int i =31; i>= 0;i--){
        cout<<((u_a.bits>> i) & 1);}
    cout << endl;
    
    cout << "Представление b: ";
    for (int i = 31; i >=0; i--){
        cout <<((u_b.bits >> i) & 1);}
    cout << endl;

// Сравнение без арифметических операций
    cout << "Сравнение без арифметических операций:" << endl;
    float x = 1.5f, y = 1.5f;
    cout << "x = ";
    cout << x ;
    cout<< ", y = " ;
    cout<< y << endl;
    cout << "x == y:" << (x==y) << endl;
    cout << "Безопасно без операций" << endl;
}
int main() {
// 1. Двоичное представление
    flotbits(5.0f);
// 2. Числа с расстоянием 1
    dist();
// 3. Отсутствие ассоциативности
    asso();
// 4. Сходимость гармонического ряда
    ruyd();
// 5. Суммирование гармонического ряда
    harm();
// 6. Сравнение float
    safe();
    return 0;
}
