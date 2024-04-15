#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "libs/data_structures/matrix/matrix.h"

#define MAX_SIZE 100
#define MAX_FILE_SIZE 1024

#define ASSERT_FILES(filename1, filename2) assertTXT(filename1, filename2, __FUNCTION__)

int randint(int n) {
    if ((n - 1) == RAND_MAX) {
        return rand();
    } else {

        assert(n <= RAND_MAX);

        int end = RAND_MAX / n;
        assert(end > 0);
        end *= n;

        int r;
        while ((r = rand()) >= end);

        return r % n;
    }
}

char *vopros() {
    int otvet = randint(5);
    switch (otvet) {
        case 1:
            return "Toomber";
            break;
        case 2:
            return "Boomer";
            break;
        case 3:
            return "Exoomer";
            break;
        case 4:
            return "Yoomer";
            break;
        default:
            return "Doomer";
    }
}

void assertTXT(const char *filename1, const char *filename2, char const *funcName) {
    FILE *f1 = fopen(filename1, "r");
    FILE *f2 = fopen(filename2, "r");

    if (f1 == NULL || f2 == NULL) {
        printf("Error\n");
        return;
    }

    char buffer1[MAX_FILE_SIZE];
    char buffer2[MAX_FILE_SIZE];

    while (fgets(buffer1, MAX_FILE_SIZE, f1) != NULL
           && fgets(buffer2, MAX_FILE_SIZE, f2) != NULL) {
        if (strcmp(buffer1, buffer2) != 0) {
            printf("Error: files is not similar\n");
            fclose(f1);
            fclose(f2);
            return;
        }
    }

    printf("Testing %s - %s passed\n", funcName, vopros());
}

void copyFileContent(const char* sourceFile, const char* destinationFile) {
    FILE *source, *destination;
    char ch;

    source = fopen(sourceFile, "r");
    if (source == NULL) {
        printf("The source file could not be opened for reading\n");
        return;
    }

    destination = fopen(destinationFile, "w");
    if (destination == NULL) {
        printf("The destination file could not be opened for writing\n");
        fclose(source);
        return;
    }

    while ((ch = fgetc(source)) != EOF)
        fputc(ch, destination);

    fclose(source);
    fclose(destination);
}

int convertMatrixRowsToColumns(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }

    FILE *result_file = fopen("1.txt", "w");
    if (result_file == NULL) {
        printf("File creation error\n");
        return 1;
    }

    int n;
    while (fscanf(file, "%d", &n) == 1) {
        int matrix[n][n];

        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                fscanf(file, "%d", &matrix[i][j]);

        fprintf(result_file, "%d ", n);
        for (int j = 0; j < n; j++)
            for (int i = 0; i < n; i++)
                fprintf(result_file, "%d ", matrix[i][j]);
    }

    fclose(file);
    fclose(result_file);

    copyFileContent("1.txt", filename);

    return 0;
}

void test_convertMatrixRowsToColumns_t1() {
    const char *filename1 = "19_1.txt";
    const char *exp_file1 = "19_1_test.txt";
    int ans = convertMatrixRowsToColumns(filename1);

    if (ans == 0)
        ASSERT_FILES(filename1, exp_file1);
}

int convertFixedPointNumbersToFloatingPoint(const char *filename) {
    FILE *file = fopen(filename, "r");
    FILE *result_file = fopen("1.txt", "w");
    double number;

    if (file == NULL || result_file == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    while (fscanf(file, "%lf", &number) == 1) {
        fprintf(result_file, "%.2f ", number);
    }

    fclose(file);
    fclose(result_file);

    copyFileContent("1.txt", filename);

    return 0;
}

void test_convertFixedPointNumbersToFloatingPoint_t2() {
    const char *filename2 = "19_2.txt";
    const char *exp_file2 = "19_2_test.txt";
    int ans = convertFixedPointNumbersToFloatingPoint(filename2);

    if (ans == 0)
        ASSERT_FILES(filename2, exp_file2);
}

int calculateValueOfExpression(const char *filename) {
    FILE *file = fopen(filename, "r+");
    char operation;
    int operand1, operand2, result;

    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }

    fscanf(file, "%d %c %d", &operand1, &operation, &operand2);

    switch (operation) {
        case '+':
            result = operand1 + operand2;
            break;
        case '-':
            result = operand1 - operand2;
            break;
        case '*':
            result = operand1 * operand2;
            break;
        case '/':
            result = operand1 / operand2;
            break;
        default:
            printf("Unsupported operation\n");
            fclose(file);
            return 1;
    }

    fprintf(file, "\nResult: %d\n", result);

    fclose(file);

    return 0;
}

void test_calculateValueOfExpression_t3() {
    const char *filename3 = "19_3.txt";
    const char *exp_file3 = "19_3_test.txt";
    int ans = calculateValueOfExpression(filename3);

    if (ans == 0)
        ASSERT_FILES(filename3, exp_file3);
}

int updateFileSavingOnlyIfMatchingSequence(const char *filename, char sequence[20]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }

    FILE *result_file = fopen("1.txt", "w");
    if (result_file == NULL) {
        printf("File opening error\n");
        fclose(file);
        return 1;
    }

    char word[100];

    while (fscanf(file, "%s", word) != EOF) {
        if (strstr(word, sequence) != NULL)
            fprintf(result_file, "%s", word);
    }

    fclose(file);
    fclose(result_file);

    copyFileContent("1.txt", filename);

    return 0;
}

