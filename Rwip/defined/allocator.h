#pragma once

// Основные функции для работы с памятью

// Освобождение памяти
void s_free(void* p){
	free(p); // Стандартная функция free
}

// Перевыделение памяти
template<class type>
type* s_realloc( type*& ar, unsigned int size){
    return (type*)realloc(ar, sizeof(type) * size); // Перевыделение с новым размером
}

// Выделение памяти и инициализация нулями
template<class type>
type* s_calloc(unsigned int size){
    return (type*)calloc(size, sizeof(type)); // Инициализация нулями
}

// Выделение памяти без инициализации
template<class type>
type* s_malloc(unsigned int size){
    return (type*)malloc(size * sizeof(type)); // Без инициализации
}

// Замена выделенной памяти с освобождением предыдущей
template<class type>
void s_replace( type*& ar, unsigned int size){
    type* tempPtr = (type*)realloc(ar, sizeof(type) * size); // Перевыделение памяти
    s_free(ar); // Освобождение старой памяти
    ar = tempPtr; // Обновление указателя
}

// Замена памяти с копированием данных и освобождением предыдущей
template<class type>
void s_replace_raw( type*& ar, unsigned int oldSize, unsigned int newSize){
    type* tempArr = (type*)calloc(newSize, sizeof(type)); // Выделение и инициализация нулями
    for(unsigned int i = 0; i < min(oldSize, newSize); i++)
    {
        tempArr[i] = ar[i]; // Копирование данных
    }
    free(ar); // Освобождение старой памяти
    ar = tempArr; // Обновление указателя
}
// Функция для преобразования строки в массив символов
void RG_StringToChar(char*& c,string s){
	c = s_calloc<char>(s.size());

	for(int i = 0; i<s.size()-1;i++){
		c[i] = s[i];
	}
}

// Коментарии сгенерированы GPT-4