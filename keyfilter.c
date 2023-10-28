#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define LINE_LENGHT 101

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
int line_reader(char *enabledChars, char *vyhlad, char *lastInputLine){
    char line[LINE_LENGHT];
    int i = 0;
    int dlzka_vyhlad = strlen(vyhlad);
    int flag = 1; // Check for EOF
    int areSame = 1; // Check for same strings

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
        line[i] = toupper(getchar());

    }
    line[i] = '\0';
    // If searched string correspond with line
    // Ak sa zhoduje riadok s vyhladanim, appenduje sa nasledujuce pismenko riadka do listu pvl znakov
    if (areSame == 1){ 
        if ((i == dlzka_vyhlad) && (dlzka_vyhlad != 0)){
            strcpy(lastInputLine, line);
            flag = -1;
        }
        else{
            char pismenko;

            pismenko = line[dlzka_vyhlad];
            int argLenght = strlen(enabledChars);

            enabledChars[argLenght] = pismenko;
            enabledChars[argLenght + 1] = '\0';
            strcpy(lastInputLine, line);
        }
    }
    return flag;
}
// Function sorts string of enabled chars alphabeticaly
void sortAlpabeticaly(char *enabledChars, int n){
    int i, j, min_index, temp;
    for (i = 0; i < n; i++) {
        // Find the minimum element in the unsorted part of the array
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (enabledChars[j] < enabledChars[min_index]) {
                min_index = j;
            }
        }
        // Change minimum element with element at index i
        temp = enabledChars[i];
        enabledChars[i] = enabledChars[min_index];
        enabledChars[min_index] = temp;
    }
}
// Function removes duplicates by editing string of enabled chars
void removeDuplicates(char *enabledChars, int n){
    int temp = 1;
    for (int i = 1; i < n + 1; i++) {
        int j;
        for (j = 0; j < temp; j++) {
            if (enabledChars[i] == enabledChars[j]) {
                break; // Character is already encountered, it's a duplicate
            }
        }
        if (j == temp) {
            enabledChars[temp] = enabledChars[i];
            temp++;
        }
    }
    enabledChars[temp] = '\0';
}
// Function sorts string of enabled chars
void sort(char *enabledChars, int n){
    sortAlpabeticaly(enabledChars, n);
    removeDuplicates(enabledChars, n);
}
// Function prints results of the program
void resultPrinter(char *enabledChars, char *lastInputLine, int shouldContinue){
    int n = strlen(enabledChars);
    if (n == 1){
        printf("Found: %s\n", lastInputLine);
        }
    else {
        if (shouldContinue != -1){
            sort(enabledChars, n);
            if (enabledChars[0] == '\0'){
                printf("Not found\n");
            }
            else if (n > 1){
                printf("Enable: %s\n", enabledChars);
            }
        }
        else if (shouldContinue == -1){
            printf("Found: %s\n", lastInputLine);
        }
    }
}
int main(int argc, char *argv[]){
    char search[LINE_LENGHT]; // Searched string prefix, entered by user
    char lastInputLine[LINE_LENGHT]; // Last saved line from the stdin
    char enabledChars[LINE_LENGHT]; // Enabled characters TODO: Make program that will work for unlimited duplicated chars

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
