#include <stdio.h>
#include <assert.h>
#include "bitset.h"

int bitset_checkValue(bitset *a, unsigned value) {
    return value >= 0 && value <= a->maxValue;
}

// добавляет элемент value в множество set
void bitset_insert(bitset *set, unsigned value) {
    if (value <= set->maxValue) {
        uint32_t bit = 1 << value;
        set->values |= bit;
    }
}

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create(unsigned maxValue) {
    bitset newBitset;
    newBitset.values = 0; // пустое множество
    newBitset.maxValue = maxValue;
    return newBitset;
}

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection(bitset set1, bitset set2) {
    assert (set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & set2.values, set1.maxValue};
}

// вывод множества set
void bitset_print(bitset set) {
    printf("{");
    int isEmpty = 1;
    for (int i = 0; i <= set.maxValue; ++i) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            isEmpty = 0;
        }
    }
    if (isEmpty)
        printf("}\n");
    else
        printf("\b\b}\n");
}

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in(bitset set, unsigned value) {
    if (value > set.maxValue)
        return false;
    return (set.values & (1 << value)) != 0;
}

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual(bitset set1, bitset set2) {
    return set1.values == set2.values && set1.maxValue == set2.maxValue;
}

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset(bitset subset, bitset set) {
    return (subset.values & set.values) == subset.values;
}

// удаляет элемент value из множества set
void bitset_deleteElement(bitset *set, unsigned value) {
    if (bitset_in(*set, value))
        set->values &= ~(1 << value);
}

// возвращает объединение множеств set1 и set2
bitset bitset_union(bitset set1, bitset set2) {
    bitset union_set;
    union_set.maxValue = set1.maxValue > set2.maxValue ?
                         set1.maxValue : set2.maxValue;
    union_set.values = set1.values | set2.values;
    return union_set;
}

// возвращает разность множеств set1 и set2
bitset bitset_difference(bitset set1, bitset set2) {
    bitset difference_set;
    difference_set.maxValue = set1.maxValue > set2.maxValue ?
                              set1.maxValue : set2.maxValue;
    difference_set.values = set1.values & ~set2.values;
    return difference_set;
}

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    bitset symmetricDifference_set;

    symmetricDifference_set.maxValue =
            set1.maxValue > set2.maxValue ?
            set1.maxValue : set2.maxValue;

    symmetricDifference_set.values = set1.values & ~set2.values;
    symmetricDifference_set.values |= set2.values & ~set1.values;

    return symmetricDifference_set;
}

// возвращает дополнение до универсума множества set
bitset bitset_complement(bitset set) {
    bitset complement;
    complement.values = ~set.values & ((1 << set.maxValue) - 1);
    complement.maxValue = set.maxValue;
    return complement;
}