#include "timer.h"

int main() {
    const int n = 1000;
    int arr[n][n];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            arr[i][j] = i * j;

    Timer t;
    int sum = 0;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sum += arr[i][j];

    return 0;
}
