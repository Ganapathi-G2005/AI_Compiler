// Predominant Optimization: Strength Reduction
// Secondary: Loop-Invariant Code Motion, Common Subexpression Elimination

#include <stdio.h>

int main() {
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
    while (i < 50) {
        
        c = i * 2;
        d = i * 4;
        e = i * 6;
        f = i * 8;
        
        g = a + b;
        
        h = c + d + e + f + g;
        
        arr[i] = h;
        
        i = i + 1;
    }
    
    i = 0;
    while (i < 50) {
        
        j = i * 3;
        k = i * 5;
        l = i * 7;
        m = i * 9;
        
        n = a - b;
        
        o = j + k + l + m + n;
        
        p = 49 - i;
        arr[p] = o;
        
        i = i + 1;
    }
    
    k = 0;
    while (k < 100) {
        
        q = k * 1;
        r = k * 5;
        s = k * 10;
        t = k * 15;
        
        u = a * b;
        
        v = q + r + s + t + u;
        
        w = k * 4;
        
        
        
        
        
        
        x = k * 3;
        y = k * 2;
        z = x + y + w;
        
        arr[k] = v - z;
        
        k = k + 1;
    }

    return 0;
}