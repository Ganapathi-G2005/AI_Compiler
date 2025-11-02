#include<stdio.h>
int main() {
    int a;
    int b;
    int c;
    int arr[4];
    int i;
    a = 15;
    b = 25;
    c = 35;
    for(i = 0; i < 4; i = i + 1) {
        arr[i] = (a * b * c) + (a + b + c) + i;
    }
    return 0;
}