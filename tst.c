#include<stdlib.h>
#include<stdio.h>
#include<string.h>



typedef union TU {
    int i;
    char* s;
    double d;
}TU;


typedef TU *test;
typedef int* I;

void main(){


    test t = (test) malloc(sizeof(TU) * 45);
    t[0].i = 4;
    t[1].s = "med";
    t[3].d = 4.4;
    printf("%s", t[1].s);

    I i = malloc(sizeof(int) * 3);
    i[0] = 4;
    int* a = i; 
    printf("\n%d",a[0]);

}