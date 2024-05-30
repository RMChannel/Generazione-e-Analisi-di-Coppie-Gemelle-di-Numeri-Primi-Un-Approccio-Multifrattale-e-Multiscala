#include <stdio.h>
#include <stdlib.h>
int count=0;

int myAtoi(char *s) {
    int n=0;
    while(*s) {
        n=(n*10)+(*s-'0');
        s++;
    }
    return n;
}

void removeNotPrimes(long long int k[], long long int c[], long long int n, long long int n3) {
    long long int n2;
    for(long long int i=0;i<n;i++) {
        n2=k[i]-1;
        //printf("%d\n",n2);
        if (n2<n3) {
            c[n2]=0;
        }
    }
}

long long int *merge(long long int a1[], long long int a2[],long long int n1, long long int n2) {
	long long int i,j,k;
    long long int *copia=calloc(n1+n2,sizeof(long long int));
	for(i=0,j=0,k=0;i<n1 && j<n2;k++) {
		if (a1[i]<=a2[j]) {
			copia[k]=a1[i];
			i++;
		}
		else {
			copia[k]=a2[j];
			j++;
		}
	}
	for(;i<n1;i++,k++) copia[k]=a1[i];
	for(;j<n2;j++,k++) copia[k]=a2[j];
	return copia;
}

void findGemelli(long long int c[], long long int n) {
    long long int i2, i3=1;//i i2 indirizzi, i3 numero coppie
    for(long long int i=0;i3<=n;i=i2) {
        while(c[i]==0) i++;
        i2=i+1;
        while(c[i2]==0) i2++;
        if ((c[i]+2)==c[i2]) {
            printf("%lld Coppie di gemelli: %lld %lld\n",i3,c[i],c[i2]);
            i3++;
        }
    }
}

void printArray(long long int a[],long long  int n) {
    for(int i=0;i<n;i++) printf("%lld ",a[i]);
}

void findAndSaveGemelli(long long int c[], long long int n) {
    long long int i2, i3=1;
    FILE *fp;
    fp=fopen("output.txt","w");
    for(long long int i=0;i3<=n;i=i2) {
        while(c[i]==0) i++;
        i2=i+1;
        while(c[i2]==0) i2++;
        if ((c[i]+2)==c[i2]) {
            fprintf(fp,"%lld Coppie di gemelli: %lld %lld\n",i3,c[i],c[i2]);
            i3++;
        }
    }
}

void createCandidate(int N) {
    long long int n2=N*50;//scrivere del compromesso
    //assgno spazio definito in modo arbitrario (con e matrici cambia)
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
    findGemelli(a,N);
    //findAndSaveGemelli(a,N);
}

void createCandidateForK(int ki1, int kf) {
    long long int n2=50000;//scrivere del compromesso
    //assgno spazio definito in modo arbitrario (con e matrici cambia)
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

int main(int argc, char *argv[]) {
    if (argc<3 || argc>4) {
        fprintf(stderr,"Uso corretto:\n./main.exe 1 numero-coppie\n./main.exe 2 ki kf\n");
        exit(EXIT_FAILURE);
    }
    if (argv[1][0]=='1') createCandidate(atoi(argv[2]));
    else if(argv[1][0]=='2') createCandidateForK(atoi(argv[2]),atoi(argv[3]));
    else {
        fprintf(stderr,"Uso corretto:\n./main.exe 1 numero-coppie\n./main.exe 2 ki kf\n");
    }
}