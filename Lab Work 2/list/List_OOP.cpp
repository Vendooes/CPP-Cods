template<typename T>
class subforwardlist {
public:
// публичные поля в классе с инвариантами?
    struct Node {
        T data;
        Node* next;    
        Node(const T& value) :data(value),next(NULL) {}
    };
    Node* begin;

    subforwardlist():begin(NULL) {}

    subforwardlist(const subforwardlist& other):begin(NULL) {
        copy_from(other);
    }
    subforwardlist& operator=(const subforwardlist& other) {
        if (this != &other) {
            clear();
            copy_from(other);
        }
        return *this;
    }
    subforwardlist(subforwardlist&& other) noexcept:begin(other.begin) {
        other.begin = NULL;
    }
    subforwardlist& operator=(subforwardlist&& other) noexcept {
        if (this != &other) {
            clear();
            begin =other.begin;
            other.begin =NULL;
        }
        return *this;
    }
    ~subforwardlist() {
        clear();
    }

    void clear() {
        while (begin !=NULL) {
            Node* current =begin;
            begin =begin->next;
            delete current;}
    }
    void copy_from(const subforwardlist& other) {
        if (other.begin ==NULL) {
            begin =NULL;
            return;}
        // Утечки памяти при begin != nullptr && other.begin == nullptr зашли в чат
        
        begin = new Node(other.begin->data);
        Node* current =begin;
        Node* other_current =other.begin->next;
        
        while (other_current != NULL) {
            current->next = new Node(other_current->data);
            current = current->next;
            other_current =other_current->next;}
    }
// Если copy_from используется только после вызова clear(), то не нужно давать её наружу пользователю, 
// потому что он точно напорется на утечку памяти. Нужно сделать её приватной и радоваться жизни. 
    
void push_back(const T& data) {
        Node* new_node =new Node(data);
        
        if (begin ==NULL) {
            begin =new_node;
            return;
        }
        
        Node* current =begin;
        while (current->next != NULL) {
            current =current->next;
        }
        current->next =new_node;}

    T pop_back() {
        if (begin ==NULL) {
            return T{};}
        
        if (begin->next ==NULL) {
            T data = begin->data;
            delete begin;
            begin =NULL;
            return data;}
        
        Node* current =begin;
        while (current->next->next !=NULL) {
            current = current->next;
        }
        
        T data = current->next->data;
        delete current->next;
        current->next =NULL;
        return data;
    }

    void push_forward(const T& data) {
        Node* new_node =new Node(data);
        new_node->next =begin;
        begin = new_node;
    }

    T pop_forward() {
        if (begin ==NULL) {
            return T{};
        }
        
        Node* first_node =begin;
        T data = first_node->data;
        begin =begin->next;
        delete first_node;
        return data;
    }

    void push_where(unsigned int where, const T& data) {
        if (where == 0) {
            push_forward(data);
            return;
        }
        
        Node* current = begin;
        for (unsigned int i = 0; i<where -1; i++) {
            if (current == NULL or current->next == NULL) {
                return;
            }
            current =current->next;
        }
        
        Node* new_node =new Node(data);
        new_node->next = current->next;
        current->next =new_node;
    }

    T erase_where(unsigned int where) {
        if (begin ==NULL) {
            return T{};
        }
        
        if (where == 0) {
            return pop_forward();
        }
        
        Node* current =begin;
        for (unsigned int i = 0; i<where -1; i++) {
            if (current ==NULL or current->next ==NULL) {
                return T{};
            }
            current = current->next;
        }
        
        if (current->next ==NULL) {
            return T{};
        }
        
        Node* node_to_delete =current->next;
        T data = node_to_delete->data;
        current->next = node_to_delete->next;
        delete node_to_delete;
        return data;
    }

// Во всех методах выше до комментария можно вынести общий паттерн -- поиск указателя на ноду по индексу -- в отдельную функцию, чтобы не копипатсить один и тот же код

    unsigned int size() {
        unsigned int count = 0;
        Node* current = begin;
        while (current !=NULL) {
            count++;
            current = current->next;
        }
        return count;
    }
};
