#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "string_.h"

char _stringBuffer[MAX_STRING_SIZE + 1];

BagOfWords _bag;
BagOfWords _bag2;

size_t strlen_(const char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;
    return end - begin;
}

char *strpbrk_(const char *str, const char *delim) {
    const char *ptr = str;

    while (*ptr != '\0') {
        const char *d = delim;
        while (*d != '\0') {
            if (*ptr == *d) {
                return (char *) ptr;
            }
            d++;
        }
        ptr++;
    }

    return NULL;
}

char *strtok_(char *str, const char *delim) {
    static char *savedToken = NULL;

    if (str != NULL) {
        savedToken = str;
    }

    if (savedToken == NULL) {
        return NULL;
    }

    char *tokenStart = savedToken;
    char *tokenEnd = strpbrk_(savedToken, delim);

    if (tokenEnd != NULL) {
        *tokenEnd = '\0';
        savedToken = tokenEnd + 1;
    } else {
        savedToken = NULL;
    }

    return tokenStart;
}

char *strcat_(char *dest, const char *src) {
    char *ptr = dest;

    while (*ptr != '\0') {
        ptr++;
    }

    while (*src != '\0') {
        *ptr = *src;
        ptr++;
        src++;
    }

    *ptr = '\0';

    return dest;
}

void strcpy_(char *dest, const char *src) {
    while (*src) {
        *dest = *src;
        dest++;
        src++;
    }

    *dest = '\0';
}

char *strncpy_(char *destination, const char *source, size_t num) {
    char *start = destination;

    while (num && (*destination++ = *source++)) {
        num--;
    }

    if (num) {
        while (--num) {
            *destination++ = '\0';
        }
    }

    return start;
}

int strncmp_(const char *s1, const char *s2, size_t n) {
    while (n--) {
        if (*s1 != *s2) {
            return (unsigned char) *s1 - (unsigned char) *s2;
        }
        if (*s1 == '\0') {
            return 0;
        }
        s1++;
        s2++;
    }
    return 0;
}


char *find(char *begin, char *end, int ch) {
    while (begin != end && *begin != ch)
        begin++;
    return begin;
}

char *findNonSpace(char *begin) {
    while (*begin != '\0' && isspace(*begin)) {
        begin++;
    }
    return begin;
}

char *findSpace(char *begin) {
    while (*begin != '\0' && !isspace(*begin)) {
        begin++;
    }
    return begin;
}

char *findNonSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && isspace(*rbegin))
        rbegin--;

    return rbegin;
}

char *findSpaceReverse(char *rbegin, const char *rend) {
    while (rbegin >= rend && !isspace(*rbegin))
        rbegin--;

    return rbegin;
}

char *copy(const char *beginSource, const char *endSource, char
*beginDestination) {
    size_t size = endSource - beginSource;
    memcpy(beginDestination, beginSource, size);

    //*(beginDestination + size) = '\0';

    return beginDestination + size;
}

char *copyIf(char *beginSource, const char *endSource, char
*beginDestination, int (*f)(int)) {
    while (beginSource != endSource) {
        if (f(*beginSource)) {
            *beginDestination = *beginSource;
            beginDestination++;
        }
        beginSource++;
    }

    //*beginDestination = '\0';

    return beginDestination;
}

char *copyIfReverse(char *rbeginSource, const char *rendSource, char
*beginDestination, int (*f)(int)) {
    char *rbeginDest = beginDestination;
    while (rbeginSource >= rendSource) {
        if (f(*rbeginSource)) {
            *rbeginDest = *rbeginSource;
            rbeginDest++;
        }
        rbeginSource--;
    }

    //*rbeginDest = '\0';

    return rbeginDest;
}

