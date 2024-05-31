#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 500000

//Questa funzione ha lo scopo di creare gli array (a 100 a 100) che corrispondono alle righe
void riallocazione(long long int** mat, int *n) {
    for (int i=0;i<100;i++) {
        mat[i]=malloc(N*sizeof(long int)); //Utilizzo la malloc, così da non sprecare memoria (spiegazione alla fine del codice)*
    }
    (*n)+=100; //Incremento il numero di righe di 100, così da avere traccia di quante righe vengono calcolate
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

int regola(long long int n, long long int *mat, int *righe, int regola) { //Questa è la funzione di controllo per ogni valore del k, è uguale per ogni regola, cambiano solo i parametri passati
    long long int x=1, y=1; //Crea le variabili di coordinate
    long long int k; //Crea il k che andrò di volta in volta a calcolare
    long long int *m=(long long int *)mat[0]; //E inizializza il puntatore alla 1°riga della matrice
    while (1) {
        if ((long int *)m[y-1]==NULL) m[y-1]=calcolo(regola,x,y); //Se il valore della matrice non esiste, allora viene calcolato e salvato nella matrice (se esiste già, semplicemente non lo calcolo)
        k=m[y-1]; //E salva direttamente in k
        if (n==k) return 0;//Se trova il  k all'interno della matrice, allora è sicuramente primo e restituisce 0
        else if (n<k && y==1) return 1;  //Altrimenti se è minore del valore di controllo e ci troviamo sulla 1°colonna, allora restituisce 1, poiché è sicuramente primo
        else if (n<k) { //Altrimenti se è minore, ma non ci troviamo sulla 1°colonna
            y=1; //Si riposiziona sulla prima colonna
            x++; //Cambio riga
            if (x>(*righe)) { //Nel caso si superino il numero di righe già create
                riallocazione((long long int **)(mat+x-1),righe); //Ne vengono allocate altre 100
            }
            m=(long long int *)mat[x-1]; //Cambio di riga sul puntatore della matrice
        }
        else if (n>k) y++;  //Invece, se il valore dato è maggiore di k, allora scorre alla posizione successiva sulla riga
    }
}

int isPrime(long long int n, int controllo, long long int *mat1, long long int *mat2, long long int *mat3, int *righe1, int *righe2, int *righe3) { //Questa funzione va a richiamare la funzione di controllo con i parametri corretti a seconda della regola che si vuole utilizzare
    if (controllo==1) { //Se è un valore k dei 6k-1, allora fa il controllo solo su regola 1
        return regola(n,mat1,righe1,1);
    }
    else if (controllo==2) { //Se è un valore k dei 6k+1, allora fa il controllo su regola 2 e regola 3
        return (regola(n,mat2,righe2,2) && regola(n,mat3,righe3,3)); //Se tutte e due restituiscono che è un numero primo, allora restituisce che è primo, altrimenti se una delle due restituisce che il numero non è primo, allora restituisce che non è primo
    }
    return 1;
}

//Questa è la funzione che stampa della gestione del calcolo e della stampa dei numeri primi.
void createCandidate(long long int c1[], long long int n) {
    clock_t inizio, fine; //Crea della variabili per il tempo
    inizio = clock(); //Salva il tempo di inizio di esecuzione del programma
    FILE *fp;
    fp=fopen("output.txt","w"); //Creazione un file di output (è possibile anche cambiare e stampare direttamente a terminale)
    long long int *mat1=malloc(N*sizeof(long long int *)); //Crea le 3 matrici partendo da un array di puntatori (che corrispondono alle righe)
    long long int *mat2=malloc(N*sizeof(long long int *)); //Poi a cascata vengano incrementati, quando necessari, di volta in volta di 100
    long long int *mat3=malloc(N*sizeof(long long int *)); //Sempre con la malloc, così da non occupare memoria inutilmente (spiegazione sotto)
    int righe1=0;
    int righe2=0; //Utilizza delle variabili intere che tengono traccia di quante righe sono state effettivamente create (così da evitare di andare fuori memoria ed avere un segmentation fault)
    int righe3=0;
    riallocazione((long long int **)mat1,&righe1);
    riallocazione((long long int **)mat2,&righe2); //Vengono create le prime 100 righe di ogni matrice
    riallocazione((long long int **)mat3,&righe3);
    for(long long int ki=1, flag, i1=0, i2=1;i2<=n; ki++) { //Ora inizia il calcolo effettivo dei numeri primi, mi fermo quando il numero di coppie trovate arriva a quello richiesto dall'utente
        flag=0; //Questa variabile controlla se è stato trovato almeno un numero primo dai 6k-1 e dai 6k+1
        if(isPrime(ki,1,mat1,mat2,mat3,&righe1,&righe2,&righe3)) { //Controlla che il k dato corrisponde ad un numero primo per la regola dei 6k-1
            flag=1; //Se si, imposta flag a 1
            c1[i1]=(6*ki)-1; //Calcola l'effettivo valore
            i1++; //Aumenta il numero di numeri primi trovati
        }
        if(isPrime(ki,2,mat1,mat2,mat3,&righe1,&righe2,&righe3)) { //Stesso discorso per quanto riguarda i 6k+1
            flag=1;
            c1[i1]=(6*ki)+1;
            i1++;
        }
        if (flag && (c1[i1-2]+2)==c1[i1-1]) { //Ora, se flag è stato attivato e se nei numeri primi c'è una coppia di numeri primi gemelli
            fine = clock(); //Fermo il tempo al calcolo
            fprintf(fp,"%lld COPPIA: %lld %lld  T: %f\n",i2,c1[i1-2],c1[i1-1],(((double) (fine - inizio)) / CLOCKS_PER_SEC)); //E stampa tutto (o su file o a terminale)
            //printf("%lld COPPIA: %lld %lld  T: %f\n",i2,c1[i1-2],c1[i1-1],(((double) (fine - inizio)) / CLOCKS_PER_SEC));
            i2++; //Incrementa il numero di coppie trovate
        }
    }
}

void createCandidateForK(long long int c1[], int ki, int kf) {
    clock_t inizio, fine; //Crea della variabili di tempo
    inizio = clock();  //Salva lora di inizio di esecuzione del programma
    FILE *fp;
    fp=fopen("output.txt","w"); //Creazione del file di output (è possibile anche cambiare e stampare direttamente a terminale)
    long long int *mat1=malloc(N*sizeof(long long int *)); //Crea le 3 matrici, esse sono create partendo da un array di puntatori (che corrispondono alle righe)
    long long int *mat2=malloc(N*sizeof(long long int *)); //Poi a cascata vengano incrementati, quando necessari, di volta in volta di 100
    long long int *mat3=malloc(N*sizeof(long long int *)); //Sempre con la malloc, così da non occupare memoria inutilmente (spiegazione sotto)
    int righe1=0;
    int righe2=0; //Utilizza delle variabili intere che mi tengono traccia di quante righe sono state effettivamente create (così da evitare di andare fuori memoria ed avere un segmentation fault)
    int righe3=0;
    riallocazione((long long int **)mat1,&righe1);
    riallocazione((long long int **)mat2,&righe2); //Vengono create le prime 100 righe di ogni matrice
    riallocazione((long long int **)mat3,&righe3);
    for(;((ki)%6)!=0;ki++); //Calcola i k corrispondenti ai numeri dati facendo la formula inversa
    for(;((kf)%6)!=0;kf--);
    ki/=6;
    kf/=6;
    for(long long int i1=0, i2=0, flag;ki<=kf; ki++) { //Inizio il calcolo effettivo
        flag=0; //Questa variabile controlla se è stato trovato almeno un numero primo dai 6k-1 e dai 6k+1
        if(isPrime(ki,1,mat1,mat2,mat3,&righe1,&righe2,&righe3)) {  //Controllo che il k dato corrisponde ad un numero primo per la regola dei 6k-1
            flag=1; //Se si, imposto flag a 1
            c1[i1]=(6*ki)-1; //Mi calcolo l'effettivo valore, nel caso in cui sia un numero primo
            i1++; //Aumento il numero di numeri primi trovati
        }
        if(isPrime(ki,2,mat1,mat2,mat3,&righe1,&righe2,&righe3)) { //Stesso discorso per i 6k+1
            flag=1;
            c1[i1]=(6*ki)+1;
            i1++;
        }
        if (flag && (c1[i1-2]+2)==c1[i1-1]) { //Ora, se flag è stato attivato e se nei numeri primi c'è una coppia di numeri primi gemelli
            fine = clock(); //Ferma il calcolo del tempo
            //fprintf(fp,"%lld Coppie di gemelli: %lld %lld\n",i2+1,c1[i1-2],c1[i1-1]); //E stampo tutto (o su file o a terminale)
            printf("%lld Coppie di gemelli: %lld %lld\n",i2+1,c1[i1-2],c1[i1-1]);
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
    long long int *c1=calloc(1000000,sizeof(long long int)); //Allocazione dell'array dove verranno messi i risultati
    if (argv[1][0]=='1') createCandidate(c1,atoi(argv[2])); //1°funzione
    else if(argv[1][0]=='2') createCandidateForK(c1,atoi(argv[2]),atoi(argv[3])); //2°Funzione
    else {
        fprintf(stderr,"Uso corretto:\n./main.exe 1 numero-coppie\n./main.exe 2 ki kf\n"); //Stampa dell'errore in caso di argomenti errati
    }
}

/*
*Utilizzo la malloc con la matrice, sia per le righe che per le colonne, perché la malloc non occupa memoria
all'interno della RAM finché non viene inizializzato il valore, quindi sfruttando quest'opzione
vado ad occupare soltanto la memoria necessaria ai calcoli e non occupo la memoria non necesssaria ai conti con degli 0.
Per controllare se un valore è inizializzato o meno, controllo se esso equivale a NULL, se lo è vuol dire che non è stato inizializzato
e che occorre calcolarlo, altrimenti viene ricavato il valore di quella locazione.
*/