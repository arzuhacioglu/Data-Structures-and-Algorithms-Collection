#include <stdio.h>
#include <stdlib.h>

/*
@brief Agacın bir yapragının icerecegi bilgiler struct yapisi olarak kurgulanmistir.
*/
typedef struct Node {
    char isim[100];
    int yas;
    int maas;
    struct Node* altCalisan;
    struct Node* yanCalisan;
} Node;

/*
@brief Dosyadan okunan elemanlar oncelikle bagli listeye eklenir. Bu sebeple bagli liste yapisi kurgulanmistir.
*/
typedef struct ElemanListesi {
    Node* node;
    struct ElemanListesi* next;
} ElemanListesi;

/*
@brief İki stringin esitligi karsilastirilir. 
@param *a 1.karakter dizisi.
@param *b 2.karakter dizisi.
@return İki string esitse 1 değilse 0 dondurulur.
*/
int str_esit(const char* a, const char* b) {
    while (*a && *b) {
        if (*a != *b) return 0;
        a++; b++;
    }
    return (*a == '\0' && *b == '\0');
}
/*
@brief Kaynak string hedef stringe kopyalanir. 
@param *a Hedef karakter dizisi.
@param *b Kaynak karakter dizisi.
*/
void str_kopyala(char* hedef, const char* kaynak) {
    while (*kaynak) {
        *hedef++ = *kaynak++;
    }
    *hedef = '\0';
}

/*
@brief Yeni bir dugum olusturulur.
@param isim Calisan personelin ismi.
@param yas Calisan personelin yasi.
@param maas Calisan personelin yasi.
@return Olusan yeni dugum dondurulur.
*/
Node* dugumOlustur(const char* isim, int yas, int maas) {
    Node* newNode = malloc(sizeof(Node));
    str_kopyala(newNode->isim, isim);
    newNode->yas = yas;
    newNode->maas = maas;
    newNode->altCalisan = NULL;
    newNode->yanCalisan = NULL;
    return newNode;
}

/*
@brief Olusturulan dugumu bagli listeye ekler
@param head Liste basinin adresidir.
@param node Eklenmesi istenilen yeni dugumdur.
*/
void listeyeEkle(ElemanListesi** head, Node* node) {
    ElemanListesi* yeni = malloc(sizeof(ElemanListesi));
    yeni->node = node;
    yeni->next = *head;
    *head = yeni;
}

/*
@brief Verilen isme sahip dugumu bagli listede arar
@param head Liste basinin adresidir.
@param isim Bulunmak istenen isimdir.
@return Aranan isme ait dugum bulunursa dugum bulunmazsa Null dondurulur.
*/
Node* dugumBul(ElemanListesi* head, const char* isim) {
    while (head) {
        if (str_esit(head->node->isim, isim)) return head->node;
        head = head->next;
    }
    return NULL;
}

/*
@brief Bir ebeveyne cocuk dugum ekler.
@param ebeveyn Ata yani ust birim dugumudur.
@param cocuk Ataya baglanacak cocuk yani alt calisan dugumudur.
*/
void altEkle(Node* ebeveyn, Node* cocuk) {
    if (ebeveyn->altCalisan == NULL) {
        ebeveyn->altCalisan = cocuk;
    } else {
        Node* temp = ebeveyn->altCalisan;
        while (temp->yanCalisan) temp = temp->yanCalisan;
        temp->yanCalisan = cocuk;
    }
}

/*
@brief Olusturulan agaci ekrana yazdirir.
@param kok Agacin kok dugumu.
@param seviye Agacin seviye sayisi.
*/
void agaci_yazdir(Node* kok, int seviye) {
    int i;
    if (!kok) return;

    for (i = 0; i < seviye; i++) printf("  ");
    printf("- %s (Yas: %d, Maas: %d)\n", kok->isim, kok->yas, kok->maas);

    agaci_yazdir(kok->altCalisan, seviye + 1);
    agaci_yazdir(kok->yanCalisan, seviye);
}

/*
@brief Olusan agacin derinligini bulur
@param Dugum Agacin dugumu.
@return Maksimum seviye sayisi.
*/
int maksimumDerinlik(Node* dugum) {
    if (!dugum) return 0;
    int maks = 0;
    Node* cocuk = dugum->altCalisan;
    while (cocuk) {
        int d = maksimumDerinlik(cocuk);
        if (d > maks) maks = d;
        cocuk = cocuk->yanCalisan;
    }
    return maks + 1;
}


/*
@brief Her seviyede kac kisi calisiyor bulur.
@param dugum Agacin kok dugumu.
@param seviye Agacin seviye sayisi.
@param sayac Seviye sayaci dizisi.
@param kapasite Sayac dizisinin kapasitesi.
*/
void seviyeSayisi(Node* dugum, int seviye, int** sayac, int* kapasite) {
    int i;
    if (!dugum) return;

    (*sayac)[seviye]++;

    Node* cocuk = dugum->altCalisan;
    while (cocuk) {
        seviyeSayisi(cocuk, seviye + 1, sayac, kapasite);
        cocuk = cocuk->yanCalisan;
    }
}

/*
@brief Bir dugumun kac alt calisani var bulur
@param dugum Alt birim sayisi bulunmak istenen dugum.
@return Dugumun alt calisan sayisi.
*/
int cocukSayisi(Node* dugum) {
    int sayac = 0;
    Node* cocuk = dugum->altCalisan;
    while (cocuk) {
        sayac++;
        cocuk = cocuk->yanCalisan;
    }
    return sayac;
}

