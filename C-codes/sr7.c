#include<stdio.h>
int main() {
    int x;
    int y;
    int arr[5];
    int i;
    x = 3;
    y = 9;
    i = 0;
    while(i < 5) {
        arr[i] = (x + y) * 128;
        i = i + 1;
    }
    return 0;
}