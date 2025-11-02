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
    int width;
    int height;
    int matrix[100];
    
    width = 10;
    height = 10;
    a = 5;
    b = 2;
    
    i = 0;
    while (i < height) {
        j = 0;
        while (j < width) {
            k = i * width;
            l = k + j;
            matrix[l] = i + j;
            
            m = i * width;
            n = m + j;
            o = matrix[n];
            
            p = i * width;
            q = p + j;
            r = a * b;
            
            matrix[q] = o + r;
            
            s = i * width;
            t = s + j;
            u = a * b;
            
            matrix[t] = matrix[t] - u;
            
            v = i * width;
            w = v + j;
            x = a * b;
            
            matrix[w] = matrix[w] + x;
            
            y = i * width;
            z = y + j;
            matrix[z] = matrix[z] + 1;
            
            j = j + 1;
        }
        i = i + 1;
    }
    
    if (1 > 10) {
        printf("This is dead");
        a = 10;
        b = 20;
        c = a + b;
        d = a - b;
        e = a * b;
        f = a / b;
        g = a % b;
        h = c + d + e + f + g;
        i = h * 2;
        j = i / 3;
        k = j - 1;
        l = k + 1;
        m = l * 5;
        n = m / 5;
        o = n + 10;
        p = o - 10;
        q = p * 1;
        r = q / 1;
        s = r + 0;
        t = s - 0;
        u = t * 2;
        v = u / 2;
        w = v * 3;
        x = w / 3;
        y = x * 4;
        z = y / 4;
    }
    
    printf("Finished");
}