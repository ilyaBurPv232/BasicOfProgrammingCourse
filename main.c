#include "string/string_.h"
#include <assert.h>
#include <string.h>

void test_strlen_() {
    char *str = "1234567890";
    char *str1 = "123";
    char *str2 = "";

    assert(strlen_(str) == 10);
    assert(strlen_(str1) == 3);
    assert(strlen_(str2) == 0);
}

void test_find() {
    char *str = "122345670";

    assert(find(&str[0], &str[9], '1') == &str[0]);
    assert(find(&str[0], &str[9], '0') == &str[8]);
    assert(find(&str[0], &str[9], '2') == &str[1]);
    assert(find(&str[0], &str[9], 'j') == &str[9]);

}

void test_findNonSpace() {
    char *str = " 5234567890";
    char *str1 = "\t     \th23";
    char *str2 = "123 123\t";
    char *str3 = "\t\t\t";

    assert(findNonSpace(str) == &str[1]);
    assert(*findNonSpace(str1) == 'h');
    assert(*findNonSpace(str2) == '1');
    assert(findNonSpace(str3) == &str3[3]);


}

void test_findSpace() {
    char *str = "523456789";
    char *str1 = "\taaaa\th23";
    char *str2 = "123 123\t";
    char *str3 = "\t\t\t";

    assert(*findSpace(str) == '\0');
    assert(*findSpace(str1) == '\t');
    assert(*findSpace(str2) == ' ');
    assert(findSpace(str3) == &str3[0]);
}

void test_findNonSpaceReverse() {
    char *str = " 5234567890";
    char *str1 = "\t     \th23";
    char *str2 = "123 123\t";
    char *str3 = "\t\t\t";

    assert(*findNonSpaceReverse(&str[10], &str[0]) == '0');
    assert(*findNonSpaceReverse(&str1[9], &str1[0]) == '3');
    assert(*findNonSpaceReverse(&str2[7], &str2[0]) == '3');
    assert(*findNonSpaceReverse(&str3[2], &str3[0]) == '\0');
}

void test_findSpaceReverse() {
    char *str = "523456789";
    char *str1 = "\taaaa\th23";
    char *str2 = "123 123\t";
    char *str3 = "\t\t\t";

    assert(*findSpaceReverse(&str[8], &str[0]) == '\0');
    assert(findSpaceReverse(&str1[8], &str1[0]) == &str1[5]);
    assert(*findSpaceReverse(&str2[7], &str2[0]) == '\t');
    assert(findSpaceReverse(&str3[2], &str3[0]) == &str3[2]);
}

void test_copy() {
    char *str = "a2b45678c";
    char *str_copied[9];

    copy(&str[0], &str[9], (char *) str_copied);

    assert(!strcmp(str, (const char *) str_copied));

}

void test_copyIf(){
    char *str = "a2b45678c";
    char *str_copied[9];
    char *test = "abc";

    copyIf(&str[0], &str[9], (char *) str_copied, isalpha);

    assert(!strcmp(test, ( char *) str_copied));
}

void test_copyIfReverse(){
    char *str = "a2b45678c";
    char *str_copied[9];
    char *test = "cba";

    copyIfReverse(&str[8], &str[0], (char *) str_copied, isalpha);

    assert(!strcmp(test, str_copied));
}

void test() {

    //find тесты
    test_strlen_();
    test_find();
    test_findNonSpace();
    test_findSpace();
    test_findNonSpaceReverse();
    test_findSpaceReverse();

    //copy тесты
    test_copy();
    test_copyIf();
    test_copyIfReverse();


    printf("\nfeels good man!\n");

}

int main() {

    test();

    return 0;
}

