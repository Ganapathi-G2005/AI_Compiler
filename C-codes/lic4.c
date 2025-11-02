#include<stdio.h>
int main() {
    int a;
    int b;
    int arr[5];
    int i;
    a = 12;
    b = 18;
    i = 0;
    while(i < 5) {
        arr[i] = (a + b) * (a - b) + i;
        i = i + 1;
    }
    return 0;
}