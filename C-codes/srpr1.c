// Optimizations: Strength Reduction (Predominant), Common Subexpression Elimination
#include <stdio.h>

void main() {
    int i;
    int j;
    int width;
    int height;
    int a;
    int b;
    int c;
    int d;
    int e;
    int f;
    int g;
    int h;
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
    
    width = 10;
    height = 10;
    a = 5;
    b = 2;
    
    i = 0;
    while (i < height) {
        
        c = i * 10;
        
        j = 0;
        while (j < width) {
            
            d = c + j;
            arr[d] = i + j;
            
            e = c + j;
            f = a + b;
            arr[e] = arr[d] + f;
            
            g = c + j;
            h = a - b;
            arr[g] = arr[d] - h;
            
            k = c + j;
            l = a * b;
            arr[k] = arr[d] * l;
            
            m = c + j;
            n = a / b;
            arr[m] = arr[d] + n;
            
            o = c + j;
            p = a + b;
            arr[o] = p;
            
            q = c + j;
            r = a - b;
            arr[q] = r;
            
            s = c + j;
            t = a * b;
            arr[s] = t;
            
            u = c + j;
            v = a / b;
            arr[u] = v;
            
            w = c + j;
            x = a % b;
            arr[w] = x;
            
            y = c + j;
            z = a + b;
            arr[y] = z + 1;
            
            j = j + 1;
        }
        i = i + 1;
    }

    printf("Finished");
}