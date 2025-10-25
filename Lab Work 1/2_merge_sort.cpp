#include <iostream>
#include <chrono>
using namespace std;

// что-то вроде подготовки для слияния 
void merge_sort(int* arr,int left,int mid,int right) {
// размеры двух подмассивов для слияния
    int n1 = mid -left +1;
    int n2 = right -mid;
// создаем временные массивы для левой и правой частей
    int* L = new int[n1];
    int* R = new int[n2];//new нужно чтобы вычислить адрес блока, в котором можно разместить массив из n2 чисел
// просто копиуем
    for (int i =0; i< n1; i++)
        L[i] = arr[left +i];
    for (int j = 0;j < n2;j++)
        R[j] = arr[mid +1 +j];
// индексы для обхода временных массивов и основного массива
    int i = 0;//для левого подмассива
    int j = 0;//для правого подмассива
    int k = left;//для основного массива
//сравниваем элементы из L и R, выбираем меньший
    while (i <n1 and j <n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;//двигаемся в L
        } else {
            arr[k] = R[j];
            j++;//двигаемся в R
        }
        k++;}//иначе двигаемся в основном массиве}
//копируем оставшиеся элементы из L (если есть)
    while (i <n1) {
        arr[k] =L[i];
        i++;
        k++;}
//копируем оставшиеся элементы из R (если есть)
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;}
// освобождаем память временных массивов()
    delete[] L;
    delete[] R;}
//рекурсивная функция сортировки слиянием
void recurs_m(int* arr,int left,int right) {
//базовый случай: 1 элемент
    if (left < right) {
//находим середину для разделения
        int mid = left +(right - left) / 2;
//рекурсивно сортируем левую половину
        recurs_m(arr,left,mid);
//рекурсивно сортируем правую половину
        recurs_m(arr, mid +1,right);
//сливаем две отсортированные половины
        merge_sort(arr,left,mid,right);}
}
//основная функция для сортировки слиянием
void main_sort(int n,int* arr) {
    recurs_m(arr, 0, n - 1);
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
    main_sort(30, my_values1);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> res1 = end1 - start1;
    print_this(my_values1,30);
    cout<<"Ассимптотика: O(n log n)"<<endl;
    cout<<"Время выполнения:";
    cout<< res1.count()<<endl;
}