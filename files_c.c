#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

    FILE *archivo;
    char *tabla=malloc(100*sizeof(char));
    char *caracter;
    archivo=fopen("s-box.txt","r");
    if(archivo==NULL){
        return 1;
    }
    else{
        printf("\n El contenido del archivo de prueba es \n\n");
        fgets(tabla,100,archivo);
        printf("%s \n",tabla);
    }
    int number;
    char *q;
    char *y;
    q=strtok(tabla,",");
    printf("1. %s\n",q);
    for(int i=2;i<17;i++){
        q=strtok(NULL,",");
        printf("%d. %d\n",i,atol(q));

    }
    printf("char : %d \n",sizeof(char));
    fclose(archivo);
    return 0;
}
