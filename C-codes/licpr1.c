// Optimizations: Loop-Invariant Code Motion (Predominant), Common Subexpression Elimination, Constant Folding, Dead Code Elimination
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
    int idx;
    
    a = 10;
    b = 20;
    c = 5;
    d = 2;
    k = 50;
    idx = 10;
    arr[idx] = 100;

    p = 100 + 200;
    q = 50 / 2;
    
    i = 0;
    while (i < 100) {
        
        x = a + b;
        y = c * d;
        z = a + b;
        w = k + 1;
        
        e = a * c;
        f = b / d;
        g = a * c;
        
        h = a + c;
        l = b + d;
        m = h - l;
        
        n = a + b;
        o = c * d;
        
        r = 5 * 5;
        s = p + q;
        
        t = arr[idx];
        u = t + a;
        v = t + b;
        
        j = i * 4;
        
        arr[i] = x + y + z + w + e + f + g + h + l + m + n + o + r + s + u + v + j;
        
        i = i + 1;
    }
    
    if (10 < 5) {
        printf("Dead Code Block");
        a = 1;
        b = 2;
        c = 3;
        d = 4;
        e = 5;
        f = 6;
        g = 7;
        h = 8;
        i = 9;
        j = 10;
        k = 11;
        l = 12;
        m = 13;
        n = 14;
        o = 15;
    }

    printf("Finished");
}