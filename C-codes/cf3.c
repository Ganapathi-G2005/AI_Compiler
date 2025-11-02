#include<stdio.h>
int main() {
    int result;
    int arr[4];
    int i;
    result = 8 * 7 + 12 - 4;
    i = 0;
    while(i < 4) {
        arr[i] = result + 50 / 2;
        i = i + 1;
    }
    return 0;
}