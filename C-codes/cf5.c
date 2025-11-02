#include<stdio.h>
int main() {
    int value;
    int arr[5];
    int i;
    value = 100 - 50 + 25 * 2;
    i = 0;
    while(i < 5) {
        arr[i] = value + 8 * 5;
        i = i + 1;
    }
    return 0;
}