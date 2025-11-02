#include <stdio.h>

void main() {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int x;
    int y;
    int z;
    int i;
    int arr[20];

    a = 10;
    b = 0;
    
    if (a < 5) {
        c = 1;
        d = 2;
        e = 3;
        f = 4;
        g = 5;
        x = 6;
        y = 7;
        z = 8;
        i = 9;
        printf("Dead Block 1");
    } else {
        c = 10;
    }

    i = 0;
    while (i < 20) {
        if (0 == 1) {
            arr[i] = 100;
            printf("Dead Block 2");
        } else {
            arr[i] = i;
        }
        i = i + 1;
    }

    if (500 > 1000) {
        d = 1;
        e = 1;
        f = 1;
        g = 1;
        x = 1;
        y = 1;
        z = 1;
        printf("Dead Block 3");
    } else {
        d = 2;
    }

    if (100 == 100) {
        e = 5;
    } else {
        e = 10;
    }

    if (100 != 100) {
        f = 1;
        g = 2;
        x = 3;
        y = 4;
        z = 5;
        printf("Dead Block 4");
    } else {
        f = 20;
    }

    printf("Finished");
}