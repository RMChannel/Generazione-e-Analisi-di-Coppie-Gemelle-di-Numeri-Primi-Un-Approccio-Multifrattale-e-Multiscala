#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define N 500000
int k; //Crea un'unica variabile k globale, così non doverla inizializzare e allocare ad ogni funzione, ma semplicemente poter cambiare il valore

//Questa funzione ha lo scopo di creare gli array incrementandoli di 100 in base alla necessità(corrispondono alle righe della matrice) 
void riallocazione(long long int* mat, int *n) {
    for (int i=0;i<100;i++) {
        mat[i]=malloc(N*sizeof(long int)); //Utilizzo la malloc, così da non sprecare memoria (spiegazione sotto)
    }
    (*n)+=100;//Incremento il numero di righe di 100, così da avere traccia di quante righe vengono calcolato
}

/*
Questa funzione si occupa di calcolare il valore da inserire nella matrice a seconda di quale delle 3 regole di selezione stiamo usando,
infatti lo swtich, a seconda se sia regola 1,2,3 cambia il calcolo.
Ed infine restituisce il valore calcolato
*/
long int calcolo(int regola, int x, int y) {
    int n=6*x*y;
    switch(regola) {
        case 1:
            return (n+x-y);
        case 2:
            return (n-x-y);
        case 3:
            return (n+x+y);
        default:
            return 0;
    }
}

int controlloLeft(long int n, long int *mat, int *righe, int regola, int x, int y) { //Questa funzione si occupa di fare il controllo (se il numero k dato è un numero primo o meno) sul lato sinistro della matrice
    long int *m=(long int *)mat[(x-1)]; //Puntatore che punta alla riga data dalla funzione regola, così da posizionarsi sulla riga da dove occorre iniziare il controllo, in questo caso non avviene nessun controllo sulle righe perchè gia avvenuto nella prima regola
    while(1) {
        if ((long int *)m[y-1]==NULL) m[y-1]=calcolo(regola,x,y); //Se il valore della matrice non esiste, allora viene calcolato e inserito nella matrice (se esiste già, non viene calcolato)
        k=m[y-1]; //Salva direttamente in k
        if (n==k) return 0; //Se viene trovato il k all'interno della matrice, allora il numero non è primo
        else if(n<k) { //Se n è minore del k calcolato
            y--; //Decrementa la colonna
            if(y<=0) return 1; //Nel caso in cui y tenta di accedere ad una posizione dopo il limite dellaa matrice, allora il numero è sicuramente primo e restituisco 1
        }
        else if (n>k) { //Al contrario, se il numero che controllo è maggiore del k, allora:
            x++; //Increnenta la riga 
            if (x>(*righe)) { //Nel caso si superino il numero di righe già create
                riallocazione(mat+x-1,righe); //Ne vengono allocate altre 100
                }
            }
        m=(long int *)mat[x-1]; //Cambio di riga sul puntatore della matrice
    }
}

int controlloRight(long int n, long int *mat, int *righe, int regola, int x, int y) { //Questa funzione si occupa di fare il controllo(se il numero k dato è un numero primo o meno) sul lato destro della matrice
    long int *m=(long int *)mat[(x-1)]; //Puntatore che punta alla riga data dalla funzione regola, così da posizionarsi sulla riga da dove occorre iniziare il controllo, in questo caso non avviene nessun controllo sulle righe perchè gia avvenuto nella prima regola
    while(1) {
        if ((long int *)m[y-1]==NULL) m[y-1]=calcolo(regola,x,y); //Se il valore della matrice non esiste viene calcolato e salvato nella matrice (se esiste già, semplicemente non viene calcolato)
        k=m[y-1]; //Salva direttamente in k
        if(n<k && x==1) return 1; //Nel caso in cui ci si trova sulla 1°riga e il numero che viene controllato è minore del k, allora vuol dire che il nostro numero è sicuramente primo
        else if (n>k) y++; //Nel caso in cui il numero sia maggiore di k, allora incrementa di colonna per scorrere in avanti
        else if(n<k && x!=1) { //Invece, nel caso in cui il numero è minore di k e non ci troviamo sulla 1°riga
            x--; //Spostamento di una riga più in alto
            m=(long int *)mat[x-1]; //Viene aggiornato il puntatore della matrice
        }
        else if (n==k) return 0; //Se viene trovato il k all'interno della matrice, allora il numero non è primo
    }
}

