// Optimizations: Strength Reduction (Predominant), Constant Folding
#include <stdio.h>

void main() {
    int a;
    int b;
    int c;
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
    int arr1[100];
    int arr2[100];
    int arr3[100];
    
    a = 10 + 5;
    b = 2 * 3;
    c = 100 / 10;
    
    i = 0;
    while (i < 100) {
        j = i * 2;
        k = i * 4;
        l = i * 8;
        m = i * 16;
        arr1[i] = j + k + l + m + a;
        i = i + 1;
    }
    
    i = 0;
    while (i < 100) {
        j = i * 3;
        k = i * 6;
        l = j + k;
        arr2[i] = l;
        m = i * 9;
        n = m + l + b;
        o = i * 12;
        p = n + o + c;
        arr3[i] = p;
        i = i + 1;
    }
    
    q = 0;
    r = 0;
    s = 0;
    t = 0;
    u = 0;
    v = 0;
    w = 0;
    x = 0;
    y = 0;
    z = 0;
    
    i = 0;
    while (i < 50) {
        q = i * 1;
        r = i * 2;
        s = i * 3;
        t = i * 4;
        u = i * 5;
        v = i * 6;
        w = i * 7;
        x = i * 8;
        y = i * 9;
        z = i * 10;
        
        arr1[i] = q + r + s + t + u;
        arr2[i] = v + w + x + y + z;
        
        i = i + 1;
    }

    printf("Finished");
}