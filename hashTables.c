#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define MAX_NAME 256
#define TABLE_SIZE 10

typedef struct {
    char name[MAX_NAME];
    int age;
    struct person *next;
    
    /*Other stuff */
} person;

person * hashTable[TABLE_SIZE]; /*Make array of pointers to hold table values*/

unsigned int hash(char *name){
    int length = strnlen(name, MAX_NAME);
    unsigned int hashValue = 0;
    for(uint8_t i = 0; i < length; i++){
        hashValue += name[i];
    }

    return hashValue % TABLE_SIZE; /*The mod operator ensures that the vaules will be 0-9, to fit in the 10 spots in the table*/
}

void initHashTable(){
    for(int i = 0; i < TABLE_SIZE; i++){
        hashTable[i] = NULL;
    }
}

void printHashTable(){
    for(int i = 0; i <= TABLE_SIZE; i++){
        if(hashTable[i] != NULL){
            printf("\t%i\t%s",i,hashTable[i]->name);
            person *tmp = hashTable[i]->next;
            while(tmp != NULL){
                printf(" <-> %s", tmp->name);
                tmp = tmp->next;
            }
            printf("\n");
        }
        else{
            printf("\t%i\t----\n",i);
        }
    }
}

bool hashTableInsert(person *p){
    if (p == NULL) return false;
    int index = hash(p->name);
    p->next = hashTable[index];
    hashTable[index] = p;
    return true;
}

bool hashTableDelete(person *p){
    
    int index = hash(p->name);
    person *tmp = hashTable[index];
    person *prev = NULL;
    while(tmp != NULL &&
            strncmp(p->name, tmp->name,TABLE_SIZE) != 0){
                prev = tmp;
                tmp = tmp->next;
    }
    if(tmp == NULL) return false;
    if(prev == NULL){
        hashTable[index] = tmp->next;
    }
    else{
        prev->next = tmp->next;
    }
    return true;
}

person *hashTableLookup(char *name){
    int index = hash(name);
    person *tmp = hashTable[index];
    while(tmp != NULL &&
            strncmp(name, tmp->name,TABLE_SIZE) != 0){
                tmp = tmp->next;
    }
    if(tmp == NULL){
        printf("%s is not in list\n",name);
        return NULL;
    }
    return tmp;
}

int main (){
    initHashTable();
    printHashTable();

    person Michael = {.name="Michael", .age=27};
    person Jacob = {.name="Jacob", .age=256};
    person Paul = {.name="Paul", .age=25};
    person Natalie = {.name="Natalie", .age=14};

    hashTableInsert(&Michael);
    hashTableInsert(&Jacob);
    hashTableInsert(&Paul);
    hashTableInsert(&Natalie);

    person *tmp = hashTableLookup("Michael");
    printf("%s has been found and age is %i\n",&tmp->name,tmp->age);
    tmp = hashTableLookup("Jenn");
    (void)hashTableLookup("Paul");
    (void)hashTableLookup("Natalie");

    (void)hashTableDelete(&Michael);
    (void)hashTableLookup("Michael");

    printHashTable();

    return 0;
}