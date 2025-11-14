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