#include "libs/data_structures/bitset/bitset.h"
#include <assert.h>


//функция проверяющая работоспособность bitset_create
void bitset_create_test() {
    bitset set = bitset_create(30);
    bitset set1 = bitset_create(31);

    assert(set.values == NULL && set.maxValue == 30);
    assert(set1.values == NULL && set1.maxValue == 31);
}

//функция проверяющая работоспособность bitset_insert
void bitset_insert_test() {
    bitset set = bitset_create(30);
    bitset_insert(&set, 2);
    assert(set.values == 4); // тк занят 3 бит и в дв записи 100
    bitset_insert(&set, 0);
    assert(set.values == 5); //тк занят 3 бит + 1 и в дв записи 101
}

//функция проверяющая работоспособность bitset_in
void bitset_in_test() {
    bitset set = bitset_create(30);
    bitset_insert(&set, 5);
    bitset_insert(&set, 10);

    assert(bitset_in(set, 5) == true);
    assert(bitset_in(set, 10) == true);
}

//функция проверяющая работоспособность bitset_isEqual
void bitset_isEqual_test() {
    bitset set1 = bitset_create(30);
    bitset set2 = bitset_create(30);

    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 19);

    bitset_insert(&set2, 1);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 19);

    assert(bitset_isEqual(set1, set2) == true);

    bitset set_a = bitset_create(10);
    bitset set_b = bitset_create(12);

    assert(bitset_isEqual(set_a, set_b) == false);
}

//функция проверяющая работоспособность bitset_isSubset
void bitset_isSubset_test() {
    bitset set1 = bitset_create(30);
    bitset set2 = bitset_create(10);

    bitset_insert(&set1, 1);
    bitset_insert(&set1, 4);
    bitset_insert(&set1, 8);
    bitset_insert(&set1, 11);
    bitset_insert(&set1, 19);

    bitset_insert(&set2, 1);
    bitset_insert(&set2, 4);
    bitset_insert(&set2, 8);

    assert(bitset_isSubset(set2, set1) == true);

    bitset_insert(&set2, 9);

    assert(bitset_isSubset(set1, set2) == false);
}

//функция проверяющая работоспособность bitset_deleteElement
void bitset_deleteElement_test() {
    bitset set = bitset_create(5);

    bitset set_test = bitset_create(5);

    bitset_insert(&set, 1);
    bitset_insert(&set, 4);

    bitset_deleteElement(&set, 1);
    bitset_deleteElement(&set, 4);

    assert(bitset_in(set, 1) == false);
    assert(bitset_in(set, 4) == false);
    assert(bitset_isEqual(set, set_test) == true);
}

//функция проверяющая работоспособность bitset_union
void bitset_union_test() {
    bitset set1 = bitset_create(20);
    bitset set2 = bitset_create(25);
    bitset set_union_test = bitset_create(25);

    bitset_insert(&set1, 1);
    bitset_insert(&set1, 5);

    bitset_insert(&set2, 2);
    bitset_insert(&set2, 6);

    bitset_insert(&set_union_test, 1);
    bitset_insert(&set_union_test, 2);
    bitset_insert(&set_union_test, 5);
    bitset_insert(&set_union_test, 6);

    bitset set_union = bitset_union(set1, set2);

    assert(bitset_isEqual(set_union_test,
                          set_union) == true);

    bitset set_a = bitset_create(10);
    bitset set_b = bitset_create(12);
    bitset set_union_test_1 = bitset_create(12);

    bitset_insert(&set_a, 2);
    bitset_insert(&set_a, 4);

    bitset_insert(&set_b, 4);
    bitset_insert(&set_b, 9);

    bitset_insert(&set_union_test_1, 2);
    bitset_insert(&set_union_test_1, 4);
    bitset_insert(&set_union_test_1, 9);

    bitset set_union_1 = bitset_union(set_a, set_b);

    assert(bitset_isEqual(set_union_test_1,
                          set_union_1) == true);
}

//функция проверяющая работоспособность bitset_difference
void bitset_difference_test() {
    bitset set1 = bitset_create(20);
    bitset set2 = bitset_create(25);
    bitset set_difference_test = bitset_create(25);

    bitset_insert(&set1, 1);
    bitset_insert(&set1, 5);

    bitset_insert(&set2, 1);
    bitset_insert(&set2, 5);

    bitset set_difference = bitset_difference(set1, set2);

    assert(bitset_isEqual(set_difference_test,
                          set_difference) == true);

    bitset set_a = bitset_create(10);
    bitset set_b = bitset_create(12);
    bitset set_difference_test_1 = bitset_create(12);

    bitset_insert(&set_a, 2);
    bitset_insert(&set_a, 4);

    bitset_insert(&set_b, 4);
    bitset_insert(&set_b, 9);

    bitset_insert(&set_difference_test_1, 2);

    bitset set_difference_1 = bitset_difference(set_a, set_b);

    assert(bitset_isEqual(set_difference_test_1,
                          set_difference_1) == true);
}

