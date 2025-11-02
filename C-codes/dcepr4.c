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
    int arr[50];
    
    a = 10;
    b = 20;
    
    if (10 > 5) {
        c = a + b;
        d = a * b;
    } else {
        printf("Dead Else 1");
        c = 0;
        d = 0;
        e = 1;
        f = 2;
        g = 3;
        h = 4;
        i = 5;
        j = 6;
        k = 7;
        l = 8;
        m = 9;
        n = 10;
    }
    
    if (100 < 50) {
        printf("Dead If 1");
        o = a + b;
        p = a * b;
        q = o * p;
        r = a + b;
        s = a * b;
        t = r + s;
        u = a + b;
        v = a * b;
        w = u - v;
        x = a + b;
        y = a * b;
        z = x / y;
    } else {
        o = 1;
        p = 2;
    }
    
    if (0 == 1) {
        printf("Dead If 2");
        q = 1;
        r = 2;
        s = 3;
        t = 4;
        u = 5;
        v = 6;
        w = 7;
        x = 8;
        y = 9;
        z = 10;
        a = q + r + s + t + u + v + w + x + y + z;
        b = a * 2;
        c = b / 10;
    }
    
    if (100 > 200) {
        printf("Dead If 3");
        i = 0;
        while (i < 10) {
            arr[i] = i * 10;
            i = i + 1;
        }
    } else {
        i = 0;
        while (i < 10) {
            arr[i] = i * 2;
            i = i + 1;
        }
    }
    
    if (1 != 0) {
        e = a + b;
        f = a * b;
        g = e + f;
    } else {
        printf("Dead Else 2");
        e = 100;
        f = 200;
        g = 300;
        h = 400;
        i = 500;
        j = 600;
        k = 700;
        l = 800;
        m = 900;
        n = 1000;
    }
    
    printf("Finished");
}