#include <stdio.h>
#define maxboyut 23

int oyuncusecme(char harf) {
    if (harf == 'K') {
        return 1;  
    } else if (harf == 'S') {
        return 2;  
    } else if(harf == 'M'){
        return 3; 
    }
}

int main() {
    // Degiskenler
    int i, j, boyut, flag, secim, cikis, x, y, devam, ksayisi, ssayisi, msayisi, kazanan, xkontrol, ykontrol, xgecici, ygecici, sira, gecerlimi,dolu,esitlik;
    char oyuncu1, oyuncu2, oyuncu3, simdikioyuncu;
    
    // Oyun Girisi
    printf("!!!!!!!!!!TRIVERSI OYUNUNA HOSGELDINIZ!!!!!!!!!!\nOYUNA BASLAMAK ICIN 1'E OYUNDAN CIKMAK ICIN 2'YE BASINIZ: ");
    scanf("%d", &secim);

    if (secim == 1) {
        cikis = 1;
        esitlik=0;
        oyuncu1 = 'K'; 
        oyuncu2 = 'S'; 
        oyuncu3 = 'M'; 
        ksayisi = 0;
        ssayisi = 0;
        msayisi = 0;
        kazanan = 0;
        simdikioyuncu = oyuncu2; 
        
        int yonler[8][2] = {
            {-1, 0},  
            {1, 0},   
            {0, -1},  
            {0, 1},   
            {-1, -1}, 
            {-1, 1},  
            {1, -1},  
            {1, 1}    
        };
        
        do {
            printf("Oyun tahtasinin boyutunu giriniz: ");
            scanf("%d", &boyut);
        } while (boyut > maxboyut);
        
        char oyuntahtasi[boyut][boyut];
        
        // Tahtayi olusturma
        for (i = 0; i < boyut; i++) {
            for (j = 0; j < boyut; j++) {
                oyuntahtasi[i][j] = '-'; 
            }
        }
        
        printf("Baslangicta tahtanin durumu asagidaki gibidir:\n");
        for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            printf("%c ", oyuntahtasi[i][j]);
        }
        printf("\n");
    }
        
        // Tahtanin ortasina tek tas koyma 
        if (boyut % 2 == 0) {
            oyuntahtasi[boyut / 2 - 1][boyut / 2 - 1] = oyuncu1;
        } else {
            oyuntahtasi[boyut / 2][boyut / 2] = oyuncu1; 
        }
        
        // Ilk tas konulduktan sonra tekrar tahtayi yazdirma
        printf("1.oyuncunun tasi otomatik olarak orta noktaya konulur.Tahtanin durumu asagidaki gibidir.\n");
        for (i = 0; i < boyut; i++) {
        for (j = 0; j < boyut; j++) {
            printf("%c ", oyuntahtasi[i][j]);
        }
        printf("\n");
    }
        
        // Oyun dongusu
        while (cikis == 1) {
            sira = oyuncusecme(simdikioyuncu);
            printf("\nOyuncu %d'nin sirasi!\n", sira);
            
            printf("Oyuna devam etmek icin 1'i, oyundan cikmak icin 2'yi tuslayınız: ");
            scanf("%d", &devam);
            
            if (devam == 2) {
                for (i = 0; i < boyut; i++) {
                    for (j = 0; j < boyut; j++) {
                        if (oyuntahtasi[i][j] == 'K') {
                            ksayisi++;
                        } else if (oyuntahtasi[i][j] == 'S') {
                            ssayisi++;
                        } else if (oyuntahtasi[i][j] == 'M') {
                            msayisi++;
                        }
                    }
                }
                
                if (ksayisi > ssayisi && ksayisi > msayisi) {
                    kazanan = 'K';
                } else if (ssayisi > ksayisi && ssayisi > msayisi) {
                    kazanan = 'S';
                } else if (msayisi > ksayisi && msayisi > ssayisi) {
                    kazanan = 'M';
                }
                
                printf("%c oyuncunun tas sayisi:%d\n",oyuncu1,ksayisi);
                printf("%c oyuncunun tas sayisi:%d\n",oyuncu2,ssayisi);
                printf("%c oyuncunun tas sayisi:%d\n",oyuncu3,msayisi);
                if(kazanan=='K'||kazanan=='S'||kazanan=='M'){
                    printf("Oyunun kazanani: %d.oyuncu\n", oyuncusecme(kazanan));
                    
                }else{
                    printf("Oyunda beraberlik soz konusu,kazanan oyuncu yok.\n");
                }
                printf("OYUNDAN CIKIS YAPILIYOR...\n");
                cikis = 0;
            } else {
                printf("Tasinizi koymak istediğiniz konumun satir ve sutun degerlerini sirasiyla giriniz: ");
                scanf("%d %d", &x, &y);
                
                // X ve y'nin sinirlari asmamasi kontrol edilir
                if (x >= 0 && x < boyut && y >= 0 && y < boyut && oyuntahtasi[x][y] == '-') {
                    
                    // Sinirlar ve bosluk uygun komsu rakip tas mı kontrol edilir
                    gecerlimi = 0;
                    for (i = 0; i < 8; i++) {
                        xkontrol = yonler[i][0]; 
                        ykontrol = yonler[i][1]; 
                        xgecici = x + xkontrol; 
                        ygecici = y + ykontrol;

                        if (xgecici >= 0 && xgecici < boyut && ygecici >= 0 && ygecici < boyut && oyuntahtasi[xgecici][ygecici] != '-' && oyuntahtasi[xgecici][ygecici] != simdikioyuncu) {
                            gecerlimi = 1;
                        }
                    }

                    if (gecerlimi == 1) {
                        // Tasi koyma islemi ve rakip taslari donuşturme
                        oyuntahtasi[x][y] = simdikioyuncu;
                        for (i = 0; i < 8; i++) {
                            xkontrol = yonler[i][0]; 
                            ykontrol = yonler[i][1]; 
                            xgecici = x + xkontrol; 
                            ygecici = y + ykontrol;
                            flag = 0;

                            // Rakip tasları kontrol etme ve donuşturme
                            while (xgecici >= 0 && xgecici < boyut && ygecici >= 0 && ygecici < boyut && oyuntahtasi[xgecici][ygecici] != '-' && oyuntahtasi[xgecici][ygecici] != simdikioyuncu) {
                                xgecici += xkontrol;
                                ygecici += ykontrol; 
                            }

                            if (xgecici >= 0 && xgecici < boyut && ygecici >= 0 && ygecici < boyut && oyuntahtasi[xgecici][ygecici] == simdikioyuncu) {
                                flag = 1; 
                            }

                            if (flag == 1) {
                                xgecici -= xkontrol;
                                ygecici -= ykontrol;
                                while (xgecici != x || ygecici != y) {
                                    oyuntahtasi[xgecici][ygecici] = simdikioyuncu; 
                                    xgecici -= xkontrol;
                                    ygecici -= ykontrol;
                                }
                            }
                        }

                        // Guncel tahtayı yazdırma
                        printf("Guncel Tahta Durumu:\n");
                        for (i = 0; i < boyut; i++){
                            for (j = 0; j < boyut; j++){
                                printf("%c ", oyuntahtasi[i][j]);
                            }
                            printf("\n");
                        }
                        
                        // Tahta dolu mu kontrol yapma
                        dolu = 0;
                        for (i = 0; i < boyut; i++) {
                            for (j = 0; j < boyut; j++) {
                                if (oyuntahtasi[i][j] != '-') {
                                    dolu++;
                                }
                            }
                        }
                        if (dolu == boyut * boyut) {
                            printf("Tahtada yer bittigi icin oyuna devam edilemiyor.Oyun sonuclari asagida gosterildigi gibidir.\n");
                            for (i = 0; i < boyut; i++) {
                                for (j = 0; j < boyut; j++) {
                                    if (oyuntahtasi[i][j] == 'K') {
                                        ksayisi++;
                                    } else if (oyuntahtasi[i][j] == 'S') {
                                        ssayisi++;
                                    } else if (oyuntahtasi[i][j] == 'M') {
                                        msayisi++;
                                    }
                                 }
                            }
                            if (ksayisi > ssayisi && ksayisi > msayisi) {
                                kazanan = 'K';
                            } else if (ssayisi > ksayisi && ssayisi > msayisi) {
                                kazanan = 'S';
                            } else if (msayisi > ksayisi && msayisi > ssayisi) {
                                kazanan = 'M';
                            }
                
                            printf("%c oyuncunun tas sayisi:%d\n",oyuncu1,ksayisi);
                            printf("%c oyuncunun tas sayisi:%d\n",oyuncu2,ssayisi);
                            printf("%c oyuncunun tas sayisi:%d\n",oyuncu3,msayisi);
                            if(kazanan=='K'||kazanan=='S'||kazanan=='M'){
                                printf("Oyunun kazanani: %d.oyuncu\n", oyuncusecme(kazanan));
                    
                            }else{
                                printf("Oyunda beraberlik soz konusu,kazanan oyuncu yok.\n");
                            }
                            printf("OYUNDAN CIKIS YAPILIYOR...\n");
                            cikis=2;
                        }
                        
                        // Sira degisimi
                        if (simdikioyuncu == oyuncu1) {
                            simdikioyuncu = oyuncu2;
                        } else if (simdikioyuncu == oyuncu2) {
                            simdikioyuncu = oyuncu3;
                        } else {
                            simdikioyuncu = oyuncu1;
                        }
                        
                    } else {
                        printf("Tasiniza rakip tasa komsu konuma koymalisiniz. Tekrar deneyiniz.\n");
                    }
                } else {
                    if (x < 0 || x > boyut || y < 0 || y > boyut ) {
                        printf("Yapmak istediginiz hamle oyun tahtasinin sinirlarini asmakta. Tekrar deneyiniz.\n");
                    } else if(oyuntahtasi[x][y]!='-') {
                        printf("Hamle yapmak istediginiz alan dolu. Tekrar deneyiniz.\n");
                    }
                }
            }
        }
    } 
    else {
           printf("OYUN BASLATILAMADI.\nOYUNDAN CIKIS YAPILIYOR...\n");
    }
    return 0;
}
