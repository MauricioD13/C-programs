#include <stdio.h>
#include <stdlib.h>

int main(){
    unsigned int x=0x24;
    unsigned int y=0x88;
    unsigned int z= x^y;
    unsigned int a=x>>1;
    printf("x: %d , y: %x ,z: %x, a: %x",x,y,z,a);

}
