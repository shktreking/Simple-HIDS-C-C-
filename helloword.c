#include <stdio.h>

#define OGRENCI_SAYISI 5
#define DERS_SAYISI 3

void girilen_girdileri_alir(int notlar[OGRENCI_SAYISI][DERS_SAYISI]);
void her_ogrenci_ortalama_hesaplar(int notlar[OGRENCI_SAYISI][DERS_SAYISI]);
void sinif_ortalamasi_hesaplar(int notlar[OGRENCI_SAYISI][DERS_SAYISI]);
void en_basarili_ogrenciyi_bulur(int notlar[OGRENCI_SAYISI][DERS_SAYISI]);

int main(void)
{
    int notlar[OGRENCI_SAYISI][DERS_SAYISI];
    int secim;
    int veri_girildi = 0;

    do
    {
        printf("\n--- OGRENCI NOT SISTEMI ---\n");
        printf("ilk önce notlari girmeniz gerekmektedir.\n");
        printf("1 - Notlari Gir\n");
        printf("2 - Ogrenci Ortalamasi\n");
        printf("3 - Sinif Ortalamasi\n");
        printf("4 - En Basarili Ogrenci\n");
        printf("0 - Cikis\n");
        printf("Seciminiz: ");
        scanf("%d", &secim);

        switch (secim)
        {
        case 1:
            girilen_girdileri_alir(notlar);
            veri_girildi = 1;
            break;

        case 2:
            if (veri_girildi  == 1)
                her_ogrenci_ortalama_hesaplar(notlar);
            else
                printf("Once notlari giriniz!\n");
            break;

        case 3:
            if (veri_girildi == 1)
                sinif_ortalamasi_hesaplar(notlar);
            else
                printf("Once notlari giriniz!\n");
            break;

        case 4:
            if (veri_girildi == 1)
                en_basarili_ogrenciyi_bulur(notlar);
            else
                printf("Once notlari giriniz!\n");
            break;

        case 0:
            printf("Programdan cikiliyor...\n");
            break;

        default:
            printf("Gecersiz secim!\n");
        }

    } while (secim != 0);

    return 0;
}

void girilen_girdileri_alir(int notlar[OGRENCI_SAYISI][DERS_SAYISI])
{
    for (int i = 0; i < OGRENCI_SAYISI; i++)
    {
        for (int j = 0; j < DERS_SAYISI; j++)
        {
            printf("%d. ogrencinin %d. ders notu: ", i + 1, j + 1);
            scanf("%d", &notlar[i][j]);
        }
    }
}

void her_ogrenci_ortalama_hesaplar(int notlar[OGRENCI_SAYISI][DERS_SAYISI])
{
    int ogrenci_no;
    int toplam = 0;

    printf("Ogrenci numarasi (1-5): ");
    scanf("%d", &ogrenci_no);

    if (ogrenci_no < 1 || ogrenci_no > OGRENCI_SAYISI)
    {
        printf("Gecersiz ogrenci numarasi!\n");
        return;
    }

    for (int j = 0; j < DERS_SAYISI; j++)
        toplam += notlar[ogrenci_no - 1][j];

    printf("%d. ogrencinin ortalamasi: %.2f\n",
           ogrenci_no, toplam / (float)DERS_SAYISI);
}

void sinif_ortalamasi_hesaplar(int notlar[OGRENCI_SAYISI][DERS_SAYISI])
{
    int toplam = 0;

    for (int i = 0; i < OGRENCI_SAYISI; i++)
        for (int j = 0; j < DERS_SAYISI; j++)
            toplam += notlar[i][j];

    printf("Sinif ortalamasi: %.2f\n",toplam / (float)(OGRENCI_SAYISI * DERS_SAYISI));
}

void en_basarili_ogrenciyi_bulur(int notlar[OGRENCI_SAYISI][DERS_SAYISI])
{
    int en_basarili = 0;
    float en_yuksek_ortalama = 0.0f;

    for (int i = 0; i < OGRENCI_SAYISI; i++)
    {
        int toplam = 0;

        for (int j = 0; j < DERS_SAYISI; j++)
            toplam += notlar[i][j];

        float ortalama = toplam / (float)DERS_SAYISI;

        if (ortalama > en_yuksek_ortalama)
        {
            en_yuksek_ortalama = ortalama;
            en_basarili = i + 1;
        }
    }

    printf("En basarili ogrenci: %d (Ortalama: %.2f)\n",en_basarili, en_yuksek_ortalama);
}
