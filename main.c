#include <stdio.h>
#include "lab_18/lab_18_solutions.h"
#include "str/string.h"
#include <malloc.h>

#define ASSERT_STRING(expected, got) assertString(expected, got, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_BOOLEAN(expected, got) assertBoolean(expected, got, __FILE__, __FUNCTION__, __LINE__)
#define ASSERT_INT(expected, got) assertInt(expected, got, __FILE__, __FUNCTION__, __LINE__)

static void assertString(char *expected, char *got, char const *fileName, char const *funcName, int line) {
    if (compareStrings(expected, got)) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", expected);
        fprintf(stderr, "Got: \"%s\"\n\n", got);
    } else {
        fprintf(stdout, "%s on line %d - OK\n", funcName, line);
    }
}

static void assertBoolean(bool expected, bool got, char const *fileName, char const *funcName, int line) {
    if (got != expected) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%s\"\n", (expected ? "true" : "false"));
        fprintf(stderr, "Got: \"%s\"\n\n", (got ? "true" : "false"));
    } else {
        fprintf(stdout, "%s on line %d - OK\n", funcName, line);
    }
}

static void assertInt(int expected, int got, char const *fileName, char const *funcName, int line) {
    if (got != expected) {
        fprintf(stderr, "File %s\n", fileName);
        fprintf(stderr, "%s - failed on line %d\n", funcName, line);
        fprintf(stderr, "Expected: \"%d\"\n", expected);
        fprintf(stderr, "Got: \"%d\"\n\n", got);
    } else {
        fprintf(stdout, "%s on line %d - OK\n", funcName, line);
    }
}

static void printTest(char* testableComponent, void (*testingFunction)()) {
    printf("Testing %s:\n\n", testableComponent);

    testingFunction();

    printf("\n--------------------------------------------------\n\n");
}

static char* moveStringToHeap(char* string) {
    size_t size = sizeof(char) * (getLength(string) + 1);
    char* heapString = malloc(size);

    memcpy(heapString, string, size);

    return heapString;
}

static void testRemoveExtraSpaces() {
    char* firstTest = moveStringToHeap("123 456");
    char* secondTest = moveStringToHeap("123  456");
    char* thirdTest = moveStringToHeap("123 456  789");

    removeExtraSpaces(firstTest);
    removeExtraSpaces(secondTest);
    removeExtraSpaces(thirdTest);

    ASSERT_STRING("123 456", firstTest);
    ASSERT_STRING("123 456", secondTest);
    ASSERT_STRING("123 456 789", thirdTest);

    free(firstTest);
    free(secondTest);
    free(thirdTest);
}

static void testLettersToStartDigitsToEnd() {
    char* firstTest = moveStringToHeap("abc123");
    char* secondTest = moveStringToHeap("123abc");
    char* thirdTest = moveStringToHeap("a1b2c3");

    forEachWord(firstTest, lettersToStartDigitsToEnd);
    forEachWord(secondTest, lettersToStartDigitsToEnd);
    forEachWord(thirdTest, lettersToStartDigitsToEnd);

    ASSERT_STRING("abc123", firstTest);
    ASSERT_STRING("abc123", secondTest);
    ASSERT_STRING("abc123", thirdTest);

    free(firstTest);
    free(secondTest);
    free(thirdTest);
}

static void testReplaceDigitsBySpaces() {
    char* firstTest = moveStringToHeap("");
    char* secondTest = moveStringToHeap("123");
    char* thirdTest = moveStringToHeap("1a2b3c");

    replaceDigitsBySpaces(firstTest);
    replaceDigitsBySpaces(secondTest);
    replaceDigitsBySpaces(thirdTest);

    ASSERT_STRING("", firstTest);
    ASSERT_STRING("      ", secondTest);
    ASSERT_STRING(" a  b   c", thirdTest);

    free(firstTest);
    free(secondTest);
    free(thirdTest);
}

static void testReplace() {
    char* test = moveStringToHeap("some test string");

    replace(test, "test", "replacement");

    ASSERT_STRING("some replacement string", test);

    free(test);
}

