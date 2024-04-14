#ifndef LAB_17_OWN_STRING_H
#define LAB_17_OWN_STRING_H

#define CHAR_SIZE sizeof(char)
#define MAX_STRING_SIZE 100
#define MAX_N_WORDS_IN_STRING 100
#define MAX_WORD_SIZE 20

static char string_buffer[MAX_STRING_SIZE + 1];

#include <memory.h>
#include <stdbool.h>

size_t getLength(const char* string);

char* find(char* start, const char* end, int character);

char* findNonSpace(char* string);

char* findSpace(char* string);

char* findNonSpaceReverse(const char* searchEnd, char* searchStart);

char* findSpaceReverse(const char* searchEnd, char* searchStart);

int compareStrings(char* left, char* right);

char* copy(const char* start, const char* end, char* destination);

char* copyIf(char* start, const char* end, char* destination, bool (*filter)(char));

char* copyIfReverse(char* reversedStart, const char* reversedEnd, char* destination, bool (*filter)(char));

char* reverse(const char* begin, const char* end);

#endif //LAB_17_OWN_STRING_H
