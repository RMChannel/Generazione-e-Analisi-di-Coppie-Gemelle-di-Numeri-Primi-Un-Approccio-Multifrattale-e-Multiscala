#include <stdio.h>
#include <stdlib.h>
#define N 500000
int i1=1, i2=1;

void printArray(int *a, int n) {
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

int binary_search(int *arr, int low, int high, int value) {
    if(value>arr[high-1]) return high;
    while (low < high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == value) {
            return mid;
        } else if (arr[mid] < value) {
            low = mid + 1;
        } else {
            high = mid;
        }
    }
    return low;
}

void inserisci_ordinato(int *arr, int *size, int value) {
    int i = binary_search(arr, 0, *size, value);
    for (int j = *size; j > i; j--) {
        arr[j] = arr[j - 1];
    }
    arr[i] = value;
    (*size)++;
}


int controlloPrime(int *primes, int n) {
    if(n==1 || (n%2)==0) return 0;
    for(int i=0, iFinal=i1-1;i<iFinal;i++,iFinal--) {
        if((n%primes[i])==0 || (n%primes[iFinal])==0) return 0;
    }
    return 1;
}

int ifNotExist(int *arr, int n, int target) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == target) {
            return 0;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 1;
}

int calcolaFamiglie(int *primes, int *notprimes, int m, int *foundPrimes, int n, int i) {
    int limit=m, first=1;
    int a,b,k;
     for(a=0,b=0,k=1,n=m*k;(a<=limit && b<=limit);k++,n=m*k) {
        b=n-1;
        if(controlloPrime(primes,b)) {
            inserisci_ordinato(primes,&i1,b);
            if(ifNotExist(notprimes,i2,b)) inserisci_ordinato(notprimes,&i2,b);
            (*foundPrimes)++;
        }
        a=n+1;
        if(controlloPrime(primes,a)) {
            inserisci_ordinato(primes,&i1,a);
            (*foundPrimes)++;
        }
        if(ifNotExist(notprimes,i2,a)) inserisci_ordinato(notprimes,&i2,a);
        if(first) {
            limit*=primes[i];
            first=0;
        }
     }
    for (; notprimes[i] < m && i < i2; i++) {
        k = 1;
        do {
            a = (m * k) + notprimes[i];
            if (controlloPrime(primes, a)) {
                if (ifNotExist(primes, i1, a)) {
                    inserisci_ordinato(primes, &i1, a);
                    (*foundPrimes)++;
                }
            } 

            if (ifNotExist(notprimes, i2, a)) {
                inserisci_ordinato(notprimes, &i2, a);
            }
            k++;
        }while (a < limit);
    }
    return limit;
}

void findPrimes(int *primes, int *notprimes, int n) {
    int foundPrimes=1, m=2, i=1;
    while(foundPrimes<n) {
        m=calcolaFamiglie(primes,notprimes,m,&foundPrimes,n,i);
        i++;
    }
    printArray(primes,n);
    printf("%d\n",foundPrimes);
}

int main() {
    int n=1000;
    size_t size=N*sizeof(int);
    int *primes=malloc(size);
    int *notprimes=malloc(size);
    notprimes[0]=4;
    primes[0]=2;
    findPrimes(primes,notprimes,n);
    return 0;
}