//функция проверяющая работоспособность bitset_intersection
void bitset_intersection_test() {
    bitset set1 = bitset_create(25);
    bitset set2 = bitset_create(25);
    bitset set_intersection_test = bitset_create(25);

    bitset_insert(&set1, 1);
    bitset_insert(&set1, 5);

    bitset_insert(&set2, 1);
    bitset_insert(&set2, 2);

    bitset_insert(&set_intersection_test, 1);

    bitset set_intersection = bitset_intersection(set1, set2);

    assert(bitset_isEqual(set_intersection_test,
                          set_intersection) == true);

    bitset set_a = bitset_create(10);
    bitset set_b = bitset_create(10);
    bitset set_intersection_test_1 = bitset_create(10);

    bitset_insert(&set_a, 2);
    bitset_insert(&set_a, 4);

    bitset_insert(&set_b, 4);
    bitset_insert(&set_b, 9);

    bitset_insert(&set_intersection_test_1, 4);

    bitset set_difference_1 = bitset_intersection(set_a, set_b);

    assert(bitset_isEqual(set_intersection_test_1,
                          set_difference_1) == true);
}

//функция проверяющая работоспособность bitset_symmetricDifference
void bitset_symmetricDifference_test() {
    bitset set1 = bitset_create(25);
    bitset set2 = bitset_create(18);
    bitset set_symmetricDifference_test = bitset_create(25);

    bitset_insert(&set1, 1);
    bitset_insert(&set1, 3);
    bitset_insert(&set1, 5);

    bitset_insert(&set2, 1);
    bitset_insert(&set2, 2);
    bitset_insert(&set2, 3);

    bitset_insert(&set_symmetricDifference_test, 2);
    bitset_insert(&set_symmetricDifference_test, 5);

    bitset set_symmetricDifference = bitset_symmetricDifference(set1, set2);

    assert(bitset_isEqual(set_symmetricDifference_test,
                          set_symmetricDifference) == true);

    bitset set_a = bitset_create(14);
    bitset set_b = bitset_create(10);
    bitset set_symmetricDifference_test_1 = bitset_create(14);

    bitset_insert(&set_a, 2);
    bitset_insert(&set_a, 4);

    bitset_insert(&set_b, 4);
    bitset_insert(&set_b, 9);
    bitset_insert(&set_b, 2);

    bitset_insert(&set_symmetricDifference_test_1, 9);

    bitset set_symmetricDifference_1 = bitset_symmetricDifference(set_a, set_b);

    assert(bitset_isEqual(set_symmetricDifference_test_1,
                          set_symmetricDifference_1) == true);
}

//функция проверяющая работоспособность bitset_complement
void bitset_complement_test() {
    bitset set = bitset_create(3);
    bitset_insert(&set, 0);
    bitset_insert(&set, 1);

    bitset set_complement = bitset_complement(set);

    bitset set_complement_test = bitset_create(3);

    bitset_insert(&set_complement_test, 2);

    assert(bitset_isEqual(set_complement_test,
                          set_complement) == true);

    bitset set1 = bitset_create(5);
    bitset_insert(&set1, 2);
    bitset_insert(&set1, 3);

    bitset set_complement1 = bitset_complement(set1);

    bitset set_complement_test1 = bitset_create(5);

    bitset_insert(&set_complement_test1, 0);
    bitset_insert(&set_complement_test1, 1);
    bitset_insert(&set_complement_test1, 4);

    assert(bitset_isEqual(set_complement_test1,
                          set_complement1) == true);
}

//функция проверяющая работоспособность bitset_print
void bitset_print_test() {
    bitset set = bitset_create(10);
    bitset_insert(&set, 1);
    bitset_insert(&set, 5);
    bitset_insert(&set, 6);

    // void bitset_print(bitset set) {
    // printf("{");
    int isEmpty = 1;
    for (int i = 0; i <= set.maxValue; ++i) {
        if (bitset_in(set, i)) {
            assert(bitset_in(set, i) == true);
            //printf("%d, ", i);
            isEmpty = 0;
        }
    }
    // if (isEmpty)
    //    printf("}\n");
    //else
    //   printf("\b\b}\n");
}

void bitset_test() {
    bitset_create_test();
    bitset_insert_test();
    bitset_in_test();
    bitset_isEqual_test();
    bitset_isSubset_test();
    bitset_deleteElement_test();
    bitset_union_test();
    bitset_difference_test();
    bitset_intersection_test();
    bitset_symmetricDifference_test();
    bitset_complement_test();
    bitset_print_test();
}

int main() {

    bitset_test();

    return 0;
}
