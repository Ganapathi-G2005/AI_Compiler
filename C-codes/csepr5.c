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
    
    a = 100;
    b = 10;
    
    i = 0;
    for (i = 0; i < 100; i = i + 1) {
        c = a / b;
        d = a * b;
        
        arr[i] = c + d;
        
        e = a / b;
        f = a * b;
        
        arr[i] = arr[i] - e;
        arr[i] = arr[i] - f;
        
        g = a / b;
        h = a * b;
        
        arr[i] = arr[i] * g;
        arr[i] = arr[i] * h;
        
        j = a / b;
        k = a * b;
        
        if (j > k) {
            arr[i] = 0;
        } else {
            arr[i] = 1;
        }
        
        l = a / b;
        m = a * b;
        n = l + m;
        
        o = a / b;
        p = a * b;
        q = o - p;
        
        r = a / b;
        s = a * b;
        t = r * s;
        
        u = a / b;
        v = a * b;
        w = u / v;
        
        x = a / b;
        y = a * b;
        z = x % y;
    }
    
    if (0 == 1) {
        printf("This is dead");
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
        p = 16;
        q = 17;
        r = 18;
        s = 19;
        t = 20;
    }
    
    printf("Finished");
}