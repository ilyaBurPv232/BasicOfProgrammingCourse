#ifndef UNIKUM_STRING__H
#define UNIKUM_STRING__H

#include <stdio.h>
#include <ctype.h>


//возвращает длину строки
size_t strlen_(const char *begin);

//возвращает указатель
//на первый элемент с кодом ch, расположенным на ленте памяти между
//адресами begin и end не включая end.
char *find(char *begin, char *end, int ch);

//возвращает указатель на первый пробельный
// символ, расположенный на ленте памяти начиная с адреса begin
// или на первый ноль-символ.
char *findNonSpace(char *begin);

// возвращает указатель на первый пробельный символ,
// расположенный на ленте памяти начиная с адреса begin
// или на первый ноль-символ.
char* findSpace(char *begin);

//Возвращает указатель на первый справа символ, отличный от пробельных,
//расположенный на ленте памяти, начиная с rbegin (последний символ
//строки, за которым следует ноль-символ) и заканчивая rend
//(адрес символа перед началом строки). Если символ не найден, возвращается адрес rend.
char* findNonSpaceReverse(char *rbegin, const char *rend);

//Возвращает указатель на первый пробельный символ справа, расположенный на ленте
//памяти, начиная с rbegin и заканчивая rend. Если символ не найден,
//возвращается адрес rend.
char* findSpaceReverse(char *rbegin, const char *rend);

//записывает по адресу beginDestination
//фрагмент памяти, начиная с адреса beginSource до endSource
//возвращает указатель на следующий свободный фрагмент памяти в
//destination:
char* copy(const char *beginSource, const char *endSource,
           char *beginDestination);

//Записывает по адресу
//beginDestination элементы из фрагмента памяти начиная с beginSource
//заканчивая endSource, удовлетворяющие функции-предикату f. Функция
//возвращает указатель на следующий свободный для записи фрагмент в
//памяти.
char* copyIf(char *beginSource, const char *endSource,
             char *beginDestination, int (*f)(int));

//Записывает по адресу
//beginDestination элементы из фрагмента памяти начиная с rbeginSource
//заканчивая rendSource, удовлетворяющие функции-предикату f.
// Функция возвращает значение beginDestination по окончанию работы
//функции.
char* copyIfReverse(char *rbeginSource, const char *rendSource,
                    char *beginDestination, int (*f)(int));

#endif
