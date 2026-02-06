/*
 * Algorithm: Nuts and Bolts Problem (Randomized QuickSort)
 * Description: Matches and sorts elements from two arrays (Locks & Keys) 
 * where elements from the same array cannot be compared directly.
 * Complexity: O(n log n) Average Case
 * Technique: Divide and Conquer, Randomized Pivot Selection
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
@brief Bir anahtar secilerek bu anahara uygun kilit bulunur. Anahtarla karsilastirilarak kilitler kucuk,buyuk,esit olmak uzere uce ayrilir. En sonunda anahtar ve kilidin dogru yeri bulunur.
@param Anahtarlara uygun kilitler karisik olarak verilmistir.
@param Anahtarlar sirasiz bicimde verilmistir.
@param Dizilerin dogru bolunmesi icin low olarak dizinin baslangici,high olarak dizinin sonu verilmistir.
@return Rastgele secilen kilidin dizide yerlesecegi index dondurulur.
*/
int partition(int kilitler[], int anahtarlar[], int low, int high) {
    int secilenAnahtar, index, i, j, k,m,n,o,gecici;
    
    srand(time(NULL));
    index = rand() % (high - low + 1) + low; //Secilecek anahtarın indexi dizi icerisinden rastgele bicimde secilir.
    secilenAnahtar = anahtarlar[index];
    
    i = low - 1;//Aranan kilidin yerlesecegi yerin bulunmasını saglar.

    for (j = low; j < high; j++) { //Dizinin en kucuk indexli elemanindan baslanarak en buyuk indexli elemanina kadar dizi okunur.
        if (kilitler[j] < secilenAnahtar) { //Mevcut kilit secilen anahtardan kucuk ise yer degistirme islemi yapilir.
            gecici = kilitler[i + 1];
            kilitler[i + 1] = kilitler[j];
            kilitler[j] = gecici;
            i++; //Secilen anahtardan kucuk bir kilit bulundukca i arttirilir.
        } else if (kilitler[j] == secilenAnahtar) {//Mevcut kilit secilen anahtara esitse pivot bulunmustur. Dizi siralamasinin daha kolay gerceklenebilmesi icin dizinin sonuna tasinir.
            gecici = kilitler[high];
            kilitler[high] = kilitler[j];
            kilitler[j] = gecici;
            j--;//Yer degistirme islemi yaptiktan sonra bulunan kilidin yerine gecen kilit tekrar kontrol ettirilir.
        }
    }

    //En sona yerlestirilen uygun kilit kendinden buyukler ve kucukler ayristirildiktan sonra kendinden kucuk sayisina esdeger olan i'nin 1 fazlasina yerlestirilir.
    gecici = kilitler[i + 1];
    kilitler[i + 1] = kilitler[high];
    kilitler[high] = gecici;
    
    //Secilen kilide uygun anahtar bulunup yerlestirildikten sonra ayni islemler kilitler dizisi icin de gerceklestirilir.
    o=low-1;//Aranan anahtarin yerlesecegi yerin bulunmasını saglar.
    
    for(m=low;m<high;m++){ //Dizinin en kucuk indexli elemanindan baslanarak en buyuk indexli elemanina kadar dizi okunur.
        if(anahtarlar[m]<kilitler[i+1]){ //Mevcut anahtar secilen kilitten kucuk ise yer degistirme islemi yapilir.
            gecici=anahtarlar[o+1];
            anahtarlar[o+1]=anahtarlar[m];
            anahtarlar[m]=gecici;
            o++; //Secilen kilitten kucuk bir anahtar bulundukca o arttirilir.
        }else if(anahtarlar[m]==kilitler[i+1]){ //Mevcut anahtar secilen kilide esitse pivot bulunmustur. Dizi siralamasinin daha kolay gerceklenebilmesi icin dizinin sonuna tasinir.
            gecici=anahtarlar[high];
            anahtarlar[high]=anahtarlar[m];
            anahtarlar[m]=gecici;
            m--;//Yer degistirme islemi yaptiktan sonra bulunan anahtarin yerine gecen anahtar tekrar kontrol ettirilir.
        }
    }
    
    //En sona yerlestirilen uygun anahtar kendinden buyukler ve kucukler ayristirildiktan sonra kendinden kucuk sayisina esdeger olan o'nun 1 fazlasina yerlestirilir.
    gecici=anahtarlar[o+1];
    anahtarlar[o+1]=anahtarlar[high];
    anahtarlar[high]=gecici;
    
    
    return i + 1;
}

/*
@brief Kilitler dizisinden secilen rastgele bir kilit kullanilarak anahtarlar dizisi, anahtarlar kullanilarak ise kilitler dizisi quick sort algoritmasiyla siralanir.Bu algoritma recursive olarak buyuk ve kucuk dizilere uygulanir.
@param Anahtarlara uygun kilitler karisik olarak verilmistir.
@param Anahtarlar sirasiz bicimde verilmistir.
@param Dizilerin dogru bolunmesi icin low olarak dizinin baslangici,high olarak dizinin sonu verilmistir.
*/
void quicksort(int kilitler[], int anahtarlar[], int low, int high){
    if(low<high){
        int pivotindex=partition(kilitler,anahtarlar,low,high);
        quicksort(kilitler,anahtarlar,low,pivotindex-1);//küçükleri sıraladı
        quicksort(kilitler,anahtarlar,pivotindex+1,high);//büyükleri sıraladı
    }
}

int main(){
    //Kullanilacak degiskenler
    int boyut,i,j,*kilitler,*anahtarlar;
    //Dosya okuma ve dizileri atama islemleri
    FILE *dosya= fopen("veri.txt", "r");

    if(dosya==NULL){
        printf("Dosya açma hatası");
    }else {
        fscanf(dosya, "%d", &boyut);
        
        kilitler=(int*)malloc(boyut*sizeof(int));
        anahtarlar=(int*)malloc(boyut*sizeof(int));

        for (i = 0; i < boyut; i++) {
            fscanf(dosya, "%d", &kilitler[i]);
        }
        for (i = 0; i < boyut; i++) {
            fscanf(dosya, "%d", &anahtarlar[i]);
        }
        //Siralamadan onceki anahtarlar ve kilitler yazdirilir.
        printf("Anahtarlar:\n");
        for (i = 0; i < boyut; i++) {
            printf("%d\t",kilitler[i]);
        }
        printf("\n");
        printf("Kilitler\n");
        for (i = 0; i < boyut; i++) {
            printf("%d\t",anahtarlar[i]);
        }
        printf("\n");

        //Quicksort algoritmasi uygulanir ve siralanmis diziler tekrar yazdirilir.
        quicksort(kilitler,anahtarlar,0,boyut-1);

        printf("Sıralanmış kilitler:\n");
        for(i=0;i<boyut;i++){
            printf("%d\t",kilitler[i]);
        }
        printf("\n");
        printf("Sıralanmış anahtarlar:\n");
        for(i=0;i<boyut;i++){
            printf("%d\t",anahtarlar[i]);
        }
        printf("\n");

        //Bellek bosaltma islemleri
        free(kilitler);
        free(anahtarlar);

        //Dosya kapama islemi
        fclose(dosya);
    }

    return 0;
}
