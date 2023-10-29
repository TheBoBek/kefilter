#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGHT 101
#define ASCII 256

// Function combines arguments of the input to one string
void strCombiner(int sumArguments, char **arguments, char *search){
    int i=1;
    int argLenght; // String argLenght of single argument
        strcpy(search, arguments[i]);
        while (i < sumArguments - 1){
            argLenght = strlen(search);
            // Append next argument to search string
            search[argLenght]= ' ';
            search[argLenght + 1] = '\0';
            strcat(search, arguments[i + 1]);

            i++;
        }
}
// Function changes the input string to uppercase
void str_upper(char *strng, char *vysledok){ 
    int dlzka = strlen(strng);

    for (int i = 0; i < dlzka; i++) {
        vysledok[i] = toupper(strng[i]);
    }
    vysledok[dlzka] = '\0';
}
// Function iterates through chars of the line
int line_reader(int *enabledChars, char *vyhlad, char *lastInputLine){
    char line[LINE_LENGHT];
    int i = 0;
    int dlzka_vyhlad = strlen(vyhlad);
    int flag = 1; // Check for EOF
    int areSame = 1; // Check for same PREFIXES

    line[i] = toupper(getchar());
    while (line[i] != '\n')
    {   
        if (i < dlzka_vyhlad){
            if(line[i] != toupper(vyhlad[i])){ // Porovnava i-ty char riadku s i-tym charom vyhladania
                    areSame= 0;
            }
        }
        if (line[i] == EOF){
            flag = 0;
            break;
        }
        i++;
        if (i > LINE_LENGHT - 1){
            fprintf(stderr, "CHYBA: Priliš mnoho znakov.");
            exit(1);
        }
        line[i] = toupper(getchar());

    }
    line[i] = '\0';
    // If searched string correspond with line
    if (areSame == 1){ 
        if ((i == dlzka_vyhlad) && (dlzka_vyhlad != 0)){
            strcpy(lastInputLine, line);
            flag = -1;
        }
        else{
            int pismenko;

            pismenko = line[dlzka_vyhlad];

            enabledChars[pismenko] += 1;
            strcpy(lastInputLine, line);
        }
    }
    return flag;
}
// Function returns decision of enabledChars (1 = ENABLE, 0 = FOUND, -1 = NOT FOUND)
int resultManager(int *enabledChars){
    int isAlone=0;
    for(int i=0; i < ASCII; i++){
        if (enabledChars[i] == 1){
            isAlone++;
        }
        else if (enabledChars[i] > 1 || isAlone > 1){
            return 1;
        }
    }
    if (isAlone == 0){
        return -1;
    }
    else if (isAlone == 1){
        return 0;
    }
    return -2;
}
// Function prints results of the program
void resultPrinter(int *enabledChars, char *lastInputLine, int shouldContinue){
    int n = resultManager(enabledChars);
    if (n == 0 || shouldContinue == -1)
    {
        printf("Found: %s\n", lastInputLine);
    }
    else if (n == 1){
        printf("Enable: ");
        for(int i = 0; i < ASCII; i++){
            if (enabledChars[i] > 0){
                printf("%c", i);
            }
        }
    }
    else {
        printf("Not found");
    }
}
int main(int argc, char *argv[]){
    char search[LINE_LENGHT]; // Searched string prefix, entered by user
    char lastInputLine[LINE_LENGHT] = {0}; // Last saved line from the stdin
    int enabledChars[ASCII] = {0}; // Enabled characters TODO: Make program that will work for unlimited duplicated chars

    // Converts all characters from string to upper case 
    str_upper(search, search); 

    // Initializes empty search string
    if (argc == 1){ 
        search[0] = '\0';
    }
    else if (argc == 2){
        strcpy(search, argv[1]);
    }

    // Initializes search string with multiple words separated by 'space'
    else if (argc > 2){ 
        strCombiner(argc, argv, search);
    }

    // Loops through input data(stdin)
    int shouldContinue = 1;
    while (shouldContinue == 1){
        shouldContinue = line_reader(enabledChars, search, lastInputLine);
    }

    resultPrinter(enabledChars, lastInputLine, shouldContinue);

    return 0;
}
