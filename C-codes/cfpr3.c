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

    a = 10;
    b = 20;
    c = 30;
    d = 40;
    
    if (10 > 5) {
        x = 10 * 2;
        y = 20 / 2;
        z = x + y;
    } else {
        x = 0;
        y = 0;
        z = 0;
    }

    if (100 < 50) {
        x = 1;
        y = 2;
        z = 3;
        printf("Dead");
    } else {
        a = 100 + 200;
        b = a / 3;
        c = b * 2;
    }

    if (1 + 1 == 2) {
        d = 50 * 2;
        e = 100 / 10;
        f = d + e;
    } else {
        d = 1;
        e = 1;
        f = 1;
    }

    if (10 * 2 == 21) {
        a = 1;
        b = 2;
        c = 3;
        printf("Dead 2");
    } else {
        g = 5 + 5;
        h = 10 + 10;
        i = g + h;
    }
    
    j = 0;
    while (j < 50) {
        k = 10 + 20;
        l = 30 + 40;
        m = k + l;
        n = 5 * 5;
        o = 10 * 10;
        p = n + o;
        q = 100 / 2;
        r = 200 / 2;
        s = q + r;
        arr[j] = m + p + s;
        j = j + 1;
    }
    
    t = 0;
    u = 0;
    v = 0;
    i = 0;
    while (i < 10) {
        w = i * 4;
        x = i * 2;
        y = w + x;
        z = 50 + 50;
        arr[i] = y + z;
        i = i + 1;
    }

    printf("Finished");
}