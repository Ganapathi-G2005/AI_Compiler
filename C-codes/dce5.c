#include<stdio.h>
int main() {
    int a;
    int b;
    int arr[4];
    int i;
    a = 5;
    b = a + 10;
    a = 20;
    if(a>3) {
        for(i = 0; i < 4; i = i + 1) {
            arr[i] = a;
        }
    }
    return 0;
}