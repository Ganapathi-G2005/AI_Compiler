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
    int arr[10];
    
    a = 10;
    b = 20;
    
    if (0 == 1) {
        printf("Dead Block 1");
        c = 1;
        d = 2;
        e = 3;
        
        i = 0;
        while (i < 10) {
            printf("Nested Dead Loop");
            arr[i] = i * 10;
            
            if (i > 5) {
                printf("Nested Dead If");
                arr[i] = arr[i] / 2;
            } else {
                printf("Nested Dead Else");
                arr[i] = arr[i] * 2;
            }
            i = i + 1;
        }
    } else {
        printf("Live Block 1");
        c = a + b;
        d = a * b;
        e = c - d;
    }
    
    f = a + b;
    g = a * b;
    
    if (100 < 10) {
        printf("Dead Block 2");
        h = 1;
        i = 2;
        j = 3;
        k = 4;
        l = 5;
        m = 6;
        n = 7;
        o = 8;
        p = 9;
        q = 10;
        r = 11;
        s = 12;
        t = 13;
        u = 14;
        v = 15;
        w = 16;
        x = 17;
        y = 18;
        z = 19;
    }
    
    h = e + f + g;
    
    if (50 > 100) {
        printf("Dead Block 3");
        a = 100;
        b = 200;
        c = 300;
        d = 400;
        e = 500;
        f = 600;
        g = 700;
        h = 800;
        i = 900;
        j = 1000;
    } else {
        printf("Live Block 2");
        i = h * 2;
        j = h / 2;
    }
    
    printf("Finished");
}