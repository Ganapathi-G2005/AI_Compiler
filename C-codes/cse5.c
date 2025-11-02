#include<stdio.h>
int main() {
    int x;
    int y;
    int z;
    int arr[4];
    int i;
    x = 10;
    y = 5;
    z = 2;
    for(i = 0; i < 4; i = i + 1) {
        arr[i] = (x * y * z) + (x * y * z) - (x * y * z);
    }
    return 0;
}