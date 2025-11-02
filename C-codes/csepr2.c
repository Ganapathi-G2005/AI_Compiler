// Optimizations: Common Subexpression Elimination (Predominant), Strength Reduction
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
    int arr[10];

    a = 100;
    b = 10;
    c = 200;
    d = 20;

    if (a > b) {
        x = a + b;
        y = c - d;
        z = x * y;
        
        w = a + b;
        v = c - d;
        u = w / v;
    } else {
        x = a + b;
        y = c - d;
        z = x / y;
        
        w = a + b;
        v = c - d;
        u = w * v;
    }

    if (c > a) {
        t = a + b;
        s = c - d;
        r = t + s;
        
        q = a + b;
        p = c - d;
        o = q - p;
    } else {
        t = a + b;
        s = c - d;
        r = t * s;
        
        q = a + b;
        p = c - d;
        o = q / p;
    }

    if (b < d) {
        n = a + b;
        m = c - d;
        l = n * m;
        
        k = a + b;
        j = c - d;
        i = k + j;
    } else {
        n = a + b;
        m = c - d;
        l = n - m;
        
        k = a + b;
        j = c - d;
        i = k * j;
    }
    
    h = 0;
    while (h < 10) {
        g = h * 8;
        arr[h] = g;
        
        f = a + b;
        e = c - d;
        arr[h] = g + f + e;
        
        h = h + 1;
    }

    printf("Finished");
}