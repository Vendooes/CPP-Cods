#include <iostream>
#include <chrono>
using namespace std;
// вспомогательная функция
void heapify(int* arr,int n,int i) {
// индекс текущего максимального элемента (изначально корень)
    int now_el =i;
// индекс левого потомка (формула 2*i + 1)
    int left =2 *i + 1;
// индекс правого потомка (формула 2*i + 2)
    int right = 2 *i+ 2;
// если левый потомок существует и больше текущего максимума
    if (left < n and arr[left] > arr[now_el])
        now_el = left;  // обновляем индекс максимума
// то же самое иначе
    if (right <n and arr[right] >arr[now_el])
        now_el = right;  

// Если максимум не в корне
    if (now_el != i) {
// Меняем местами корень и наибольший потомок
        std::swap(arr[i],arr[now_el]);
// Рекурсивно применяем к поддереву, которое могло нарушиться
        heapify(arr, n,now_el);}
}

// сама сортировка
void heap_sort(int n, int* arr) {
// начинаем с последнего нелистового узла (n/2 - 1) и идем к корню
    for (int i = n / 2-1; i>= 0; i--)
        heapify(arr,n,i);

// извлекаем элементы
    for (int i = n - 1; i > 0; i--) {
// Перемещаем текущий максимум (корень) в конец массива
        std::swap(arr[0], arr[i]);
        
// Восстанавливаем свойство кучи для уменьшенной кучи (без последнего элемента)
        heapify(arr, i, 0);}
}

    void print_this(int* arr,int n ) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}
int main(){
// Задаем рандомный массив
    int my_values1[30]{199,30,40,23,54,56,73,11,681,32,58,33,787,453,605,321,87,123,345,567,789,98,764,239,23,57,89,423,760,90};

//Выведем массив до сортировки
    cout<<"Массив до сортировки:"<<endl;
    print_this(my_values1,30);

// Выведем после сорировки
    cout<<"Массив после сортировки:"<<endl;
//Измерим время с помощью библиотеки chrono (информация с habr.com)
    auto start1 = std::chrono::high_resolution_clock::now();
    heap_sort(30, my_values1);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res1 = end1 - start1;
    print_this(my_values1,30);
    cout<<"Ассимптотика: O(n log n)"<<endl;
    cout<<"Время выполнения:";
    cout<< res1.count()<<endl;
}