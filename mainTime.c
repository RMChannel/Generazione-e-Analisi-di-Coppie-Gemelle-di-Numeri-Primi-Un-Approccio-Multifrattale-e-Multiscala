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

//Funzione che stampa l'intero array su terminale
void printArray(int *a, int n) {
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

void printFileArray(int *a, int n) {
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

/*

Abbiamo scelto di utilizzare la funzione di ricerca binaria su un array perché, 
per array di grandi dimensioni come i nostri, la ricerca lineare risultava estremamente inefficiente, 
rallentando significativamente il programma.
*/

int binary_search(int *arr, int low, int high, int value) {
    if(value > arr[high - 1]) return high; // Se il valore cercato è maggiore dell'ultimo elemento dell'array, ritorna high
    while (low < high) { // Ciclo while per continuare la ricerca finché 'low' è minore di 'high'
        // Calcola il punto medio dell'intervallo corrente
        int mid = low + (high - low) / 2;
        if (arr[mid] == value) { 
            return mid;        // Se l'elemento a 'mid' è min ore del valore cercato, restringi la ricerca alla metà superiore
        } else if (arr[mid] < value) {
            low = mid + 1;

        // Se l'elemento a mid è maggiore del valore cercato, restringi la ricerca alla metà inferiore
        } else {
            high = mid;
        }
    }
    // Se il ciclo termina senza trovare il valore, ritorna la posizione 'low'
    return low;
}


/*
inserisci_ordinato aggiunge gli elementi secondo una relazione d'ordine.
Volevamo che gli elementi fossero inseriti secondo una precisa relazione d'ordine, 
in modo da poterli analizzare in maniera più efficiente.
*/

void inserisci_ordinato(int *arr, int *size, int value) {
    // Trova la posizione corretta per 'value' utilizzando la ricerca binaria
    int i = binary_search(arr, 0, *size, value);    
    for (int j = *size; j > i; j--) {// Sposta tutti gli elementi a destra di 'i' di una posizione per fare spazio al nuovo valore
        arr[j] = arr[j - 1];
    }
    arr[i] = value; // Inserisce 'value' nella posizione corretta trovata
    (*size)++;// Incrementa la dimensione dell'array
}


/*
La funzione `controlloPrime` verifica se un numero n è primo utilizzando un array preesistente di numeri primi. 
Prima controlla se n è 1 o pari (escluso 2), restituendo 0 in tal caso poiché tali numeri non sono primi. 
Successivamente, itera sull'array primes confrontando gli elementi dall'inizio e dalla fine verso il centro. 
Se n è divisibile per uno degli elementi dell'array, restituisce 0, indicando che n non è primo. 
Se nessuna divisione ha resto zero, la funzione restituisce 1, confermando che n è primo.
*/

int controlloPrime(int *primes, int n) {
    // Controlla se n è uguale a 1 o se è pari, in tal caso non è primo
    if (n == 1 || (n % 2) == 0) return 0;
    // Itera attraverso gli elementi dell'array primes
    for (int i = 0, iFinal = i1 - 1; i < iFinal; i++, iFinal--) {
        // Controlla se il numero è divisibile per uno degli elementi dell'array
        if ((n % primes[i]) == 0 || (n % primes[iFinal]) == 0) return 0;
    }
    // Se il numero supera i controlli precedenti, è considerato primo
    return 1;
}


/*
La funzione ifNotExist controlla atraverso una ricerca binaria se un certo target all'interno dell'array
esiste oppure no.
*/

int ifNotExist(int *arr, int n, int target) {
    //guarda la ricerca binaria
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

int calcolaFamiglie(int *primes, int *notprimes, int m, int *foundPrimes, int n, int i, FILE *fp, clock_t inizio) {
    int limit=m, first=1, a, b, k; //Imposta limite ad m e first viene iniziallizato ad 1
    clock_t fine;
    for(a=0,b=0,k=1,n=m*k;(a<=limit && b<=limit);k++,n=m*k) { // il ciclo termina quando o a o b o entrambi superano il limite
        b=n-1; //In n si trova m*k e con esso calcola sia a che b
        if(controlloPrime(primes,b)) { //Controlla che b sia un numero primo
            inserisci_ordinato(primes,&i1,b); //Nel caso lo sia, viene inserito in primes in modo ordinato
            if(ifNotExist(notprimes,i2,b)) inserisci_ordinato(notprimes,&i2,b); //E nel caso non esista in notprimes, allora viene aggiunto anche lì (visto che i controlli li facciamo in modo univoco con un unico array)
            (*foundPrimes)++; //Il numero di numeri primi trovati viene incrementato
            fine=clock();
            fprintf(fp,"Numero primo: %d T: %f\n",*foundPrimes,(((double) (fine - inizio)) / CLOCKS_PER_SEC)); //Stampa su file il tempo
        }
        a=n+1;
        if(controlloPrime(primes,a)) { //Controlla che a sia un numero primo
            inserisci_ordinato(primes,&i1,a); //Nel caso lo sia, viene inserito in primes in modo ordinato
            (*foundPrimes)++; //Il numero di numeri primi trovati viene incrementato
            fine=clock();
            fprintf(fp,"Numero primo: %d T: %f\n",*foundPrimes,(((double) (fine - inizio)) / CLOCKS_PER_SEC)); //Stampa su file il tempo
        }
        if(ifNotExist(notprimes,i2,a)) inserisci_ordinato(notprimes,&i2,a);
        if(first) { //Il limite viene moltplicato col numero primo successivo, così che troviamo l'effettivo limite
            limit*=primes[i];
            first=0; //first viene riportato a 0, visto che oramai il limite è stato calcolato
        }
     }
    for (; notprimes[i] < m && i < i2; i++) {
        k = 1;
        do {
            a = (m * k) + notprimes[i]; //Ora viene effettuato il calcolo per ogni numero trovato in notprimes, così da trovare altri possibili numeri primi seguendo la formula m*k+n
            if (controlloPrime(primes, a)) { //Controlla che il numero trovato sia prima
                if (ifNotExist(primes, i1, a)) { //Se si e non si trova in primes
                    inserisci_ordinato(primes, &i1, a); //Allora viene aggiunto
                    (*foundPrimes)++; //E il numero di numeri primi trovati ivene incrementato
                    fine=clock();
                    fprintf(fp,"Numero primo: %d T: %f\n",*foundPrimes,(((double) (fine - inizio)) / CLOCKS_PER_SEC)); //Stampa su file il tempo
                }
            } 
            if (ifNotExist(notprimes, i2, a)) { //Se non si trova in notprimes
                inserisci_ordinato(notprimes, &i2, a); //Allora viene aggiunto anche li
            }
            k++; //Incremento k
        }while (a < limit); //Fa questo calcolo per ogni numero di notprimes e finché quel numero non supera il limite
    }
    return limit; //Ritorno il limite, così che esso venga salvato in m e venga utilizzato come prossimo punto di calcolo
}

/*
La funzione findPrimes, per prima cosa alloca lo spazio di memoria per i due array, 
e passa i valori ad calcolaFamiglie.
*/

void findPrimes(int n) {
    FILE *fp;
    fp=fopen("output.txt","w");
    clock_t inizio, fine;
    size_t size=N*sizeof(int);
    int *primes=malloc(size); //Array dove verrano salvati i numeri primi
    int *notprimes=malloc(size); //Array dove verrano salvati i numeri NON primi
    notprimes[0]=4;
    primes[0]=2; //Inizializza solo un valore
    int foundPrimes=1, m=2, i=1;
    while(foundPrimes<n) { //Cicla finché il numero di numeri primi trovati non supera quello richiesto
        m=calcolaFamiglie(primes,notprimes,m,&foundPrimes,n,i,fp,inizio);
        i++;
    }
    printArray(primes,n); //Stampo tutto
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
    FILE *fp;
    fp=fopen("output.txt","w");
    clock_t inizio, fine;
    size_t size=N*sizeof(int);
    int *primes=malloc(size); //Array dove verrano salvati i numeri primi
    int *notprimes=malloc(size); //Array dove verrano salvati i numeri NON primi
    notprimes[0]=4;
    primes[0]=2; //Inizializza solo un valore
    int foundPrimes=1, m=2, i=1;
    while(foundPrimes<(n*5)) {
        m=calcolaFamiglie(primes,notprimes,m,&foundPrimes,n,i,fp,inizio); //Avvia il calcolo, calcolando il tanti numeri primi quanto il quintuplo del numero di coppie richieste
        i++;
    }
    for(int i1=0, i2, i3=1;i3<=n;i1=i2) { //i1 rappresenta il 1°numero, i2 il 2°numero e i3 il conto delle coppie trovate
        i2=i1+1; //i2 viene spostato al successivo di i1
        if((primes[i1]+2)==primes[i2]) { //Se l'elemento in i1, sommato di 2, è uguale all'elemento in i2, allora ha trovato una coppia di numeri primi gemelli
            printf("%d COPPIA: %d %d\n",i3,primes[i1],primes[i2]); //Stampa
            i3++; //Incrementa il numero di coppie trovate
        } //i1 viene spostato ad i2
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