#include <stdio.h>
#include <assert.h>
#include "bitset.h"


int bitset_checkValue(bitset *a, unsigned value) {
    return value >= 0 && value <= a->maxValue;
}

void bitset_insert(bitset *set, unsigned value) {
    if (value <= set->maxValue) {
        uint32_t bit = 1 << value;
        set->values |= bit;
    }
}

bitset bitset_create(unsigned maxValue) {
    bitset newBitset;
    newBitset.values = 0; // пустое множество
    newBitset.maxValue = maxValue;
    return newBitset;
}

bitset bitset_intersection(bitset set1, bitset set2) {
    assert (set1.maxValue == set2.maxValue);
    return (bitset) {set1.values & set2.values, set1.maxValue};
}

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

bool bitset_in(bitset set, unsigned value) {
    if (value > set.maxValue)
        return false;
    return (set.values & (1 << value)) != 0;
}

bool bitset_isEqual(bitset set1, bitset set2) {
    return set1.values == set2.values && set1.maxValue == set2.maxValue;
}

bool bitset_isSubset(bitset subset, bitset set) {
    return (subset.values & set.values) == subset.values;
}

void bitset_deleteElement(bitset *set, unsigned value) {
    if (bitset_in(*set, value))
        set->values &= ~(1 << value);
}

bitset bitset_union(bitset set1, bitset set2) {
    bitset union_set;
    union_set.maxValue = set1.maxValue > set2.maxValue ?
                         set1.maxValue : set2.maxValue;
    union_set.values = set1.values | set2.values;
    return union_set;
}

bitset bitset_difference(bitset set1, bitset set2) {
    bitset difference_set;
    difference_set.maxValue = set1.maxValue > set2.maxValue ?
                              set1.maxValue : set2.maxValue;
    difference_set.values = set1.values & ~set2.values;
    return difference_set;
}

bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    bitset symmetricDifference_set;

    symmetricDifference_set.maxValue =
            set1.maxValue > set2.maxValue ?
            set1.maxValue : set2.maxValue;

    symmetricDifference_set.values = set1.values & ~set2.values;
    symmetricDifference_set.values |= set2.values & ~set1.values;

    return symmetricDifference_set;
}

bitset bitset_complement(bitset set) {
    bitset complement;
    complement.values = ~set.values & ((1 << set.maxValue) - 1);
    complement.maxValue = set.maxValue;
    return complement;
}