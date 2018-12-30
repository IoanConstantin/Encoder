#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void citire()
//realizeaza citirea caracterelor introduse 
{
int cuv=0,car=0,nr=0,i;
char line[1000]; //sirul de caractere de pe fiecare linie in parte
FILE *fp;
//iesire.txt este un fisier in care se salveaza pe prima pozitie a fiecarui sir de caractere 
// tipul sirului de caractere(L-caracter singular, N-numar, C-cuvant) 
fp=fopen("iesire.txt","w"); 
do
 {
   fgets(line,1000,stdin);//citeste sirul de caractere curent
   if((strlen(line)==2)&&line[0]!='1'&&line[0]!='2'&&line[0]!='3'&&line[0]!='4'&&line[0]!='5'&&line[0]!='6'&&line[0]!='7'&&line[0]!='8'&&line[0]!='9') {
   car++;
   fputs("L",fp);//este caracter singular
   fputs(line,fp);
   }
  else
   {
       int oknr=1;//flag verificare numar 
       if (!(line[0]=='-'||line[0]=='1'||line[0]=='2'||line[0]=='3'||line[0]=='4'||line[0]=='5'||line[0]=='6'||line[0]=='7'||line[0]=='8'||line[0]=='9')) oknr=0;
       if(oknr==1)
       {
       for(i=1;i<strlen(line)-1;i++)
         {
              if (!(line[i]=='1'||line[i]=='2'||line[i]=='3'||line[i]=='4'||line[i]=='5'||line[i]=='6'||line[i]=='7'||line[i]=='8'||line[i]=='9')) oknr=0;
          }
       }
       if(oknr==0) {
         cuv++;
         fputs("C",fp);//este cuvant
         fputs(line,fp);
       }
       if(oknr==1) {
         nr++;
         fputs("N",fp);//este numar fiindca contine numai cifre si eventual minus pe prima poz
         fputs(line,fp);
       }
   }
  } while(!(strlen(line)==4&&line[0]=='E'&&line[1]=='N'&&line[2]=='D'));
//printeaza nr. de cuvinte cu exceptia lui END,
// nr. de caractere singulare si nr. de numere cu exceptia lui n
printf("%d %d %d\n",cuv-1,car,nr-1);                        
fclose(fp);//inchidere fisier
}

int fnumar(int n)
//stabileste codificarea lui n conform algoritmului
{
    int max,aux1,aux2,cif=0,prod=1,i;
    max=n;
    aux1=n;
    aux2=n;
    while(aux1!=0)
    {
    aux1=aux1/10;
    cif++;//numarul de cifre al lui n
    }
    for(i=1;i<cif;i++)
    prod=prod*10;
    do{
    aux2=(aux2%prod)*10+aux2/prod;
    if(aux2>max) max=aux2;
    }while(aux2!=n);
    if(n>0) return max;//valoarea rezultata pentru numar pozitiv
         else return (-max);//valoarea rezultata pentru numar negativ
}