static void testAreWordsSorted() {
    char* firstTest = moveStringToHeap("abc def");
    char* secondTest = moveStringToHeap("abc abc");
    char* thirdTest = moveStringToHeap("def abc");

    ASSERT_BOOLEAN(true, areWordsSorted(firstTest));
    ASSERT_BOOLEAN(true, areWordsSorted(secondTest));
    ASSERT_BOOLEAN(false, areWordsSorted(thirdTest));

    free(firstTest);
    free(secondTest);
    free(thirdTest);
}

void testCountPalindromes() {
    char* firstTest = moveStringToHeap("abba abc");
    char* secondTest = moveStringToHeap("abc def");
    char* thirdTest = moveStringToHeap("abba ceec cde beeb");

    ASSERT_INT(1, countPalindromes(firstTest));
    ASSERT_INT(0, countPalindromes(secondTest));
    ASSERT_INT(3, countPalindromes(thirdTest));

    free(firstTest);
    free(secondTest);
    free(thirdTest);
}

void testMixWords() {
    char* left = "Skyscrapers actually and hot";
    char* right = "are giant very sandcastles";

    char* destination = malloc(sizeof(char) * (getLength(left) + getLength(right) + 1));

    mixWords("Skyscrapers actually and hot", "are giant very sandcastles", destination);

    ASSERT_STRING("Skyscrapers are actually giant and very hot sandcastles", destination);

    free(destination);
}

void testReverseWordsOrder() {
    char* test = moveStringToHeap("Skyscrapers are actually giant and very hot sandcastles");

    reverseWordsOrder(test);

    ASSERT_STRING("sandcastles hot very and giant actually are Skyscrapers", test);

    free(test);
}

void testFindLastEqualWordInBothStr() {
    char* expected = moveStringToHeap("ghi");

    WordDescriptor word;

    ASSERT_BOOLEAN(true, findLastEqualWordInBothStr("abc def ghi", "xyz def ghi", &word));
    ASSERT_INT(0, compareWords(word, (WordDescriptor) {expected, expected + 3}));

    free(expected);
}

void testHasStringEqualWords() {
    ASSERT_BOOLEAN(true, hasStringEqualWords("abc def abc"));
    ASSERT_BOOLEAN(false, hasStringEqualWords("abc def"));
}

void testHasStrWordsFromEqualSymbols() {
    ASSERT_BOOLEAN(true, hasStrWordsFromEqualSymbols("abcabc accbab"));
    ASSERT_BOOLEAN(false, hasStrWordsFromEqualSymbols("abcabc cdef"));
}

void testGetStrFromWordsNotEqualToTheLast() {
    char* string = moveStringToHeap("abc def ghi");

    getStrFromWordsNotEqualToTheLast(string);

    ASSERT_STRING("abc def", string);

    free(string);
}

void testRemovePalindromes() {
    char* firstTest = moveStringToHeap("abba cde effe ghhg");
    char* secondTest = moveStringToHeap("abc def ghi");

    removePalindromes(firstTest);
    removePalindromes(secondTest);

    ASSERT_STRING(" cde  ", firstTest);
    ASSERT_STRING("abc def ghi", secondTest);

    free(firstTest);
    free(secondTest);
}

void testAddWordsToShorterStr() {
    char* left = moveStringToHeap("abc def");
    char* right = moveStringToHeap("def ghi jkl");

    addWordsToShorterStr(left, right);

    ASSERT_STRING("abc def jkl", left);
    ASSERT_STRING("def ghi jkl", right);

    free(left);
    free(right);
}

