#include<stdio.h>
int main() {
    int x;
    int y;
    int arr[3];
    int i;
    x = 10;
    y = 20;
    if(x > 15) {
        y = 30;
        for(i = 0; i < 3; i = i + 1) {
            arr[i] = y;
        }
    } else {
        i = 0;
        while(i < 3) {
            arr[i] = x;
            i = i + 1;
        }
    }
    y = 40;
    return 0;
}