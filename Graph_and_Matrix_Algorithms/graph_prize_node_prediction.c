#include <stdio.h>
#include <stdlib.h>

//Tahmin edilen sonuc yazdirilirken bu sonuca kac adimda ulasildiği da yazdirilmalidir.
//Bu sebeple kullanilacak struct yapisi
typedef struct {
    int bulunanDugum;
    int adimSayisi;
} TahminSonuc;

/**
 * @brief Verilen dugum kullanici tarafindan belirlenen odule komsu mudur kontrol eder.
 * @param x Odul dugumu ile komsulugu kontrol edilecek olan dugum.
 * @param dugumSayisi Graftaki mevcut dugum sayisi.
 * @param **komsulukMatrisi Dosyadan okunan komsuluk matrisini gosteren isaretci.
 * @param odul Kullanici tarafindan belirlenen odul dugumu.
 * @return Komsular ise 1 degiller ise 0 dondurulur.
 */
int komsuMu(int x, int dugumSayisi, int **komsulukMatrisi, int odul) {
    return komsulukMatrisi[x][odul] == 1;
}

/**
 * @brief Verilen dugumun derecesini belirler.
 * @param dugum Derecesi kontrol edilecek olan dugumdur.
 * @param dugumSayisi Graftaki mevcut dugum sayisi.
 * @param **komsulukMatrisi Dosyadan okunan komsuluk matrisini gosteren isaretci.
 * @return Mevcut dugumun derecesi dondurulur.
 */
int derece(int dugum, int dugumSayisi, int **komsulukMatrisi) {
    int k = 0, i;
    for (i = 0; i < dugumSayisi; i++) {
        if (komsulukMatrisi[dugum][i] == 1)
            k++;
    }
    return k;
}

/**
 * @brief Bir dugumun komsuluklari tespit ediltikten ve elemeler yapildiktan sonra kalan adaylari yazdirir.
 * @param dugumSayisi Graftaki mevcut dugum sayisi.
 * @param odulMu Dugumun odul olma potansiyeli odulMu dizisi icerisinde tutulur.
 * Bu sebeple odulMu dizisinin isaretcisi parametre olarak girilir.
 */
void printAdaylar(int dugumSayisi, int *odulMu) {
    int i;
    printf("Aday düğümler: ");
    for (i = 0; i < dugumSayisi; i++) {
        if (odulMu[i]) printf("%d ", i);
    }
    printf("\n");
}

/**
 * @brief Dosyadan okunan komsuluk matrisi uzerinden dugumlere komsu diye sorarak odul tahmini yapilir.
 * Bu fonksiyon, tum dugumleri baslangicta aday olarak kabul eder. Dugumler, sahip olduklari komsuluk sayisina gore azalan sirayla degerlendirilir.
 * Her adimda secilen dugum icin odul dugumune komsu olup olmadigi sorgulanir ve verilen cevaba gore odul adaylari olmayanlar elenir.
 * Yalnizca bir aday kaldiginda, bu dugum odul dugumu olarak tahmin edilir.
 * @param dugumSayisi Graftaki mevcut dugum sayisi.
 * @param **komsulukMatrisi Dosyadan okunan komsuluk matrisini gosteren isaretci.
 * @param odul Kullanici tarafindan belirlenen odul dugumu.
 * @return Tahmin edilen odul dugumu ve bu odul dugumune ulasmak icin kac adim atildigi dondurulur.
 */
