#include <iostream>
#include <vector>
#include <deque>
#include <list>
#include <chrono>
#include <algorithm>
#include <iterator>

template<typename RandomAccessIterator, typename Compare>
void my_sort(RandomAccessIterator first, RandomAccessIterator last, Compare comp) {

    auto size = last - first;

    if (size <= 1) {
        return;}

    RandomAccessIterator pivot_iter = first + size / 2;

    auto pivot_value = *pivot_iter;

    RandomAccessIterator left  = first;
    RandomAccessIterator right = last - 1;

    while (left <= right) {

        while (comp(*left, pivot_value)) {
            ++left;}

        while (comp(pivot_value, *right)) {
            --right;}
        if (left <= right) {
            std::iter_swap(left, right);
            ++left;
            --right;}
    }

    my_sort(first, right + 1, comp);
    my_sort(left,  last,      comp);}

struct DescendingComparator {
    bool operator()(int a, int b) const {
        return a > b;}
};

bool ascending(int a, int b) {
    return a < b;}

template<typename Container>
void print(const std::string& label, const Container& c) {
    std::cout << label << ": ";
    for (const auto& elem : c) {
        std::cout << elem << " ";}
    std::cout << "\n";}

int main() {

    std::vector<int> vec = {5, 3, 8, 1, 2, 7, 4, 6};
    print("До сортировки", vec);

    my_sort(vec.begin(), vec.end(), [](int a, int b) {
        return a < b;
    });
    print("После сортировки (vector, лямбда, возр.)", vec);

    std::vector<int> vec2 = {5, 3, 8, 1, 9, 2, 7, 4, 6};
    my_sort(vec2.begin(), vec2.end(), DescendingComparator{});
    print("После сортировки (vector, функтор, убыв.)", vec2);

    std::vector<int> vec3 = {5, 3, 8, 1, 9, 2};
    my_sort(vec3.begin(), vec3.end(), ascending);
    print("После сортировки (vector, функция, возр.)", vec3);

    std::deque<int> dq = {9, 4, 7, 2, 5, 1};
    print("До сортировки (deque)", dq);
    my_sort(dq.begin(), dq.end(), [](int a, int b) { return a < b; });
    print("После сортировки (deque, лямбда)", dq);

    const int N = 100000;

    std::vector<int> big_vec;
    std::deque<int>  big_deq;
    for (int i = N; i >= 1; --i) {
        big_vec.push_back(i);
        big_deq.push_back(i);}

    auto start = std::chrono::high_resolution_clock::now();
    my_sort(big_vec.begin(), big_vec.end(), [](int a, int b) { return a < b; });
    auto end = std::chrono::high_resolution_clock::now();

    auto vec_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    start = std::chrono::high_resolution_clock::now();
    my_sort(big_deq.begin(), big_deq.end(), [](int a, int b) { return a < b; });
    end = std::chrono::high_resolution_clock::now();

    auto deq_time = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    std::cout << "\nЗамер времени (" << N << " элементов)\n";
    std::cout << "vector: " << vec_time << " мкс\n";
    std::cout << "deque:  " << deq_time << " мкс\n";
    std::cout << "Итог: vector быстрее, потому что его элементы лежат в памяти подряд,а deque разбит на отдельные блоки.\n";
    return 0;
}