#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"
#include <malloc.h>
#include "string.h"
#include "stdio.h"


void firstTask(matrix *m, size_t countRequests, size_t *requestsArray[]) {
    size_t row1, col1, row2, col2;
    for (size_t request = 0; request < countRequests; request++) {
        row1 = requestsArray[request][0];
        col1 = requestsArray[request][1];
        row2 = requestsArray[request][2];
        col2 = requestsArray[request][3];
        for (size_t idx_row = row1; idx_row <= row2; idx_row++)
            for (size_t idx_col = col1; idx_col <= col2; idx_col++)
                m->values[idx_row][idx_col]++;
    }
}

void test_firstTask() {
    matrix got = createMatrixFromArray((int[]) {
                                               0, 0, 0,
                                               0, 0, 0,
                                               0, 0, 0},
                                       3, 3);
    size_t count_requests = 2;
    size_t first_request[4] = {1, 1, 2, 2};
    size_t second_request[4] = {0, 0, 1, 1};
    size_t *requests[2] = {first_request, second_request};
    firstTask(&got, count_requests, requests);
    matrix expected = createMatrixFromArray((int[]) {
                                                    1, 1, 0,
                                                    1, 2, 1,
                                                    0, 1, 1},
                                            3, 3);

    assert(areTwoMatricesEqual(&got, &expected));
}



bool isIndex(size_t rows, size_t cols, int idx_row, int idx_col) {
    if (idx_row > -1 && idx_row < rows && idx_col > -1 && idx_col < cols)
        return true;

    return false;
}
size_t calculateCountNeighbors(matrix m, int idx_row, int idx_col, size_t
rows, size_t cols) {
    size_t count_neighbors = 0;
    for (int idx_row_math = idx_row - 1; idx_row_math < idx_row + 2; idx_row_math++) {
        for (int idx_col_math = idx_col - 1; idx_col_math < idx_col + 2; idx_col_math++) {
            if (isIndex(rows, cols, idx_row_math, idx_col_math) &&
                m.values[idx_row_math][idx_col_math] &&
                (idx_row != idx_row_math || idx_col != idx_col_math)) {
                count_neighbors++;
            }
        }
    }

    return count_neighbors;
}

int cellResultByPosition(matrix m, int idx_row, int idx_col, size_t countNeighbors) {
    return ((m.values[idx_row][idx_col] == 1 && (countNeighbors == 2 || countNeighbors == 3))
            || (m.values[idx_row][idx_col] == 0 && countNeighbors == 3));
}


void secondTask(matrix m, matrix *newM, size_t rows, size_t cols) {
    for (int idx_row = 0; idx_row < rows; idx_row++) {
        for (int idx_col = 0; idx_col < cols; idx_col++) {
            size_t count_neighbors =
                    calculateCountNeighbors(m, idx_row, idx_col, rows, cols);

            newM->values[idx_row][idx_col] =
                    cellResultByPosition(m, idx_row, idx_col, count_neighbors);
        }
    }
}

void test_secondTask() {
    size_t rows = 4;
    size_t cols = 3;
    matrix start = createMatrixFromArray((int[]) {
                                                 0, 1, 0,
                                                 0, 0, 1,
                                                 1, 1, 1,
                                                 0, 0, 0},
                                         4, 3);
    matrix got = getMemMatrix(rows, cols);
    secondTask(start, &got, rows, cols);
    matrix expected = createMatrixFromArray((int[]) {
                                                    0, 0, 0,
                                                    1, 0, 1,
                                                    0, 1, 1,
                                                    0, 1, 0},
                                            4, 3);

    assert(areTwoMatricesEqual(&got, &expected));
}



int sortedNumsCompare(const void *first_num, const void *second_num) {
    return (*(int *) first_num - *(int *) second_num);
}

void fillingNumFrameSorted(int *array, matrix m, size_t idx_row, size_t idx_col) {
    size_t arrayInd = 0;
    for (size_t midx_row = idx_row - 1; midx_row < idx_row + 2; midx_row++) {
        for (size_t midx_col = idx_col - 1; midx_col < idx_col + 2; midx_col++) {
            if (midx_row != idx_row || midx_col != idx_col)
                array[arrayInd++] = m.values[midx_row][midx_col];
        }
    }

    qsort(array, 8, sizeof(int), sortedNumsCompare);
}

void thirdTask(matrix *m, size_t size) {
    int frame[8];
    for (size_t idx_row = 1; idx_row < size - 1; idx_row++) {
        for (size_t idx_col = 1; idx_col < size - 1; idx_col++) {
            fillingNumFrameSorted(frame, *m, idx_row, idx_col);
            int median = (frame[3] + frame[4]) / 2;
            m->values[idx_row][idx_col] = median;
        }
    }
}

void test_thirdTask() {
    size_t size = 3;
    matrix got = createMatrixFromArray((int[]) {
                                               10, 20, 30,
                                               25, 35, 45,
                                               15, 25, 35},
                                       3, 3);
    thirdTask(&got, size);
    matrix expected = createMatrixFromArray((int[]) {
                                                    10, 20, 30,
                                                    25, 25, 45,
                                                    15, 25, 35},
                                            3, 3);

    assert(areTwoMatricesEqual(&got, &expected));
}




typedef struct domain {
    size_t visits;
    char name[200];
} domain;

size_t searchDomainInResults(const domain results[], size_t size, char *s) {
    for
            (size_t ind = 0; ind < size; ind++) {
        if (strcmp(results[ind].name, s) == 0) {
            return ind;
        }
    }
    return size;
}

bool searchNumFromArray(const size_t array[], size_t length, size_t num) {
    for (size_t ind = 0; ind < length; ind++) {
        if (num == array[ind])
            return true;
    }

    return false;
}

void handlerDotPrtNotNull(domain *array, size_t ind, char *dotPtr,
                          domain results[], size_t *sizeResult) {
    strcpy(array[ind].name, dotPtr + 1);
    size_t pos = searchDomainInResults(results, *sizeResult, array[ind].name);
    if (pos == *sizeResult) {
        results[*sizeResult] = array[ind];
        *sizeResult += 1;
    } else {
        results[pos].visits += array[ind].visits;
    }
}

void outputResultDomains(domain *results, size_t size) {
    for (size_t ind = 0; ind < size; ind++) {
        printf("%zd %s\n", results[ind].visits, results[ind].name);
    }
}

void fourthTask(domain array[], size_t size) {
    size_t close_idxs[size];
    size_t count_close = 0;
    domain results[200];
    size_t size_res = 0;

    for (size_t ind = 0; ind < size; ind++)
        results[size_res++] = array[ind];

    while (count_close != size) {
        for (size_t ind = 0; ind < size; ind++) {
            if (!searchNumFromArray(close_idxs, count_close, ind)) {
                char *dot_ptr;
                dot_ptr = strchr(array[ind].name, '.');

                if (dot_ptr != NULL)
                    handlerDotPrtNotNull(array, ind, dot_ptr, results, &size_res);
                else
                    close_idxs[count_close++] = ind;
            }
        }
    }

    outputResultDomains(results, size_res);
}

void test_fourthTask() {
    size_t size = 4;
    domain array[4] = {{900, "google.mail.com"},
                       {50,  "yahoo.com"},
                       {1,   "intel.mail.com"},
                       {5,   "wiki.org"}};

    fourthTask(array, size);
}



int main() {

    test_firstTask();
    test_secondTask();
    test_thirdTask();
    test_fourthTask();

    return 0;
}