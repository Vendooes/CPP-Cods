#include <iostream>
#include <array>
#include <tuple>

template<int I, int N, typename Tuple>
struct PrintTuple {
    static void print(const Tuple& t) {
        std::cout << std::get<I>(t);
        if (I + 1 < N) std::cout << ", ";
        PrintTuple<I + 1, N, Tuple>::print(t);
    }
};

template<int N, typename Tuple>
struct PrintTuple<N, N, Tuple> {
    static void print(const Tuple&) {}
};

template<typename... Args>
void print_tuple(const std::tuple<Args...>& t) {
    std::cout << "(";
    PrintTuple<0, sizeof...(Args), std::tuple<Args...>>::print(t);
    std::cout << ")";}

template<typename T0, std::size_t N0,
         typename T1, std::size_t N1,
         std::size_t... Flat>
constexpr auto product2_impl(
    const std::array<T0, N0>& a0,
    const std::array<T1, N1>& a1,
    std::index_sequence<Flat...>)
{

    return std::array{ std::make_tuple(a0[Flat / N1], a1[Flat % N1])... };}

template<typename T0, std::size_t N0,
         typename T1, std::size_t N1>
constexpr auto cartesian_product2(
    const std::array<T0, N0>& a0,
    const std::array<T1, N1>& a1)
{
    return product2_impl(a0, a1, std::make_index_sequence<N0 * N1>{});}

template<typename T0, std::size_t N0,
         typename T1, std::size_t N1,
         typename T2, std::size_t N2,
         std::size_t... Flat>
constexpr auto product3_impl(
    const std::array<T0, N0>& a0,
    const std::array<T1, N1>& a1,
    const std::array<T2, N2>& a2,
    std::index_sequence<Flat...>)
{
    return std::array{
        std::make_tuple(
            a0[Flat / (N1 * N2)],
            a1[(Flat / N2) % N1],
            a2[Flat % N2]
        )...
    };
}

template<typename T0, std::size_t N0,
         typename T1, std::size_t N1,
         typename T2, std::size_t N2>
constexpr auto cartesian_product3(
    const std::array<T0, N0>& a0,
    const std::array<T1, N1>& a1,
    const std::array<T2, N2>& a2)
{
    return product3_impl(a0, a1, a2,
        std::make_index_sequence<N0 * N1 * N2>{});}

template<std::size_t I0, std::size_t I1,
         typename T0, std::size_t N0,
         typename T1, std::size_t N1>
constexpr auto get_element(
    const std::array<T0, N0>& a0,
    const std::array<T1, N1>& a1)
{
    static_assert(I0 < N0, "I0 выходит за границы первого массива");
    static_assert(I1 < N1, "I1 выходит за границы второго массива");
    return std::make_tuple(a0[I0], a1[I1]);
}

template<std::size_t I0, std::size_t I1, std::size_t I2,
         typename T0, std::size_t N0,
         typename T1, std::size_t N1,
         typename T2, std::size_t N2>
constexpr auto get_element(
    const std::array<T0, N0>& a0,
    const std::array<T1, N1>& a1,
    const std::array<T2, N2>& a2)
{
    static_assert(I0 < N0, "I0 выходит за границы первого массива");
    static_assert(I1 < N1, "I1 выходит за границы второго массива");
    static_assert(I2 < N2, "I2 выходит за границы третьего массива");
    return std::make_tuple(a0[I0], a1[I1], a2[I2]);}

int main() {

    constexpr std::array<int, 2>    arr1 = {1, 2};
    constexpr std::array<double, 3> arr2 = {10.0,20.0, 30.0};
    constexpr std::array<char, 2>   arr3 = {'a', 'b'};

    std::cout << " arr1 x arr2  \n";
    constexpr auto prod2 = cartesian_product2(arr1,arr2);
    for (const auto& e :prod2) {
        print_tuple(e);
        std::cout << "\n";}

    std::cout << "\n arr1 x arr2 x arr3 \n";
    constexpr auto prod3 = cartesian_product3(arr1, arr2, arr3);
    for (const auto& e : prod3) {
        print_tuple(e);
        std::cout << "\n";}

    std::cout << "\n Один эл по индексам \n";

    constexpr auto e1 = get_element<1, 2, 0>(arr1, arr2, arr3);
    std::cout << "get_element<1,2,0>: ";
    print_tuple(e1);
    std::cout << "\n";

    constexpr auto e2 = get_element<0, 1>(arr1, arr2);
    std::cout << "get_element<0,1>:   ";
    print_tuple(e2);
    std::cout << "\n";

    static_assert(std::get<0>(prod2) == std::make_tuple(1, 10.0),
                  "Первая пара должна быть (1, 10.0)");
    std::cout << "\nstatic_assert прошёл — вычислено при компиляции\n";

    return 0;
}