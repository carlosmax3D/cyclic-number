// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>

#define MAXCHAR 1000
#define strcpy_s(x,y,z) strcpy(x,z)
#define itoa(x,y,z) sprintf(y,"%llu",x)
#define DIV 9

unsigned long long divide(char *number, 
                          unsigned long long dividendo){
    char ptr[MAXCHAR] = {'\0'};
    strcpy_s(ptr,MAXCHAR,number);
    char temp[MAXCHAR] = {'\0'};
    int index = 0, indexN = 1, indexT = 0;
    unsigned long long rest = 0;
    while (ptr[index] != '\0'){
        temp[indexT]   = ptr[index];
        temp[indexT+1] = '\0';
        index++;
        rest = (unsigned long long)atoi(temp);
        number[indexN] = (char)((rest / dividendo) + 48);
        indexN++;
        rest = rest % dividendo;
        if (rest == 0)
          indexT = 0;
        else {
            itoa(rest, temp, 10);
            indexT = strlen(temp);
        }
    }
    number[indexN] = '\0';
    return rest;
}

int main(int argc, char **argv){
    char result[MAXCHAR] = {'\0'};
    unsigned long long rest = 1;
    unsigned long long digit = 1;
    char* last = result;
    last++;
    for (digit = digit; digit < 10; digit++){
        result[0] = digit + 48; 
        result[1] = '\0';
        unsigned long long count = 0;
        while (result[0] != *last || rest != 0){
            rest = divide(result, DIV);
            last = result + strlen(result) - 1;
            if (count == 0 && (*last - 48) == 0){
                break;
            }
            count++;
        }
        result[0] = ' ';
        if (count != 0)
            printf("%llu %s\n",digit, result);
    }
    return 0;
} 
