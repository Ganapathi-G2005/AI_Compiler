// Predominant Optimization: Common Subexpression Elimination
// Secondary: Strength Reduction, Loop-Invariant Code Motion
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
    
    a = 100;
    b = 10;
    c = 50;
    d = 5;
    
    i = 0;
    while (i < 100) {
        
        x = a + b;
        y = c - d;
        z = x + y;
        
        w = a + b;
        v = c - d;
        u = w - v;
        
        t = a + b;
        s = c - d;
        r = t * s;
        
        q = a + b;
        p = c - d;
        o = q / p;
        
        n = a + b;
        m = c - d;
        l = n % m;
        
        k = i * 4;
        
        arr[i] = z + u + r + o + l + k;
        
        if (arr[i] > 100) {
            j = a + b;
            h = c - d;
            g = j - h;
            arr[i] = g;
        } else {
            f = a + b;
            e = c - d;
            arr[i] = f + e;
        }
        
        x = a + b;
        y = c - d;
        z = x + y;
        
        w = a + b;
        v = c - d;
        u = w - v;
        
        t = a + b;
        s = c - d;
        r = t * s;
        
        q = a + b;
        p = c - d;
        o = q / p;
        
        n = a + b;
        m = c - d;
        l = n % m;
        
        arr[i] = arr[i] + z + u + r + o + l;
        
        i = i + 1;
    }

    return 0;
}