#include <stdio.h>
#include <stdlib.h>
#include <string.h>



void print_matrix(int** matrix){
    for(int i = 0; i<16; i++){
        for(int j = 0; j<16; j++){
            printf("%x\t",*((*matrix+j)+i));
        }
        printf("\n");
    }
}
int main(){

    FILE *file;
    char *table=malloc(100*sizeof(char));
    file=fopen("s-box.txt","r");
    if(file==NULL){
        printf("Error opening the file");
        return 1;
    }
    int **matrix = malloc(16*sizeof(int*));
    int j = 0;
    while(fgets(table,100,file)){
        
        int number;
        char *hex;
        int *row = malloc(16*sizeof(int));
        hex = strtok(table,","); 
        number = (int)strtol(hex,NULL,16);
        *row = number;
        
        for(int i=1;i<16;i++){
            hex = strtok(NULL,",");
            number = (int)strtol(hex,NULL,16); //Convertir de 
            printf("%x,",number);
            *(row + i) = number;

        }
        *(matrix+j) = row;
        j++;
        printf("\n");
    }
    //print_matrix(matrix);
    fclose(file);
    return 0;
}
