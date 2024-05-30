#include <stdio.h>
#include <stdlib.h>
#include "list.h"



int myAtoi(char *s) {
    int n=0;
    for(;*s;s++) {
        if(*s<'0' || *s>'9') {
            fprintf(stderr,"Uno degli argomenti non è un numero");
            exit(EXIT_FAILURE);
        }
        n=(n*10)+((*s)-'0');
    }
    return n;
}

void calcolaFamiglie(List primes, List notPrimes, int m, int *foundPrimes, int n, int i) {
    int limit=m, first=1;
    for(int a=0, b=0,k=1,n=m*k;(a<=limit && b<=limit);k++,n=m*k) {
        a=n+1;
        b=n-1;
        if (controlPrime(primes,b)) {
            addListOrd(primes,b);   
            if(ifExist(notPrimes,b)) addListOrd(notPrimes,b);
            (*foundPrimes)++;
        }
        else if(ifExist(notPrimes,b)) addListOrd(notPrimes,b);
        if (controlPrime(primes,a)) {
            addListOrd(primes,a);
            if(ifExist(notPrimes,a)) addListOrd(notPrimes,a);
            (*foundPrimes)++;
        }
        else if(ifExist(notPrimes,a)) addListOrd(notPrimes,a);
        if(first) {
                limit*=getNext(primes,i);
                first=0;
        }
    }
    CalcoloFamiglie(primes,notPrimes,m,foundPrimes,n,limit);
}

void findPrimes(int n, int n2) {
    List primes=newList();
    List notPrimes=newList();
    addListTail(primes,2);
    addListTail(primes,3);
    int foundPrimes=1, m, i=1;
    if(n2==0) {
        while(foundPrimes<n) {
            calcolaM(primes,i,&m);
            calcolaFamiglie(primes,notPrimes,m,&foundPrimes,n,i);
            i++;
        }
        printList(primes,n);
        printf("%d\n",foundPrimes);
    }
    else if (n2==-1) {
        while(foundPrimes<(n*5)) {
            calcolaM(primes,i,&m);
            calcolaFamiglie(primes,notPrimes,m,&foundPrimes,n*5,i);
            i++;
        }
        findCoppie(primes,n);
    }
    else {
        while(foundPrimes<n2) {
            calcolaM(primes,i,&m);
            calcolaFamiglie(primes,notPrimes,m,&foundPrimes,n2,i);
            i++;
        }
        printListFromTo(primes,n,n2);
    }
}

int main(int argc, char *argv[]) {
    if(argc<3 || argc>4) {
        fprintf(stderr,"Uso corretto:\n./a.out n-primi\n");
        exit(EXIT_FAILURE);
    }
    switch(argv[1][0]) {
        case '1':
            findPrimes(myAtoi(argv[2]),0);
            break;
        case '2':
            findPrimes(myAtoi(argv[2]),myAtoi(argv[3]));
            break;
        case '3':
            findPrimes(myAtoi(argv[2]),-1);
            break;
        default:
            fprintf(stderr,"Uso corretto:\n./a.out n-primi\n");
            exit(EXIT_FAILURE);
    }
}