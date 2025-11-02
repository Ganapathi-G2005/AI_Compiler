// Optimizations: Strength Reduction (Predominant), Constant Folding
#include <stdio.h>

void main() {
    int width;
    int height;
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
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
    int base_row_1;
    int base_row_2;
    int base_row_3;
    int base_row_4;
    int idx;
    int val1;
    int val2;
    int val3;
    int val4;
    int matrix[100];
    int arr[100];

    width = 10;
    height = 10;
    a = 5 + 1;
    b = 10 * 2;
    c = 100 / 4;
    d = 50 - 20;

    i = 0;
    while (i < height) {
        base_row_1 = i * 10;
        base_row_2 = i * 4;
        base_row_3 = i * 2;
        base_row_4 = i * 8;
        
        j = 0;
        while (j < width) {
            idx = base_row_1 + j;
            val1 = j * 3;
            val2 = j * 5;
            val3 = j * 7;
            val4 = j * 9;
            matrix[idx] = val1 + val2 + val3 + val4 + base_row_2 + base_row_3 + base_row_4;
            j = j + 1;
        }
        i = i + 1;
    }

    k = 0;
    while (k < 100) {
        l = k * 5;
        m = k * 10;
        n = k * 15;
        o = k * 20;
        p = l + m + n + o + a + b + c + d;
        arr[k] = p;
        k = k + 1;
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

    printf("Finished");
}