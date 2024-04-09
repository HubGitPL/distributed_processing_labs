#include <math.h>
#include <time.h>
#include <windows.h>
#include <stdio.h>

#define LICZBA 1000000000
#define MAX_THREADS 64

struct ThreadData {
    long long int start;
    long long int end;
};

int is_prime(long long int liczba) {
    if (liczba < 2) {
        return 0;
    }
    for (long long int i = 2; i <= sqrt(liczba); i++) {
        if (liczba % i == 0) {
            return 0;
        }
    }
    return 1;
}

int is_fibonacci(long long int liczba) {
    if (liczba <= 3)
        return 1;
    long long int a = 2, b = 3;
    while (b < liczba) {
        long long int c = a + b;
        a = b;
        b = c;
    }
    return b == liczba;
}

long long int count_fibonacci_primes(long long int start, long long int end) {
    long long int count = 0;
    for (long long int i = start; i <= end; i++) {
        if (is_fibonacci(i)) {
            if (is_prime(i)) {
                count++;
            }
        }
    }
    return count;
}

DWORD WINAPI ThreadFunction(LPVOID lpParameter) {
    struct ThreadData* data = (struct ThreadData*)lpParameter;
    long long int count = 0;
    for (long long int i = data->start; i <= data->end; i++) {
        if (is_fibonacci(i)) {
            if (is_prime(i)) {
                printf("%lld ", i);
                count++;
            }
        }
    }
    return count;
}

long long int multiThreadingImplementation(int numberOfThreads) {
    long long int N = LICZBA;
    long long int P = N / numberOfThreads;
    HANDLE threads[MAX_THREADS];
    struct ThreadData threadData[MAX_THREADS];

    for (int i = 0; i < numberOfThreads; i++) {
        threadData[i].start = i * P + 1;
        threadData[i].end = (i + 1) * P;
        threads[i] = CreateThread(NULL, 0, ThreadFunction, &threadData[i], 0, NULL);
    }

    long long int total_count = 0;
    for (int i = 0; i < numberOfThreads; i++) {
        WaitForSingleObject(threads[i], INFINITE);
        DWORD exitCode;
        GetExitCodeThread(threads[i], &exitCode);
        total_count += exitCode;
        CloseHandle(threads[i]);
    }

    return total_count;
}

int main() {
    clock_t startTime, stopTime;

    int threadCounts[] = { 2, 4, 8, 16, 32, 64 };
    for (int i = 0; i < 6; i++) {
        startTime = clock();
        long long int sumPrimeAndFibonacci = multiThreadingImplementation(threadCounts[i]);
        stopTime = clock();
        printf("Suma dla watków %d wynosi: %lld\n", threadCounts[i], sumPrimeAndFibonacci);
        printf("Czas wykonania: %f\n", (double)(stopTime - startTime) / CLOCKS_PER_SEC);
    }
    return 0;
}
