#include<stdio.h>
int main() {
    int x;
    int arr[4];
    int i;
    x = 5;
    if (1) {
        x = 10;
        for(i = 0; i < 4; i = i + 1) {
            arr[i] = x;
        }
    } else {
        x = 15;
        i = 0;
        while(i < 4) {
            arr[i] = x;
            i = i + 1;
        }
    }
    return 0;
}