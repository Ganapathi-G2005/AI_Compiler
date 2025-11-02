// Predominant Optimization: Loop-Invariant Code Motion
// Secondary: Strength Reduction, Common Subexpression Elimination

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
    int arr2[50];
    
    a = 10;
    b = 20;
    c = 30;
    d = 40;
    
    e = a + b;
    f = c + d;
    g = a - b;
    h = c - d;
    
    k = a * b;
    l = c * d;
    m = a / 2;
    n = c / 5;
    
    o = a % 3;
    p = b % 3;
    q = e + f;
    r = g + h;
    
    s = k + l;
    t = m + n;
    u = o + p;
    v = q + r + s + t + u;
    
    i = 0;
    while (i < 100) {
        
        x = a + b;
        y = c * d;
        z = x + y;
        
        w = g + h;
        
        j = i * 4;
        
        arr[i] = x + y + z + w + j + v;
        
        i = i + 1;
    }
    
    i = 0;
    while (i < 50) {
        
        x = a + c;
        y = b + d;
        z = x + y;
        
        w = k + l;
        
        j = i * 4;
        
        arr2[i] = x + y + z + w + j;
        
        i = i + 1;
    }

    return 0;
}