int regola(long int n, long int *mat, int *righe, int regola) { //Questa è la funzione che va a controllare in quale punto della diagonale si deve andare a cercare se è il numero è primo o meno 
    int x=1, y=1; //Inizializza le variabili di coordinate
    long int *m=(long int *)mat[0]; //E viene inizializzato il puntatore alla 1°riga della matrice
    do {
        if ((long int *)m[y-1]==NULL) m[y-1]=calcolo(regola,x,y); //Se il valore della matrice non esiste, allora viene calcolato e salvato nella matrice (se esiste già, semplicemente non lo calcolo)
        k=m[y-1]; //Salva direttamente in k
        if (n==k) return 0; //Se viene trovato il  k all'interno della matrice, allora è sicuramente non?????? è primo e restituisco 0????????????
        x++; //Nel caso non si trova, cambio di riga
        if (x>(*righe)) { //Nel caso in cui non ci siano più righe allocate, ne vengono allocate altre
            riallocazione(mat+x-1,righe);
        }
        m=(long int *)mat[x-1]; //Punto alla prossima riga
        y++; //Incremento anche la colonna(visto che dobbiamo scorrere sulla diagonale, vengono incrementati x e y contemporaneamente di 1 a 1)
    } while(n>k); //Il ciclo si ripete finché il k calcolato non è minore rispetto alla n che stiamo cercando
    return (controlloLeft(n,mat,righe,regola,x-1,y-1) && controlloRight(n,mat,righe,regola,x-1,y-1)); //Infine si effettua il controllo a sinistra e a destra della matrice, infatti se uno dei due restituisce che non è primo, allora non sarà primo, se invece tutte e due restituiscono che è primo, allora è sicuramente primo e restituisco che è primo
}

int isPrime(long int n, int controllo, long int *mat1, long int *mat2, long int *mat3, int *righe1, int *righe2, int *righe3) { //Questa funzione va a richiamare la funzione di controllo con i parametri corretti a seconda della regola che si vuole utilizzare
    if (controllo==1) return regola(n,mat1,righe1,1); //Se è un valore k dei 6k-1, allora fa il controllo solo su regola 1
    else return (regola(n,mat2,righe2,2) && regola(n,mat3,righe3,3)); //Se è un valore k dei 6k+1, allora fa il controllo su regola 2 e regola 3
    //Se tutte e due restituiscono che è un numero primo, allora restituisce che è primo, altrimenti se una delle due restituisce che il numero non è primo, allora restituisce che non è primo
}

void createCandidate(long int n) {
    clock_t inizio, fine; //Crea della variabili di tempo
    inizio = clock(); //Salva il tempo di inizio di esecuzione del programma
    FILE *fp;
    fp=fopen("output2.txt","w"); //Creazione del file di output (è possibile anche cambiare e stampare direttamente a terminale)
    long long int *mat1=malloc(N*sizeof(long long int *)); //Crea le 3 matrici, esse sono create partendo da un array di puntatori (che corrispondono alle righe)
    long long int *mat2=malloc(N*sizeof(long long int *)); ////Vengono create le prime 100 righe di ogni matrice
    long long int *mat3=malloc(N*sizeof(long long int *)); //Sempre con la malloc, così da non occupare memoria inutilmente (spiegazione sotto)
    int righe1=0;
    int righe2=0; //Inizializza delle variabili intere che tengono traccia di quante righe sono state effettivamente create (così da evitare di andare fuori memoria ed avere un segmentation fault)
    int righe3=0;
    riallocazione(mat1,&righe1);
    riallocazione(mat2,&righe2); //Vengono create le prime 100 righe di ogni matrice
    riallocazione(mat3,&righe3);
    long int c1[2]={0}; //Questo è un array con solo 2 posizioni, dove verrano salvate di volta in volta le coppie
    for(int ki=1, i1=0, i2=1;i2<=n; ki++,i1=0) { //Inizio il calcolo effettivo (in questo caso calcola finché il numero di coppie trovate non corrisponde a quello richiesto dall'utente)
        if(isPrime(ki,1,mat1,mat2,mat3,&righe1,&righe2,&righe3)) { //Se il k, preso in esame (nei 6k-1), corrisponde ad un numero primo
            c1[i1]=(6*ki)-1; //Allora ci calcoliamo il valore corrispondente
            i1++; //E incrementiamo il numero di numeri primi trovati
        }
        if(isPrime(ki,2,mat1,mat2,mat3,&righe1,&righe2,&righe3)) { //Stesso discorso per i 6k-1
            c1[i1]=(6*ki)+1;
            i1++;
        }
        if (i1!=0 && (c1[0]+2)==c1[1]) { //Nel caso in cui è stato trovato almeno un numero primo e se i 2 numeri sono una coppia, allora:
            fine = clock(); //Ferma il conteggio del tempo
            fprintf(fp,"%d COPPIA: %ld %ld  T: %f\n",i2,c1[0],c1[1],(((double) (fine - inizio)) / CLOCKS_PER_SEC)); //E stampo (su file o su terminale)
            //printf("%d COPPIA: %ld %ld  T: %f\n",i2,c1[0],c1[1],(((double) (fine - inizio)) / CLOCKS_PER_SEC));
            i2++; //Incrementa il numero di coppie trovate
        }
    }
}

