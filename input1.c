// Optimizations: Constant Folding (Predominant), Strength Reduction
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
    int u;
    int v;
    int w;
    int x;
    int y;
    int z;
    int arr[100];

    a = 10 + 20;
    b = 30 * 2;
    c = 400 / 4;
    d = 100 - 10;
    e = 5 % 2;
    f = a + b;
    g = c - d;
    h = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9 + 10;
    i = 10 * 20 * 3;
    j = 1000 / 10 / 2;
    k = a + 5;
    l = b - 10;
    m = c * 1;
    n = d / 1;
    o = e + 0;
    p = f - 0;
    q = 100;
    r = 200;
    s = q + r;
    t = q - r;
    u = q * r;
    v = r / q;
    w = r % q;
    x = 10;
    y = 20;
    z = 30;
    
    a = x + y;
    b = y + z;
    c = x + z;
    d = 1 + 1;
    e = 2 + 2;
    f = 3 + 3;
    g = 4 + 4;
    h = 5 + 5;
    i = 6 + 6;
    j = 7 + 7;
    k = 8 + 8;
    l = 9 + 9;
    m = 10 + 10;
    n = 11 + 11;
    o = 12 + 12;
    p = 13 + 13;
    q = 14 + 14;
    r = 15 + 15;
    s = 16 + 16;
    t = 17 + 17;
    u = 18 + 18;
    v = 19 + 19;
    w = 20 + 20;
    x = 21 + 21;
    y = 22 + 22;
    z = 23 + 23;
    
    a = 100 / 2;
    b = 100 / 4;
    c = 100 / 5;
    d = 100 / 10;
    e = 100 / 20;
    f = 100 / 25;
    g = 100 / 50;

    i = 0;
    while (i < 20) {
        j = i * 4;
        k = i * 2;
        arr[i] = j + k;
        i = i + 1;
    }

    printf("Finished");
}