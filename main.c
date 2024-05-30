#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 5000000
int i1=1, i2=1;



//Funzione che replica la funzione atoi, creata così da evitare il linkaggio con la string.h e migliorare l'efficienza
int myAtoi(char *s) {
    int n=0;
    while(*s) {
        if(*s<'0' || *s>'9') {
            fprintf(stderr,"Argomenti non corretti\n");
            exit(EXIT_FAILURE);
        }
        n=(n*10)+(*s-'0');
        s++;
    }
    return n;
}

void printArray(int *a, int n) {
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

/*

Abbiamo scelto di utilizzare la funzione di ricerca binaria su un array perché, 
per array di grandi dimensioni come i nostri, la ricerca lineare risultava estremamente inefficiente, 
rallentando significativamente il programma.
*/

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

/*
inserisci_ordinato aggiunge gli elementi secondo una relazione d'ordine.
Volevamo che gli elementi fossero inseriti secondo una precisa relazione d'ordine, 
in modo da poterli analizzare in maniera più efficiente.
*/

void inserisci_ordinato(int *arr, int *size, int value) {
    int i = binary_search(arr, 0, *size, value);
    for (int j = *size; j > i; j--) {
        arr[j] = arr[j - 1];
    }
    arr[i] = value;
    (*size)++;
}

/*
La funzione `controlloPrime` verifica se un numero n è primo utilizzando un array preesistente di numeri primi. 
Prima controlla se n è 1 o pari (escluso 2), restituendo 0 in tal caso poiché tali numeri non sono primi. 
Successivamente, itera sull'array primes confrontando gli elementi dall'inizio e dalla fine verso il centro. 
Se n è divisibile per uno degli elementi dell'array, restituisce 0, indicando che n non è primo. 
Se nessuna divisione ha resto zero, la funzione restituisce 1, confermando che n è primo.
*/

int controlloPrime(int *primes, int n) {
    if(n==1 || (n%2)==0) return 0;
    for(int i=0, iFinal=i1-1;i<iFinal;i++,iFinal--) {
        if((n%primes[i])==0 || (n%primes[iFinal])==0) return 0;
    }
    return 1;
}

/*
La funzione ifNotExist controlla atraverso una ricerca binaria se un certo target all'interno dell'array
esiste oppure no.
*/

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

/*
La funzione calcolaFamiglie genera numeri primi e non primi a partire da un valore di base m, 
espandendo progressivamente utilizzando il metodo del Multiscala: abbiamo due array, uno per i numeri primi 
primes e uno per i non primi notprimes. La funzione utilizza diverse variabili per controllare 
i limiti di iterazione e per determinare se un numero è primo o meno, aggiungendo i numeri trovati 
agli array appropriati.
*/

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

/*
La funzione findPrimes, per prima cosa alloca lo spazio di memoria per i due array, 
e passa i valori ad calcolaFamiglie.
*/

void findPrimes(int n) {
    size_t size=N*sizeof(int);
    int *primes=malloc(size);
    int *notprimes=malloc(size);
    notprimes[0]=4;
    primes[0]=2;
    int foundPrimes=1, m=2, i=1;
    while(foundPrimes<n) {
        m=calcolaFamiglie(primes,notprimes,m,&foundPrimes,n,i);
        i++;
    }
    printArray(primes,n);
    printf("%d\n",foundPrimes);
}

/*
La funzione findCoppie trova e stampa n coppie di numeri primi gemelli. 
Alloca memoria per due array, primes e notprimes, inizializzandoli rispettivamente con 2 e 4. 
Utilizza un ciclo while per riempire questi array chiamando la funzione calcolaFamiglie, 
finché non vengono trovati almeno 5n numeri primi. Successivamente, itera attraverso l'array primes 
per identificare coppie di numeri primi gemelli, ovvero coppie di primi che differiscono di 2, stampandole. 
Infine, libera la memoria allocata per gli array.

*/

void findCoppie(int n) {
    size_t size=N*sizeof(int);
    int *primes=malloc(size);
    int *notprimes=malloc(size);
    notprimes[0]=4;
    primes[0]=2;
    int foundPrimes=1, m=2, i=1;
    while(foundPrimes<(n*5)) {
        m=calcolaFamiglie(primes,notprimes,m,&foundPrimes,n*5,i);
        i++;
    }
    for(int i1=0, i2, i3=1;i3<=n;i1=i2) {
        i2=i1+1;
        if((primes[i1]+2)==primes[i2]) {
            printf("%d COPPIA: %d %d\n",i3,primes[i1],primes[i2]);
            i3++;
        }
    }
}


/*
Questo programma ha 2 funzioni:
1°Calcolo dei primi n numeri primi, n dato dall'utente da temrinale
2°Calcolo delle prime n coppie di numeri primi gemelli, n sempre dato dall'utente da terminale
*/
int main(int argc, char *argv[]) {
    if(argc!=3) { //Controlla che il numero degli argomenti sia corretto
        fprintf(stderr,"Uso corretto:\n./a.exe 1 (n numeri primi)\n./a.exe 2 (n coppie gemelle)\n"); //In caso di numero errato, stampa l'errore e termina
        exit(EXIT_FAILURE);
    }
    else {
        switch(argv[1][0]) { //Controlla quale funzione devo eseguire
            case '1':
                findPrimes(myAtoi(argv[2])); //Calcolo dei primi n numeri primi
                break;
            case '2':
                findCoppie(myAtoi(argv[2])); //Calcolo delle prime n coppie di numeri primi gemelli
                break;
            default:
                fprintf(stderr,"Uso corretto:\n./a.exe 1 (n numeri primi)\n./a.exe 2 (n coppie gemelle)\n"); //In caso la funzione non corrispondi, stampa l'errore etermina
                exit(EXIT_FAILURE);
        }
    }
    return 0;
}