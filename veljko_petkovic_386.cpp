//VELJKO PETKOVIC 386
#include <stdio.h>
#include <math.h>
int br_cif(int n);
int palindrom(int n, int del = 10, int pw = 1);
void zad1(){
    int n;
    scanf("%d",&n);
    if(palindrom(n)==n)
        printf("Broj %d JESTE palindrom",n);
    else
        printf("Broj %d NIJE palindrom",n);
}
int dv_fak(int n);
int sum_k_dv_f(int n);
void zad2(){
    int n,i=1;
    scanf("%d",&n);
    for(i=1;i<n;i++)
        if(sum_k_dv_f(i)==i) printf("Broj %d jeste \n", i);
}
int sum_del(int br);
void zad3(){
    for(int i=1;i<=10000;i++){
        int br1 = sum_del(i);
        for(int j=1;j<=10000;j++){
            if(br1==j && i==sum_del(j) && i!=j)
                printf("%d i %d su prijateljski \n", i, j);
        }
    }
}
void sab(int x1,int y1,int x2,int y2);
void odu(int x1,int y1,int x2,int y2);
void mno(int x1,int y1,int x2,int y2);
void delj(int x1,int y1,int x2,int y2);
void zad4(){
    int x1,x2,y1,y2,x,y;
    printf("Unesite x1 i y1 za kompleksan broj c1 = x1+y1*i \n");
    scanf("%d %d",&x1,&y1);
    printf("Unesite x2 i y2 za kompleksan broj c2 = x2+y2*i \n");
    scanf("%d %d",&x2,&y2);
    printf("Za brojeve C1 i C2  c1 = %d+%d*i c2 = %d+%d*i  Operacije su: \n",x1,y1,x2,y2);
    sab(x1,y1,x2,y2);
    odu(x1,y1,x2,y2);
    mno(x1,y1,x2,y2);
    delj(x1,y1,x2,y2);
}
int c(int a,int n);
void zad5(){
    double x,sum=0.0,f; int a,p=0,n=0;
    scanf("%lf %d",&x, &a);
    while(true){
        f = fabs(pow(x,2*n))/dv_fak(2*n);
        if(f < 0.0001) break;
        if(p%2==0)
            sum += (c(a,n*n)*pow(x,2*n))/dv_fak(2*n);
        else
            sum -= (c(a,n*n)*pow(x,2*n))/dv_fak(2*n);
        p++;n++;
    }
    printf("%0.4lf",sum);
}
int main(){
    //zad1();
    //zad2();
    //zad3();
    //zad4();
    //zad5();
}

int br_cif(int n){
    if(n==0) return 0;
    return 1 + br_cif(n/10);
}
int palindrom(int n, int del,int pw){
    if(n==0) return 0;
    int zbr = ((n % del)/pow(10,pw-1)) * pow(10,br_cif(n)-pw);
    n -= n % del; del *= 10;
    return zbr + palindrom(n,del,pw+1);
}
int dv_fak(int n){
    if(n<1)
        return 1;
    return n * dv_fak(n-2);
}
int sum_k_dv_f(int n){
    if(n==0) return 0;
    int cif = n%10;
    cif = dv_fak(cif);
    return cif*cif + sum_k_dv_f(n/10);
}
int sum_del(int br){
    int sum=0;
    for(int i=1;i<=br/2;i++)
        if(br%i==0)
            sum += i;
    return sum;
}
void sab(int x1,int y1,int x2,int y2){
    printf("Sabiranje: %d + %d*i \n", x1 + x2, y1 + y2);
}
void odu(int x1,int y1,int x2,int y2){
    printf("Oduzimanje: %d - %d*i \n",x1 + x2, y1 + y2);
}
void mno(int x1,int y1,int x2,int y2){
    printf("Mnozenje: %d + %d*i \n",x1*x2-y1*y2, x1*y2+x2*y1);
}
void delj(int x1,int y1,int x2,int y2){
    printf("Deljenje: %d + %d*i / %d \n",(x1*x2-y1*y2)/(x2*x2+y2*y2),y1*x2-x1*y2,x2*x2+y2*y2);
}
int c(int a,int n){
    int br=0,cif;
    while(n!=0){
        cif = n % 10;
        if(a==cif) br++;
        n /= 10;
    }
    return br;
}



