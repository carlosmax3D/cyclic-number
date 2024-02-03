// Online C compiler to run C program online
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <limits.h>

#define THP 8
#define MTP 9 //142857

//Hola de nuevo

DWORD WINAPI worker(void* d) {
    unsigned long long* data = (unsigned long long*)d;
    unsigned long long maxLong = data[3];
    unsigned long long l = maxLong - 1;//data[0];
    unsigned long long spaces = data[1];
    unsigned long long endCounter = data[2];
    unsigned long long result = 0;
    printf("+%20llu - %20llu - %20llu\n", l, spaces, data[0]);
    if (l > 1 && l % MTP != 0)
        l = l - (l % MTP) == 0 ? 1 : l - (l % MTP);
    for (l = l; l >= data[0]; l = l < MTP ? l - 1 : l - MTP) {
        if (l == endCounter) {
            spaces = endCounter;
            endCounter = endCounter * ((unsigned long long)10);
        }
        if (l == 1 || l % MTP != 0) continue;
        unsigned long long ls1 = (l / ((unsigned long long)MTP));
        if (ls1 < spaces) continue;
        unsigned long long fd = ls1 % 10;
        unsigned long long ls = ls1 / 10;
        if (fd == 0) continue;
        fd = fd * spaces;
        if (fd <= ls1) continue;
        unsigned long long t = fd + ls;
        if ((t % ls1) == 0 && l == t) {
            result = ls1;
            break;
        }
    }
    data[0] = result;
    data[1] = l;
    return 0;
}

int main(int argc, char **argv) {
    unsigned long long l = 1;
    unsigned long long spaces = 1;
    unsigned long long endCounter = spaces * 10;
    printf("%20llu _ %20llu - %20llu\n", l, spaces, endCounter);
    for (l = l; l < ULLONG_MAX; l = l * 10) {
        if (l == endCounter) {
            spaces = endCounter;
            endCounter = endCounter * ((unsigned long long)10);
            printf("%20llu _ %20llu - %20llu\n", l, spaces, endCounter);
        }
        unsigned long long splice = endCounter - l, mod = 0;
        while (splice % THP != 0) {
            splice--;
            mod++;
        }
        int five = 0;
        HANDLE th[THP+1];
        unsigned long long param[THP+1][4] = { 0 };
        if (splice > 0) {
            unsigned long long parts = splice / ((unsigned long long)THP);
            unsigned long long starts = l;
            unsigned long long i = 0;
            for (i = 0; i < THP; i++) {
                param[i][0] = starts;
                param[i][1] = spaces;
                param[i][2] = endCounter;
                param[i][3] = starts + parts;
                th[i] = CreateThread(NULL, 0, worker, param[i] , 0, NULL);
                starts += parts;
            }
            if (mod > 0) {
                param[THP][0] = starts;
                param[THP][1] = spaces;
                param[THP][2] = endCounter;
                param[THP][3] = starts + mod;
                th[THP] = CreateThread(NULL, 0, worker, param[THP], 0 ,NULL);
                starts += mod;
                five = 1;
            }
            for (i = 0; i < THP; i++)
                WaitForSingleObject(th[i], INFINITE);
        }
        else if (mod > 0) {
            param[THP][0] = l;
            param[THP][1] = spaces;
            param[THP][2] = endCounter;
            param[THP][3] = l + mod;
            th[THP] = CreateThread(NULL, 0, worker, param[THP], 0, NULL);
            five = 1;
        }
        if (five)
            WaitForSingleObject(th[THP], INFINITE);
        for (int i = 0; i < THP+1; i++)
            if (param[i][0] != 0) {
                printf("The number is: %llu - %llu\n", param[i][0], param[i][1]);
                five = 2;
            }
        if (five == 2)
            return 0;
    }
    return 0;
}
