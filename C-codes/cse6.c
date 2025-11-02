#include<stdio.h>
int main() {
    int x;
    int y;
    int z;
    int arr[5];
    int i;
    x = 8;
    y = 6;
    z = 4;
    for(i = 0; i < 5; i = i + 1) {
        arr[i] = (x + y + z) * (x + y + z) + (x + y + z);
    }
    return 0;
}