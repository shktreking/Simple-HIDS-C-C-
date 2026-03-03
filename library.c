#include "library.h"
#include <stdio.h>
#include "stdlib.h"
#include "locale.h"
#include "dirent.h"
#include <unistd.h>
#include <sys/stat.h>
#include <time.h>
/* * NOT: Bu dosya projenin ilk aşamalarına ait bir taslaktır (sketch).
 * Yeni ve optimize edilmiş mimari üzerinde çalışmalar devam etmektedir.
 */


    /*
    DIR *dizin;
    struct dirent *dosya;
    int dosya_sayisi = 0;
    char *yol = ".";
    dizin = opendir("c:\\");
    dizin=opendir(yol);


    if (dizin == NULL) {
        perror("hata");
        return 1;
    }

    printf("--------------------------------------%s klasorun icindekiler---------------------------\n");

    while ((dosya = readdir(dizin))  != NULL ) {
        dosya_sayisi ++ ;
    }

    printf("toplamda %d kadar oge bulundu ", dosya_sayisi);

    closedir(dizin);





    return 0;
}


void dosyayiAnalizEt(char *yol, char *dosyaAdi) {
    char tamYol[1024];
    struct stat dosyaBilgisi;

    // Tam yolu oluştur (Örn: /etc + / + passwd)
    snprintf(tamYol, sizeof(tamYol), "%s/%s", yol, dosyaAdi);

    // 1. access(): Dosyaya erişim iznimiz var mı?
    if (access(tamYol, R_OK) == 0) {
        // 2. stat(): Dosyanın detaylı kimliğini al
        if (stat(tamYol, &dosyaBilgisi) == 0) {
            printf("[OKUNABİLİR] %-20s | Boyut: %ld byte | Son Değişim: %s",
                    dosyaAdi,
                    dosyaBilgisi.st_size,
                    ctime(&dosyaBilgisi.st_mtime));
        }
    } else {
        // Erişim engellendiyse HIDS için bu bir şüpheli durum olabilir
        printf("[ERİŞİM YOK]  %-20s | Yetki yetersiz!\n", dosyaAdi);
    }
}

int main() {
    // getuid(): Root kontrolü
    if (getuid() != 0) {
        printf("--- UYARI: Tam tarama için ROOT yetkisi lazım! ---\n\n");
    }

    DIR *d;
    struct dirent *dir;
    char *hedefDizin = "/etc"; // Kritik sistem dizini

    d = opendir(hedefDizin);

    if (d) {
        printf("%s Dizini Güvenlik Taraması Başlatıldı...\n", hedefDizin);
        printf("------------------------------------------------------------\n");

        while ((dir = readdir(d)) != NULL) {
            // "." ve ".." klasörlerini atla
            if (dir->d_name[0] == '.') continue;

            dosyayiAnalizEt(hedefDizin, dir->d_name);
        }
        closedir(d);
    } else {
        perror("Dizin açılamadı");
    }
*/
void analizVeKaydet(FILE *fp, char *yol, struct dirent *girdi) {
    char tamYol[1024];
    struct stat st;


    snprintf(tamYol, sizeof(tamYol), "%s/%s", yol, girdi->d_name);

    if (stat(tamYol, &st) == 0) {
        char *zaman = ctime(&st.st_mtime);
        if(zaman) zaman[strlen(zaman) - 1] = '\0';
        fprintf(fp, "  {\n");
        fprintf(fp, "    \"isim\": \"%s\",\n", girdi->d_name);
        fprintf(fp, "    \"boyut\": %ld,\n", st.st_size);
        fprintf(fp, "    \"tip\": \"%s\",\n", (S_ISDIR(st.st_mode) ? "Klasor" : "Dosya"));
        fprintf(fp, "    \"degisim\": \"%s\"\n", zaman);
        fprintf(fp, "  },\n");
    }
}
/*
int main() {
    char dizin[256];
    char secim;

    do {
        printf("\n--- HIDS ANALIZ MOTORU ---\n");
        printf("Taranacak dizin yolu: ");
        scanf("%255s", dizin); // Taşıma korumalı girdi

        DIR *d = opendir(dizin);
        if (!d) {
            perror("Kanki dizin bulunamadi");
        } else {
            FILE *f = fopen("hids_database.json", "a");
            if (!f) {
                perror("Dosya acilamadi");
                closedir(d);
                return 1;
            }

            fprintf(f, "{\n  \"tarih\": \"%ld\",\n  \"dizin\": \"%s\",\n  \"icerik\": [\n", time(NULL), dizin);

            struct dirent *ent;
            while ((ent = readdir(d)) != NULL) {
                if (ent->d_name[0] == '.') continue;
                analizVeKaydet(f, dizin, ent);
            }

            fprintf(f, "    {}\n  ]\n},\n"); // JSON'u kapat ve sonraki tarama için hazır bırak
            fclose(f);
            closedir(d);
            printf("Tarama basariyla hids_database.json dosyasina eklendi.\n");
        }


        while (1) {
            printf("\nDevam mi (e/h)? ");
            scanf(" %c", &secim);
            secim = tolower(secim);
            if (secim == 'e' || secim == 'h') break;
            printf("Gecersiz karakter! Sisteme girmeye calisma kanki.\n");
            while (getchar() != '\n'); // Tamponu süpür
        }

    } while (secim == 'e');

    printf("HIDS Motoru durduruldu. Python arayuzune gecis icin hazirsin!\n");
    return 0;
    void derin_paket_analizi(const u_char *packet, int size) {
        char *src_ip = get_ip_header(packet);

        // ADIM 1: Veritabanından Sabıka Kontrolü (Hızlı Kontrol)
        if (is_ip_in_blacklist(src_ip)) {
            log_to_db(src_ip, "BLOCKED", "Cihaz kapıda engellendi (Sabıkalı IP)");
            return;
        }

        // ADIM 2: Katman 4 ve 7 Derin Analiz
        char *payload = get_tcp_payload(packet);
        if (payload != NULL) {
            // SQL Injection veya Shellcode taraması
            if (strstr(payload, "UNION SELECT") || strstr(payload, "/bin/bash")) {
                // ADIM 3: Suçluyu Sabıkaya Kaydet
                add_to_blacklist(src_ip, "Katman 7 Saldırısı Saptandı");
                save_attack_to_json_or_sql(src_ip, "Critical", "Deep Packet Inspection Alert");
            }
        }
    }*\
}