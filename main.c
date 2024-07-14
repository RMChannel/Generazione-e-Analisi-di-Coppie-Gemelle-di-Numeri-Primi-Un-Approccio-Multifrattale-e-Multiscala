#include <stdio.h>
#include <stdlib.h>

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

void inserisci_ordinato(int *arr, int *size, int value) {
    // Trova la posizione corretta per 'value' utilizzando la ricerca binaria
    int i = binary_search(arr, 0, *size, value);    
    for (int j = *size; j > i; j--) {// Sposta tutti gli elementi a destra di 'i' di una posizione per fare spazio al nuovo valore
        arr[j] = arr[j - 1];
    }
    arr[i] = value; // Inserisce 'value' nella posizione corretta trovata
    (*size)++;// Incrementa la dimensione dell'array
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

void printFounded(int found[], int iFound) {
    for(int i=0;i<iFound;i++) {
        if((found[i]+2)==found[i+1]) printf("%d %d\n",found[i],found[i+1]);
    }
    printf("iFound: %d\n",iFound);
}

int verify(int n) {
    if((n%3)!=0) return 0;
    else if (n<10) return 1;
    else {
        int control[]={0,1,4,5,6,9};
        int u=n%10;
        for(int i=0;i<6;i++) if(u==control[i]) return 1;
    }
    return 0;
}

void addFound(int *iFound, int found[], int k) {
    if(verify(k)) {
        int n=(2*k)-1;
        if(ifNotExist(found,*iFound,n)) {
            inserisci_ordinato(found,iFound,n);
        }
        n+=2;
        if(ifNotExist(found,*iFound,n)) {
            inserisci_ordinato(found,iFound,n);
        }
    }
}

void printArray(int a[], int n) {
    for(int i=0;i<n;i++) printf("%d ",a[i]);
    printf("\n");
}

int main() {
    int H, found[200000], jMax;
    found[0]=3;
    int iFound=1, k=0, kGen=3;
    printf("Inserisci il numero di coppie da trovare: ");
    scanf("%d",&H);
    jMax=(H/3)-1;
    printf("jMax= %d\n",jMax);
    while((iFound/2)<H) {
        int kTemp=k;
        for(int i=1;i<=jMax;i++) {
            addFound(&iFound,found,kGen*i);
            while(kTemp>0) {
                addFound(&iFound,found,(kGen*i)+kTemp);
                addFound(&iFound,found,(kGen*i)-kTemp);
                kTemp--;
            }
        }
        kGen+=2;
        k++;
    }
    //printFounded(found,iFound);
    printArray(found,iFound);
}