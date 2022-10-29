#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <cstring>
#define duzina_stringa 100
typedef struct tacka {
    int x,y;
} tacka;
typedef struct prav {
    tacka gornjaleva;
    tacka donjadesna;
} prav;
char* izbaci(char* str);
bool palindrom(char* string);
void sortiraj(char** str, int broj_stringova);
int br_razl_karaktera(char* string);
bool pripada(prav p, tacka t);
void zad1(){
    char* str = (char*)malloc(sizeof(char)*duzina_stringa);
    int n=0,rez=0,duz=0,pozicija;
    char c;
    while((c = getc(stdin)) != '.'){
        str[n] = c;
        n++;
    }
    str[n++] = ' '; str[n] = '\0';
    for(int i=0;i<n;i++){
        if(isalpha(str[i])){
            duz++;
        } else if(str[i]==' '){
            if(rez<duz){
                rez = duz;
                pozicija = i - rez;
            }
            duz = 0;
        }
    }
    printf("Najduza rec je: ");
    for(int i=pozicija;i<rez+pozicija;i++){
        printf("%c", str[i]);
    }
    printf(" ima %d slova u stringu %s", rez, str);
    free(str);
}
void zad2(){
    FILE* ulaz = fopen("ulaz.txt", "r");
    FILE* izlaz = fopen("izlaz.txt", "w");
    char str[duzina_stringa];
    while(!feof(ulaz)){
        fgets(str, 100, ulaz);
        char* novi_string = izbaci(str);
        fputs(novi_string, izlaz);
        free(novi_string);
    }
    fclose(ulaz);
    fclose(izlaz);
}
void zad3(char* ime_fajla){
    /*
        ZA ULAZ.TXT:
addacc
asavc
aaad
a
ppPp
pp
a
Ada
arfgfra
sS
kik
saas
adda
kik
fa
kik
lkjhghjkl
        IZLAZ.TXT CE BITI:
a
a
pp
ppPp
kik
kik
adda
saas
kik
sS
Ada
arfgfra
lkjhghjkl
    */
    int i=0,broj_izdvojenih=0,n=0,s=0;
    FILE* ulaz = fopen(ime_fajla, "r");
    FILE* izlaz = fopen("C:\\Users\\Veljko\\Desktop\\FAKULTET\\Uvod u programiranje\\izlaz.txt", "w");
    char stringovi[100][duzina_stringa];
    while(!feof(ulaz)){
        fgets(stringovi[n],100,ulaz);
        n++;
    }
    char ** izdvojeni;
    izdvojeni = new char*[n];
    for(i=0;i<n;i++) izdvojeni[i] = new char[100];
    for(i=0;i<n;i++){
        if(palindrom(stringovi[i])){
            strcpy(izdvojeni[s], stringovi[i]);
            s++;
        }
    }
    sortiraj(izdvojeni,s);
    for(i=0;i<s;i++){
        fputs(izdvojeni[i], izlaz);
    }
    for(i=0;i<n;i++) delete[] izdvojeni[i];
    delete[] izdvojeni;
    fclose(ulaz); fclose(izlaz);
}
void zad4(){
    /*
    -ZA ULAZE:
        ULAZ1.TXT - 1 7 5 3
        ULAZ2.TXT - 3 5 9 1
        TACKE.TXT - 1 1 2 2 6 2 8 4 8 7 2 5 3 6 4 4
    -IZLAZ PROGRAMA CE BITI (ovaj rezultat je kopiran iz programa):

Tacka 1 1 ne pripada ni A ni B
Tacka 2 2 ne pripada ni A ni B
Tacka 6 2 pripada B
Tacka 8 4 pripada B
Tacka 8 7 ne pripada ni A ni B
Tacka 2 5 pripada A
Tacka 3 6 pripada A
Tacka 4 4 pripada A i B

Pravougaoniku A pripada 3 tacaka,
Pravougaoniku B pripada 3 tacaka,
Pravougaonicima A i B pripada 1 tacaka,
Nijednom pravougaoniku pripada 3 tacaka.

Pravougaoniku A pripada 37.50% tacaka,
Pravougaoniku B pripada 37.50% tacaka,
Pravougaoniku A i B pripada 12.50% tacaka,
Nijednom ne pripada 37.50% tacaka.
    */
    FILE* ulaz1 = fopen("ulaz1.txt","r");
    FILE* ulaz2 = fopen("ulaz2.txt","r");
    FILE* tacke = fopen("tacke.txt","r");
    prav A,B;
    tacka T[50];
    int i,n=0,ucitani,pripadaA=0,pripadaB=0,pripadaAiB=0,nepripada;
    fscanf(ulaz1,"%d %d %d %d",&A.gornjaleva.x,&A.gornjaleva.y,&A.donjadesna.x,&A.donjadesna.y);
    fscanf(ulaz2,"%d %d %d %d",&B.gornjaleva.x,&B.gornjaleva.y,&B.donjadesna.x,&B.donjadesna.y);
    while(!feof(tacke)){
        fscanf(tacke,"%d %d",&T[n].x,&T[n].y);
        n++;
    }
    for(i=0;i<n;i++){
        if(pripada(A,T[i])){
            if(pripada(B,T[i])){
                pripadaAiB++;
                pripadaB++;
                pripadaA++;
                printf("Tacka %d %d pripada A i B\n",T[i].x,T[i].y);
                continue;
            }
            pripadaA++;
            printf("Tacka %d %d pripada A\n",T[i].x,T[i].y);
        } else if(pripada(B,T[i])){
            pripadaB++;
            printf("Tacka %d %d pripada B\n",T[i].x,T[i].y);
        } else {
            printf("Tacka %d %d ne pripada ni A ni B\n",T[i].x,T[i].y);
        }
    }
    nepripada = n-pripadaA-pripadaB+pripadaAiB;
    float procenatA = (float)pripadaA / (float)n * 100;
    float procenatB = (float)pripadaB / (float)n * 100;
    float procenatAiB = (float)pripadaAiB / (float)n * 100;
    float procenatne = (float)nepripada / (float)n * 100;
    char c = '%';
    printf("\nPravougaoniku A pripada %d tacaka,\nPravougaoniku B pripada %d tacaka,\nPravougaonicima A i B pripada %d tacaka,\nNijednom pravougaoniku pripada %d tacaka.\n\n",pripadaA,pripadaB,pripadaAiB,nepripada);
    printf("Pravougaoniku A pripada %0.2f%c tacaka,\nPravougaoniku B pripada %0.2f%c tacaka,\nPravougaoniku A i B pripada %0.2f%c tacaka,\nNijednom ne pripada %0.2f%c tacaka.",procenatA,c,procenatB,c,procenatAiB,c,procenatne,c);
    fclose(ulaz1);fclose(ulaz2);fclose(tacke);
}
int main(int argc, char** argv){
    //zad1();
    //zad2();
    //zad3(argv[1]);
    //zad4();
}
char* izbaci(char* str){
    int n = strlen(str),j=0;
    char* novi_string = (char*)malloc(sizeof(char)*n);
    for(int i=0;i<n;i++){
        if(isalpha(str[i])){
            novi_string[j] = str[i]; j++;
        }
    }
    novi_string[j] = '\0';
    return novi_string;
}
bool palindrom(char* string){
    int n = strlen(string);
    int i=0,j=n-1;
    while(i<j){
        if(isspace(string[i])){i++; continue;}
        if(isspace(string[j])){j--; continue;}
        if(tolower(string[i])!=tolower(string[j])) return false;
        i++;j--;
    }
    return true;
}
void sortiraj(char** stringovi, int broj_stringova){
    char tmp[duzina_stringa];
    int i,j,duz1,duz2;
    for(i=0;i<broj_stringova;i++){
        duz1 = br_razl_karaktera(stringovi[i]);
        for(j=i+1;j<broj_stringova;j++){
            duz2 = br_razl_karaktera(stringovi[j]);
            if(duz1>duz2){
                strcpy(tmp, stringovi[i]);
                strcpy(stringovi[i], stringovi[j]);
                strcpy(stringovi[j], tmp);
            }
        }
    }
}
int br_razl_karaktera(char* string){
    //a i A ce se tretirati kao razliciti karakteri
    char c;
    int rez=0;
    for(c='a';c<'z';c++){
        for(int i=0;i<strlen(string);i++){
            if(c==string[i]){
                rez++; break;
            }
        }
    }
    for(c='A';c<'Z';c++){
        for(int i=0;i<strlen(string);i++){
            if(c==string[i]){
                rez++; break;
            }
        }
    }
    return rez;
}
bool pripada(prav p, tacka t){
    //AKO JE TACKA NA STRANICI PRAVOUGAONIKA, ONDA SE NECE SMATRATI DA PRIPADA TOM PRAVOUGAONIKU.
    if((p.gornjaleva.x < t.x)&&(p.gornjaleva.y > t.y)&&(p.donjadesna.x > t.x)&&(p.donjadesna.y < t.y))
        return true;
    else
        return false;
}
