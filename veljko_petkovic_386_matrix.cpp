#include <stdio.h>
#include <stdlib.h>
//VELJKO PETKOVIC 386
void mergesort(int* a, int levo, int desno);
void insertionsort(int* a, int n);
void merge(int* a, int levo, int sredina, int desno);
void unos_niza(int* a, int n);
void ispis_niza(int* a, int n);
void zad1(){
    int n; printf("Unesite n: "); scanf("%d", &n);
    int a[n]; unos_niza(a,n);
    //mergesort(a,0,n-1);
    insertionsort(a,n);
    ispis_niza(a,n);
}
void unos_matrice(int** a, int m, int n);
void ispis_matrice(int** a, int m, int n);
int* nadji_vrhove(int** a, int m, int n, int &br_vrhova);
int veci(int a, int b);
void ispis_niza_nerastuce(int* a, int n);
void zad2(){
    int i,n,m,br_vrhova=0;
    scanf("%d %d", &m, &n);
    int** a;
    a = new int*[m];
    for(i=0;i<m;i++) a[i] = new int[n];
    unos_matrice(a,m,n);
    int* vrhovi = nadji_vrhove(a,m,n,br_vrhova);
    mergesort(vrhovi,0,br_vrhova-1);
    ispis_niza_nerastuce(vrhovi, br_vrhova);
    for(i=0;i<m;i++) delete[] a[i];
    delete[] a;
    free(vrhovi);
}
void napravi_teplicovu(int** matrica, int n);
void napravi_fibonacijevu(int** matrica, int n);
void napravi_lukasovu(int** matrica, int n);
void zad3(){
    int n; scanf("%d", &n);
    int** matrica;
    matrica = new int*[n];
    for(int i=0;i<n;i++) matrica[i] = new int[n];
    napravi_teplicovu(matrica, n);
    printf("TEPLICOVA MATRICA: \n"); ispis_matrice(matrica, n, n);
    napravi_fibonacijevu(matrica, n);
    printf("FIBONACIJEVA MATRICA: \n"); ispis_matrice(matrica, n, n);
    napravi_lukasovu(matrica, n);
    printf("LUKASOVA MATRICA: \n"); ispis_matrice(matrica, n, n);
    for(int i=0;i<n;i++) delete[] matrica[i];
    delete[] matrica;
}
void pomnozi_matrice(int** a, int** b, int** pomocna, int n);
void stepenuj(int** a, int** b, int** pomocna, int n, int stepen);
void zad4(){
    int n,i,j,stepen;
    printf("Prvo unesi stepen matrice, onda N, a zatim matricu NxN ");
    scanf("%d %d",&stepen, &n);
    int** a;
    a = new int*[n];
    for(i=0;i<n;i++) a[i] = new int[n];
    int** b;
    b = new int*[n];
    for(i=0;i<n;i++) b[i] = new int[n];
    int** pomocna;
    pomocna = new int*[n];
    for(i=0;i<n;i++) pomocna[i] = new int[n];
    unos_matrice(a,n,n);
    for(i=0;i<n;i++){
        for(j=0;j<n;j++) b[i][j] = a[i][j];
    }
    stepenuj(a,b,pomocna,n,stepen);
    ispis_matrice(b,n,n);
    for(i=0;i<n;i++){
        delete[] a[i];
        delete[] b[i];
        delete[] pomocna[i];
    }
    delete[] a; delete[] b; delete[] pomocna;

}
int main(){

    //zad1();
    //zad2();
    //zad3();
    zad4();

}
void merge(int* a, int levo, int sredina, int desno) {
    int i,j,k,nl,nd;
    nl = sredina - levo + 1;
    nd = desno - sredina;
    int levi_niz[nl];
    int desni_niz[nd];
    for(i=0;i<nl;i++){
        levi_niz[i] = a[levo+i];
    }
    for(j=0;j<nd;j++){
        desni_niz[j] = a[sredina+1+j];
    }
    i=0;j=0;k=levo;
    while(i<nl && j<nd){
        if(levi_niz[i]<=desni_niz[j]){
            a[k] = levi_niz[i];
            i++;
        } else {
            a[k] = desni_niz[j];
            j++;
        }
        k++;
    }
    while(i<nl){
        a[k] = levi_niz[i];
        i++; k++;
    }
    while(j<nd){
        a[k] = desni_niz[j];
        j++; k++;
    }
}
void mergesort(int* a, int levo, int desno) {
    if(levo<desno){
        int sredina = (levo + desno) / 2;
        mergesort(a,levo,sredina);
        mergesort(a,sredina+1, desno);
        merge(a,levo,sredina,desno);
    }
}
void insertionsort(int* a, int n){
    int i,k,j;
    for(i=1;i<n;i++){
        k = a[i];
        j = i-1;
        while(j>=0 && a[j]>k){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = k;
    }
}
void unos_niza(int* a, int n){
    for(int i=0;i<n;i++) scanf("%d", &a[i]);
}
void ispis_niza(int* a, int n){
    for(int i=0;i<n;i++) printf("%d ", a[i]);
}
void unos_matrice(int** a, int m, int n){
    int i,j;
    for(i=0;i<m;i++)
        for(j=0;j<n;j++)
            scanf("%d", &a[i][j]);
}
void ispis_matrice(int** a, int m, int n){
    int i,j;
    for(i=0;i<m;i++){
        for(j=0;j<n;j++){
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}
int* nadji_vrhove(int** a, int m, int n, int &br_vrhova){
    int * niz = (int*)malloc(sizeof(int));
    int brojac=0;
    for(int i=1;i<m-1;i++){
        for(int j=1;j<n-1;j++){
            if(a[i-1][j]<a[i][j] && a[i+1][j]<a[i][j] && a[i][j+1]<a[i][j] && a[i][j-1]<a[i][j]){
                niz = (int*)realloc(niz, (brojac+1)*sizeof(int));
                niz[brojac] = a[i][j] - (veci(a[i][j+1], veci(a[i][j-1], veci(a[i+1][j], a[i-1][j]))));
                brojac++;
            }
        }
    }
    br_vrhova = brojac;
    return niz;
}
int veci(int a, int b){
    if(a>b) return a; else return b;
}
void ispis_niza_nerastuce(int* a, int n){
    for(int i=n-1;i>=0;i--) printf("%d ", a[i]);
}
void napravi_teplicovu(int** matrica, int n){
    int i,j,k=1,r=1,v;
    for(i=0;i<n;i++) matrica[i][i] = 1;
    for(i=1;i<n;i++){
        r=i;k++;
        for(j=0;j<n-k+1;j++){
            matrica[r][j] = k; r++;
        }
    }
    v=k+1;r=1;k=1;
    for(i=1;i<n;i++){
        r=i;k++;
        for(j=0;j<n-k+1;j++){
            matrica[j][r] = v; r++;
        }
        v++;
    }
}
void napravi_fibonacijevu(int** matrica, int n){
    /*
        Primer fibonacijeve matrice sam uradio koristeci primer ove slike:
        https://www.google.com/search?q=fibonacci+matrix&sxsrf=AOaemvLC_E7d0LVNSiM8mDoamsl7XDuPeg:1639360282142&source=lnms&tbm=isch&sa=X&ved=2ahUKEwi67Jn61N_0AhXHh_0HHa0yDdsQ_AUoAXoECAEQAw&biw=871&bih=872&dpr=1.1#imgrc=JEsPs1030bSmeM
    */
    int i,j,r,k=n-1;
    for(i=0;i<n-1;i++){
        matrica[i][i] = 1;
        matrica[i+1][i] = 1;
        matrica[i][i+1] = 1;
    }
    matrica[n-1][n-1] = 1;
    for(i=2;i<n;i++){
        k--;r=i;
        for(j=0;j<k;j++){
            matrica[r][j] = matrica[r-1][j+1] + matrica[r][j+1]; r++;
        }
    }
    k=n-1;
    for(i=2;i<n;i++){
        k--;r=i;
        for(j=0;j<k;j++){
            matrica[j][r] = matrica[j][r-1] + matrica[j+1][r-1]; r++;
        }
    }
}
void napravi_lukasovu(int** matrica, int n){
    int i,j,r,k=n-1;
    for(i=0;i<n-1;i++){
        matrica[i][i] = 2;
        matrica[i+1][i] = 1;
        matrica[i][i+1] = 1;
    }
    matrica[n-1][n-1] = 2;
    for(i=2;i<n;i++){
        k--;r=i;
        for(j=0;j<k;j++){
            matrica[r][j] = matrica[r-1][j+1] + matrica[r][j+1]; r++;
        }
    }
    k=n-1;
    for(i=2;i<n;i++){
        k--;r=i;
        for(j=0;j<k;j++){
            matrica[j][r] = matrica[j][r-1] + matrica[j+1][r-1]; r++;
        }
    }
}
void stepenuj(int** a, int**b , int** pomocna, int n, int stepen){
    int i;
    if(stepen==1){
        return;
    } else if(stepen%2==0){
        for(i=1;i<stepen/2;i++){
            pomnozi_matrice(a,b,pomocna,n);
        }
        pomnozi_matrice(b,b,pomocna,n);
    } else {
        for(i=1;i<stepen/2;i++){
            pomnozi_matrice(a,b,pomocna,n);
        }
        pomnozi_matrice(b,b,pomocna,n);
        pomnozi_matrice(a,b,pomocna,n);
    }
}
void pomnozi_matrice(int** a, int** b, int** pomocna, int n){
    int i,j,k;
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            pomocna[i][j] = 0;
            for(k=0;k<n;k++){
                pomocna[i][j] += b[i][k]*a[k][j];
            }
        }
    }
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            b[i][j] = pomocna[i][j];
        }
    }
}
