// name: Anastasia
// email: yakauleva.a@northeastern.edu

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAXSTRING 200
#define TABLE_SIZE 400

// finite state machine states
#define STARTSTATE 0
#define S1 1
#define S2 2
#define S3 3
#define S4 4
#define S5 5
#define S6 6
#define ACCEPTSTATE 10
#define ERRORSTATE 11

// hash table node structure
typedef struct HashNode {
    char city[MAXSTRING];
    int population;
    struct HashNode* next;
} HashNode;

// hash tables
HashNode* hashTable1[TABLE_SIZE];
HashNode* hashTable2[TABLE_SIZE];
HashNode* hashTable3[TABLE_SIZE];

// initialize hash tables
void initHashTab() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable1[i] = NULL;
        hashTable2[i] = NULL;
        hashTable3[i] = NULL;
    }
}

// hash function 1: length of the city/state string (modulo size of table)
int hashFunction1(char* city) {
    return strlen(city) % TABLE_SIZE;
}

// hash function 2: sum of the character codes of the city/state string (modulo size of table)
int hashFunction2(char* city) {
    int sum = 0;
    for (int i = 0; city[i] != '\0'; i++) {
        sum += city[i];
    }
    return sum % TABLE_SIZE;
}

// hash function 3: product of the first 2 character codes in city/state string (modulo size of table)
int hashFunction3(char* city) {
    if (strlen(city) < 2) {
        return city[0] % TABLE_SIZE;
    }
    return (city[0] * city[1]) % TABLE_SIZE;
}

// insert into hash table
void insert(HashNode* hashTable[], char* city, int population, int hashIndex) {
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    strcpy(newNode->city, city);
    newNode->population = population;
    newNode->next = hashTable[hashIndex];
    hashTable[hashIndex] = newNode;
}

// print hash table
void printTable(HashNode* hashTable[], const char* tableName) {
    printf("****** %s ******\n", tableName);
    printf("--------------------------\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("\nTABLE[%d]:\n", i);
        HashNode* current = hashTable[i];
        while (current != NULL) {
            printf("key/value: [%s] / [%d]\n", current->city, current->population);
            current = current->next;
        }
    }
    printf("\n");
}

// check if a character c is a digit
bool isDigit(char c) {
    return '0' <= c && c <= '9';
}

// append character c to string s
void appendChar(char* s, char c) {
    char charToStr[2]; // convert char to string
    charToStr[0] = c;
    charToStr[1] = '\0'; // add NUL to terminate string
    strcat(s, charToStr);
}

int main () {
    char inputLine[MAXSTRING]; // temporary string to hold input line
    char cityStr[MAXSTRING]; // city name
    int lineNum; // line number (city rank)
    int popInt; // population
    int state; // FSM state
    int nextChar; // index of next character in input string
    char temp[MAXSTRING]; // temp string to build up extracted strings from input characters

    initHashTab();

    FILE* fp;
    fp = fopen("pop.csv", "r");

    if (fp != NULL) {
        fgets(inputLine, MAXSTRING, fp); // prime the pump for the first line

        // ***** BEGIN FINITE STATE MACHINE *****
        
        // STARTSTATE: digit -> S1
        // S1: digit -> S1; , -> S2
        // S2: " -> S3
        // S3: !" -> S3; " -> S4
        // S4: , -> S5
        // S5: " -> S6; ( -> ACCEPTSTATE
        // S6: digit -> S6; , -> S6; " -> ACCEPTSTATE; 
        // ACCEPTSTATE: done!
        // else go to ERRORSTATE
        //
        while (feof(fp) == 0) {
            nextChar = 0;
            state = STARTSTATE;
            strcpy(temp, ""); // temp = "", reset
            strcpy(cityStr, "");

            if (nextChar >= strlen(inputLine)) {
                // if no input string then go to ERRORSTATE
                state = ERRORSTATE;
            }

            while ((state != ERRORSTATE) && (state != ACCEPTSTATE)) {
                switch (state) {
                    case STARTSTATE:
                        // look for a digit to confirm a valid line
                        if (isDigit(inputLine[nextChar])) {
                            state = S1;
                            appendChar(temp, inputLine[nextChar]);
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S1:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',') {
                            state = S2;
                            strcpy(temp, "");
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S2:
                        if (inputLine[nextChar] == '"') {
                            state = S3;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S3:
                        if (inputLine[nextChar] != '"') {
                            appendChar(cityStr, inputLine[nextChar]);
                        } else {
                            state = S4;
                        }
                        break;

                    case S4:
                        if (inputLine[nextChar] == ',') {
                            state = S5;
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S5:
                        if (inputLine[nextChar] == '"') {
                            state = S6;
                            strcpy(temp, "");
                        } else if (inputLine[nextChar] == '(') {
                            state = ACCEPTSTATE;
                            popInt = 0; // missing population
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case S6:
                        if (isDigit(inputLine[nextChar])) {
                            appendChar(temp, inputLine[nextChar]);
                        } else if (inputLine[nextChar] == ',') {
                            // Ignore commas
                        } else if (inputLine[nextChar] == '"') {
                            state = ACCEPTSTATE;
                            popInt = atoi(temp);
                        } else {
                            state = ERRORSTATE;
                        }
                        break;

                    case ACCEPTSTATE:
                        // nothing to do - we are done!
                        break;

                    default:
                        state = ERRORSTATE;
                        break;
                } // end switch

                // advance input
                nextChar++;

            } // end while state machine loop

            // ***** END FINITE STATE MACHINE *****
            
            if (state == ACCEPTSTATE) {
                // calculate hash indices
                int hashIndex1 = hashFunction1(cityStr);
                int hashIndex2 = hashFunction2(cityStr);
                int hashIndex3 = hashFunction3(cityStr);

                // insert into hash tables
                insert(hashTable1, cityStr, popInt, hashIndex1);
                insert(hashTable2, cityStr, popInt, hashIndex2);
                insert(hashTable3, cityStr, popInt, hashIndex3);
            }

            // get next line
            fgets(inputLine, MAXSTRING, fp);

        } // end while file input loop

        fclose(fp);

        // Print out the contents of the hash tables
        printTable(hashTable1, "HASH TABLE 1");
        printTable(hashTable2, "HASH TABLE 2");
        printTable(hashTable3, "HASH TABLE 3");

    } else {
        printf("File not found!\n");
    }

    return 0;
}