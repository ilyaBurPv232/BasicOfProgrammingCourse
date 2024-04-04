#include "string/string_.h"
#include <stdio.h>
#include <malloc.h>
#include <assert.h>


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

void test_digitsToStart1() {
    char str[] = "1bo58ob9a 223924 faadba";
    char exp[] = "1589booba 223924 faadba";
    digitsToStart(str);

    ASSERT_STRING(exp, str);
}

void test_digitsToStart2() {
    char str[] = "";
    char exp[] = "";
    digitsToStart(str);

    ASSERT_STRING(exp, str);
}

void test_digitsToStart3() {
    char str[] = "123abc abc123 1a2b3c";
    char exp[] = "123abc 123abc 123abc";
    digitsToStart(str);

    ASSERT_STRING(exp, str);
}

void test_replaceDigitsToNumOfSpaces1() {
    char str[MAX_STRING_SIZE] = "p3a1s lol";
    char exp[] = "p   a s lol";
    replaceDigitsToNumOfSpaces(str);

    ASSERT_STRING(exp, str);
}

void test_replaceDigitsToNumOfSpaces2() {
    char str[MAX_STRING_SIZE] = "p3a1s 101";
    char exp[] = "p   a s   ";
    replaceDigitsToNumOfSpaces(str);

    ASSERT_STRING(exp, str);
}

void test_replaceDigitsToNumOfSpaces3() {
    char str[MAX_STRING_SIZE] = "";
    char exp[] = "";
    replaceDigitsToNumOfSpaces(str);

    ASSERT_STRING(exp, str);
}

void test_replace1() {
    char str[MAX_STRING_SIZE] = "aboba i love my mom aboba";
    char w1[] = "aboba";
    char w2[] = "goddamn";
    replace(str, w1, w2);
    char exp[MAX_STRING_SIZE] = "goddamn i love my mom goddamn";

    ASSERT_STRING(exp, str);
}

void test_replace2() {
    char str[MAX_STRING_SIZE] = "i love aboba, my mom is baking aboba";
    char w1[] = "aboba";
    char w2[] = "cake";
    replace(str, w1, w2);
    char exp[MAX_STRING_SIZE] = "i love cake, my mom is baking cake";

    ASSERT_STRING(exp, str);
}

void test_replace3() {
    char str[MAX_STRING_SIZE] = "where is my mom mom dad";
    char w1[] = "mom";
    char w2[] = "";
    replace(str, w1, w2);
    char exp[MAX_STRING_SIZE] = "where is my   dad";

    ASSERT_STRING(exp, str);
}

