// Predominant Optimization: Constant Folding
// Secondary: Dead Code Elimination, Common Subexpression Elimination

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
    c = 5;
    d = 2;

    e = a + b;
    f = b - a;
    g = e * f;
    h = g / 2;
    i = a * c;
    j = b * d;
    k = i + j;
    l = k % 7;
    
    m = 100;
    n = 50;
    o = m - n;
    p = o * 3;
    q = p + 99;
    r = q / 10;
    s = r - 10;
    t = s * 5;
    u = t + 50;
    v = u / 5;
    w = v % 3;
    
    x = 1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9;
    y = x * 2;
    z = y - 10;
    
    a = l + w + z;
    
    b = 500;
    c = 100;
    d = b / c;
    e = d * 4;
    f = e + 8;
    g = f - 1;
    
    h = 10;
    i = 20;
    j = 30;
    k = 40;
    l = 50;
    m = 60;
    n = 70;
    o = 80;
    p = 90;
    q = 100;
    
    r = h + i;
    s = j + k;
    t = l + m;
    u = n + o;
    v = p + q;
    
    w = r + s;
    x = t + u;
    y = v + w;
    z = x + y;
    
    a = z + a + g;
    
    if (100 < 10) {
        b = a + 1;
        c = a + 2;
        d = c + b;
        e = d * 5;
        f = e / 2;
        arr[0] = f;
    }
    
    if (50 * 2 == 100) {
        a = a + 1;
    } else {
        a = a - 1;
    }
    
    if (10 > 5) {
        b = 1;
    }
    
    if (0 == 1) {
        c = 1000;
        d = 2000;
        e = 3000;
        f = 4000;
        g = 5000;
        h = 6000;
        i = 7000;
        j = 8000;
        k = 9000;
        l = 10000;
        m = 11000;
        n = 12000;
        o = 13000;
        p = 14000;
        q = 15000;
        r = 16000;
        s = 17000;
        t = 18000;
        u = 19000;
        v = 20000;
        w = 21000;
        x = 22000;
        y = 23000;
        z = 24000;
        arr[1] = a + b + c + d + e + f + g + h + i + j;
    }

    arr[9] = a;

    return 0;
}