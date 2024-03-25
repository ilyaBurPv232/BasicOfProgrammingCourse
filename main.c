#include "string/string_.h"
#include <stdio.h>


#define ASSERT_STRING(expected, got) assertString(expected, got, \
__FILE__, __FUNCTION__, __LINE__)

void test_removeExtraSpaces1() {
    char str[] = "Hallo   , Peter      ?";
    char exp[] = "Hallo , Peter ?";
    removeExtraSpaces(str);

    ASSERT_STRING(exp, str);
}

void test_removeExtraSpaces2() {
    char str[] = "";
    char exp[] = "";
    removeExtraSpaces(str);

    ASSERT_STRING(exp, str);
}

void test_removeExtraSpaces3() {
    char str[] = "ABoba ,slon 1 2 3";
    char exp[] = "ABoba ,slon 1 2 3";
    removeExtraSpaces(str);

    ASSERT_STRING(exp, str);
}

void test_removeExtraSpaces4() {
    char str[] = "      ";
    char exp[] = "";
    removeExtraSpaces(str);

    ASSERT_STRING(exp, str);
}

void test_removeAdjacentEqualLetters1() {
    char str[] = "1111  22222 aaaaaaabbbbbaaaaa";
    char exp[] = "1 2 aba";
    removeAdjacentEqualLetters(str);

    ASSERT_STRING(exp, str);
}

void test_removeAdjacentEqualLetters2() {
    char str[] = "";
    char exp[] = "";
    removeAdjacentEqualLetters(str);

    ASSERT_STRING(exp, str);
}

void test_removeAdjacentEqualLetters3() {
    char str[] = "A B C";
    char exp[] = "A B C";
    removeAdjacentEqualLetters(str);

    ASSERT_STRING(exp, str);
}

void test_removeAdjacentEqualLetters4() {
    char str[] = "AAAaaa";
    char exp[] = "Aa";
    removeAdjacentEqualLetters(str);

    ASSERT_STRING(exp, str);
}


void test_removeAdjacentEqualLetters() {
    test_removeAdjacentEqualLetters1();
    test_removeAdjacentEqualLetters2();
    test_removeAdjacentEqualLetters3();
    test_removeAdjacentEqualLetters4();

}

void test_removeExtraSpaces() {
    test_removeExtraSpaces1();
    test_removeExtraSpaces2();
    test_removeExtraSpaces3();
    test_removeExtraSpaces4();

}

void test() {

    test_removeExtraSpaces();

}

int main() {

    test();

    return 0;
}