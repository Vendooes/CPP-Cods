bool init(subvector *qv){
    qv -> top = 0;
    qv -> capacity = 0;
    qv -> mas = NULL;
    return true;
}

bool push_back(subvector *qv, int d) {
    if (qv->top == qv->capacity) {
        unsigned int new_capacity;
        if (qv->capacity == 0) {
            new_capacity = 1;
        } else {
            new_capacity = qv->capacity * 2;}

        int *new_mas = new int[new_capacity];
        
        if (new_mas == NULL) {
            return false;
        }
        for (unsigned int i = 0; i < qv->top; i++) {
            new_mas[i] = qv->mas[i];
        }
        if (qv->mas != NULL) {
            delete[] qv->mas;
        }
        qv->mas = new_mas;
        qv->capacity = new_capacity;
    }
    qv->mas[qv->top] = d;
    qv->top++;
    return true;
}

int pop_back(subvector *qv){
    if (qv->top == 0) {
    return 0;}

    else {
    qv->top = qv->top - 1;
    int last = qv->mas[qv->top];
    return last;}
}

bool resize(subvector *qv, unsigned int new_capacity){
    if (new_capacity == qv->capacity) return true;

    if (new_capacity == 0) {
        delete[] qv->mas;
        qv->mas = NULL;
        qv->capacity = qv->top = 0;
        return true;
    }
    
    int *temporary_storage = new int[new_capacity];
    if (temporary_storage == NULL) {
        return false;
    }
    
    unsigned int limit;
    if (qv->top < new_capacity) {
        limit = qv->top;
    } else {
        limit = new_capacity;
    }

    for (unsigned int i = 0; i < limit; ++i) {
        temporary_storage[i] = qv->mas[i];
    }
    
    delete[] qv->mas;
    qv->mas = temporary_storage;
    qv->capacity = new_capacity;
    qv->top = limit; 
    
    return true;
}

void shrink_to_fit(subvector *qv) {
    if (qv->top >= qv->capacity) {
        return;
    }

    if (qv->top == 0) {
        delete[] qv->mas;
        qv->mas = NULL;
        qv->capacity = 0;
        return;
    }
    
    int *temp_mas = new int[qv->top];
    
    if (temp_mas != NULL) {
        unsigned int current_index = 0;
        while (current_index < qv->top) {
            temp_mas[current_index] = qv->mas[current_index];
            current_index++;
        }

        delete[] qv->mas;
        qv->mas = temp_mas;
        qv->capacity = qv->top;
    }
}

void clear(subvector *qv) {
    qv->top = 0;
}

void destructor(subvector *qv) {
    if (qv->mas) {
        delete[] qv->mas;
    }
    qv->mas = NULL;
    qv->top = 0;
    qv->capacity = 0;
}