void testIsSubstringBySymbols() {
    ASSERT_BOOLEAN(true, isSubstringBySymbols("maxim", "aimx"));
    ASSERT_BOOLEAN(false, isSubstringBySymbols("maxim", "abc"));
}
void testFind(){
    char testString[] = "Hello, world!";
    char* result = find(testString, testString + sizeof(testString) - 1, 'o');

    if (*result == 'o') {
        printf("Character 'o' found at position %ld\n", result - testString);
    } else {
        printf("Character 'o' not found.\n");
    }
}
void testFindNonSpace(){
char testString[] = "   Hello, world!"; 
    char* result = findNonSpace(testString);

    printf("La première position non-espace dans la chaîne est : %ld\n", result - testString);
}
void testFindSpace(){
char testString[] = "Hello, world!"; 
    char* result = findSpace(testString);

    if (*result == ' ') {
        printf("Espace trouvé à la position %ld\n", result - testString);
    } else {
        printf("Aucun espace trouvé.\n");
    }
}
void testFindNonSpaceRevers (){
char testString[] = "Hello, world!   "; // Chaîne de caractères avec des espaces à la fin
    char* result = findNonSpaceReverse(testString + sizeof(testString) - 2, testString);

    if (*result == ' ') {
        printf("Espace trouvé à la position %ld en partant de la fin.\n", testString + sizeof(testString) - 1 - result);
    } else {
        printf("Aucun espace trouvé.\n");
    }
}
void testFindSpaceReverse(){
char testString[] = "Hello, world!   "; // Chaîne de caractères avec des espaces à la fin
    char* result = findSpaceReverse(testString + sizeof(testString) - 2, testString);

    if (*result == ' ') {
        printf("Espace trouvé à la position %ld en partant de la fin.\n", testString + sizeof(testString) - 1 - result);
    } else {
        printf("Aucun espace trouvé.\n");
    }
}
void testCampareStrings(){
char string1[] = "apple";
    char string2[] = "banana";

    int result = compareStrings(string1, string2);

    if (result < 0) {
        printf("'%s' comes before '%s'\n", string1, string2);
    } else if (result > 0) {
        printf("'%s' comes after '%s'\n", string1, string2);
    } else {
        printf("'%s' and '%s' are equal\n", string1, string2);
    }
}
void testCopy(){
const char* source = "Hello, world!";
    char destination[20]; // Tableau de destination pour stocker la copie

    char* result = copy(source + 7, source + 12, destination); // Copie "world" dans destination

    printf("Copie : %s\n", destination);
}
void testCopyIf(){
const char* source = "Hello, world! 123";
    char destination[20]; // Tableau de destination pour stocker la copie

    char* result = copyIf(source, source + strlen(source), destination, isAlphabetic); // Copie uniquement les caractères alphabétiques

    printf("Copie : %s\n", destination);
}
void testCopyIfReverse(){
const char* source = "Hello, world! 123";
    char destination[20]; // Tableau de destination pour stocker la copie

    char* result = copyIfReverse(source + strlen(source) - 1, source - 1, destination, isAlphabetic); // Copie uniquement les caractères alphabétiques en sens inverse

    printf("Copie inversée : %s\n", destination);
}
void testReverse(){
const char* originalString = "Hello, world!";
    char* reversedString = reverse(originalString, originalString + strlen(originalString));

    printf("Chaîne originale : %s\n", originalString);
    printf("Chaîne inversée : %s\n", reversedString);

    free(reversedString); // Libération de la mémoire allouée dynamiquement
}
void testGetLength(){
const char* testString = "Hello, world!";
    size_t length = getLength(testString);
    printf("Length of \"%s\": %zu\n", testString, length);
}
int main() {
    testGetLength();
    testFind();
    testFindSpace();
    testFindNonSpace();
    testFindNonSpaceReverse();
    testFindSpaceReverse();
    testCampareStrings();
    testCopy();
    testCopyIf();
    testCopyIfReverse();
    testReverse();
    printTest("removeExtraSpaces", testRemoveExtraSpaces);
    printTest("legacyReverseWords", testLettersToStartDigitsToEnd);
    printTest("replaceDigitsBySpaces", testReplaceDigitsBySpaces);
    printTest("replace", testReplace);
    printTest("areWordsSorted", testAreWordsSorted);
    printTest("countPalindromes", testCountPalindromes);
    printTest("mixWords", testMixWords);
    printTest("reverseWordsOrder", testReverseWordsOrder);
    printTest("findLastEqualWordInBothStr", testFindLastEqualWordInBothStr);
    printTest("hasStringEqualWords", testHasStringEqualWords);
    printTest("hasStrWordsFromEqualSymbols", testHasStrWordsFromEqualSymbols);
    printTest("getStrFromWordsNotEqualToTheLast", testGetStrFromWordsNotEqualToTheLast);
    printTest("removePalindromes", testRemovePalindromes);
    printTest("addWordsToShorterStr", testAddWordsToShorterStr);
    printTest("isSubstringBySymbols", testIsSubstringBySymbols);
}
