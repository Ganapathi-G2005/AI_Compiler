// Optimizations: Loop-Invariant Code Motion (Predominant), Strength Reduction, Constant Folding, Dead Code Elimination
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
    int arr2[100];

    a = 10 + 20;
    b = 30 * 2;
    c = 400 / 4;
    d = 100 - 10;
    
    e = a + b;
    f = c + d;
    g = a - b;
    h = c - d;
    
    k = a * b;
    l = c * d;
    m = a / d;
    n = c / b;
    
    o = a % d;
    p = c % b;
    q = e + f;
    r = g + h;
    
    s = k * l;
    t = m * n;
    u = o * p;
    v = q * r * s * t * u;
    
    i = 0;
    while (i < 100) {
        
        x = e + f;
        y = g + h;
        z = k + l;
        
        w = m + n;
        
        j = i * 2;
        
        arr[i] = x * y * z * w * j * v;
        
        i = i + 1;
    }
    
    i = 0;
    while (i < 50) {
        
        x = a + b;
        y = c + d;
        z = x + y;
        
        w = a - b;
        
        j = i * 4;
        
        arr[i] = x * y * z * w * j;
        
        i = i + 1;
    }
    
    if (10 < 5) {
        printf("Dead Code Block");
        a = 1;
        b = 2;
        c = 3;
    }

    printf("Finished");
}