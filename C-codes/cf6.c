#include<stdio.h>
int main() {
    int arr[4];
    int i;
    int result;
    result = (100 - 25) * 2 + 50 / 5;
    i = 0;
    while(i < 4) {
        if(i % 2 == 0) {
            arr[i] = result + 8 * 3;
        } else {
            arr[i] = result - 12 / 3;
        }
        i = i + 1;
    }
    return 0;
}//not working