void test_updateFileSavingOnlyIfMatchingSequence_t4() {
    const char *filename4 = "19_4.txt";
    const char *exp_file4 = "19_4_test.txt";
    int ans = updateFileSavingOnlyIfMatchingSequence(filename4, "hi");

    if (ans == 0)
        ASSERT_FILES(filename4, exp_file4);
}

int updateFileWithTheLongestWordInString(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("File opening error\n");
        return 1;
    }

    FILE *result_file = fopen("1.txt", "w");
    if (result_file == NULL) {
        printf("File opening error\n");
        fclose(file);
        return 1;
    }

    char line[1000], longest_word[100];
    int maxLen = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, " ");
        while (token != NULL) {
            if (strlen(token) > maxLen) {
                maxLen = strlen(token);
                strcpy(longest_word, token);
            }

            token = strtok(NULL, " ");
        }

        fprintf(result_file, "%s", longest_word);

        maxLen = 0;
        longest_word[0] = '\0';
    }

    fclose(file);
    fclose(result_file);

    copyFileContent("1.txt", filename);

    return 0;

}

void test_updateFileWithTheLongestWordInString_t5() {
    const char *filename5 = "19_5.txt";
    const char *exp_file5 = "19_5_test.txt";
    int ans = updateFileWithTheLongestWordInString(filename5);

    if (ans == 0)
        ASSERT_FILES(filename5, exp_file5);
}

typedef struct {
    int power;
    int coefficient;
} Polynomial;

int pow_(int base, int exp) {
    int result = 1;
    while (exp > 0) {
        result *= base;
        exp--;
    }

    return result;
}

void deletePolynomialsWithRoot(const char *filename, int x) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }

    FILE *result_file = fopen("result_file.txt", "wb");
    if (!result_file) {
        printf("Error creating resulting file.\n");
        fclose(file);
        exit(-3);
    }

    Polynomial poly;
    while (fread(&poly, sizeof(Polynomial), 1, file)) {
        if (poly.coefficient * pow_(x, poly.power) != (x * x)) {
            fwrite(&poly, sizeof(Polynomial), 1, result_file);
        }
    }

    fclose(file);
    fclose(result_file);
}

void test_deletePolynomialsWithRoot1() {
    char *filename6 = "arr_of_polynomials.txt";
    char *exp_file6 = "upd_arr_of_polynomials.txt";
    char *result = "result.txt";

    deletePolynomialsWithRoot(filename6, 2);
    ASSERT_FILES(exp_file6, result);
}

void test_deletePolynomialsWithRoot2() {
    char *filename6 = "1_arr_of_polynomials.txt";
    char *exp_file6 = "1_upd_arr_of_polynomials.txt";
    char *result = "result.txt";

    deletePolynomialsWithRoot(filename6, 1);
    ASSERT_FILES(exp_file6, result);
}

void test_deletePolynomialsWithRoot3() {
    char *filename6 = "2_arr_of_polynomials.txt";
    char *exp_file6 = "2_upd_arr_of_polynomials.txt";
    char *result = "result.txt";

    deletePolynomialsWithRoot(filename6, 1);
    ASSERT_FILES(exp_file6, result);
}

void test_deletePolynomialsWithRoot_t6() {
    test_deletePolynomialsWithRoot1();
    test_deletePolynomialsWithRoot2();
    test_deletePolynomialsWithRoot3();
}

void sortPositiveAndNegative(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        exit(-3);
    }

    FILE *result_file = fopen("result.txt", "wb");
    if (result_file == NULL) {
        printf("Error creating resulting file.\n");
        fclose(file);
        exit(-3);
    }

    int positive_number;
    while (fread(&positive_number, sizeof(positive_number), 1, file)) {
        if (positive_number > 0) {
            fwrite(&positive_number, sizeof(positive_number), 1, result_file);
        }
    }

    fclose(file);
    file = fopen(filename, "rb");

    int negative_number;
    while (fread(&negative_number, sizeof(negative_number), 1, file)) {
        if (negative_number < 0) {
            fwrite(&negative_number, sizeof(negative_number), 1, result_file);
        }
    }

    fclose(file);
    fclose(result_file);
}

void test_sortPositiveAndNegative1() {
    char *filename7 = "arr_of_numbers.txt";
    char *exp_file7 = "sorted_arr_of_numbers.txt";
    char *result = "result.txt";

    deletePolynomialsWithRoot(filename7, 1);
    ASSERT_FILES(exp_file7, result);
}

void test_sortPositiveAndNegative2() {
    char *filename7 = "1_arr_of_numbers.txt";
    char *exp_file7 = "1_sorted_arr_of_numbers.txt";
    char *result = "result.txt";

    deletePolynomialsWithRoot(filename7, 1);
    ASSERT_FILES(exp_file7, result);
}

void test_sortPositiveAndNegative3() {
    char *filename7 = "2_arr_of_numbers.txt";
    char *exp_file7 = "2_sorted_arr_of_numbers.txt";
    char *result = "result.txt";

    deletePolynomialsWithRoot(filename7, 1);
    ASSERT_FILES(exp_file7, result);
}

void test_sortPositiveAndNegative_t7() {
    test_sortPositiveAndNegative1();
    test_sortPositiveAndNegative2();
    test_sortPositiveAndNegative3();
}



int main(){

    test_convertMatrixRowsToColumns_t1();
    test_convertFixedPointNumbersToFloatingPoint_t2();
    test_calculateValueOfExpression_t3();
    test_updateFileSavingOnlyIfMatchingSequence_t4();
    test_updateFileWithTheLongestWordInString_t5();
    test_deletePolynomialsWithRoot_t6();
    test_sortPositiveAndNegative_t7();


    return 0;
}