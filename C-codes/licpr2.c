// Optimizations: Loop-Invariant Code Motion (Predominant), Common Subexpression Elimination, Constant Folding, Strength Reduction
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
    c = 5;
    d = 2;
    k = 100;
    l = 200;
    m = 300;
    n = 400;
    o = 500;
    p = 600;
    q = 700;
    r = 800;
    s = 900;
    t = 1000;
    
    i = 0;
    while (i < 100) {
        
        x = a + b;
        y = c * d;
        z = l - k;
        
        e = m + n;
        f = p - o;
        g = q + r;
        
        h = s - t;
        u = x + y;
        v = z + e;
        
        w = f + g;
        
        j = i * 4;
        
        arr[i] = j + x + y + z + e + f + g + h + u + v + w;
        
        if (i > 50) {
            
            x = a + b;
            y = c * d;
            z = l - k;
            
            e = m + n;
            f = p - o;
            
            arr[i] = x + y + z + e + f;
            
        } else {
            
            g = q + r;
            h = s - t;
            
            arr[i] = g + h;
        }
        
        x = a + b;
        y = c * d;
        z = l - k;
        
        e = m + n;
        f = p - o;
        g = q + r;
        
        h = s - t;
        u = x + y;
        v = z + e;
        
        w = f + g;
        
        arr[i] = arr[i] + x + y + z + e + f + g + h + u + v + w;
        
        i = i + 1;
    }

    printf("Finished");
}