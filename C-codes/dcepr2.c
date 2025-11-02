#include <stdio.h>

void main() {
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int i;
    int j;
    int k;
    int l;
    int m;
    int n;

    a = 10;
    b = 20;
    c = a + b;
    
    if (10 > 5) {
        d = 1;
    } else {
        d = 2;
    }

    if (1 == 0) {
        e = 100;
        f = e * 2;
        g = f + e;
        h = g / 3;
        i = h - 10;
        printf("Dead Code Block 1");
    } else {
        e = 1;
        f = 2;
    }

    if (200 < 100) {
        g = 100;
        h = 200;
        i = 300;
        j = g + h + i;
        k = j * 2;
        printf("Dead Code Block 2");
    } else {
        g = 3;
        h = 4;
    }

    if (0 > 1) {
        i = 1;
        j = 2;
        k = 3;
        l = 4;
        m = 5;
        n = 6;
        printf("Dead Code Block 3");
    } else {
        i = 5;
        j = 6;
        k = 7;
    }

    l = a + c;
    m = b + d;
    n = e + f;

    printf("Finished");
}