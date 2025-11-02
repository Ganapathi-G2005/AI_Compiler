#include<stdio.h>
int main() {
    int a;
    int b;
    int c;
    int arr[4];
    int i;
    a = 5;
    b = 8;
    c = 3;
    i = 0;
    while(i < 4) {
        arr[i] = (a * b) + (c * c) + i;
        i = i + 1;
    }
    return 0;
}