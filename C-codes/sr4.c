#include<stdio.h>
int main() {
    int arr[5];
    int i;
    int j;
    j = 3;
    for(i = 0; i < 5; i = i + 1) {
        arr[i] = j * 2;
    }
    return 0;
}