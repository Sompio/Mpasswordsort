#include <stdio.h>
#include "list.h"
#include <stdlib.h>
#include <string.h>

typedef struct user {
    unsigned int userID;
    char* userName;
} user;

#define buffersize 1023;

void UsersToList(FILE* read, list* l) {
    char rows [1023];
    char* endNr;
    int startNr;
    long nrTemp;
    int i = 0;
    int colon = 0;
    int fieldCount = 0;
    bool addData;



    while(fgets(rows, 1023, read) != NULL){

        i = 0;
        colon = 0;
        fieldCount = 0;
        addData = true;
        // sees if the line starts with blankline
        if (rows[0] == '\n'){
            fprintf(stderr, "Encountered a <BLANKLINE>\n");
            addData = false;
        }
        // checks how many colons there are in the line
        while(rows[i] != '\n' && addData) {
            if(rows[i] == ':'){
                colon++;
            }
            i++;
        }
        if(colon != 6 && addData){
            fprintf(stderr, "Invalid format: %s\n", rows);
            addData = false;
        }
        i = 0;

        /********username********/
        while(rows[i] != ':' && addData){
            i++;
        }
        user *name = malloc(sizeof(user));
        rows[i] = 0;
        if (i > 1 && i <= 32 && addData) {
            name->userName = strdup(rows);
        } else if(addData){
            fprintf(stderr, " Username \"%s\" is invalid length. "
                    "Expected to be 1-32 characters.\n", rows);
            addData = false;
        }
        i++;

        /*********password********/
        do {
            i++;
        }while (rows[i] != ':');
        rows[i] = 0;
        i++;
        /*******uid*********/
        startNr = i;
        while (rows[i] != ':') {
            i++;
        }
        rows[i] = 0;
        i++;
        endNr = &rows[i];
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if(nrTemp < 0 && addData){
            fprintf(stderr, "Uid must be positive\n");
        }else if ( *endNr != 0 && addData) {
            fprintf(stderr, "Uid must be a number, got \"%s\"\n", rows + startNr);
        }else{
            name->userID = nrTemp;
        }

        /******GID********/
        startNr = i;
        while (rows[i] != ':') {
            i++;
        }
        rows[i] = 0;
        i++;
        endNr = &rows[i];
        nrTemp = strtol(rows + startNr, &endNr, 10);
        if(nrTemp < 0 && addData){
            fprintf(stderr, "Gid must be positive\n");
        }else if ( *endNr != 0 && addData) {
            fprintf(stderr, "Gid must be a number, got \"%s\"\n", rows + startNr);
        }

        /********GECOS******/
        while (rows[i] != ':') {
            rows[i] = rows[i];
            i++;
        }
        rows[i] = 0;
        i++;

        /********directory*******/
        while (rows[i] != ':') {
            rows[i] = rows[i];
            i++;
            fieldCount++;
        }
        if (fieldCount < 1) {
            fprintf(stderr, "Directory field can't be empty\n");
            addData = false;
        }
        rows[i] = 0;
        i++;

        /********shell*******/
        fieldCount = 0;
        while (rows[i] != '\0'){
            i++;
            fieldCount++;
        }
        if (fieldCount < 2) {
            fprintf(stderr, "Shell field can't be empty\n");
            addData = false;
        }
        memset(&rows[0], '\0', sizeof(rows));
        if(addData){
            listInsert(listLast(l), (data*)name);
        }else{
            free(name->userName);
            free(name);
        }
    }
}




int main(int argc, char* argv[]) {

    /*if(argc != 2) {
        printf("expected 1 file as an argument");
    }
    FILE* read;
    read = fopen(argv[1], "r");

    list* list = list_create();
    printf("hej7\n");
    UsersToList(read, list);
    printf("hej8\n");
    //list_position current = malloc(sizeof(list_position));
    */

    list* list = listEmpty();
    listPosition  current = malloc(sizeof(listPosition));

    printf("hej\n");
    printf("hej2\n");

    printf("hej3\n");
    printf("hej4\n");



    return 0;
}