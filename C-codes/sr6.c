#include<stdio.h>
int main() {
    int arr[6];
    int i;
    int base;
    base = 7;
    for(i = 0; i < 6; i = i + 1) {
        if(i % 2 == 0) {
            arr[i] = i * 64;
        } else {
            arr[i] = base * 4;
        }
    }
    return 0;
}//not working