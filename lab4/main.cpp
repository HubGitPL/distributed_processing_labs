#include <iostream>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <sys/wait.h>
#include <unistd.h>
#define LICZBA 1000000000

bool is_prime(long long int liczba){
    if(liczba < 2){
        return false;
    }
    for(long long int i=2;i <= sqrt(liczba); i++){
        if(liczba%i==0){
            return false;
        }
    }
    return true;
}

bool is_fibonacci(long long int liczba){
    if(liczba <= 3)
        return true;
    long long int a=2, b=3;
    while(b < liczba){
        long long int c = a+b;
        a = b;
        b = c;
    }
    return b == liczba;
}

long long int count_fibonacci_primes(long long int start, long long int end){
    long long int count = 0;
    for(long long int i=start; i<=end; i++){
        if(is_fibonacci(i)){
            if(is_prime(i)) {
                count++;
            }
        }
    }
    return count;
}

long long int multiThreadingImplementation(){

}

using namespace std;
int main() {
    clock_t startTime, stopTime;

    int threadCounts[] = {2, 4, 8, 16, 32, 64};
    for(int i=0; i<6; i++){
        startTime = clock();
        long long int sumPrimeAndFibonacci = multiThreadingImplementation(threadCounts[i]);
        stopTime = clock();
        std::cout << "Suma dla watków " << threadCounts[i] << " wynosi: " << sumPrimeAndFibonacci << std::endl;
        cout << "Czas wykonania: " << (double)(stopTime - startTime) / CLOCKS_PER_SEC <<endl;
    }
    return 0;

}
