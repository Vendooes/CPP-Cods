#include <iostream>
#include <deque>
#include <vector>
#include <string>
#include <stdexcept>

template<typename T, typename Container = std::deque<T>>
class Stack {
private:
    Container data;

public:
    void push(const T& value) {
        data.push_back(value);}

    void pop() {
        if (empty()) {
            throw std::out_of_range("pop() вызван на пустом стеке!");
        }
        data.pop_back();}

    T& top() {
        if (empty()) {
            throw std::out_of_range("top() вызван на пустом стеке!");
        }
        return data.back();}

    const T& top() const {
        if (empty()) {
            throw std::out_of_range("top() вызван на пустом стеке!");
        }
        return data.back();}

    std::size_t size() const {
        return data.size();}

    bool empty() const {
        return data.empty();}
};

template<>
class Stack<char, std::string> {
private:
    std::string data;

public:
    void push(char value) {
        data.push_back(value);
    }

    void pop() {
        if (empty()) {
            throw std::out_of_range("pop() вызван на пустом стеке!");
        }
        data.pop_back();}

    char& top() {
        if (empty()) {
            throw std::out_of_range("top() вызван на пустом стеке!");
        }
        return data.back();}

    const char& top() const {
        if (empty()) {
            throw std::out_of_range("top() вызван на пустом стеке!");
        }
        return data.back();}

    std::size_t size() const {
        return data.size();}

    bool empty() const {
        return data.empty();}

    const std::string& str() const {
        return data;}
};

int main() {

    Stack<int> stack_deque;

    stack_deque.push(10);
    stack_deque.push(20);
    stack_deque.push(30);

    std::cout << "Стек на deque (int)\n";
    std::cout << "Размер: " << stack_deque.size() << "\n";
    std::cout << "Верхний элемент: " << stack_deque.top() << "\n";

    stack_deque.pop();
    std::cout << "После pop(), верхний: " << stack_deque.top() << "\n";
    std::cout << "Пуст? " << (stack_deque.empty() ? "да" : "нет") << "\n";

    Stack<double, std::vector<double>> stack_vec;

    stack_vec.push(1.1);
    stack_vec.push(2.2);
    stack_vec.push(3.3);

    std::cout << "\n Стек на vector (double)\n";
    std::cout << "Верхний: " << stack_vec.top() << "\n";
    stack_vec.pop();
    std::cout << "После pop(), верхний: " << stack_vec.top() << "\n";

    Stack<char, std::string> stack_str;

    stack_str.push('H');
    stack_str.push('e');
    stack_str.push('l');
    stack_str.push('l');
    stack_str.push('o');

    std::cout << "\n Стек на string (char)\n";
    std::cout << "Содержимое: " << stack_str.str() << "\n";
    std::cout << "Верхний символ: " << stack_str.top() << "\n";
    std::cout << "Размер: " << stack_str.size() << "\n";

    std::cout << "Обратно: ";
    while (!stack_str.empty()) {
        std::cout << stack_str.top();
        stack_str.pop();}
    std::cout << "\n";

    Stack<int> empty_stack;
    std::cout << "\n Проверка исключений \n";
    try {
        empty_stack.pop();
    } catch (const std::out_of_range& e) {
        std::cout << "Исключение: " << e.what() << "\n";}

    return 0;
}