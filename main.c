#include <stdio.h>
#include <stdlib.h>
#define N 200000
int i1=1, i2=1;

void printArray(int *a, int n) {
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

void inserisci_ordinato(int arr[], int *n, int key) {
    int i;
    for (i=(*n)-1; (i >= 0 && arr[i] > key); i--)
        arr[i+1] = arr[i];

    arr[i+1] = key;
    (*n)++;
}

int controlloPrime(int *primes, int n) {
    if(n==1) return 0;
    for(int i=0;i<i1;i++) if((n%primes[i])==0) return 0;
    return 1;
}

int ifNotExist(int *primes, int max, int n) {
    for(int i=0;i<max;i++) if(n==primes[i]) return 1;
    return 0;
}

void CalcoloFamiglie(int *primes, int *notprimes, int m, int *foundPrimes, int n, int limit) {
    int k;
    for(int a=0, i=0;notprimes[i]<m && i<i2;a=0,i++) {
        for(k=1;a<limit;k++) {
            a=(m*k)+notprimes[i];
            if(controlloPrime(primes,a)) {
                inserisci_ordinato(primes,&i1,a);
                if(!ifNotExist(notprimes,i2,a)) inserisci_ordinato(notprimes,&i2,a);
                (*foundPrimes)++;
            }
            else if(!ifNotExist(notprimes,i2,a)) inserisci_ordinato(notprimes,&i2,a);
        }
    }
}

void calcolaFamiglie(int *primes, int *notprimes, int m, int *foundPrimes, int n, int i) {
    int limit=m, first=1;
     for(int a=0, b=0,k=1;(a<=limit && b<=limit);k++) {
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
        else if(ifNotExist(notprimes,i2,a)) inserisci_ordinato(notprimes,&i2,a);
        if(first) {
            limit*=primes[i];
            first=0;
        }
     }
     CalcoloFamiglie(primes,notprimes,m,foundPrimes,n,limit);
}

void findPrimes(int *primes, int *notprimes, int n) {
    int foundPrimes=1, m=1, i=1;
    while(foundPrimes<n) {
        m*=primes[i-1];
        calcolaFamiglie(primes,notprimes,m,&foundPrimes,n,i);
        
        i++;
    }
}

int main() {
    int *primes=calloc(N,sizeof(int));
    int *notprimes=calloc(N,sizeof(int));
    notprimes[0]=4;
    primes[0]=2;
    int n=100;
    findPrimes(primes,notprimes,n);
    printArray(primes,n);
}
