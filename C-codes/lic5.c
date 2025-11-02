#include<stdio.h>
int main() {
    int x;
    int y;
    int z;
    int arr[4];
    int i;
    x = 6;
    y = 4;
    z = 2;
    for(i = 0; i < 4; i = i + 1) {
        arr[i] = x * y * z + i;
    }
    return 0;
}