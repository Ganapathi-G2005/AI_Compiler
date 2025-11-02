#include<stdio.h>
int main() {
    int x;
    int y;
    int arr[6];
    int i;
    x = 8;
    y = 4;
    for(i = 0; i < 6; i = i + 1) {
        if(i < 3) {
            arr[i] = (x + y) * (x + y);
        } else {
            arr[i] = (x + y) + (x + y);
        }
    }
    return 0;
}