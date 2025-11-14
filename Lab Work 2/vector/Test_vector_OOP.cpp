#include <iostream>
#include <random>
#include <chrono>
/////////////////////////////////
template<typename T>
class subvector {
    T* mas;
    unsigned int top;
    unsigned int capacity;
public:
    subvector() :mas(NULL),top(0),capacity(0) {}
    
    subvector(unsigned int initial_capacity):mas(NULL),top(0),capacity(0) {
        if (initial_capacity >0) {
            resize(initial_capacity);}
    }
    ~subvector() {
        delete[] mas;
    }
    subvector(const subvector& other):mas(NULL),top(0),capacity(0) {
        if (other.capacity>0) {
            mas = new T[other.capacity];
            capacity =other.capacity;
            top =other.top;
            for (unsigned int i =0; i<top; ++i) {
                mas[i] =other.mas[i];}
        }
    } 
    subvector& operator=(const subvector& other) {
        if (this !=&other) {
            delete[] mas;
            mas =NULL;
            top =0;
            capacity =0;
            
            if (other.capacity > 0) {
                mas = new T[other.capacity];
                capacity = other.capacity;
                top = other.top;
                for (unsigned int i = 0; i <top;++i) {
                    mas[i] =other.mas[i];}
                }
        }
        return *this;}

    subvector(subvector&& other):mas(other.mas),top(other.top),capacity(other.capacity) {
        other.mas = NULL;
        other.top =0;
        other.capacity =0;
    }
    subvector& operator=(subvector&& other) {
          if (this != &other) {
            delete[] mas;
            mas = other.mas;
            top =other.top;
            capacity = other.capacity;
            other.mas =NULL;
            other.top =0;
            other.capacity =0;}
        return *this;}

    bool push_back(const T& d) {
        if (top == capacity) {
            unsigned int n_cap;
        if (capacity == 0) {
            n_cap =1;
        } else {
        n_cap = capacity *2;}

            if (!resize(n_cap)) {
                return false;}
        }
        mas[top] =d;
        top++;
        return true;}

    T pop_back() {
        if (top == 0) {
            return T{};}
        top--;
        return mas[top];}

    bool resize(unsigned int n_cap) {
        if (n_cap == capacity) return true;
        if (n_cap == 0) {
            delete[] mas;
            mas =NULL;
            capacity =0;
            top =0;
            return true;}

        T* st_tp=new T[n_cap];
        if (st_tp==NULL) {
            return false;}
            
        
        unsigned int limit;
    if (top <n_cap) {
        limit=top;
    } else {
        limit =n_cap;}

        for (unsigned int i =0; i <limit; ++i) {
            st_tp[i] = mas[i];}
        delete[] mas;
        mas = st_tp;
        capacity =n_cap;
        top =limit;
        return true;
    }

    void shrink_to_fit() {
        if (top >=capacity) {
            return;}

        if (top ==0) {
            delete[] mas;
            mas = NULL;
            capacity =0;
            return;}

        T* mass = new T[top];
        if (mass != NULL) {
            for (unsigned int i =0; i<top; ++i) {
                mass[i] =mas[i];
            }
            delete[] mas;
            mas =mass;
            capacity =top;
        }
    }
    void clear() {
        top = 0;}

    T* get_mas() const { return mas; }
    unsigned int get_top() const { return top; }
    unsigned int get_capacity() const { return capacity; }
};
/////////////////////////////////
using vector = subvector<int>;
using std::cout;
using std::endl;
double get_time()
{
    return std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now().time_since_epoch()).count()/1e6;
}
int rand_uns(int min, int max)
{
        unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
        static std::default_random_engine e(seed);
        std::uniform_int_distribution<int> d(min, max);
        return d(e);
}
int main()
{
    int n = 100000;
    int *test_sequence = new int[n], sum_for_O3 = 0, sum_check = 0,
        *pop_push_sequence_eq = new int[n],
        *pop_push_sequence_push = new int[n],
        *pop_push_sequence_pushpush = new int[n];
    double start = 0, finish = 0, total = 0;
    cout << std::fixed;
    cout.precision(4);
//----------- Initialization
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        test_sequence[i] = rand_uns(0, n - 1);
        pop_push_sequence_eq[i] = rand_uns(0, 1);
        pop_push_sequence_push[i] = rand_uns(0, 5);
        pop_push_sequence_pushpush[i] = rand_uns(0, 10);
    }
    finish = get_time();
    cout << "Test sequence initialization: \t\t" << finish - start << endl;
    vector sv{};
//----------- Test 000 Straight push_back
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sv.push_back(test_sequence[i]);
        // sv.push_back(test_sequence[i])
    }
    finish = get_time();
    for (int i = 0; i < n; i++)   //!!! This is a hack to bamboozle the O3 optimization.
        sum_for_O3 += sv.get_mas()[i];;  // I might as well use it to test push/pop.
    cout << "000 Straight push_back: \t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 001 Straight pop_back
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sum_check += sv.pop_back();
    }
    finish = get_time();
    if (sum_check != sum_for_O3)
    {
        cout <<endl <<"--- !!! Failed push/pop consistency !!! ---" << endl;
        return 0;
    }
    cout << "001 Straight pop_back: \t\t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 002 Straight resize up
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        sv.resize(i);
    }
    finish = get_time();
    sv.shrink_to_fit();
    if (sv.get_capacity())
    {
        cout <<endl <<"--- !!! Failed resize/shrink consistency !!! ---" << endl;
        return 0;
    }
    cout << "002 Straight resize up: \t\t" << finish - start << endl;
    total += finish - start;
//----------- Test 003 Random pop/push equal amount
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_eq[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();
    sv = vector{};
    sv.shrink_to_fit();
    if (sv.get_top())
    {
        cout <<endl <<"--- !!! Falied clear !!! ---" << endl;
        return 0;
    }
    if (sv.get_capacity())
    {
        cout <<endl <<"--- !!! Falied shrink_to_fit !!! ---" << endl;
        return 0;
    }
    cout << "003 Random pop/push equal amount: \t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 004 Random pop/push more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_push[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();
    sv.clear();
    sv.shrink_to_fit();
    cout << "004 Random pop/push more push: \t\t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- Test 005 Random pop/push much more push
    sum_for_O3 = 0; // This variable will be printed so O3 won't cut the whole thing.
    start = get_time();
    for (int i = 0; i < n; i++)
    {
        if (pop_push_sequence_pushpush[i])
            sv.push_back(test_sequence[i]);
        else
            sum_for_O3 += sv.pop_back();
    }
    finish = get_time();
    cout << "005 Random pop/push much more push: \t" << finish - start << "\t\t" << sum_for_O3 << endl;
    total += finish - start;
//----------- End of tests
    cout << "-----------" << endl <<"Alltests finished, total time: \t" << total << endl;
    delete[] test_sequence;
    delete[] pop_push_sequence_eq;
    delete[] pop_push_sequence_push;
    delete[] pop_push_sequence_pushpush;
    return 0;
}


