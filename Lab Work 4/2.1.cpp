#include <iostream>
#include <tuple>
#include <string>

template<int I, int N, typename Func, typename... Types>
struct TupleForEach {
    static void apply(std::tuple<Types...>& t, Func func) {
        func(std::get<I>(t));

        TupleForEach<I + 1, N, Func, Types...>::apply(t, func);}
};

template<int N, typename Func, typename... Types>
struct TupleForEach<N, N, Func, Types...> {
    static void apply(std::tuple<Types...>& t, Func func) {
    }
};

template<typename Func, typename... Types>
void for_each_in_tuple(std::tuple<Types...>& t, Func func) {
    TupleForEach<0, sizeof...(Types), Func, Types...>::apply(t, func);}

int main() {

    std::tuple<int, double, std::string> t1 = {20, 3.14, "привет"};

    std::cout << " Печать элементов кортежа\n";
    for_each_in_tuple(t1, [](const auto& elem) {

        std::cout << elem << "\n";});

    std::tuple<int, int, int> t2 = {1, 2, 3};

    std::cout << "\n До умножения \n";
    for_each_in_tuple(t2, [](const auto& elem) {
        std::cout << elem << " ";
    });

    for_each_in_tuple(t2, [](auto& elem) {
        elem *= 2;});

    std::cout << "\n После умножения на 2\n";
    for_each_in_tuple(t2, [](const auto& elem) {
        std::cout << elem << " ";
    });
    std::cout << "\n";

    std::tuple<int, double, std::string, char> t3 = {10, 2.71, "Димон", 'q'};

    std::cout << "\n Блок из 4 разных типов \n";
    for_each_in_tuple(t3, [](const auto& elem) {
        std::cout << "Элемент: " << elem << "\n";});
    return 0;
}