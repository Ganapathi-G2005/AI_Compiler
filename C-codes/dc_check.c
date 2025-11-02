// Predominant Optimization: Dead Code Elimination
// Secondary: Constant Folding, Strength Reduction (inside dead blocks)

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
    int arr[10];

    a = 10;
    b = 20;
    c = a + b;
    
    d = 1;
    e = 2;
    f = 3;
    g = 4;
    h = 5;
    
    x = 100;
    y = 200;
    z = 300;
    
    x = 1;
    y = 2;
    z = 3;
    
    if (0 == 1) {
        
        a = 100;
        b = 200;
        c = a + b;
        d = a * b;
        e = c / d;
        f = e - 100;
        
        i = 0;
        while (i < 10) {
            j = i * 4;
            k = i * 2;
            l = j + k;
            arr[i] = l;
            i = i + 1;
        }
        
        m = 10 + 20;
        n = m * 3;
        o = n / 5;
        
        p = a + b;
        q = c + d;
        r = p * q;
        s = a + b;
        t = r + s;
        
        arr[9] = t;
    }
    
    if (10 * 2 == 21) {
        
        a = 100;
        b = 200;
        c = a + b;
        d = a * b;
        e = c / d;
        f = e - 100;
        
        i = 0;
        while (i < 10) {
            j = i * 4;
            k = i * 2;
            l = j + k;
            arr[i] = l;
            i = i + 1;
        }
        
        m = 10 + 20;
        n = m * 3;
        o = n / 5;
        
        p = a + b;
        q = c + d;
        r = p * q;
        s = a + b;
        t = r + s;
        
        arr[9] = t;
    } else {
        
        a = 5;
        b = 2;
        c = a * b;
    }
    
    
    d = 10;
    e = 20;
    f = 30;
    g = d + e + f;
    
    
    i = 0;
    while (i < 5) {
        arr[i] = c;
        i = i + 1;
    }
    
    
    k = 1;
    l = 2;
    m = 3;
    n = 4;
    o = 5;
    p = 6;
    q = 7;
    r = 8;
    s = 9;
    t = 10;
    u = 11;
    v = 12;
    w = 13;
    x = 14;
    y = 15;
    z = 16;
    
    
    arr[0] = a;
    arr[1] = b;
    arr[2] = c;

    return 0;
}