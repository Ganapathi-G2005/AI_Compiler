#include<stdio.h>
int main() {
    int a;
    int b;
    int arr[5];
    int i;
    a = 10;
    b = 20;
    b = 30;
    for(i = 0; i < 5; i = i + 1) {
        if(i > 10) {
            arr[i] = a;
        } else {
            arr[i] = b;
        }
    }
    return 0;
}