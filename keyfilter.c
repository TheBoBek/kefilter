#include <stdio.h>
#include <ctype.h>
#include <string.h>

void str_upper(char *strng, char *vysledok){ //zadany retazec na uppercase
    int dlzka = strlen(strng);

    for (int i = 0; i < dlzka; i++) {
        vysledok[i] = toupper(strng[i]);
    }
    vysledok[dlzka] = '\0';
    // printf("%s", vysledok);
}
int line_reader(char *pismenka, char *vyhlad, char *posledny_reatzec){ // Porovnavanie charkterov
    char pismenko;
    char line[101];
    int i = 0;
    int dlzka_vyhlad = strlen(vyhlad);
    int flag = 1;
    int flag2 = 1;
    // printf("%s-", vyhlad);
    while (1)
    {   
        // printf("Bug2");

        line[i] = toupper(getchar());

        if (i < dlzka_vyhlad){
            if(line[i] != toupper(vyhlad[i])){ // Porovnava i-ty char riadku s i-tym charom vyhladania
                    flag2= 0;
            }
        }
        
            

        if (line[i] == EOF){
            line[i] = '\0';
            flag = 0;
            break;
        }

        else if(line[i] == '\n'){
            line[i] = '\0';
            break;
        }
        i++;
    }
    // printf("Interacia sa rovna: %d\n", i);
    if (flag2 == 1){ // Ak sa zhoduje riadok s vyhladanim, appenduje sa nasledujuce pismenko riadka do listu pvl znakov
        if (i == dlzka_vyhlad && dlzka_vyhlad != 0){
            printf("Found: %s\n", line);
            flag = -1;
        }
        else{
            pismenko = line[dlzka_vyhlad];
            int lenght = strlen(pismenka);

            pismenka[lenght] = pismenko;
            pismenka[lenght + 1] = '\0';
            strcpy(posledny_reatzec, line);
        }
    }
    return flag;
}

void zorad(char *pismenka, int n){
    // printf("NEzoradene pismenka:%s\n", pismenka);

    int i, j, min_index, temp, tail;
    tail = 1;
    for (i = 0; i < n; i++) {
        // Find the minimum element in the unsorted part of the array
        min_index = i;
        for (j = i + 1; j < n; j++) {
            if (pismenka[j] < pismenka[min_index]) {
                min_index = j;
            }
        }

        // Swap the found minimum element with the element at index i
        temp = pismenka[i];
        pismenka[i] = pismenka[min_index];
        pismenka[min_index] = temp;
    }
    // printf("Zoradene pismenka:%s\n", pismenka);

    for (int i = 1; i < n + 1; i++) {
        int j;
        for (j = 0; j < tail; j++) {
            if (pismenka[i] == pismenka[j]) {
                break; // Character is already encountered, it's a duplicate
            }
        }
        if (j == tail) {
            pismenka[tail] = pismenka[i];
            tail++;
        }
    }
    pismenka[tail] = '\0';
    // printf("Dlzka pismenok: %s\n", pismenka);
    // printf("PISMENKA SU: %s", pismenka);

    if (pismenka[0] == '\0'){
        printf("Not found\n");
    }
    else if (n > 1){
        // printf("Zoradene pismenka, odstranene duplikaty:'%s'\n", pismenka);
        printf("Enable: %s\n", pismenka);
    }
}

int main(int argc, char *argv[]){
    char posledny_retazec[101];
    char pvl_znaky[27];
    int shd_continue = 1;
    char retazec[101]; // Vyhladavanie

    int i;
    str_upper(retazec, retazec); //zadany retazec na uppercase
    // printf("%d", argc);

    if (argc == 1){
        retazec[0] = '\0';
    }
    else if (argc == 2){
        strcpy(retazec, argv[1]);
    }
    else if (argc > 2){
        // printf("Bug\n");
        
        
        i=1;
        int lenght;
        strcpy(retazec, argv[i]);
        while (i < argc - 1){
            lenght = strlen(retazec);
            // printf("%d\n", lenght);
            retazec[lenght]= ' ';
            retazec[lenght + 1] = '\0';
            strcat(retazec, argv[i + 1]);
            // printf("Argument %d sa rovná '%s'\n", i, retazec);

            i++;
        }
        

    }
    i = 0;
    while (shd_continue == 1){
        shd_continue = line_reader(pvl_znaky,retazec, posledny_retazec);
        // printf("Posledny retazec je: %s\n", posledny_retazec);
        // printf("%d, %s\n", i, posledny_retazec);
        // printf("Iteracia:%d\n", i);
        // printf("Pismenka su: %s\n", pvl_znaky);
        i++;
    }
    
    int n = strlen(pvl_znaky);
    if (n == 1){
        printf("Found: %s\n", posledny_retazec);
        }
    else {
        // printf("Cely string je: %s a pocet znakov je: %d\n", pvl_znaky, n);
        if (shd_continue != -1){
            zorad(pvl_znaky, n);
        }

    }


    return 0;
}
