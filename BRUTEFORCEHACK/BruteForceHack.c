#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

/* Data in the dat file structure */

typedef struct node{
	char * firstNameInDatFile;
	char * lastNameInDatFile;
	char * phoneNumberInDatFile;
	char * BirthYearInDatFile;
	int length;
	struct node * next;
    
}DATA_IN_DAT_FILE;



/* Function prototypes  and global variables */


DATA_IN_DAT_FILE * createNode(char * firstNameInDatFile, char * lastNameInDatFile, char * phoneNumberInDatFile, char * BirthYearInDatFile);
DATA_IN_DAT_FILE * parse(char stringData[256]);
DATA_IN_DAT_FILE * addToFront(DATA_IN_DAT_FILE * head, DATA_IN_DAT_FILE * newData);
void printNode(DATA_IN_DAT_FILE * node);
void printStack(DATA_IN_DAT_FILE * node);
void BRUTE_HACK_PASSWORD_PERM(DATA_IN_DAT_FILE * contactNode, int startIndexOfString, int endIndexOfString);
int count = 0;


int main(){
    
    char strings[256];
    DATA_IN_DAT_FILE * head;
    DATA_IN_DAT_FILE * temp;
    FILE * inFile;

    inFile = fopen("dataFile.dat","r");    
    

    while(fgets(strings,256,inFile) != NULL){  /* Reading the data from the text file here until it's null */

    	 if(head == NULL){
             head = parse(strings);        
    	 }
    	 else{
             /* Building the stack */
            temp = head;
            head = parse(strings);
            head->next = temp;         
         }
         BRUTE_HACK_PASSWORD_PERM(head,0,strlen(head->BirthYearInDatFile)-1);  /* Hacked only birth year as possible 4 digit bank pin*/	  
    }
     
    printStack(head);   /* Printing the entire list here */
    printf("Total Permutations: %d \n", count); /* Printing the total number of permutations for all contacts in the dat file */
    
	return 0;
}

/* Creating the list data structure */

DATA_IN_DAT_FILE * createNode(char * firstNameInDatFile, char * lastNameInDatFile, char * phoneNumberInDatFile, char * BirthYearInDatFile){

    DATA_IN_DAT_FILE * stackPtr;
    stackPtr = malloc(sizeof(DATA_IN_DAT_FILE));
    
    stackPtr->firstNameInDatFile = malloc(sizeof(char*)*strlen(firstNameInDatFile));
    stackPtr->lastNameInDatFile = malloc(sizeof(char*)*strlen(lastNameInDatFile));
    stackPtr->phoneNumberInDatFile = malloc(sizeof(char*)*strlen(phoneNumberInDatFile));
    stackPtr->BirthYearInDatFile = malloc(sizeof(char*)*strlen(BirthYearInDatFile));
    
    strcpy(stackPtr->firstNameInDatFile, firstNameInDatFile);
    strcpy(stackPtr->lastNameInDatFile, lastNameInDatFile);
    strcpy(stackPtr->phoneNumberInDatFile,phoneNumberInDatFile);
    strcpy(stackPtr->BirthYearInDatFile,BirthYearInDatFile);
    stackPtr->next = NULL;
    
    return stackPtr;
}



/* Parsing the text file to get the data */

DATA_IN_DAT_FILE * parse(char stringData[256]){

	char * firstNameInDatFileTokens;
	char * lastNameInDatFileTokens;
	char * phoneNumberInDatFileTokens;
	char * BirthYearInDatFileTokens;

	DATA_IN_DAT_FILE * head;

	char phoneNumber[256];
	char firstName[256];
	char LastName[256];
	char BirthYear[256];

    
     /* Getting tokens here from text file */

	 firstNameInDatFileTokens = strtok(stringData," ");
	 lastNameInDatFileTokens = strtok(NULL," ");
	 phoneNumberInDatFileTokens = strtok(NULL," ");
	 BirthYearInDatFileTokens = strtok(NULL," ");
    
    
    /* Storing tokens after parsing into string type */

	strcpy(firstName,firstNameInDatFileTokens);
	strcpy(LastName,lastNameInDatFileTokens);

	strcpy(phoneNumber,phoneNumberInDatFileTokens); 
	strcpy(BirthYear,BirthYearInDatFileTokens);

    
    head = createNode(firstName,LastName,phoneNumber,BirthYear);

    return head;

}

/* Printing the entire list data */

void printStack(DATA_IN_DAT_FILE * node){

    printf("--------------------------------------------------\n");
    printf("CONTACTS STACK\n");
    printf("--------------------------------------------------\n");

	while(node != NULL){

	    printNode(node);
	    node = node->next;
    }

    printf("\n");
}

/* Helps in printing a list node data */

void printNode(DATA_IN_DAT_FILE * node){

    if(node != NULL){
        printf("Name: %s %s, 4 DIGIT BANK PIN: %s\n", node->firstNameInDatFile, node->lastNameInDatFile, node->BirthYearInDatFile);
    }
}


/* Helps to swap character elements */

void swap(char * x, char * y){
    char temp;
    temp = *x;
    *x = *y;
    *y = temp;
}


/* Brute force hack helps to get the permuations of the birth year for each contact as a possible bank card pin */


void BRUTE_HACK_PASSWORD_PERM(DATA_IN_DAT_FILE * contactNode, int startIndexOfString, int endIndexOfString){

    if(startIndexOfString == endIndexOfString){

            printNode(contactNode);
            count++;
    }
    else{
     
        for(int j = startIndexOfString; j <= endIndexOfString; j++){

            swap((contactNode->BirthYearInDatFile + startIndexOfString), contactNode->BirthYearInDatFile + j);

             BRUTE_HACK_PASSWORD_PERM(contactNode, startIndexOfString + 1, endIndexOfString);

             swap((contactNode->BirthYearInDatFile + startIndexOfString), contactNode->BirthYearInDatFile + j);
	    }
     }
}


