#include<stdio.h>
int main() {
    int a;
    int b;
    int arr[4];
    int i;
    a = 5;
    b = 10;
    if(0) {
        a = 25;
        b = 35;
    }
    for(i = 0; i < 4; i = i + 1) {
        if(1) {
            arr[i] = a;
        } else {
            arr[i] = b;
        }
    }
    b = 50;
    return 0;
}//not workingg