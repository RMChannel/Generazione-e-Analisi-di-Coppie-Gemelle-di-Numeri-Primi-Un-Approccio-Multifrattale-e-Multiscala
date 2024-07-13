#include <stdio.h>
#include <stdlib.h>

int rule1(int j){
    return j%3==0;
}

int rule2(int j){
    int u = j%10;
    int r2[6] = {0, 1, 4, 5, 6, 9};
    for(int i=0;i<6;i++) {
        if(u==r2[i]) return 1;
    }
    return 0;
}

int calcMMax(int i, int H) {
    return H/((2*i)+1);
}


int main() {
    int H, jMax, Mmax;
    int temp;

    printf("Inserisci H: ");
    scanf("%d",&H);
    jMax=(H/3)-1;
    printf("jmax = %d\n",jMax);

    for (int i = 1; i <= jMax; i++){
        if(rule1(i) || rule2(i)) {
            printf("i=%d %d %d\n",i,(2*i)-1,(2*i)+1);
        }
    }
    
} //Ma che stai facendo
// mo ho provato ad applicare le due regole alla prima cosa ma è inutile