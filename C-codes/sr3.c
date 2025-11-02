#include<stdio.h>
int main() {
    int x;
    int arr[4];
    int i;
    x = 5;
    for(i = 0; i < 4; i = i + 1) {
        if(i > 1) {
            arr[i] = x * 4;
        } else {
            arr[i] = x * 32;
        }
    }
    return 0;
}