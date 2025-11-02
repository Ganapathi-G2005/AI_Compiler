#include<stdio.h>
int main() {
    int a;
    int b;
    int arr[3];
    int i;
    a = 7;
    b = 9;
    i = 0;
    while(i < 3) {
        arr[i] = (a + b) * 8;
        i = i + 1;
    }
    return 0;
}