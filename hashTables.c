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
            printf("\t%i\t%s\n",i,hashTable[i]->name);
        }
        else{
            printf("\t%i\t----\n",i);
        }
    }
}

bool hashTableInsert(person *p){
    /*Generally, it is better for your hash table us a linked list in case of collision, but here we will just be searching for the next open spot*/
    if (p == NULL) return false;
    int index = hash(p->name);
    if(hashTable[index] != NULL){
        printf("Collision: %s is trying to access %s's table index\n", p->name, hashTable[index]->name);
        for(int i = 0; i < TABLE_SIZE; i++){
            int try = (i + index) % TABLE_SIZE;
            if(hashTable[try] == NULL){
                hashTable[try] = p;
                return true;                
            }
        }
        printf("Table full\n");
        return false;
    }
    else{
        hashTable[index] = p;
        return true;                
    }
}

bool hashTableDelete(person *p){
    if(p == NULL) return false;
    int index = hash(p->name);
    if(hashTable[index] == NULL){
        printf("They do not exist in the list\n");
        return false;
    }
    else{
        printf("Deleting %s.\n",p->name);
        hashTable[index] = NULL;
        return true;
    }
}

person *hashTableLookup(char *name){
    int index = hash(name);
    for (int i = 0; i < TABLE_SIZE; i++){
        int try = (index + i) % TABLE_SIZE;
        if(hashTable[try] != NULL && 
            strncmp(hashTable[try]->name,name,TABLE_SIZE) == 0){
            printf("%s Found!\n",name);
            return hashTable[try];   
        }

    }
    printf("%s not found\n",name);
    return NULL;

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

    (void)hashTableLookup("Michael");
    (void)hashTableLookup("Jenn");
    (void)hashTableLookup("Paul");
    (void)hashTableLookup("Natalie");

    (void)hashTableDelete(&Michael);
    (void)hashTableLookup("Michael");

    printHashTable();

    return 0;
}