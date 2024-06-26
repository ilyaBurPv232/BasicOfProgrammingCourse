#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"
#include <malloc.h>
#include "string.h"
#include "stdio.h"
#include "libs/data_structures/vector/vector.h"
#include <conio.h>


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


void fillingCalcMatrix(matrix m, matrix *calc_matrix, size_t rows, size_t cols) {
    for (size_t idx_row = 0; idx_row < rows; idx_row++) {
        for (size_t idx_col = 0; idx_col < cols; idx_col++) {
            if (m.values[idx_row][idx_col] == 1) {
                if (idx_row != 0) {
                    calc_matrix->values[idx_row][idx_col] =
                            calc_matrix->values[idx_row - 1][idx_col] + 1;
                } else {
                    calc_matrix->values[idx_row][idx_col] = 1;
                }
            } else {
                calc_matrix->values[idx_row][idx_col] = 0;
            }
        }
    }
}

void fifthTask(matrix m, size_t rows, size_t cols, size_t *result) {
    matrix calc_matrix = getMemMatrix(rows, cols);
    fillingCalcMatrix(m, &calc_matrix, rows, cols);
    size_t calc_res = 0;
    for (size_t idx_col = 0; idx_col < cols; idx_col++) {
        for (size_t idx_row = 0; idx_row < rows; idx_row++) {
            for (size_t idx_k = idx_col + 1; idx_k < cols + 1; idx_k++) {
                int min = calc_matrix.values[idx_row][idx_col];

                for (size_t indFromColToK = idx_col; indFromColToK < idx_k; indFromColToK++) {
                    if (calc_matrix.values[idx_row][indFromColToK] < min)
                        min = calc_matrix.values[idx_row][indFromColToK];
                }

                calc_res += min;
            }
        }
    }

    *result = calc_res;
}

void test_fifthTask() {
    size_t rows1 = 3;
    size_t cols1 = 3;
    matrix m1 = createMatrixFromArray((int[]) {
                                              1, 0, 1,
                                              1, 1, 0,
                                              1, 1, 0},
                                      3, 3);
    size_t result1 = 0;
    fifthTask(m1, rows1, cols1, &result1);

    assert(result1 == 13);

    size_t rows2 = 3;
    size_t cols2 = 4;
    matrix m2 = createMatrixFromArray((int[]) {
                                              0, 1, 1, 0,
                                              0, 1, 1, 1,
                                              1, 1, 1, 0},
                                      3, 4);
    size_t result2 = 0;
    fifthTask(m2, rows2, cols2, &result2);

    assert(result2 == 24);
}


void sixthTask(const char *s, size_t length, char *result, size_t *res_len) {
    char buffer[10];
    size_t buffer_len = 0;
    size_t calc_res_len = 0;
    char num = '1';
    for (size_t idx = 0; idx < length; idx++) {
        buffer[buffer_len++] = num++;
        if (s[idx] == 'I')
            while (buffer_len > 0)
                result[calc_res_len++] = buffer[--buffer_len];
    }

    buffer[buffer_len++] = num;
    while (buffer_len > 0)
        result[calc_res_len++] = buffer[--buffer_len];

    result[calc_res_len] = '\0';

    *res_len = calc_res_len;
}

void test_sixthTask() {
    char s1[10] = "IIIDIDDD";
    size_t length1 = 8;
    char got1[10];
    size_t resLength1;
    sixthTask(s1, length1, got1, &resLength1);
    char expected1[10] = "123549876";

    assert(strcmp(got1, expected1) == 0);

    char s2[5] = "DDD";
    size_t length2 = 3;
    char got2[5];
    size_t resLength2;
    sixthTask(s2, length2, got2, &resLength2);
    char expected2[10] = "4321";

    assert(strcmp(got2, expected2) == 0);
}


typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} node;

node *createNode(int k) {
    node *new_node = (node *) malloc(sizeof(node));
    new_node->key = k;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

int searchMaxIdx(const int array[], int start, int end) {
    if (start > end) {
        return end + 1;
    } else {
        int max_num_idx = start;
        for (int ind = start + 1; ind <= end; ind++) {
            if (array[ind] > array[max_num_idx])
                max_num_idx = ind;
        }

        return max_num_idx;
    }
}

node *insert(node *p, int k, bool isLeft) {
    node *new_node = createNode(k);
    if (isLeft)
        p->left = new_node;
    else
        p->right = new_node;

    return new_node;
}

void buildNodes(node *p, int array[], int start, int end, bool isLeft) {
    int max_num_idx = searchMaxIdx(array, start, end);
    if (max_num_idx == end + 1) {
        if (isLeft)
            p->left = NULL;
        else
            p->right = NULL;

        printf("null ");

        return;
    } else {
        printf("%d ", array[max_num_idx]);
        node *new_node = insert(p, array[max_num_idx], isLeft);
        buildNodes(new_node, array, start, max_num_idx - 1, true);
        buildNodes(new_node, array, max_num_idx + 1, end, false);
    }
}

void seventhTask(int array[], int lengthArray) {
    if (lengthArray == 0) {
        return;
    } else {
        int maxNumInd = searchMaxIdx(array, 0, lengthArray - 1);
        node *newNode = createNode(array[maxNumInd]);
        printf("%d ", array[maxNumInd]);

        buildNodes(newNode, array, 0, maxNumInd - 1, true);
        buildNodes(newNode, array, maxNumInd + 1, lengthArray - 1, false);

        printf("\n");
    }
}

void test_seventhTask() {
    int array1[6] = {3, 2, 1, 6, 0, 5};
    int len1 = 6;

    seventhTask(array1, len1);

    int array2[3] = {3, 2, 1};
    int len2 = 3;

    seventhTask(array2, len2);
}


void eighthTask(const char *s, size_t length,
                const size_t indexes[], char *new_s) {
    for (size_t ind = 0; ind < length; ind++) {
        new_s[ind] = s[indexes[ind]];
    }

    new_s[length] = '\0';
}

void test_eighthTask() {
    char s1[4] = "abc";
    size_t lengthS1 = 3;
    size_t indexes1[3] = {0, 1, 2};
    char got1[4];
    eighthTask(s1, lengthS1, indexes1, got1);
    char expected1[4] = "abc";

    assert(strcmp(got1, expected1) == 0);

    char s2[5] = "abap";
    size_t lengthS2 = 4;
    size_t indexes2[4] = {0, 3, 2, 1};
    char got2[5];
    eighthTask(s2, lengthS2, indexes2, got2);
    char expected2[5] = "apab";

    assert(strcmp(got2, expected2) == 0);
}


FILE *openFile(char *fileName, char *action) {
    FILE *file = fopen(fileName, action);
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        exit(1);
    }

    return file;
}