void createCandidateForK(int ki, int kf) {
    clock_t inizio, fine; //Crea della variabili di tempo
    inizio = clock(); //Salva l'orario di inizio esecuzione
    //FILE *fp;
    //fp=fopen("output2.txt","w");
    long long int *mat1=malloc(N*sizeof(long long int *)); //Crea le 3 matrici, esse sono create partendo da un array di puntatori (che corrispondono alle righe)
    long long int *mat2=malloc(N*sizeof(long long int *)); ////Vengono create le prime 100 righe di ogni matrice
    long long int *mat3=malloc(N*sizeof(long long int *)); //Sempre con la malloc, così da non occupare memoria inutilmente (spiegazione sotto)
    int righe1=0;
    int righe2=0; //Crea delle variabili intere che mi tengono traccia di quante righe sono state effettivamente create (così da evitare di andare fuori memoria ed avere un segmentation fault)
    int righe3=0;
    riallocazione(mat1,&righe1);
    riallocazione(mat2,&righe2); //Vengono create le prime 100 righe di ogni matrice
    riallocazione(mat3,&righe3);
    long int c1[2]={0}; //Questo è un array con solo 2 posizioni, dove verrano salvate passo passo le coppie
    for(;((ki)%6)!=0;ki++); //Calcola i k corrispondenti ai numeri dati facendo la formula inversa
    for(;((kf)%6)!=0;kf--);
    ki/=6;
    kf/=6;
    for(int i1=0, i2=1;ki<=kf; ki++,i1=0) { //Inizia il calcolo effettivo (in questo caso però k partirà da ki e il ciclo finirà quando ki supererà kf)
        if(isPrime(ki,1,mat1,mat2,mat3,&righe1,&righe2,&righe3)) { //Controlla  che il k dato corrisponde ad un numero primo per la regola dei 6k-1
            c1[i1]=(6*ki)-1; //Calcola l'effettivo valore, nel caso in cui sia un numero primo
            i1++; //Incrementa il numero dei numeri primi trovati
        }
        if(isPrime(ki,2,mat1,mat2,mat3,&righe1,&righe2,&righe3)) { //Stesso discorso per i 6k+1
            c1[i1]=(6*ki)+1;
            i1++;
        }
        if (i1!=0 && (c1[0]+2)==c1[1]) { //Nel caso in cui è stato trovato almeno un numero primo e se i 2 numeri sono una coppia, allora:
            fine = clock(); //Viene salvato l'orario di fine esecuzione
            //fprintf(fp,"%d COPPIA: %ld %ld  T: %f\n",i2,c1[0],c1[1],(((double) (fine - inizio)) / CLOCKS_PER_SEC)); 
            printf("%d COPPIA: %ld %ld  T: %f\n",i2,c1[0],c1[1],(((double) (fine - inizio)) / CLOCKS_PER_SEC)); //E stampo (o su file o su terminale)
            i2++; //Incrementa il numero di coppie trovate
        }
    }
}

/*
Il programma offre 2 opzioni:
1° Calcola un numero n di coppie di numeri primi gemelli
2° Calcola le coppie di numeri primi gemelli con valore compreso tra ki e kf
*/
int main(int argc, char *argv[]) {
    if (argc<3 || argc>4) {
        fprintf(stderr,"Uso corretto:\n./main.exe 1 numero-coppie\n./main.exe 2 ki kf\n"); //Controllo sugli argomenti e stampa dell'errore nel caso siano errati
        exit(EXIT_FAILURE);
    }
    if (argv[1][0]=='1') createCandidate(atoi(argv[2])); //1°Funzione
    else if(argv[1][0]=='2') createCandidateForK(atoi(argv[2]),atoi(argv[3])); //2°Funzione
    else {
        fprintf(stderr,"Uso corretto:\n./main.exe 1 numero-coppie\n./main.exe 2 ki kf\n"); //Stampa dell'errore in caso di argomenti errati
    }
}

/*
Utilizzo la malloc con la matrice, sia per le righe che per le colonne, perché la malloc non occupa memoria
all'interno della RAM finché non viene inizializzato il valore, quindi sfruttando quest'opzione
vado ad occupare soltanto la memoria necessaria ai calcoli e non occupo la memoria non necesssaria ai conti con degli 0.
Per controllare se un valore è inizializzato o meno, controllo se esso equivale a NULL, se lo è vuol dire che non è stato inizializzato
e che devo calcolarlo, altrimenti viene ricavato il valore da quella locazione.
*/