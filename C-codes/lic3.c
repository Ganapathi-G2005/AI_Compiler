#include<stdio.h>
int main() {
    int x;
    int y;
    int arr[6];
    int i;
    x = 15;
    y = 25;
    for(i = 0; i < 6; i = i + 1) {
        if(i < 3) {
            arr[i] = x * y + i;
        } else {
            arr[i] = x - y + i;
        }
    }
    return 0;
}