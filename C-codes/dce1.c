#include<stdio.h>
int main() {
    int a;
    int arr[3];
    int i;
    a = 10;
    if (a>5) {
        a = 20;
        for(i = 0; i < 3; i = i + 1) {
            arr[i] = a;
        }
    }
    return 0;
}