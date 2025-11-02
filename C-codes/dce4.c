#include<stdio.h>
int main() {
    int x;
    int arr[3];
    int i;
    x = 100;
    while (x>10) {
        x = x - 1;
        for(i = 0; i < 3; i = i + 1) {
            arr[i] = x;
        }
    }
    i = 0;
    while(i < 3) {
        arr[i] = x;
        i = i + 1;
    }
    return 0;
}