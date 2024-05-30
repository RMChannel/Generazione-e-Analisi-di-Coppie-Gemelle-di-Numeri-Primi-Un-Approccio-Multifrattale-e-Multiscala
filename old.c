#include <stdio.h>
#include <stdlib.h>
int count=0;

int myAtoi(char *s) { //Ricreazione dell'atoi()
    int n=0;
    while(*s) {
        n=(n*10)+(*s-'0');
        s++;
    }
    return n;
}

/*
Questa funzione si occupa di rimuovere tutti i numeri non primi da c attraverso i k calcolati.
Per farlo, semplicemente imposta tutti i numeri rilevati come non primi a 0.
*/
void removeNotPrimes(long long int k[], long long int c[], long long int n, long long int n3) {
    long long int n2;
    for(long long int i=0;i<n;i++) { //Scorro per tutto k
        n2=k[i]-1; //Mi salvo il k dentro l'array e diminuisco di 1 (questo perché gli array partono da 0)
        if (n2<n3) { //Questo controllo copre il caso in cui l'indirizzo dato da k sia maggiore di quello disponibile in c, nel caso lo sia non va a modificare (evito il segmentation fault)
            c[n2]=0; //In caso contrario, imposta la posizione k in c a 0 (così da skipparla nella stampa)
        }
    }
}

/*
Questa funzione si occupa di fare il merge tra i due array di calcolo, così che possa restituire un array fusione (tra i 2 array passati) ordinato.
Essa si basa sul principio del Merge Sort.
*/
long long int *merge(long long int a1[], long long int a2[],long long int n1, long long int n2) {
	long long int i,j,k; //Dichiara 3 interi che verrano usati come puntatori
    long long int *copia=calloc(n1+n2,sizeof(long long int)); //Crea l'array copia di dimensione uguale alla somma delle dimensioni dei 2 array passati
	for(i=0,j=0,k=0;i<n1 && j<n2;k++) { //Inizia il ciclo (ad ogni iterazione vado avanti sull'array copia) e si ferma quando uno dei due array è terminato
		if (a1[i]<=a2[j]) { //Se il numero del 1°array è minore o uguale a quello del 2°
			copia[k]=a1[i]; //Copio dal 1°
			i++; //Vado avanti sul 1°
		}
		else { //In caso contario
			copia[k]=a2[j]; //Copia il numero del 2°array nell'array copia
			j++; //Vado avanti sull'array 2
		}
	}
	for(;i<n1;i++,k++) copia[k]=a1[i]; //Copia i restanti elementi dall'array ancora non finito
	for(;j<n2;j++,k++) copia[k]=a2[j];
	return copia; //Restituisco l'array copia
}

//Questa funzione si occupa di trovare e stampare tutti i numeri primi gemelli trovati
void findGemelli(long long int c[], long long int n) {
    long long int i2, i3=1; //Questi due puntatori, uno corrisponderà al numero successivo per trovare le coppie (i2), l'altro invece si occupa di tenere traccia di quante coppie sono state trovate
    for(long long int i=0;i3<=n;i=i2) { //i scorre l'array ed ad ogni iterazione viene reimpostato ad i2
        while(c[i]==0) i++; //Scorre finché ci sono gli 0 (visto che sono da saltare)
        i2=i+1; //i2 va nella posizione avanti a quella di i 
        while(c[i2]==0) i2++; //Scorre finché ci sono gli 0 (visto che sono da saltare)
        if ((c[i]+2)==c[i2]) { //Se il numero dato dalla posizione i, sommato di 2, è uguale a quello presente nella posizione i2, allora è stata trovata una coppia di numeri primi gemelli
            printf("%lld Coppie di gemelli: %lld %lld\n",i3,c[i],c[i2]); //Viene stampata
            i3++; //E viene incrementato il contatore di coppie di numeri primi
        }
    }
}

//Questa funzione si occupa di trovare e stampare, su file, tutti i numeri primi gemelli trovati
void findAndSaveGemelli(long long int c[], long long int n) {
    long long int i2, i3=1; //Questi due puntatori, uno corrisponderà al numero successivo per trovare le coppie (i2), l'altro invece si occupa di tenere traccia di quante coppie sono state trovate
    FILE *fp;
    fp=fopen("output.txt","w"); //Apro il file
    for(long long int i=0;i3<=n;i=i2) { //i scorre l'array ed ad ogni iterazione viene reimpostato ad i2
        while(c[i]==0) i++; //Scorre finché ci sono gli 0 (visto che sono da saltare)
        i2=i+1;
        while(c[i2]==0) i2++; //Scorre finché ci sono gli 0 (visto che sono da saltare)
        if ((c[i]+2)==c[i2]) { //Se il numero dato dalla posizione i, sommato di 2, è uguale a quello presente nella posizione i2, allora è stata trovata una coppia di numeri primi gemelli
            fprintf(fp,"%lld Coppie di gemelli: %lld %lld\n",i3,c[i],c[i2]); //Viene stampata
            i3++; //E viene incrementato il contatore di coppie di numeri primi
        }
    }
    fclose(fp); //Chiudo il file
}

