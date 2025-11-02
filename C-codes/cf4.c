#include<stdio.h>
int main() {
    int a;
    int b;
    int arr[6];
    int i;
    a = 25 * 4 / 5;
    b = (10 + 20) * 2;
    for(i = 0; i < 6; i = i + 1) {
        if(i < 3) {
            arr[i] = a;
        } else {
            arr[i] = b;
        }
    }
    return 0;
}