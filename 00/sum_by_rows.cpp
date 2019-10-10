#include "timer.h"


int main() {
    const int n = 1300;
    int arr[n][n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = i * j;

    Timer t;
    volatile int sum = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sum += arr[i][j];

    return 0;
}