void createCandidate(int N) {
    long long int n2=N*50; //Moltiplico per 50 il numero di input, così da essere sicuro da avere abbastanza spazio per tutti i valori di c
    //assgno spazio definito in modo arbitrario ai k, così da poter coprire tutti i casi di input
    long long int *k1=calloc(100000000,sizeof(long long int));
    long long int *k2=calloc(100000000,sizeof(long long int));
    long long int *k3=calloc(100000000,sizeof(long long int));
    long long int *c1=calloc(n2,sizeof(long long int));
    long long int *c2=calloc(n2,sizeof(long long int));
    
    //generano tutti i k con le 3 regole di selezione
    for (long long int x=1, i=0;x<=10000;x++) {
        for (long long int y=1;y<=10000;y++,i++) {
            k1[i]=((6*x*y)+x-y);
            k2[i]=((6*x*y)-x-y);
            k3[i]=((6*x*y)+x+y);
        }
    }
    //genero i candidati primi
    for(long long int ki=1, i=0;ki<=n2; ki++, i++) {  
        c1[i]=(6*ki)-1;
        c2[i]=(6*ki)+1;
    }
    //Richiamo alla funzione di rimozione dei numeri non primi per ogni regola di selezione
    removeNotPrimes(k1,c1,100000000,n2); //Rimuove i non primi dall'array formato dai candidati della regola 6k-1 con la 1°regola
    removeNotPrimes(k2,c2,100000000,n2); //Rimuove i non primi dall'array formato dai candidati della regola 6k+1 con la 2°regola
    removeNotPrimes(k3,c2,100000000,n2); //Rimuove i non primi dall'array formato dai candidati della regola 6k+1 con la 3°regola
    long long int *a=merge(c1,c2,n2,n2); //Infine faccio un merge degli array di, con numeri non primi rimossi, così da avere un unico array ordinato contenente tutti i numeri primi
    findGemelli(a,N); //Stampo il risultato su terminale
    //findAndSaveGemelli(a,N); //Se si vuole salvare su file si può usare questa funzione
}

void createCandidateForK(int ki1, int kf) {
    long long int n2=50000;
    //assgno spazio definito in modo arbitrario ai k e a tutti i valori c, così da poter coprire tutti i casi di input
    long long int *k1=calloc(100000000,sizeof(long long int));
    long long int *k2=calloc(100000000,sizeof(long long int));
    long long int *k3=calloc(100000000,sizeof(long long int));
    long long int *c1=calloc(n2,sizeof(long long int));
    long long int *c2=calloc(n2,sizeof(long long int));
    
    //generano tutti i k con le 3 regole di selezione
    for (long long int x=1, i=0;x<=10000;x++) {
        for (long long int y=1;y<=10000;y++,i++) {
            k1[i]=((6*x*y)+x-y);
            k2[i]=((6*x*y)-x-y);
            k3[i]=((6*x*y)+x+y);
        }
    }
    //genero i candidati primi
    for(long long int ki=1, i=0;ki<=n2; ki++, i++) {  
        c1[i]=(6*ki)-1;
        c2[i]=(6*ki)+1;
    }
    removeNotPrimes(k1,c1,100000000,n2);
    removeNotPrimes(k2,c2,100000000,n2);
    removeNotPrimes(k3,c2,100000000,n2);
    long long int *a=merge(c1,c2,n2,n2);
    for(;((ki1)%6)!=0;ki1++);
    for(;((kf)%6)!=0;kf--);
    for(long long int i=0,i2=i+1,i3=1;a[i2]<kf;i=i2) {
        while(a[i]==0) i++;
        i2=i+1;
        while(a[i2]==0) i2++;
        if ((a[i]+2)==a[i2] && (a[i]+2)>ki1) {
            printf("%lld Coppie di gemelli: %lld %lld\n",i3,a[i],a[i2]);
            i3++;
        }
    }
}


/*
Questo programma ha 2 funzioni:
1°Calcola un numero n di coppie di numeri primi gemelli
2°Calcola tutte le coppie comprese tra x e y
*/
int main(int argc, char *argv[]) {
    if (argc<3 || argc>4) {
        fprintf(stderr,"Uso corretto:\n./main.exe 1 numero-coppie\n./main.exe 2 ki kf\n"); //Controlla il numero di argomenti, nel caso siano errati, stampa errore
        exit(EXIT_FAILURE); //E termina il programma
    }
    if (argv[1][0]=='1') createCandidate(atoi(argv[2])); //Richiamo alla 1°funzione
    else if(argv[1][0]=='2') createCandidateForK(atoi(argv[2]),atoi(argv[3])); //Richiamo alla 2°funzione
    else {
        fprintf(stderr,"Uso corretto:\n./main.exe 1 numero-coppie\n./main.exe 2 ki kf\n"); //Nel caso in cui gli argomenti siano errati, allora stampa errore
    }
}