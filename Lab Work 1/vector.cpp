#include <iostream>
using namespace std;

struct subvector {
    int *mas;//указатель на динамический массив элементов
    unsigned int top;//текущее количество элементов
    unsigned int capacity;//общая емкость вектора
};
//предварительное объявление функции
bool ano_s(subvector *qv,unsigned int new_capacity);
//инициализирует пустой subvector
bool init(subvector *qv) {
    qv->mas =0;
    qv->top =0;
    qv->capacity=0;
    return true;
}
bool ret_back(subvector *qv, int d) {
//если вектор заполнен, увеличиваем емкость
    if (qv->top == qv->capacity) {
        unsigned int new_capacity = (qv->capacity == 0) ? 1 : qv->capacity * 2;
        if (!ano_s(qv, new_capacity)) {
            return false;}
    }
//добавляем элемент и увеличиваем счетчик
    qv->mas[qv->top] = d;
    qv->top++;
    return true;}
//удаляем последний елемент 
int pop_back(subvector *qv) {
    if (qv->top == 0) {
        return 0; //вектор пуст
    }
    qv->top--;//уменьшаем количество элементов
    return qv->mas[qv->top];//возвращаем удаленный элемент
}
//изменяем размер вектора
bool ano_s(subvector *qv, unsigned int new_capacity) {
//обработка нулевой емкости
    if (new_capacity == 0) {
        delete[] qv->mas;
        qv->mas = nullptr;
        qv->top = 0;
        qv->capacity = 0;
        return true;
    }
//если новая емкость меньше текущего размера, обрезаем вектор
    if (new_capacity < qv->top) {
        qv->top = new_capacity;}
//пытаемся выделить новый массив (new(nothrow) возвращает nullptr при ошибке)
    int *new_mas = new(std::nothrow) int[new_capacity];
    if (new_mas == nullptr) {
        return false;} // Не удалось выделить память
//копируем существующие элементы
    for (unsigned int i = 0; i < qv->top; i++) {
        new_mas[i] = qv->mas[i];}
//освобождаем старую память и обновляем структуру
    delete[] qv->mas;
    qv->mas = new_mas;
    qv->capacity =new_capacity;
    
    return true;
}
//уменьшаем емкость до нужного размера
void shrink_to_fit(subvector *qv) {
//если вектор пуст, полностью освобождаем память
    if (qv->top == 0) {
        delete[] qv->mas;
        qv->mas = nullptr;
        qv->capacity =0;
        return;}
//если есть неиспользуемая емкость, уменьшаем ее
    if (qv->top <qv->capacity) {
//пытаемся выделить массив точного размера
        int *new_mas =new(std::nothrow) int[qv->top];
        if (new_mas!=nullptr) {
//копируем элементы
            for (unsigned int i =0; i < qv->top; i++) {
                new_mas[i]=qv->mas[i];}
//освобождаем старую память и обновляем структуру
            delete[] qv->mas;
            qv->mas = new_mas;
            qv->capacity = qv->top;}
//если не удалось выделить память, оставляем все как есть
    }
}
//очищает содержимое без освобожения памяти
void clear(subvector *qv) {
    qv->top = 0;
}
//уничтожает и очищает вектор и память
void destructor(subvector *qv) {
    delete[] qv->mas;//освобождаем память
    init(qv);//инициализируем как пустой
}
void print_vector(const subvector *qv) {
    cout << "Элементы: [";
    for (unsigned int i = 0; i < qv->top; i++) {
        cout << qv->mas[i];
        if (i < qv->top - 1) {
            cout << ", ";
        }
    }
    cout << "],размер:"<< qv->top << ",емкость:"<< qv->capacity<< endl;}
int main() {
    subvector sv;
    cout << "Вектор" <<endl;
//инициализация
    cout << "1. Инициализация пустого вектора:" << endl;
    init(&sv);
    print_vector(&sv);
//добавление элементов
    cout << "\n2. Добавление элементов" << endl;
    ret_back(&sv, 10);
    ret_back(&sv, 20);
    print_vector(&sv);
//удаление элемента
    cout << "\n3. Удаление последнего элемента: " << pop_back(&sv) << endl;
    print_vector(&sv);
//добавление еще элементов для демонстрации увеличения емкости
    cout << "\n4. Добавление элементов" << endl;
    ret_back(&sv, 80);
    ret_back(&sv, 90);
    print_vector(&sv);
//изменение размера
    cout << "\n5. Уменьшение емкости до 3:" <<endl;
    ano_s(&sv,3);
    print_vector(&sv);
//очистка содержимого и уничтожение
    cout << "\n7. Очистка содержимого:"<< endl;
    clear(&sv);
    print_vector(&sv);
    cout << "\n8. Уничтожение вектора:"<< endl;
    destructor(&sv);
    print_vector(&sv);
    return 0;}