TahminSonuc odulTahminEt(int dugumSayisi, int **komsulukMatrisi, int odul) {
    int i, j;
    int adim = 0,flag=0;
    int tahmin = -1;

    //Bir dugumu odul olup olmama potansiyelini kontrol etmek icin kullanilir.
    int *odulMu = (int *)malloc(dugumSayisi * sizeof(int));
    for (i = 0; i < dugumSayisi; i++)
        odulMu[i] = 1;

    //Dugumlerin derecelerini tutar.
    int *dereceler = (int *)malloc(dugumSayisi * sizeof(int));
    for (i = 0; i < dugumSayisi; i++)
        dereceler[i] = derece(i, dugumSayisi, komsulukMatrisi);

    int *sira = (int *)malloc(dugumSayisi * sizeof(int));
    for (i = 0; i < dugumSayisi; i++)
        sira[i] = i;

    //Dugumler azalan derecelerine gore sira dizisine siralanirlar.
    for (i = 0; i < dugumSayisi - 1; i++) {
        for (j = 0; j < dugumSayisi - i - 1; j++) {
            if (dereceler[sira[j]] < dereceler[sira[j + 1]]) {
                int tmp = sira[j];
                sira[j] = sira[j + 1];
                sira[j + 1] = tmp;
            }
        }
    }

    int mevcutIndex = 0;

    //Kontrol edilen index dugum sayisini asmadikca ya da erken cikis sarti saglandikca dongu devam eder.
    while (mevcutIndex < dugumSayisi && flag==0) {
        int dugum = sira[mevcutIndex];

        printf("Soru #%d: %d düğümü ödül düğümüne komşu mu?\n", adim + 1, dugum);
        adim++;
        int cevap = komsuMu(dugum, dugumSayisi, komsulukMatrisi, odul);//Dugumlerin komsuluklari kontrol edilir.
        printf("  Cevap: %s\n", cevap ? "EVET" : "HAYIR");

        if (!cevap) {//Dugumler komsu ise bu dugume komsu olmayan dugumlerin odul adayligi sifirlanir.
            for (j = 0; j < dugumSayisi; j++) {
                if (komsulukMatrisi[dugum][j] == 1)
                    odulMu[j] = 0;
            }
        } else {//Dugumler komsu degil ise bu dugume komsu olan dugumlerin odul adayligi sifirlanir.
            for (j = 0; j < dugumSayisi; j++) {
                if (komsulukMatrisi[dugum][j] != 1)
                    odulMu[j] = 0;
            }
        }

        //Sorgulama yapildiktan sonra kalan odul adaylarini yazdirir
        printAdaylar(dugumSayisi, odulMu);

        int kalanAday = 0, sonAday = -1;
        for (j = 0; j < dugumSayisi; j++) {
            if (odulMu[j]) {
                kalanAday++;
                sonAday = j;
            }
        }

        if (kalanAday == 1) {
            tahmin = sonAday;
            flag=1;
        }

        mevcutIndex++;
    }

    free(odulMu);
    free(sira);
    free(dereceler);

    TahminSonuc sonuc;
    sonuc.bulunanDugum = tahmin;
    sonuc.adimSayisi = adim;
    return sonuc;
}

int main() {
    int i, j, odul;
    char *satir = (char *)malloc(1024 * sizeof(char));
    //Once dosya acilir ve dugum sayisi tespit edilir.
    FILE *fp = fopen("G1KMAT.txt", "r");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }

    int dugumSayisi = 0;
    while (fgets(satir, 1024, fp) != NULL) {
        dugumSayisi++;
    }
    fclose(fp);

    int **komsulukMatrisi = (int **)malloc(dugumSayisi * sizeof(int *));
    for (i = 0; i < dugumSayisi; i++) {
        komsulukMatrisi[i] = (int *)malloc(dugumSayisi * sizeof(int));
    }
    
    //Dosya tekrardan acilarak komsuluk matrisi okunur.
    fp = fopen("G1KMAT.txt", "r");
    if (fp == NULL) {
        printf("Dosya acilamadi!\n");
        return 1;
    }
    for (i = 0; i < dugumSayisi; i++) {
        for (j = 0; j < dugumSayisi; j++) {
            fscanf(fp, "%d", &komsulukMatrisi[i][j]);
        }
    }
    fclose(fp);

    printf("Komsuluk Matrisi:\n");
    for (i = 0; i < dugumSayisi; i++) {
        for (j = 0; j < dugumSayisi; j++)
            printf("%d ", komsulukMatrisi[i][j]);
        printf("\n");
    }

    //Kullanicidan odul dugumu alinir.
    printf("\nOdul dugumu olarak belirlemek istediginiz dugumu giriniz: ");
    scanf("%d", &odul);

    if (odul < 0 || odul >= dugumSayisi) {
        printf("Girmis oldugunuz dugum grafta mevcut degildir!\n");
        return 1;
    }

    //Tasarlanan algoritma ile odul tahmini yaptirilir ve sonuclar ekrana yazdirilir.
    TahminSonuc sonuc = odulTahminEt(dugumSayisi, komsulukMatrisi, odul);

    printf("************************************************************************************************************************************************\n");
    printf("Tahmin edilen odul dugumu: %d\n", sonuc.bulunanDugum);
    printf("Toplam adim sayisi: %d\n", sonuc.adimSayisi);

    if (sonuc.bulunanDugum == odul)
        printf("Algoritmanin yaptigi tahmin dogrudur!\n");
    else{
        printf("Algoritmanin buldugu odul: %d\n",sonuc.bulunanDugum);
        printf("Algoritmanin yaptigi tahmin yanlistir, gercek odul: %d\n", odul);
    }

    for (i = 0; i < dugumSayisi; i++) {
        free(komsulukMatrisi[i]);
    }
    free(komsulukMatrisi);
    free(satir);

    return 0;
}
