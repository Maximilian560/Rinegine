#pragma once



// Управление сборкой мусора
// Структура для управления сборкой мусора
struct RG_Garbage_Collector{
    RG_Array<void*> GC_pointer; // Массив указателей на выделенную память
    RG_Array<int> GC_size; // Массив размеров выделенной памяти

    // Добавление нового указателя и его размера в массивы
    void add(void* p,int size){
        GC_pointer.push_back(p); // Добавление указателя
        GC_size.push_back(size); // Добавление размера
    }

    // Удаление указателя и его размера из массивов
    void del(void* p){
        for(int i = 0; i<GC_pointer.size(); i++){
            if(GC_pointer[i] == p){
                GC_pointer.erase(i); // Удаление указателя
                GC_size.erase(i); // Удаление размера
                break;
            }
        }
    }

    // Получение индекса указателя в массиве
    int get(void* p){
        for(int i = 0; i<GC_pointer.size(); i++){
            if(GC_pointer[i] == p){
                return i; // Возвращение индекса
            }
        }
        cout<<"\nGC_ERR\n";
        return -1; // Возвращение -1, если указатель не найден
    }

    // Очистка массивов указателей и размеров
    void clear(){
        for(int i = 0; i<GC_pointer.size(); i++){
            s_free(GC_pointer[i]); // Освобождение памяти
        }
        GC_pointer.clear(); // Очистка массива указателей
        GC_size.clear(); // Очистка массива размеров
    }
    
    // Деструктор, очищающий массивы при уничтожении объекта
    ~RG_Garbage_Collector(){
        clear();
    }
    
}RG_MainGC; // Глобальный объект для управления сборкой мусора

// Выделение памяти и инициализация нулями с учетом сборки мусора
template<class type>
type* s_calloc_gc(unsigned int size){
    RG_MainGC.add((void*)calloc(size, sizeof(type)),size);
    if(RG_MainGC.GC_pointer[RG_MainGC.GC_pointer.size()-1] == nullptr){
        throw RG_ERROR_OUT_OF_MEMORY;
    }
    return (type*)RG_MainGC.GC_pointer[RG_MainGC.GC_pointer.size()-1]; // Возвращение указателя на выделенную память
}

// Выделение памяти без инициализации с учетом сборки мусора
template<class type>
type* s_malloc_gc(unsigned int size){
    RG_MainGC.add((void*)malloc(size * sizeof(type)),size);
    if(RG_MainGC.GC_pointer[RG_MainGC.GC_pointer.size()-1] == nullptr){
        throw RG_ERROR_OUT_OF_MEMORY;
    }
    return (type*)RG_MainGC.GC_pointer[RG_MainGC.GC_pointer.size()-1]; // Возвращение указателя на выделенную память
}

// Перевыделение памяти с учетом сборки мусора
template<class type>
type* s_realloc_gc( type*& ar, unsigned int size){
    type* tempPtr = (type*)realloc(ar, sizeof(type) * size);
    if(tempPtr==nullptr){
        throw RG_ERROR_OUT_OF_MEMORY;
    }
    RG_MainGC.GC_size[RG_MainGC.get(ar)] = size; // Обновление размера в массиве
    RG_MainGC.GC_pointer[RG_MainGC.get(ar)] = tempPtr;
    return tempPtr;
}

// Замена выделенной памяти с освобождением предыдущей и учетом сборки мусора
template<class type>
void s_replace_gc( type*& ar, unsigned int size){
    type* tempPtr = (type*)realloc(ar, sizeof(type) * size); // Перевыделение памяти
    if(tempPtr==nullptr){
        throw RG_ERROR_OUT_OF_MEMORY;
    }
    RG_MainGC.GC_size[RG_MainGC.get(ar)] = size; // Обновление размера в массиве
    RG_MainGC.GC_pointer[RG_MainGC.get(ar)] = tempPtr; // Обновление указателя в массиве
    s_free(ar); // Освобождение старой памяти
    ar = tempPtr; // Обновление указателя
}

// Замена памяти с копированием данных, освобождением предыдущей и учетом сборки мусора
template<class type>
void s_replace_raw_gc( type*& ar, unsigned int oldSize, unsigned int newSize){
    type* tempArr = (type*)calloc(newSize, sizeof(type)); // Выделение и инициализация нулями новой памяти
    if(tempArr==nullptr){
        throw RG_ERROR_OUT_OF_MEMORY;
    }
    for(unsigned int i = 0; i < min(oldSize, newSize); i++)
    {
        tempArr[i] = ar[i]; // Копирование данных
    }
    RG_MainGC.GC_size[RG_MainGC.get(ar)] = newSize; // Обновление размера в массиве
    RG_MainGC.GC_pointer[RG_MainGC.get(ar)] = tempArr; // Обновление указателя в массиве
    free(ar); // Освобождение старой памяти
    ar = tempArr; // Обновление указателя
}
// Коментарии сгенерированы GPT-4