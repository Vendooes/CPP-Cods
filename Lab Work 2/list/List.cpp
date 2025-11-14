template<typename T>
class subforwardlist {
public:
    struct Node {
        T data;
        Node* next;    
        Node(const T& value) : data(value), next(nullptr) {}
    };
    
    Node* begin;

    subforwardlist() : begin(nullptr) {}

    ~subforwardlist() {
        clear();
    }

    void clear() {
        while (begin != nullptr) {
            Node* current = begin;
            begin = begin->next;
            delete current;
        }
    }

    subforwardlist(const subforwardlist& other) : begin(nullptr) {
        copy_from(other);
    }

    subforwardlist& operator=(const subforwardlist& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }

    subforwardlist(subforwardlist&& other) : begin(other.begin) {
        other.begin = nullptr;
    }

    subforwardlist& operator=(subforwardlist&& other) {
        if (this != &other) {
            clear();
            begin = other.begin;
            other.begin = nullptr;
        }
        return *this;
    }

    void push_back(const T& data) {
        Node* new_node = new Node(data);
        
        if (begin == nullptr) {
            begin = new_node;
            return;
        }
        
        Node* current = begin;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = new_node;
    }

    T pop_back() {
        if (begin == nullptr) {
            return T();
        }
        
        if (begin->next == nullptr) {
            T data = begin->data;
            delete begin;
            begin = nullptr;
            return data;
        }
        
        Node* current = begin;
        while (current->next->next != nullptr) {
            current = current->next;
        }
        
        T data = current->next->data;
        delete current->next;
        current->next = nullptr;
        return data;
    }

    void push_forward(const T& data) {
        Node* new_node = new Node(data);
        new_node->next = begin;
        begin = new_node;
    }

    T pop_forward() {
        if (begin == nullptr) {
            return T();
        }
        
        Node* first_node = begin;
        T data = first_node->data;
        begin = begin->next;
        delete first_node;
        return data;
    }

    void push_where(unsigned int position, const T& data) {
        if (position == 0) {
            push_forward(data);
            return;
        }
        
        Node* current = begin;
        for (unsigned int i = 0; i < position - 1; i++) {
            if (current == nullptr || current->next == nullptr) {
                return;
            }
            current = current->next;
        }
        
        Node* new_node = new Node(data);
        new_node->next = current->next;
        current->next = new_node;
    }

    T erase_where(unsigned int position) {
        if (begin == nullptr) {
            return T();
        }
        
        if (position == 0) {
            return pop_forward();
        }
        
        Node* current = begin;
        for (unsigned int i = 0; i < position - 1; i++) {
            if (current == nullptr || current->next == nullptr) {
                return T();
            }
            current = current->next;
        }
        
        if (current->next == nullptr) {
            return T();
        }
        
        Node* node_to_delete = current->next;
        T data = node_to_delete->data;
        current->next = node_to_delete->next;
        delete node_to_delete;
        return data;
    }
    unsigned int size() {
        unsigned int count = 0;
        Node* current = begin;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }}