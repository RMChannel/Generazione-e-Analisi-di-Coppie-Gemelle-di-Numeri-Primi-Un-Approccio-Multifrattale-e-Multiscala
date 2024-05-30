#include <stdio.h>
#include <stdlib.h>
#define N 1000000
long long int i1=1, i2=1;

void printArray(long long int *a, long long int n) {
    for(long long int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

void inserisci_ordinato(long long int *arr, long long int *size, long long int value) {
    long long int i;
    for (i = *size - 1; (i >= 0 && arr[i] > value); i--) {
        arr[i + 1] = arr[i];
    }
    arr[i + 1] = value;
    (*size)++;
}

long long int controlloPrime(long long int *primes, long long int n) {
    if(n==1) return 0;
    for(long long int i=0;i<i1;i++) if((n%primes[i])==0) return 0;
    return 1;
}

long long int ifNotExist(long long int *arr, long long int n, long long int target) {
    long long int left = 0, right = n - 1;
    while (left <= right) {
        long long int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

void CalcoloFamiglie(long long int *primes, long long int *notprimes, long long int m, long long int *foundPrimes, long long int n, long long int limit) {
    long long int k, a, i;

    for (i = 0; notprimes[i] < m && i < i2; i++) {
        a = 0;
        k = 1;
        
        while (a < limit) {
            a = (m * k) + notprimes[i];
            k++;

            if (controlloPrime(primes, a)) {
                if (!ifNotExist(primes, i1, a)) {
                    inserisci_ordinato(primes, &i1, a);
                    (*foundPrimes)++;
                }
            } 

            if (!ifNotExist(notprimes, i2, a)) {
                inserisci_ordinato(notprimes, &i2, a);
            }
        }
    }
}

void calcolaFamiglie(long long int *primes, long long int *notprimes, long long int m, long long int *foundPrimes, long long int n, long long int i) {
    long long int limit=m, first=1;
     for(long long int a=0, b=0,k=1;(a<=limit && b<=limit);k++) {
        a=(m*k)+1;
        b=(m*k)-1;
        if(controlloPrime(primes,b)) {
            inserisci_ordinato(primes,&i1,b);
            if(!ifNotExist(notprimes,i2,b)) inserisci_ordinato(notprimes,&i2,b);
            (*foundPrimes)++;
        }
        else if(ifNotExist(notprimes,i2,b)) inserisci_ordinato(notprimes,&i2,b);
        if(controlloPrime(primes,a)) {
            inserisci_ordinato(primes,&i1,a);
            if(!ifNotExist(notprimes,i2,a)) inserisci_ordinato(notprimes,&i2,a);
            (*foundPrimes)++;
        }
        else if(!ifNotExist(notprimes,i2,a)) inserisci_ordinato(notprimes,&i2,a);
        if(first) {
            limit*=primes[i];
            first=0;
        }
     }
     CalcoloFamiglie(primes,notprimes,m,foundPrimes,n,limit);
}

void findPrimes(long long int *primes, long long int *notprimes, long long int n) {
    long long int foundPrimes=1, m=1, i=1;
    while(foundPrimes<n) {
        m*=primes[i-1];
        calcolaFamiglie(primes,notprimes,m,&foundPrimes,n,i);
        
        i++;
    }
}

long long int main() {
    long long int *primes=malloc(N*sizeof(int));
    long long int *notprimes=malloc(N*sizeof(int));
    notprimes[0]=4;
    primes[0]=2;
    long long int n=10000;
    findPrimes(primes,notprimes,n);
    printArray(primes,n);
}