void assertString(const char *expected, char *got,
                  char const *fileName, char const *funcName,
                  int line) {
    if (strcmp(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else
        fprintf(stderr, "%s - OK\n", funcName);
}


void removeExtraSpaces(char *s) {
    int i, j;

    for (i = 0, j = 0; s[i]; i++) {
        if (s[i] != ' ' || (i > 0 && s[i - 1] != ' ')) {
            s[j++] = s[i];
        }
    }

    s[j] = '\0';
}


void removeAdjacentEqualLetters(char *s) {
    if ((s == NULL || strlen(s) == 0))
        return;

    int i, j;

    for (i = 0, j = 0; s[i] != '\0'; i++) {
        if (s[i] != s[i + 1]) {
            s[j] = s[i];
            j++;
        }
    }
    s[j] = '\0';
}

int getWord(char *beginSearch, WordDescriptor *word) {
    word->begin = findNonSpace(beginSearch);
    if (*word->begin == '\0')
        return 0;
    word->end = findSpace(word->begin);
    return 1;
}


char *getEndOfString(char *begin) {
    char *end = begin;
    while (*end != '\0')
        end++;

    return end;
}

void removeNonLetters(char *s) {
    char *endSource = getEndOfString(s);
    char *destination = copyIf(s, endSource, s, isgraph);
    *destination = '\0';
}

void reversedDigitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);

    char *recPosition = copyIfReverse(endStringBuffer - 1,
                                      _stringBuffer - 1,
                                      word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}

void digitToStart(WordDescriptor word) {
    char *endStringBuffer = copy(word.begin, word.end,
                                 _stringBuffer);

    char *recPosition = copyIf(_stringBuffer,
                               endStringBuffer,
                               word.begin, isdigit);
    copyIf(_stringBuffer, endStringBuffer, recPosition, isalpha);
}


void digitsToStart(char *s) {
    char *beginSearch = s;
    WordDescriptor word;
    while (getWord(beginSearch, &word)) {

        digitToStart(word);
        beginSearch = word.end;
    }
}

int getWordReverse(char *rbegin, char *rend, WordDescriptor *word) {
    word->end = findNonSpaceReverse(rbegin, rend);
    if (*word->begin == *rend)
        return 0;

    word->begin = findSpaceReverse(word->end, rend);
    word->begin++;

    return 1;
}

void replaceDigitsToNumOfSpaces(char *s) {

    copy(s, getEndOfString(s), _stringBuffer);

    char *recPtr = s;

    char *readPtr = _stringBuffer;

    for (int i = 0; i < strlen_(_stringBuffer); ++i) {
        if (strlen_(s) >= MAX_STRING_SIZE) {
            fprintf(stderr, "Out of MAX_STRING_SIZE");
            exit(1);
        }

        if (!isdigit(_stringBuffer[i])) {
            *recPtr = *readPtr;
            recPtr++;
            readPtr++;

        } else {
            int counter = _stringBuffer[i] - '0';
            for (int j = counter; j > 0; --j) {
                *recPtr = ' ';
                recPtr++;
            }
            readPtr++;
        }
    }
    _stringBuffer[0] = '\0';
    *recPtr = '\0';

}

void replace(char *source, char *w1, char *w2) {
    size_t w1Size = strlen_(w1);
    size_t w2Size = strlen_(w2);
    WordDescriptor word1 = {w1, w1 + w1Size};
    WordDescriptor word2 = {w2, w2 + w2Size};
    char *readPtr, *recPtr;

    if (w1Size >= w2Size) {
        readPtr = source;
        recPtr = source;
    } else {
        copy(source, getEndOfString(source), _stringBuffer);
        readPtr = _stringBuffer;
        recPtr = source;
    }

    while (*readPtr != '\0') {
        if (memcmp(readPtr, w1, w1Size) == 0) {
            for (int i = 0; i < w2Size; ++i) {
                *recPtr = w2[i];
                recPtr++;
            }

            readPtr += w1Size;

        } else {
            *recPtr = *readPtr;
            readPtr++;
            recPtr++;
        }
    }

    *recPtr = '\0';
}

bool areWordsEqual(WordDescriptor w1, WordDescriptor w2) {
    char *ptr1 = w1.begin;
    char *ptr2 = w2.begin;
    while (ptr1 <= w1.end && ptr2 <= w2.end) {
        if (*ptr1 != *ptr2)
            return false;

        ptr1++;
        ptr2++;
    }

    if (ptr1 > w1.end && ptr2 > w2.end)
        return true;
    else
        return false;
}

bool areWordsOrdered(char *s) {
    WordDescriptor word1;
    WordDescriptor word2;
    if (getWord(s, &word1)) {
        word2 = word1;
        while (getWord(s, &word1)) {
            if (areWordsEqual(word1, word2) < 0)
                return false;
            word2 = word1;
            s = word1.end;
        }

        return true;
    } else
        return true;
}

void getBagOfWords(BagOfWords *bag, char *s) {
    WordDescriptor word;
    bag->size = 0;
    while (getWord(s, &word)) {
        bag->words[bag->size] = word;
        bag->size++;
        s = word.end;
    }
}

char *copyReverse(char *rbeginSource, const char *rendSource, char
*beginDestination) {
    while (rbeginSource != rendSource)
        (*beginDestination++) = *rbeginSource--;

    return beginDestination;
}

void reverseWordsBag(char *s) {
    *copy(s, getEndOfString(s), _stringBuffer) = '\0';
    getBagOfWords(&_bag, _stringBuffer);
    char *copyS = s;
    for (int i = 0; i < _bag.size; i++) {
        copyS = copyReverse(_bag.words[i].end - 1, _bag.words[i].begin -
                                                   1, copyS);
        *copyS++ = ' ';
    }
    if (copyS != s)
        copyS--;

    *copyS = '\0';
}

bool isWordPalindrome(char *begin, char *end) {
    end--;
    while (end - begin > 0) {
        if (*begin != *end)
            return false;
        begin++;
        end--;
    }

    return true;
}

size_t howManyWordsPalindromes(char *s) {
    char *endS = getEndOfString(s);
    char *beginSearch = findNonSpace(s);
    int countPalindromes = 0;
    char *commaPos = find(beginSearch, endS, ',');
    bool lastComma = *commaPos == '\0' && endS - beginSearch != 0;

    while (*commaPos != '\0' || lastComma) {
        beginSearch = findNonSpace(beginSearch);
        countPalindromes += isWordPalindrome(beginSearch, commaPos);
        beginSearch = commaPos + 1;
        if (lastComma)
            break;

        commaPos = find(beginSearch, endS, ',');
        lastComma = *commaPos == '\0';
    }

    return countPalindromes;
}



void mergeStrings(char *s1, char *s2, char *result) {
    char *word1 = strtok_(s1, " ");
    char *word2 = strtok_(s2, " ");

    while (word1 != NULL || word2 != NULL) {
        if (word1 != NULL) {
            strcat_(result, word1);
            strcat_(result, " ");
            word1 = strtok_(NULL, " ");
        }
        if (word2 != NULL) {
            strcat_(result, word2);
            strcat_(result, " ");
            word2 = strtok_(NULL, " ");
        }
    }
}

void reverseWords(char *str) {
    int i = 0;
    _bag.size = 0;
    WordDescriptor word;

    while (*str && _bag.size < 1) {
        if (*str != ' ' && *(str + 1) == ' ' || *(str + 1) == '\0') {
            word.begin = str - i;
            word.end = str + 1;
            _bag.words[_bag.size] = word;
            _bag.size++;
            i = -1;
        }

        str++;
        i++;
    }

    while (*str) {
        if (*str != ' ' && *(str + 1) == ' ' || *(str + 1) == '\0') {
            word.begin = str - i + 1;
            word.end = str + 1;
            _bag.words[_bag.size] = word;
            _bag.size++;
            i = -1;
        }
        str++;
        i++;
    }

    char *reversedStr = malloc(strlen_(str) + 1);
    char *p = reversedStr;

    for (int j = _bag.size - 1; j >= 0; j--) {
        for (char *p = _bag.words[j].begin; p < _bag.words[j].end; p++) {
            *reversedStr = *p;
            reversedStr++;
        }
        *reversedStr = ' ';
        reversedStr++;
    }

    *reversedStr = '\0';

    strcpy_(str, p);

    free(p);
}

void printWordBeforeFirstWordWithA(char *s) {
    char *word = NULL;
    char *token = strtok_(s, " ");

    while (token != NULL) {
        int foundA = 0;
        for (int i = 0; token[i] != '\0'; i++) {
            if (tolower(token[i]) == 'a') {
                foundA = 1;
                break;
            }
        }

        if (foundA) {
            if (word != NULL) {
                printf("%s\n", word);
                return;
            }
        } else {
            word = token;
        }

        token = strtok_(NULL, " ");
    }
}

WordBeforeFirstWordWithAReturnCode getWordBeforeFirstWordWithA(char *s, WordDescriptor *w) {
    if (s == NULL || strlen_(s) == 0)
        return EMPTY_STRING;

    char *wordBegin = NULL;
    char *wordEnd = NULL;
    char *token = strtok_(s, " ");

    while (token != NULL) {
        int foundA = 0;
        for (int i = 0; token[i] != '\0'; i++)
            if (tolower(token[i]) == 'a') {
                foundA = 1;
                break;
            }

        if (foundA) {
            if (wordBegin != NULL) {
                w->begin = wordBegin;
                w->end = wordEnd;
                return WORD_FOUND;
            } else
                return FIRST_WORD_WITH_A;

        } else {
            wordBegin = token;
            wordEnd = token + strlen_(token);
        }

        token = strtok_(NULL, " ");
    }

    return NOT_FOUND_A_WORD_WITH_A;
}

void wordDescriptorToString(WordDescriptor word, char *destination) {
    int length = word.end - word.begin;
    strncpy_(destination, word.begin, length);
    destination[length] = '\0';
}

BagOfWords createBagOfWordsFromString(char *s) {
    BagOfWords bag;
    bag.size = 0;

    char *wordBegin = s;
    for (; *s; s++) {
        if (isspace(*s)) {
            if (s > wordBegin) {
                bag.words[bag.size].begin = wordBegin;
                bag.words[bag.size].end = s;
                bag.size++;
            }

            wordBegin = s + 1;
        }
    }

    if (s > wordBegin) {
        bag.words[bag.size].begin = wordBegin;
        bag.words[bag.size].end = s;
        bag.size++;
    }

    return bag;
}

int isWordInBagOfWords(WordDescriptor word, BagOfWords bag) {
    for (size_t i = 0; i < bag.size; ++i) {
        if (strncmp_(word.begin, bag.words[i].begin, word.end - word.begin) == 0)
            return 1;
    }

    return 0;
}

WordDescriptor lastWordInFirstStringInSecondString(char *s1, char *s2) {
    BagOfWords bag = createBagOfWordsFromString(s2);
    WordDescriptor lastWord = {NULL, NULL};

    BagOfWords wordsInS1 = createBagOfWordsFromString(s1);
    for (size_t i = 0; i < wordsInS1.size; ++i) {
        if (isWordInBagOfWords(wordsInS1.words[i], bag))
            lastWord = wordsInS1.words[i];
    }

    return lastWord;
}

bool hasDuplicateWords(char *s) {
    char *words[100];
    int wordCount = 0;

    char *word = strtok_(s, " ");
    while (word != NULL) {
        words[wordCount] = word;
        wordCount++;
        word = strtok_(NULL, " ");
    }

    for (int i = 0; i < wordCount; i++)
        for (int j = i + 1; j < wordCount; j++)
            if (strcmp(words[i], words[j]) == 0)
                return true;

    return false;
}
