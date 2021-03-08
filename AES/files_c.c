#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void convert_str(char *hexa_char,int *number){
    int j = 0;
    for (int i = 0; i < 2 ;i++){
        if(atoi(hexa_char+i) == 0){ 
            if(*(hexa_char+i)=='A'){
                *(number+i) = 10;
            }
            else if(*(hexa_char+i)=='B'){
                *(number+i) = 11;
            }else if(*(hexa_char+i)=='C'){
                *(number+i) = 12;
            }else if(*(hexa_char+i)=='D'){
                *(number+i) = 13;
            }else if(*(hexa_char+i)=='E'){
                *(number+i) = 14;
            }else if(*(hexa_char+i)=='F'){
                *(number+i) = 15;
            }else{
                *(number+i) = 0;
            }
            j++;
        }else{
            if(i==1 && j==0){
                break;
            }
            
            *(number+i) = atoi(hexa_char+i);
            
            
        }
        
    }
    
}



int main(){

    FILE *archivo;
    char *tabla = malloc(100*sizeof(char));
    char *caracter;
    archivo = fopen("s-box.txt","r");

    if(archivo==NULL){
        return 1;
    }
    else{
        printf("\n El contenido del archivo de prueba es \n\n");
        fgets(tabla,100,archivo);
        printf("%s \n",tabla);
    }
    int *number = malloc(2*sizeof(int));
    char *token = malloc(sizeof(tabla));
    char *vect_char[15];

    token=strtok(tabla,",");
    vect_char[0] = token;
    for(int i=1;i<16;i++){
        
        token=strtok(NULL,",");
        vect_char[i] = token;
        
    }
    char *hexa_char;
    for(int j=0;j<16;j++){
        
        printf("%d. %s ",j,vect_char[j]);
        hexa_char = vect_char[j];

        convert_str(hexa_char,number);

        printf("%d - %d\n",*number,*(number+1));
        *number = 0;
        *(number+1) = 0;
    }
    fclose(archivo);
    return 0;
}
