#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned int x=0x57;
    unsigned int y=0x83;
    unsigned int z=((x&~y)|(~x&y));
    unsigned int a=x>>1;
    printf("x: %x , y: %x ,z: %x, a: %x",x,y,z,a);
    
}