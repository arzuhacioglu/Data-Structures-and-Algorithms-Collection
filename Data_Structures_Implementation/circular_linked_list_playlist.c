#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Linkli listeleri olustururken kullanilacak struct yapilari:
typedef struct {//Sarki bilgilerini tutar.
    char isim[100];
    int sure;
    int oynatmaSayisi;
} Sarki;

typedef struct Node {//Circular double linked listin her bir dugumunde olan bilgileri tutar.
    Sarki* sarki;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct {//Kullanici dizisinin bas dugumunu tutar.
    Node* head;
} Kullanici;

/**
 * @brief Yeni bir dugum olusturur.
 * Bu fonksiyon, verilen bir Sarki pointer'i ile yeni bir dugum olusturur ve bu dugumun baglantilarini  NULL olarak ayarlar.
 * @param sarki Pointer türünde bir sarki nesnesi.
 * @return Node* Yeni oluşturulan düğümün adresi döndürülür.
 */
Node* yeniNode(Sarki* sarki) {
    Node* yeni = (Node*)malloc(sizeof(Node));
    yeni->sarki = sarki;
    yeni->next = NULL;
    yeni->prev = NULL;
    return yeni;
}

/**
 * @brief Circular doubly linked list'e yeni bir sarki ekler.
 * Bu fonksiyon, verilen sarkiyi circular doubly linked list'e ekler. Liste bossa eklenen sarkiyi ilk eleman yapar. Liste zaten doluysa, 
 * yeni sarkiyi listenin sonuna ekler ve baglantilari gunceller.
 * @param kullanici Kullanici bilgilerini iceren struct. Bu struct, kullaniciya ait sarki listesini tutar.
 * @param sarki Yeni eklenecek sarkiyi temsil eden pointer.
 */
void circularListeyeEkle(Kullanici* kullanici, Sarki* sarki) {
    Node* yeni = yeniNode(sarki);
    if (kullanici->head == NULL) {
        yeni->next = yeni;
        yeni->prev = yeni;
        kullanici->head = yeni;
    } else {
        Node* tail = kullanici->head->prev;
        tail->next = yeni;
        yeni->prev = tail;
        yeni->next = kullanici->head;
        kullanici->head->prev = yeni;
    }
}

/**
 * @brief Videoda kontrol icin kullanicilarin playlistleri yazdirilir.
 * @param kullanicilar Kulanicilarin listesini tutan array.
 * @param K Kullanici sayisi.
 */
void yazdir(Kullanici* kullanicilar, int K) {
    int i;
    for (i = 0; i < K; i++) {
        printf("Kullanici %d: ", i + 1);
        Node* temp = kullanicilar[i].head;
        if (temp != NULL) {
            Node* baslangic = temp;
            do {
                printf("%s(%d) ", temp->sarki->isim, temp->sarki->sure);
                temp = temp->next;
            } while (temp != baslangic);
        }
        printf("\n");
    }
}

/**
 * @brief Dairesel listede belirtilen adim kadar ileri veya geri hareket eder.
 * Bu fonksiyon, verilen "steps" parametresine gore dairesel bir bagli listede hareket eder. 
 * @param node Baslangic noktasi olan dugum.
 * @param steps İleri veya geri gidilmesi gereken adim sayisi.
 * @return Node* Verilen adim sayisi kadar hareket edildikten sonra olusan yeni dugum.
 */
Node* moveCircular(Node* node, int steps) {
    int i;
    if (node == NULL) return NULL;
    Node* current = node;
    if (steps >= 0) {
        for (i = 0; i < steps; i++) {
            current = current->next;
        }
    } else {
        for (i = 0; i < -steps; i++) {  
            current = current->prev;
        }
    }
    return current;
}

/**
 * @brief Sarkilari, oynatma suresi ve sayisina gore karsilastiran fonksiyon.
 * Bu fonksiyon, iki sarkiyi karsilastirarak siralama yapar. Oncelikle sarkilarin
 * oynatma sayilari karsilastirilir. Eger oynatma sayilari farkliysa, buyuk olan 
 * sarki once gelir. Eger oynatma sayilari esitse, sarkilarin sureleri karsilastirilir.
 * Daha uzun süreli şarkı önce gelir.
 * @param a Karsilastirilacak ilk sarki.
 * @param b Karsilastirilacak ikinci şarkı.
 * @return int Karşılaştırma sonucu secilen sarki dondurulur.
 */
int karsilastirma(const void* a, const void* b) {
    Sarki* sarkiA = (Sarki*)a;
    Sarki* sarkiB = (Sarki*)b;

    if (sarkiB->oynatmaSayisi != sarkiA->oynatmaSayisi)
        return sarkiB->oynatmaSayisi - sarkiA->oynatmaSayisi;
    else
        return sarkiB->sure - sarkiA->sure;
}

/**
 * @brief Insertion Sort algoritmasi ile sarkilari siralama
 * Bu fonksiyon, şarkıları oynatma sayısı ve süreye göre sıralar. Sıralama, her seferinde 
 * en büyük öğeyi dizinin sonuna yerleştirerek yapılır.
 * @param dizi Sıralanacak şarkılar dizisi.
 * @param N Şarkıların toplam sayısı.
 * @param karsilastir Şarkılar arasındaki karşılaştırmayı yapan fonksiyon.
 */
void insertionSort(Sarki* dizi,int (*karsilastir)(const void*, const void*)) {
    int i, j;
    for (i = 1; i < 10; i++) {
        Sarki key = dizi[i];  
        j = i - 1;

        while (j >= 0 && karsilastir(&dizi[j], &key) > 0) {
            dizi[j + 1] = dizi[j];  
            j--;
        }
        dizi[j + 1] = key;  
    }
}

int main() {
    int i, j, N, K;
    srand(time(NULL));

    // Dosya acma islemleri
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Dosya açılamadı.\n");
        return 1;
    }

    fscanf(file, "%d %d", &N, &K);
    int ch;
    do {
        ch = fgetc(file);
    } while (ch != '\n' && ch != EOF);

    Sarki* sarkilar = (Sarki*)malloc(N * sizeof(Sarki));
    for (i = 0; i < N; i++) {
        fscanf(file, "%s %d", sarkilar[i].isim, &sarkilar[i].sure);
        sarkilar[i].oynatmaSayisi = 0;
    }

    Kullanici* kullanicilar = (Kullanici*)malloc(K * sizeof(Kullanici));
    int* playlistSizes = (int*)malloc(K * sizeof(int));

    for (i = 0; i < K; i++) {
        kullanicilar[i].head = NULL;
        playlistSizes[i] = 0;
    }

    char satir[1024];
    int userIndex = 0;

    // Kullanıcıların playlist'lerini olusturma
    while (userIndex < K) {
        if (fgets(satir, sizeof(satir), file) != NULL) {
            int index = 0, sarkiIndex = 0, satirBos = 1;

            while (satir[index] != '\0') {
                if (sscanf(satir + index, "%d", &sarkiIndex) == 1) {
                    satirBos = 0;
                    if (sarkiIndex >= 1 && sarkiIndex <= N) {
                        circularListeyeEkle(&kullanicilar[userIndex], &sarkilar[sarkiIndex - 1]);
                        playlistSizes[userIndex]++;
                    }
                }
                while (satir[index] >= '0' && satir[index] <= '9') index++;
                while (satir[index] == ' ' || satir[index] == '\r' || satir[index] == '\n') index++;
            }

            if (!satirBos) {
                userIndex++;
            }
        }
    }

    //Kullanicilarin playlistleri dogru okundu mu kontrol etmek icin kullanilir.
    yazdir(kullanicilar, K);
    printf("\n");

    int playlistIndex = 0;
    while (playlistIndex < K) {//Her kullanici icin 1 defa doner
        printf("\n");
        printf("Kullanıcı %d için adımlar:\n", playlistIndex + 1);
        int adimSayisi = (rand() % playlistSizes[playlistIndex]) + 1;  
        int* adimlar = (int*)malloc(adimSayisi * sizeof(int));

        //Kullanicilar icin istenen aralikta random bir adim dizisi olusturulur. Ardindan kontrol etmek icin yazdirilir.
        for (j = 0; j < adimSayisi; j++) {
            adimlar[j] = (rand() % (2 * playlistSizes[playlistIndex] + 1)) - playlistSizes[playlistIndex];
        }
        for (j = 0; j < adimSayisi; j++) {
            printf("%d\t", adimlar[j]);
        }
        printf("\n");

        Node* current = kullanicilar[playlistIndex].head;

        for (j = 0; j < adimSayisi; j++) {
            current = moveCircular(current, adimlar[j]);
            printf(" -> %s", current->sarki->isim);
            current->sarki->oynatmaSayisi++; 
        }
        free(adimlar);
        playlistIndex++;
    }

    // En cok dinlenen 10 sarkiyi bulma ve yazdirma
    Sarki* sorted = (Sarki*)malloc(N * sizeof(Sarki));
    for (i = 0; i < N; i++) {
        sorted[i] = sarkilar[i];
    }

    insertionSort(sorted,karsilastirma);

    printf("\n--- Genel Top 10 Şarkı Listesi ---\n");
    for (i = 0; i < 10 ;i++) {
        if (sorted[i].oynatmaSayisi > 0) {
            float toplamDakika = (sorted[i].sure * sorted[i].oynatmaSayisi) / 60.0f;
            printf("%d.Sarki :%s - %d kez dinlenmiş - Toplam %.2f dakika\n",
                i+1,
                sorted[i].isim,
                sorted[i].oynatmaSayisi,
                toplamDakika);
        }
    }

    // Temizlik
    fclose(file);
    free(sarkilar);
    free(kullanicilar);
    free(playlistSizes);
    free(sorted);

    return 0;
}
