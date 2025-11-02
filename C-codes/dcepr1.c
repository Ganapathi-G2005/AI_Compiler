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
    int arr[10];

    a = 10;
    b = 20;
    c = a + b;
    d = c * 2;
    e = 400 / 20;
    f = e - 10;
    g = a * 0;
    x = 100 + 200;
    y = x / 3;
    z = y - 100;
    
    i = 0;
    while (i < 10) {
        x = i * 2;
        y = x + 5;
        arr[i] = y;
        i = i + 1;
    }

    if (100 < 50) {
        a = 1;
        b = 2;
        c = 3;
        d = 4;
        e = 5;
        f = 6;
        g = 7;
        x = 8;
        y = 9;
        z = 10;
        printf("This is dead");
    } else {
        z = 1;
    }

    a = a + 1;
    b = b + 1;
    c = c + 1;
    d = d + 1;
    e = e + 1;
    f = f + 1;
    g = g + 1;
    x = x + 1;
    y = y + 1;
    z = z + 1;

    printf("Finished");
}