// Optimizations: Strength Reduction (Predominant), Common Subexpression Elimination
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
    
    i = 0;
    while (i < 20) {
        c = i * 2;
        d = c + 1;
        arr[i] = d;
        
        e = i * 2;
        f = e - 1;
        arr[i] = f;
        
        g = a + b;
        arr[i] = g + c;
        
        i = i + 1;
    }
    
    j = 0;
    while (j < 20) {
        k = j * 4;
        l = k + 10;
        arr[j] = l;
        
        m = j * 4;
        n = m - 5;
        arr[j] = n;
        
        o = a + b;
        arr[j] = o + k;
        
        j = j + 1;
    }
    
    p = 0;
    while (p < 20) {
        q = p * 8;
        r = q * 2;
        arr[p] = r;
        
        s = p * 8;
        t = s / 2;
        arr[p] = t;
        
        u = a - b;
        arr[p] = u + q;
        
        p = p + 1;
    }
    
    v = 0;
    while (v < 20) {
        w = v * 12;
        x = w + 100;
        arr[v] = x;
        
        y = v * 12;
        z = y + 200;
        arr[v] = z;
        
        v = v + 1;
    }

    printf("Finished");
}