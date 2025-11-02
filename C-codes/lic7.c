#include<stdio.h>
int main() {
    int x;
    int y;
    int z;
    int arr[5];
    int i;
    x = 8;
    y = 12;
    z = 4;
    i = 0;
    while(i < 5) {
        if(i > 2) {
            arr[i] = (x * y) + (y * z) + i;
        } else {
            arr[i] = (x + z) * (y - z) + i;
        }
        i = i + 1;
    }
    return 0;
}