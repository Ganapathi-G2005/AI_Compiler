#include<stdio.h>
int main() {
    int x;
    int y;
    int arr[3];
    int i;
    x = (15 + 5) * 2;
    y = 100 / 4 + 3;
    if(x > 0) {
        for(i = 0; i < 3; i = i + 1) {
            arr[i] = y * 2;
        }
    }
    return 0;
}