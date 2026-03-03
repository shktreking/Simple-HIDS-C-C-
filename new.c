#include <stdio.h>

int Girdiler[100];
int sayac, toplam = 0;
int enBuyuk;
int enKucuk;

int main(){
   FILE *d;
   dosya = fopen("sonuc.txt", "w");
    printf("Kac sayi gireceksiniz: ");
    scanf("%d", &sayac);
 if (sayac <=0 || sayac > 100) {
        printf("Gecersiz sayi girdiniz.\n");
        return 1;
    }
 for (int i = 0; i<sayac; i++){
      scanf("%d", &Girdiler[i]);
      toplam += Girdiler[i];
 }   
   enBuyuk = Girdiler[0];
   enKucuk = Girdiler[0];
   toplam = Girdiler[0];
   for(int i = 1 ; i < sayac ; i++){
         if (Girdiler[i] > enBuyuk){
            enBuyuk = Girdiler[i];
         }
         if (girdiler[i] < enKucuk){
            enKuuck = Girdiler[i];
         }
   }
    fprintf(d, "\nToplam: %d\n", toplam);
    fprintf(d, "En buyuk: %d\n", enBuyuk);
    fprintf(d, "En kucuk: %d\n", enKucuk);

    fclose(d);
    return 0;
}