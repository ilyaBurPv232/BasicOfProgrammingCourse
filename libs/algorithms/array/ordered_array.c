#include <malloc.h>
#include <stdlib.h>
#include "ordered_array.h"


ordered_array_set ordered_array_set_create(size_t capacity) {
    ordered_array_set set;
    set.data = malloc(capacity * sizeof(int)); // выделение памяти для массива элементов
    set.size = 0; // инициализация размера множества
    set.capacity = capacity; // установка максимального количества элементов
    return set;
}

// Уменьшает размер внутреннего массива данных unordered_array_set до его фактического размера.
// Если размер внутреннего массива данных не равен его текущей ёмкости,
// то происходит перевыделение памяти под массив данных так, чтобы его ёмкость равнялась его фактическому размеру.
static void ordered_array_set_shrink_in_size(ordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set set = ordered_array_set_create(size);

    for (size_t i = 0; i < size; i++) {
        ordered_array_set_insert(&set, a[i]);
    }

    ordered_array_set_shrink_in_size(&set);

    return set;
}

bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size != set2.size)
        return false;
    return memcmp(set1.data, set2.data, sizeof(int) * set1.size) == 0;
}

void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (ordered_array_set_in(set, value) == set->size) {
        ordered_array_set_isAbleAppend(set);
        append_(set->data, &set->size, value);
    }
}

bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    for (size_t i = 0; i < subset.size; i++) {
        bool found = false;

        for (size_t j = 0; j < set.size; j++)
            if (subset.data[i] == set.data[j]) {
                found = true;
                break;
            }

        if (!found)
            return false;
    }

    return true;
}

ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result;
    result.size = 0;
    result.capacity = set1.capacity;

    result.data = malloc(result.capacity * sizeof(int));
    if (result.data == NULL) {

        result.capacity = 0;
        return result;
    }

    size_t i = 0;
    size_t j = 0;

    while (i < set1.size && j < set2.size) {
        if (set1.data[i] < set2.data[j]) {
            i++;
        } else if (set1.data[i] > set2.data[j]) {
            j++;
        } else {
            result.data[result.size++] = set1.data[i];
            i++;
            j++;
        }
    }

    return result;
}

ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result;
    result.data = malloc((set1.size + set2.size) * sizeof(int));
    result.size = set1.size;
    result.capacity = set1.size + set2.size;

    memcpy(result.data, set1.data, set1.size * sizeof(int));

    for (size_t i = 0; i < set2.size; ++i) {
        int element = set2.data[i];
        int found = 0;
        for (size_t j = 0; j < set1.size; ++j) {
            if (element == set1.data[j]) {
                found = 1;
                break;
            }
        }
        if (!found) {
            result.data[result.size] = element;
            result.size++;
        }
    }

    return result;
}

ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set difference_set;
    difference_set.capacity = set1.capacity; // емкость разности множеств будет равна емкости set1
    difference_set.data = malloc(difference_set.capacity * sizeof(int)); // выделение памяти для разности множеств

    size_t i = 0; // индекс для перебора set1
    size_t j = 0; // индекс для перебора set2
    size_t k = 0; // индекс для записи элементов в разность множеств

    // сравниваем элементы set1 и set2 и записываем элементы, которые есть в set1 и отсутствуют в set2, в разность множеств
    while (i < set1.size && j < set2.size) {
        if (set1.data[i] < set2.data[j]) {
            difference_set.data[k++] = set1.data[i++];
        } else if (set1.data[i] > set2.data[j]) {
            j++;
        } else {
            i++;
            j++;
        }
    }

    while (i < set1.size) {
        difference_set.data[k++] = set1.data[i++];
    }

    difference_set.size = k;

    return difference_set;
}

void ordered_array_set_isAbleAppend(ordered_array_set *set) {
    assert(set->size < set->capacity);
}

size_t ordered_array_set_in(ordered_array_set *set, int value) {
    return binarySearch_(set->data, set->size, value);
}

void ordered_array_set_print(ordered_array_set set) {
    printf("{");
    int is_empty = 1;

    for (size_t i = 0; i < set.size; i++) {
        printf("%d, ", *(set.data + i));
        is_empty = 0;
    }
    if (is_empty)
        printf("}\n");
    else
        printf("\b\b}\n");
}

ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set result;
    result.size = 0;
    result.capacity = set1.size + set2.size;
    result.data = (int *) malloc(result.capacity * sizeof(int));

    for (size_t i = 0; i < set1.size; i++) {
        int value = set1.data[i];
        int found = 0;

        for (size_t j = 0; j < set2.size; j++) {
            if (set2.data[j] == value) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result.data[result.size] = value;
            result.size++;
        }
    }

    for (size_t i = 0; i < set2.size; i++) {
        int value = set2.data[i];
        int found = 0;

        for (size_t j = 0; j < set1.size; j++) {
            if (set1.data[j] == value) {
                found = 1;
                break;
            }
        }

        if (!found) {
            result.data[result.size] = value;
            result.size++;
        }
    }

    return result;
}

ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    size_t new_capacity = universumSet.size;
    ordered_array_set set_complement = ordered_array_set_create(new_capacity);
    size_t i = 0, j = 0;
    while (i < universumSet.size) {
        if (j < set.size && universumSet.data[i] == set.data[j]) {
            i++;
            j++;
        } else {
            set_complement.data[set_complement.size] = universumSet.data[i];
            set_complement.size++;
            i++;
        }
    }
    ordered_array_set_shrink_in_size(&set_complement);
    assert(ordered_array_set_isSubset(set_complement, universumSet));

    return set_complement;
}

void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t index = ordered_array_set_in(set, value);

    if (index != set->size) {
        deleteByPosSaveOrder_(set->data, &set->size, index);
    }
}

// освобождает память, занимаемую множеством set
void ordered_array_set_delete(ordered_array_set *set) {
    free(set->data);
    set->data = NULL;
    set->size = 0;
    set->capacity = 0;
}