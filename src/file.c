// Online C compiler to run C program online
#include <stdio.h>
#include <limits.h>

int main(){
    unsigned long long l = 0;
    unsigned long long spaces = 1;
    unsigned long long endCounter = spaces * 10;
    for (l = 1; l <  ULLONG_MAX; l++){
        if (l == endCounter){
            spaces = endCounter;
            endCounter = endCounter * ((unsigned long long)10);
            printf("%20llu _ %20llu - %20llu\n",l,spaces,endCounter);
        }
        unsigned long long fd = (unsigned long long)(l % ((unsigned long long)10));
        if (fd == 0) continue;
        fd = fd * spaces;
        if (fd <= l) continue;
        unsigned long long t = fd + ((unsigned long long)(l / ((unsigned long long)10)));
        if ((t % l) == 0 && t == (unsigned long long)(((unsigned long long)5) * l))
            break;
    }
    printf("The number is: %llu\n",l);
    return 0;
} 