void test_areWordsOrdered1() {
    char s[] = "";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered2() {
    char s[] = "dream";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered3() {
    char s[] = "pass op";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered4() {
    char s[] = "pass pass";
    assert(areWordsOrdered(s) == true);
}

void test_areWordsOrdered5() {
    char s[] = "a ab baaa ca cd";
    assert(areWordsOrdered(s) == true);
}

void test_reverseWordsBag1() {
    char s[MAX_STRING_SIZE] = "h e y";
    reverseWordsBag(s);

    ASSERT_STRING("h e y", s);
}

void test_reverseWordsBag2() {
    char s[MAX_STRING_SIZE] = "Artyom";
    reverseWordsBag(s);

    ASSERT_STRING("moytrA", s);
}

void test_reverseWordsBag3() {
    char s[MAX_STRING_SIZE] = "";
    reverseWordsBag(s);

    ASSERT_STRING("", s);
}

void test_howManyWordsPalindromes1() {
    char s[] = "";

    assert(howManyWordsPalindromes(s) == 0);
}

void test_howManyWordsPalindromes2() {
    char s[] = "heh";

    assert(howManyWordsPalindromes(s) == 1);
}

void test_howManyWordsPalindromes3() {
    char s[] = "heh,heyeh";

    assert(howManyWordsPalindromes(s) == 2);
}

void test_howManyWordsPalindromes4() {
    char s[] = "heh,hi";

    assert(howManyWordsPalindromes(s) == 1);
}

void test_howManyWordsPalindromes5() {
    char s[] = "a";

    assert(howManyWordsPalindromes(s) == 1);
}

void test_mergeString1() {
    char s1[] = "Hello how are you";
    char s2[] = "I am fine thank you";
    char result[100] = "";

    mergeStrings(s1, s2, result);

    ASSERT_STRING("Hello I am fine thank you ", result);
}

void test_mergeString2() {
    char s1[] = "Thank you my friend";
    char s2[] = "Hello how are you";
    char result[100] = "";

    mergeStrings(s1, s2, result);

    ASSERT_STRING("Thank Hello how are you ", result);
}

void test_reverseWords() {
    char p[MAX_STRING_SIZE] = "Hello world! This is a test.";
    reverseWords(p);

    ASSERT_STRING(".test a is This !world Hello", p);

    char c[MAX_STRING_SIZE] = ".test a is This !world Hello";
    reverseWords(c);

    ASSERT_STRING("Hello world! This is a test.", c);
}

void test_getWordBeforeFirstWordWithA() {
    WordDescriptor word;
    char s1[] = "";
    assert(getWordBeforeFirstWordWithA(s1, &word) == EMPTY_STRING);

    char s2[] = "ABC";
    assert(getWordBeforeFirstWordWithA(s2, &word) == FIRST_WORD_WITH_A);

    char s3[] = "BC A";
    assert(getWordBeforeFirstWordWithA(s3, &word) == WORD_FOUND);

    char s4[] = "B Q WE YR OW  IUWR";
    assert(getWordBeforeFirstWordWithA(s4, &word) == NOT_FOUND_A_WORD_WITH_A);
}

void test_lastWordInFirstStringInSecondString1() {
    char s1_1[] = "Hi ha he";
    char s2_1[] = "Hi he";
    WordDescriptor word1 = lastWordInFirstStringInSecondString(s1_1, s2_1);
    char str1[MAX_WORD_SIZE];

    wordDescriptorToString(word1, str1);

    ASSERT_STRING("he", str1);
}

void test_lastWordInFirstStringInSecondString2() {
    char s1_2[] = "Hi ha he";
    char s2_2[] = "Hi ha";
    WordDescriptor word2 = lastWordInFirstStringInSecondString(s1_2, s2_2);
    char str2[MAX_WORD_SIZE];

    wordDescriptorToString(word2, str2);

    ASSERT_STRING("ha", str2);
}

void test_hasDuplicateWords() {
    char str1[] = "my friend Hello my";
    assert(hasDuplicateWords(str1) == true);

    char str2[] = "my friend Hello";
    assert(hasDuplicateWords(str2) == false);
}

void test_FindPairWithSameLetters1() {
    BagOfWords bag1;
    bag1.size = 0;
    parseString("hello world olleh dlrow", &bag1);
    assert(findPairWithSameLetters(&bag1) == 1);
}

void test_FindPairWithSameLetters2() {
    BagOfWords bag2;
    bag2.size = 0;
    parseString("hey hi ha", &bag2);
    assert(findPairWithSameLetters(&bag2) == 0);
}

void test_FindPairWithSameLetters() {
    test_FindPairWithSameLetters1();
    test_FindPairWithSameLetters2();
}

void test_lastWordInFirstStringInSecondString() {
    test_lastWordInFirstStringInSecondString1();
    test_lastWordInFirstStringInSecondString2();
}

void test_mergeString() {
    test_mergeString1();
    test_mergeString2();
}

void test_howManyWordsPalindromes() {
    test_howManyWordsPalindromes1();
    test_howManyWordsPalindromes2();
    test_howManyWordsPalindromes3();
    test_howManyWordsPalindromes4();
    test_howManyWordsPalindromes5();
}

void test_reverseWordsBag() {
    test_reverseWordsBag1();
    test_reverseWordsBag2();
    test_reverseWordsBag3();
}

void test_areWordsOrdered() {
    test_areWordsOrdered1();
    test_areWordsOrdered2();
    test_areWordsOrdered3();
    test_areWordsOrdered4();
    test_areWordsOrdered5();
}


void test_replaceDigitsToNumOfSpaces(){
    test_replaceDigitsToNumOfSpaces1();
    test_replaceDigitsToNumOfSpaces2();
    test_replaceDigitsToNumOfSpaces3();
}

void test_removeAdjacentEqualLetters() {
    test_removeAdjacentEqualLetters1();
    test_removeAdjacentEqualLetters2();
    test_removeAdjacentEqualLetters3();
    test_removeAdjacentEqualLetters4();

}

void test_digitsToStart() {
    test_digitsToStart1();
    test_digitsToStart2();
    test_digitsToStart3();
}

void test_removeExtraSpaces() {
    test_removeExtraSpaces1();
    test_removeExtraSpaces2();
    test_removeExtraSpaces3();
    test_removeExtraSpaces4();

}

void test_replace(){
    test_replace1();
    test_replace2();
    test_replace3();
}

void test() {

    test_removeExtraSpaces();
    test_removeAdjacentEqualLetters();
    test_digitsToStart();
    test_replaceDigitsToNumOfSpaces();
    test_replace();
    test_areWordsOrdered();
    test_reverseWordsBag();
    test_howManyWordsPalindromes();
    test_mergeString();
    test_reverseWords();
    test_getWordBeforeFirstWordWithA();
    test_lastWordInFirstStringInSecondString();
    test_hasDuplicateWords();
    test_FindPairWithSameLetters();

}

int main() {

    test();




    return 0;
}