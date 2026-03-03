/*
#include <iostream>
#include <string>
int main() {
    const int KAPASITE = 5;
    std::string isimler[KAPASITE];
    int notlar[KAPASITE];
    int ogrenciSayisi;
    int gecmeNotu = 50;

    std::cout << "Kac ogrenci gireceksiniz (Max 5): ";
    std::cin >> ogrenciSayisi;

    for (int i = 0; i < ogrenciSayisi; i++) {
        std::cout << i + 1 << ". Ogrenci Ismi: ";
        std::cin >> isimler[i];
        std::cout << isimler[i] << " notu: ";
        std::cin >> notlar[i];
    }

   
    int EnYuksekNot = notlar[0];
    std::string enBasariliOgrenci = isimler[0];
    double toplam = 0;

    std::cout << "\n--- SINIF RAPORU ---" << std::endl;


    for (int i = 0; i < ogrenciSayisi; i++) {
        toplam += notlar[i];

        if (notlar[i] > EnYuksekNot) {
            EnYuksekNot = notlar[i];
            enBasariliOgrenci = isimler[i];
        }
        if (notlar[i] < gecmeNotu) {
            std::cout << isimler[i] << " -> KALDI" << std::endl;
        }
        else {
            std::cout << isimler[i] << " -> GECTI" << std::endl;
        }
    }

    double ortalama = toplam / ogrenciSayisi;
    std::cout << "--------------------" << std::endl;
    std::cout << "Sinif Ortalamasi: " << ortalama << std::endl;
    std::cout << "En Yuksek Not: " << EnYuksekNot << " (" << enBasariliOgrenci << ")" << std::endl;

    return 0;
}


#include <iostream>

int main() {
    int sayi = 10;

    // 1. Bir pointer tanımlayalım. 
    // '*' işareti bunun bir pointer olduğunu söyler.   
    // '&' işareti ise değişkenin bellek adresini verir.
    int* ptr = &sayi;

    std::cout << "Sayinin degeri: " << sayi << std::endl;
    std::cout << "Sayinin bellek adresi (&sayi): " << &sayi << std::endl;
    std::cout << "Pointer'in tuttugu adres (ptr): " << ptr << std::endl;

    // 2. Dereferencing (Adresteki degere erisme)
    // Pointer'ın başına '*' koyarsak, o adresteki kutunun icini acariz.
    *ptr = 20;

    std::cout << "\nPointer uzerinden degistirildikten sonra;" << std::endl;
    std::cout << "Sayinin yeni degeri: " << sayi << std::endl;

    return 0;
}

#include <iostream>

int main() {
    int sayilar[] = { 10, 20, 30, 40, 50 };
    int* ptr = sayilar; // Şu an lazer 10'un üzerinde (0. indeks)

    // Hiç arttırmadan değiştirirsek:
    *ptr = 99; // 10 artık 99 oldu.

    // Şimdi 2 adım kaydıralım:
    ptr = ptr + 2; // Lazer 20'yi atladı, 30'un üzerine geldi.

    // Şimdi değiştirirsek:
    *ptr = 77; // 30 artık 77 oldu.

    std::cout << "Dizinin yeni hali: ";
    for (int i = 0; i < 5; i++) {
        std::cout << sayilar[i] << " ";
    }
    // Çıktı: 99 20 77 40 50 olacak.

    return 0;
}

#include <iostream>

// Referans kullanarak iki sayının yerini değiştiriyoruz
// & işaretleri sayesinde kopyalama yapmıyoruz, doğrudan 'a' ve 'b'ye erişiyoruz
void YerDegistir(int& ilk, int& ikinci) {
    int gecici = ilk;
    ilk = ikinci;
    ikinci = gecici;
}

int main() {
    int x = 10;
    int y = 20;

    std::cout << "Degisimden once -> x: " << x << " y: " << y << std::endl;

    // Fonksiyona x ve y'yi gönderiyoruz
    YerDegistir(x, y);

    std::cout << "Degisimden sonra -> x: " << x << " y: " << y << std::endl;

    return 0;
}
#include <iostream>
#include <string>

class Ogrenci {
public:
    std::string isim;
    int notu;

    // --- CONSTRUCTOR BURADA ---
    // Sınıf ismiyle aynı, parametre alıyor
    Ogrenci(std::string pIsim, int pNotu) {
        isim = pIsim;
        notu = pNotu;
        std::cout << isim << " icin nesne olusturuldu!" << std::endl;
    }

    void GectiMi() {
        if (notu >= 50) {
            std::cout << isim << " gecti!" << std::endl;
        }
        else {
            std::cout << isim << " kaldi!" << std::endl;
        }
    }
};

int main() {
    // Nesneyi oluştururken verileri parantez içinde gönderiyoruz
    // Artık 3-4 satır yazmamıza gerek kalmadı!
    Ogrenci ogr1("Ali", 85);
    Ogrenci ogr2("Ayse", 40);

    ogr1.GectiMi();
    ogr2.GectiMi();

    return 0;
},

#include <iostream>
#include <string>



class Karakter {
    public:
	std::string isim ;
    int saglık;
    void BilgiGoster() {
        std::cout << "Isim: " << isim << std::endl;
        std::cout << "Saglik: " << saglık << std::endl;
	}
};
 class Savasci : public Karakter {
    public:
    int kilicGucu ;
    Savasci(std::string pIsim, int pSaglik, int pGuc) {
        isim = pIsim;
        saglık = pSaglik;
        kilicGucu = pGuc;
    }

   void saldir(){
       std::cout <<isim<< " kılıcıyla " << kilicGucu << " kadar hasar verdi" << std::endl;
   }
};
int main() {
	Savasci savasci1("Aragorn", 100, 25);
	Savasci* ptr = &savasci1;
    ptr->saldir();
    

    Savasci& ref =  savasci1;
	ref.BilgiGoster();

    return 0; 
}*/