void fillingFile(int nums_arr[], size_t len, char *fileName) {
    FILE *file = openFile(fileName, "w");
    for (size_t ind = 0; ind < len; ind++) {
        fprintf(file, "%d ", nums_arr[ind]);
    }

    fclose(file);
}

void readingNumsFilteringAndWriting(vector *v, char *rFileName, int
controlNum, char *wFileName) {
    FILE *rFile = openFile(rFileName, "r");
    FILE *wFile = openFile(wFileName, "w");
    int num;
    while (fscanf(rFile, "%d", &num) == 1) {
        if (num < controlNum) {
            pushBack(v, num);
            fprintf(wFile, "%d ", num);
        }
    }

    fclose(rFile);
    fclose(wFile);
}

void ninthTask(int numsArray[], size_t lengthArray, int controlNum, char
*firstFileName, char *secondFileName, vector *v) {
    fillingFile(numsArray, lengthArray, firstFileName);
    readingNumsFilteringAndWriting(v, firstFileName, controlNum,
                                   secondFileName);

    shrinkToFit(v);
}

void test_ninthTask() {
    int num_arr[5] = {2, 4, 1, 3, 5};
    size_t lengthArray = 5;
    int control_num = 3;
    char *firstFileName = "../firstFile.txt";
    char *secondFileName = "../secondFile.txt";
    vector v = createVector(10);
    ninthTask(num_arr, lengthArray, control_num, firstFileName, secondFileName, &v);
    size_t exp_len = 2;
    int exp_arr[2] = {2, 1};

    assert(exp_len == v.size);

    for (size_t ind = 0; ind < exp_len; ind++) {
        assert(v.data[ind] == exp_arr[ind]);
    }
}


void fillingFileWithText(char *fileName, char *text) {
    FILE *file = openFile(fileName, "w");

    fprintf(file, "%s", text);

    fclose(file);
}

void tenthTask(char *fileName, size_t count_output_lines, char *text) {
    fillingFileWithText(fileName, text);
    FILE *file = openFile(fileName, "r");
    char line[127];
    size_t count = 0;
    while (fgets(line, 127, file) != NULL) {
        printf("%s", line);
        count++;
        if (count == count_output_lines) {
            printf("Please, press Ctrl + C\n");
            while (getch() != 3);
        }
    }
}

void test_tenthTask() {
    char *fileName = "../tenthTask.txt";
    size_t count_output_lines = 3;
    char text[200] = "123\n456\n789\n0";

    tenthTask(fileName, count_output_lines, text);
}


void eleventhTask(char **dict, char **requests, int *num_in_req, int n, int q) {
/**
    int n, q;
    scanf("%d %d", &n, &q);
    char dict[n][100], requests[q][100];
    for (int i = 0; i < n; ++i)
        scanf("%s", dict[i]);

    int num_in_req[q];
    for (int i = 0; i < q; ++i)
        scanf("%d %s", &num_in_req[i], requests[i]);
**/
    int temp_pepe = 0;
    int temp_pepe2 = 0;
    for (int i = 0; i < q; ++i) {
        for (int j = 0; j < n; ++j) {
            if (strstr(dict[j], requests[i]) != NULL) {
                temp_pepe++;
                temp_pepe2++;
            } else
                temp_pepe++;

            if (temp_pepe2 == num_in_req[i]) {
                printf("%d\n", temp_pepe);
                break;
            }
        }

        if (num_in_req[i] > temp_pepe2) {
            printf("-1\n");
            temp_pepe = 0;
            temp_pepe2 = 0;
        } else {
            temp_pepe = 0;
            temp_pepe2 = 0;
        }
    }
}


void test_eleventhTask() {
    int n = 10;
    int q = 3;
    char *dict[100] = {"aa", "aaa", "aab", "ab", "abc", "ac",
                       "ba", "daa", "dab", "dadba"};
    char *requests[100] = {"a", "da", "da"};
    int num_in_req[3] = {4, 2, 4};

    eleventhTask(dict, requests, num_in_req, n, q);
}


int main() {

    test_firstTask();
    test_secondTask();
    test_thirdTask();
    test_fourthTask();
    test_fifthTask();
    test_sixthTask();
    test_seventhTask();
    test_eighthTask();
    test_ninthTask();
    test_eleventhTask();
    test_tenthTask();

    return 0;
}