/**
 * This program reads a text file and prints the top 5 most frequent letters (upper or lower case)
 * and the top 5 most frequent digits that are in the file. If the file has less than 5 unique letters
 * and/or digits the top list is adjusted accordingly. The file name is provided using command line 
 * arguments. If the file name is not provided or the file is not readable, the program will exit
 * and provide an error message.
 *
 * @author Bryan Bennett {@literal <bennbc16@wfu.edu>}
 * @date Sept. 20, 2020
 * @assignment Lab 2
 * @course CSC 250
 **/

#include <ctype.h>
#include <stdio.h>

/*function declarations go here*/
void addChar(char c, int *letterPtr, int *numberPtr);
void insertionSortandPrint(int * charArray, char c, int topNum);

/* addChar takes char input from main, determines if its a letter or number and then increments the corresponding integer/count array*/
void addChar(char c, int *letterPtr, int *numberPtr){
    if(isalpha(c)){letterPtr[tolower(c) - 'a']++;}      /*Letter. Convert to lowercase and increment the correct position in the index (0-25)*/
    if(isdigit(c)){numberPtr[c - '0']++;}               /*Number. Increment the correct position in the index (0-9)*/
}

/*This method sorts the array from least to greatest, then prints the topNum most frequent chars of that type*/
void insertionSortandPrint(int * charArray, char c, int topNum){
    int i, j, tmp, size; int k = 0; char tmpChar; 

    /*char c is used to determine if the array being analyzed represents letters or digits*/
    if(c =='a'){size = 26; printf("Alpha top %d out of %d\n", topNum, size);} 
    if(c =='0'){size = 10; printf("Digit top %d out of %d\n", topNum, size);}
    printf("-----------------------\n");

    /*Create and populate an array of characters that corresponds with the count/frequency arrays*/
    char arrayOfChars[size];
    for(i = 0; i<size; i++){arrayOfChars[i] = i + c;}

    /*Use insertion sort algorithm to comb up the array, swapping chars and their counts if appropriate*/
    for(i=1;i<size;i++){
        /*Compare this value with previous values, if it is smaller move it to the left via swaps*/
        for(j=i;j>0;j--){
            if(charArray[j-1]>charArray[j]){
                /*Swap this and previous index using temparary values*/
                tmp = charArray[j]; tmpChar = arrayOfChars[j];
                charArray[j] = charArray[j-1]; arrayOfChars[j] = arrayOfChars[j-1]; 
                charArray[j-1] = tmp; arrayOfChars[j-1] = tmpChar;
            }
        }
    }

    /*If MAX characters are found, print them in descending order starting at the right end of the arrays*/
    if(charArray[size-1]==0){printf("No characters of this type found\n\n");}
    else{
        for(i=(size-1); i>(size-(topNum+1)); i--){
            /*If this character's count is zero or we are about to reference a location outside array bounds, break*/
            if((k>(size-1))||(charArray[i]==0)){break;}
            printf("[%c]  %d \n", arrayOfChars[i], charArray[i]); /*Print the char and its value*/
            k++;
        }
    }
}

int main(int argc, char* argv[]){ 
    
    /*Variable Declarations*/
    int topNum; char c; 
    FILE *fptr = fopen(argv[1], "r");                             /*Open file */
    int letterArray[26] = {0}; int *letterArrayPtr = letterArray; /*Letter array and pointer*/
    int numberArray[10] = {0}; int *numberArrayPtr = numberArray; /*Number array and pointer*/

    /* File errors and messages */
    if(argc < 2){printf("Usage: %s filename \n", argv[0]); return 1;}               /*File name not sent to main*/
    if(fptr == NULL){printf("File does not exist or cannot be read\n"); return 1;}  /*File DNE or cannot be read*/

    /*IF there are 3 command-line arguments passed, determine how many MAX values to print, else assume 5*/
    if(argc == 3){
        /*If the third argument is a two-digit number, store that (only useful to see top letters since there are 10 numbers)*/
        if((isdigit(argv[2][0]))&&(isdigit(argv[2][1]))){topNum = 10*(argv[2][0]-'0') + (argv[2][1]-'0');}
        /*Else if there is one-digit number, pull that*/
        else if(isdigit(argv[2][0])){topNum = (argv[2][0]-'0');}      
    }
    else{topNum = 5;}

    /* While there is more chars in file, read in each char and send to addChar method*/
    c = fgetc(fptr);
    while(!feof(fptr)){
        addChar(c, letterArrayPtr, numberArrayPtr);
        c = fgetc(fptr);
    }

    /* Print results, specifying whether it is a letter or number array, and close file */
    insertionSortandPrint(letterArrayPtr,'a',topNum);
    insertionSortandPrint(numberArrayPtr,'0',topNum);
    fclose(fptr);
    return 0;
}