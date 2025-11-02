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
    int o;
    int p;
    int q;
    int r;
    int s;
    int t;

    a = 10;
    b = 2;
    c = a * b;
    d = c + 10;
    e = d - 5;
    f = e / 5;
    g = 100;
    h = 200;
    i = g + h;
    j = i * 2;
    k = j - 100;
    l = k / 10;
    m = l + 1;
    n = m * 3;
    o = n - 9;
    p = o / 4;
    q = 1 + 2 + 3 + 4 + 5;
    r = q * 2;
    s = r - 10;
    t = s / 5;
    
    if (5 > 10) {
        a = 1000;
        b = 2000;
        c = 3000;
        d = 4000;
        e = 5000;
        f = 6000;
        g = 7000;
        printf("Dead Code Here");
    } else {
        a = 1;
    }

    if (a > 0) {
        printf("Hello");
    }

    b = c + d;
    e = f + g;
    h = i + j;
    k = l + m;
    n = o + p;
    q = r + s;

    printf("Finished");
}