#include<stdio.h>
int main() {
    int a;
    int b;
    int c;
    int arr[4];
    int i;
    a = 10;
    b = 5;
    c = 2;
    i = 0;
    while(i < 4) {
        if(i < 2) {
            arr[i] = (a * b) + (a * b) - (a * b);
        } else {
            arr[i] = (b * c) * (b * c) + (b * c);
        }
        i = i + 1;
    }
    return 0;
}