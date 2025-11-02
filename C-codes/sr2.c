#include<stdio.h>
int main() {
    int a;
    int arr[6];
    int i;
    a = 10;
    i = 0;
    while(i < 6) {
        arr[i] = a * 16;
        i = i + 1;
    }
    return 0;
}