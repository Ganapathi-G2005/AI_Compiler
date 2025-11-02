#include<stdio.h>
int main() {
    int a;
    int b;
    int arr[5];
    int i;
    a = 64 / 8 * 3;
    b = (15 + 5) * (10 - 2);
    for(i = 0; i < 5; i = i + 1) {
        if(i > 2) {
            arr[i] = a + 7 * 4;
        } else {
            arr[i] = b - 50 / 2;
        }
    }
    return 0;
}