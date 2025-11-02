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
    e = 1;
    
    i = 0;
    while (i < 100) {
        x = a + b;
        y = c * d;
        z = a + b;
        w = c * d;
        
        arr[i] = x + y + z + w;
        
        f = a + b;
        g = c * d;
        
        arr[i] = arr[i] - f;
        arr[i] = arr[i] - g;
        
        j = x + y;
        k = f + g;
        l = j - k;
        
        if (i > 50) {
            m = a + b;
            n = c * d;
            o = m * n;
            arr[i] = o;
        } else {
            p = a + b;
            q = c * d;
            r = p + q;
            arr[i] = r;
        }
        
        s = a + b;
        t = c * d;
        u = s - t;
        
        v = a + b;
        w = c * d;
        x = v / w;
        
        y = a + b;
        z = c * d;
        
        arr[i] = y % z;
        
        i = i + 1;
    }
    
    if (10 < 5) {
        printf("This is dead");
        a = 100;
        b = 200;
        c = a + b;
        d = c * 2;
        e = d / 10;
        f = e - 5;
        g = f + 1;
        h = g * 3;
        i = h / 2;
        j = i + 10;
        k = j - 5;
        l = k * 1;
        m = l / 1;
        n = m + 0;
        o = n - 0;
        p = o * 10;
        q = p / 10;
        r = q + 1;
        s = r - 1;
        t = s * 2;
        u = t / 2;
        v = u + 3;
        w = v - 3;
        x = w * 4;
        y = x / 4;
        z = y + 5;
        arr[0] = z;
    }
    
    printf("Finished");
}