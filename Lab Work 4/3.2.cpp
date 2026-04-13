#include <iostream>

template<long long... Values>
struct IntList {};

template<int I, typename List>
struct Get;

template<long long First, long long... Rest>
struct Get<0, IntList<First, Rest...>> {
    static constexpr long long value = First;};

template<int I, long long First, long long... Rest>
struct Get<I, IntList<First, Rest...>> {
    static constexpr long long value = Get<I - 1, IntList<Rest...>>::value;};

template<typename List>
struct Size;

template<long long... Vals>
struct Size<IntList<Vals...>> {
    static constexpr int value = sizeof...(Vals);
};

template<int N, typename Coeffs, typename Inits>
struct Rec;

template<int N, int I, int Order, typename Coeffs, typename Inits>
struct SumHelper {
    static constexpr long long value =
        Get<I, Coeffs>::value * Rec<N - Order + I, Coeffs, Inits>::value
        + SumHelper<N, I - 1, Order, Coeffs, Inits>::value;
};

template<int N, int Order, typename Coeffs, typename Inits>
struct SumHelper<N, 0, Order, Coeffs, Inits> {
    static constexpr long long value =
        Get<0, Coeffs>::value * Rec<N - Order, Coeffs, Inits>::value;
};

template<int N, typename Coeffs, typename Inits,
         bool IsBase = (N < Size<Coeffs>::value)>
struct RecImpl;

template<int N, typename Coeffs, typename Inits>
struct RecImpl<N, Coeffs, Inits, true> {
    static constexpr long long value = Get<N, Inits>::value;
};

template<int N, typename Coeffs, typename Inits>
struct RecImpl<N, Coeffs, Inits, false> {
    static constexpr int Order = Size<Coeffs>::value;
    static constexpr long long value =
        SumHelper<N, Order - 1, Order, Coeffs, Inits>::value;
};

template<int N, typename Coeffs, typename Inits>
struct Rec {
    static constexpr long long value = RecImpl<N, Coeffs, Inits>::value;
};

int main() {

    using FibCoeffs = IntList<1LL, 1LL>;
    using FibInits  = IntList<0LL, 1LL>;

    std::cout << "Числа Фибоначчи \n";
    std::cout << "F(0)  = " << Rec<0,  FibCoeffs, FibInits>::value << "\n";  // 0
    std::cout << "F(1)  = " << Rec<1,  FibCoeffs, FibInits>::value << "\n";  // 1
    std::cout << "F(2)  = " << Rec<2,  FibCoeffs, FibInits>::value << "\n";  // 1
    std::cout << "F(5)  = " << Rec<5,  FibCoeffs, FibInits>::value << "\n";  // 5
    std::cout << "F(10) = " << Rec<10, FibCoeffs, FibInits>::value << "\n";  // 55
    std::cout << "F(15) = " << Rec<15, FibCoeffs, FibInits>::value << "\n";  // 610

    using TribCoeffs = IntList<1LL, 1LL, 1LL>;
    using TribInits  = IntList<0LL, 0LL, 1LL>;

    std::cout << "\n Числа Трибоначчи \n";
    std::cout << "T(0) = " << Rec<0, TribCoeffs, TribInits>::value << "\n";  // 0
    std::cout << "T(1) = " << Rec<1, TribCoeffs, TribInits>::value << "\n";  // 0
    std::cout << "T(2) = " << Rec<2, TribCoeffs, TribInits>::value << "\n";  // 1
    std::cout << "T(3) = " << Rec<3, TribCoeffs, TribInits>::value << "\n";  // 1
    std::cout << "T(4) = " << Rec<4, TribCoeffs, TribInits>::value << "\n";  // 2
    std::cout << "T(7) = " << Rec<7, TribCoeffs, TribInits>::value << "\n";  // 13

    using CustomCoeffs = IntList<1LL, 2LL>;
    using CustomInits  = IntList<1LL, 1LL>;

    std::cout << "\n Произвольный рекуррент (a0=1, a1=2) \n";
    std::cout << "x(0) = " << Rec<0, CustomCoeffs, CustomInits>::value << "\n";  // 1
    std::cout << "x(1) = " << Rec<1, CustomCoeffs, CustomInits>::value << "\n";  // 1
    std::cout << "x(2) = " << Rec<2, CustomCoeffs, CustomInits>::value << "\n";  // 3
    std::cout << "x(3) = " << Rec<3, CustomCoeffs, CustomInits>::value << "\n";  // 7
    std::cout << "x(4) = " << Rec<4, CustomCoeffs, CustomInits>::value << "\n";  // 17

    return 0;
}