void codificare()
//calculeaza si printeaza sirul rezultat conform task-ului de codificare
{
FILE *fp2;
int final_numar,w,varnumar,ninitial,i,diviz,j,ok,ok1,b[1000],k=0,max=0,min=1000,scontor=0,auxiliar,y=0;
char line2[1000], lineaux[1000],aux[1000],aux1[1000],aux2[1000],laux[1000],a[1000],c[1000]="0",d[1000]="0",sfinal[10000],aux3[1000];
memset(sfinal,0,10000);
//deshide fisierul in care s-au salvat liniile citite
fp2=fopen("iesire.txt","r");
do {
   fgets(line2,1000,fp2);//citeste linia curenta din fisier
   if (line2[0]=='N')//daca linia este de tip numar
       {
         for (w=1;w<=strlen(line2);w++) lineaux[w-1]=line2[w];//elimin primul caracter('N')
         ninitial=atoi(lineaux);//va salva in final ultimul numar(care nu va fi prelucrat)
       }
} while(!(strlen(line2)==5&&line2[1]=='E'&&line2[2]=='N'&&line2[3]=='D'));
fclose(fp2);
fp2=fopen("iesire.txt","r");
do {
   fgets(line2,1000,fp2);
   if (line2[0]=='C')//daca linia este de tip cuvant    
   {
         if(!(line2[1]=='E'&&line2[2]=='N'&&line2[3]=='D'&&strlen(line2)==5))
         {
            memset(aux,0,1000);
            memset(aux1,0,1000);
            memset(aux2,0,1000);
            for (w=1;w<=strlen(line2);w++) lineaux[w-1]=line2[w];//elimin primul caracter('C')
            ok=1;//flag pentru verificare daca cuvantul contine cifre
            for(j=0;j<strlen(lineaux)-1;j++)
            if(lineaux[j]=='0'||lineaux[j]=='1'||lineaux[j]=='2'||lineaux[j]=='3'||lineaux[j]=='4'||lineaux[j]=='5'||lineaux[j]=='6'||lineaux[j]=='7'||lineaux[j]=='8'||lineaux[j]=='9') ok=0;
            if(ok==1)//daca nu contine cifre
            {
               diviz=1;//diviz este cel mai mare divizor al lungimii liniei curente
               for(i=1;i<=(strlen(lineaux)-1)/2;i++)
               if((strlen(lineaux)-1)%i==0) diviz=i;
               //mut subsirul aux la finalul subsirului aux1
               strncpy(aux,lineaux,diviz);
               strncpy(aux1,lineaux+diviz,strlen(lineaux)-diviz-1);
               strcat(aux1,aux);
            }
            if(ok==0)
            {
               diviz=1;
               for(i=1;i<=(strlen(lineaux)-1)/2;i++)
               if((strlen(lineaux)-1)%i==0) diviz=i;
               strncpy(aux,lineaux,diviz);
               strncpy(aux1,lineaux+diviz,strlen(lineaux)-diviz-1);
               //se inverseaza subsirul aux1 si se muta la finalul subsirului aux
               for(i=0;i<strlen(aux1);i++)
               aux2[i]=aux1[i];
               for(i=0;i<strlen(aux1);i++)
               aux1[i]=aux2[strlen(aux2)-i-1];
               strcat(aux1,aux);
            }
            //in sirul final se adauga sirul rezultat
            for(i=0;i<strlen(aux1);i++)
                sfinal[i+scontor]=aux1[i];
            scontor=scontor+strlen(aux1);//contorul curent al sirului sfinal
         }
   }
   if (line2[0]=='N')//daca linia este de tip numar
       {
         for (w=1;w<=strlen(line2);w++) lineaux[w-1]=line2[w];
         varnumar=atoi(lineaux);//converteste din cuvant in numar
         if(varnumar!=ninitial)//daca nu este ultimul numar citit
         {
            final_numar=fnumar(varnumar);//final_numar retine numarul codificat
         auxiliar=final_numar;
         memset(aux3,0,1000);
         y=0;
         //numarul auxiliar este transformat in sirul aux3
         while(auxiliar!=0)
         {
            if(auxiliar%10==1) aux3[y++]='1';
            if(auxiliar%10==2) aux3[y++]='2';
	    if(auxiliar%10==3) aux3[y++]='3';
	    if(auxiliar%10==4) aux3[y++]='4';
	    if(auxiliar%10==5) aux3[y++]='5';
	    if(auxiliar%10==6) aux3[y++]='6';
	    if(auxiliar%10==7) aux3[y++]='7';
	    if(auxiliar%10==8) aux3[y++]='8';
	    if(auxiliar%10==9) aux3[y++]='9';
            auxiliar=auxiliar/10;
         }
         //se adauga fiecare caracter al sirului aux3 la sirul sfinal
         for(i=0;i<strlen(aux3);i++)
            sfinal[i+scontor]=aux3[strlen(aux3)-i-1];
            scontor=scontor+strlen(aux3);
         }
       }
   if  (line2[0]=='L')//daca este de tip caracter singular
      {
         for (w=1;w<=strlen(line2);w++) lineaux[w-1]=line2[w];
         for (w=0;w<(strlen(lineaux)-1);w++) laux[w]=lineaux[w];
         //sirul a contine unic fiecare caracter citit pana la linia curenta
         //sirul b contine pentru fiecare caracter din sirul a numarul de aparitii in sirul sfinal
         for(i=strlen(sfinal)-1;i>=0;i--)
         { 
              ok1=1;
              for(j=0;j<i;j++)
              {
                 if(a[j]==sfinal[i])  ok1=0;
              }
               if(ok1==1) a[k++]=sfinal[i];//daca nu exista caracterul in sirul a, il adaug
         }
         for(i=0;i<1000;i++) b[i]=0;
         for(i=0;i<strlen(sfinal);i++)
         {
            for(j=0;j<strlen(a);j++)
            { 
                  //daca caracterul exista in sirul a, incrementez numarul de aparitii coresp in b
                  if(sfinal[i]==a[j]) b[j]++; 
            }
         }
            for(j=0;j<strlen(a);j++)
               if(b[j]>max) max=b[j];//numarul maxim de aparitii
            for(j=0;j<strlen(a);j++)
               if(b[j]==max)  c[0]=a[j];//caracterul cu numar maxim de aparitii
            for(j=0;j<strlen(a);j++)
               if(b[j]<min&&b[j]!=0) min=b[j];//numar minim de aparitii
            for(j=0;j<strlen(a);j++)
               if(b[j]==min)  d[0]=a[j];//caracterul cu numar minim de aparitii
       if(d[0]=='0'&&c[0]=='0')//daca e primul caracter citit
       {
         sfinal[scontor]=laux[0];
         scontor=scontor+1;
      }
       else
       {
         //adaug caracterul cu numar maxim de aparitii, caracterul curent si cel cu numar minim
         sfinal[scontor]=c[0];
         sfinal[scontor+1]=laux[0];
         sfinal[scontor+2]=d[0];
         scontor=scontor+3;
       }
    }
} while(!(strlen(line2)==5&&line2[1]=='E'&&line2[2]=='N'&&line2[3]=='D'));
printf("%s\n",sfinal);//scrie sirul final   
fclose(fp2);
}

int main(){
//apeleaza functiile de citire si codificare
citire();
codificare();
return 0;
}
