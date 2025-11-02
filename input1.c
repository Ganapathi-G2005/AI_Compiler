#include<stdio.h>
int main() {
    int arr[5];
    int i;
    int x;
    int y;
    x = 10;
    y = 20;
    for(i = 0; i < 5; i = i + 1) {
        arr[i] = x * y + i;
    }
    return 0;
}