/*
@brief Sirkette hangi personelin daha cok alt birimi var bulur.
@param en_cok Bulunan dugum adresidir.
@param max_sayi Maksimum cocuk sayisi.
*/
void maksimumCocuk(Node* dugum, Node** en_cok, int* max_sayi) {
    if (!dugum) return;

    int sayi = cocukSayisi(dugum);
    if (sayi > *max_sayi) {
        *max_sayi = sayi;
        *en_cok = dugum;
    }

    Node* cocuk = dugum->altCalisan;
    while (cocuk) {
        maksimumCocuk(cocuk, en_cok, max_sayi);
        cocuk = cocuk->yanCalisan;
    }
}


/*
@brief Sirkette calisan personellerin yas ortalamasini ve sirketin bir aylik maas giderini hesaplar.
@param dugum Agacin kok dugumu.
@param toplam_yas Toplam yas birikimi.
@param toplam_maas Toplam maas birikimi.
@param kisi_sayisi Sirkette calisan kisi sayisi.
*/
void hesaplamalar(Node* dugum, int* toplam_yas, int* toplam_maas) {
    if (!dugum) return;

    *toplam_yas += dugum->yas;
    *toplam_maas += dugum->maas;

    Node* cocuk = dugum->altCalisan;
    while (cocuk) {
        hesaplamalar(cocuk, toplam_yas, toplam_maas);
        cocuk = cocuk->yanCalisan;
    }
}


/*
@brief Olusturulan agac ile islemler bittikten sonra hafızayı temizlemek icin kullanilir.
@param dugum Agacin kok dugumu.
*/
void agaci_sil(Node* dugum) {
    if (!dugum) return;

    Node* cocuk = dugum->altCalisan;
    while (cocuk) {
        Node* sonraki = cocuk->yanCalisan;
        agaci_sil(cocuk);
        cocuk = sonraki;
    }

    free(dugum);
}

/*
@brief Olusturulan gecici bagli liste ile islemler bittikten sonra hafızayı temizlemek icin kullanilir.
@param head Bagli listenin ilk elemaninin adresi.
*/
void listeyi_sil(ElemanListesi* head) {
    while (head) {
        ElemanListesi* next = head->next;
        free(head);
        head = next;
    }
}

int main() {
    int kisiSayisi,i, toplamYas = 0, toplamMaas = 0;;
    FILE* dosya = fopen("personel3.txt", "r");
    if (!dosya) {
        printf("Dosya acma hatasi.\n");
        return 1;
    }

    fscanf(dosya, "%d", &kisiSayisi);

    ElemanListesi* liste = NULL;
    Node* kok = NULL;

    for (i = 0; i < kisiSayisi; i++) { //Once dosyadan elemanlar ve ozellikleri okunur. 
        char ad[30], ebeveynAdi[30];
        int yas, maas;

        fscanf(dosya, "%s %d %d %s", ad, &yas, &maas, ebeveynAdi);
        Node* yeni = dugumOlustur(ad, yas, maas); 
        listeyeEkle(&liste, yeni); // Gecici bir bagli liste olusturulur.

        if (str_esit(ebeveynAdi, "NULL")) {
            kok = yeni;
        } else {
            Node* ebeveyn = dugumBul(liste, ebeveynAdi); // Ebeveyn kontrolu yapilarak agac yapisi kurulur.
            if (ebeveyn) {
                altEkle(ebeveyn, yeni);
            } else {
                printf("HATA: Ebeveyn bulunamadi → %s\n", ebeveynAdi);
            }
        }
    }
    fclose(dosya);

    printf("\n Agac Yapisi:\n"); //Olusturulan agac yapisinin dogrulugunu kontrol etmek icin kullanilir.
    agaci_yazdir(kok, 0);

    //Agacin derinligi bulunur.
    int derinlik = maksimumDerinlik(kok);
    printf("\n Agac toplam %d seviyeden olusuyor.\n", derinlik);

    int* seviyeSayar = malloc(sizeof(int) * derinlik);
    int kapasite = derinlik;
    for (i = 0; i < kapasite; i++) seviyeSayar[i] = 0;

    //Agacin her seviyesinde kisi sayisi ayri ayri yazdirilir
    seviyeSayisi(kok, 0, &seviyeSayar, &kapasite);
    printf("\n Her seviyedeki kisi sayisi:\n");
    for (int i = 0; i < kapasite; i++) {
        if (seviyeSayar[i] > 0)
            printf(" Seviye %d: %d kisi\n", i+1, seviyeSayar[i]);
    }
    free(seviyeSayar);

    //En fazla calisana sahip olan personel bulunur.
    Node* enCokAlt = NULL;
    int maksCocuk = -1;
    maksimumCocuk(kok, &enCokAlt, &maksCocuk);
    if (enCokAlt)
        printf("\n En fazla alt calısana sahip kisi: %s (%d kisi)\n", enCokAlt->isim, maksCocuk);

    //Sirket calisanlarinin yas ortalamasi ve aylik maas giderleri bulunur.
   
    hesaplamalar(kok, &toplamYas, &toplamMaas);

    printf("\n Sirketin yas ortalamasi: %.2f\n", (double)toplamYas / kisiSayisi);
    printf(" Sirketin aylik toplam maas gideri: %d TL\n", toplamMaas);
    
    printf("\n");

    agaci_sil(kok);
    listeyi_sil(liste);

    return 0;
}
