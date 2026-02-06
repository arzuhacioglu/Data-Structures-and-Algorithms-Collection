#include <stdio.h>

int main() {
    int k, N, i, boyut, ucaksayisi1 = 0, ucaksayisi2 = 0,boyut;
    float gecikme1 = 0.0, gecikme2 = 0.0;

    printf("Ucaklarin kac dakika arayla kalkabileceginin bilgisini giriniz: ");
    scanf("%d", &k);

    printf("Kalkis yapmak isteyen ucak adetini giriniz: ");
    scanf("%d", &N);

    int ucakno[N], kalkisaat[N];

    for (i = 0; i < N; i++) {
        printf("%d. ucagin numarasini ve kalkis saatini sirasiyla giriniz: ", i + 1);
        scanf("%d %d", &ucakno[i], &kalkisaat[i]);
    }

    // Pistler için diziler
    if(N%2==0){
        boyut= N/2;
    }else{
        boyut=N/2+1;
    }

    int pist1[boyut], pist2[boyut], pistucakno1[boyut], pistucakno2[boyut];

    for (i = 0; i < boyut; i++) {
        pist1[i] = 0;
        pist2[i] = 0;
        pistucakno1[i] = 0;
        pistucakno2[i] = 0;
    }

    // Uçakları sırayla diziye yerleştirme
    for (i = 0; i < N; i++) {
        if (ucaksayisi1 == 0 || (pist1[ucaksayisi1 - 1] + k <= kalkisaat[i])) {
            pist1[ucaksayisi1] = kalkisaat[i];
            pistucakno1[ucaksayisi1] = ucakno[i];
            ucaksayisi1++;
        } else if (ucaksayisi2 == 0 || (pist2[ucaksayisi2 - 1] + k <= kalkisaat[i])) {
            pist2[ucaksayisi2] = kalkisaat[i];
            pistucakno2[ucaksayisi2] = ucakno[i];
            ucaksayisi2++;
        } else {
            if (ucaksayisi1 <= ucaksayisi2) {
                pist1[ucaksayisi1] = pist1[ucaksayisi1 - 1] + k;
                pistucakno1[ucaksayisi1] = ucakno[i];
                gecikme1 += pist1[ucaksayisi1] - kalkisaat[i];
                ucaksayisi1++;
            } else {
                pist2[ucaksayisi2] = pist2[ucaksayisi2 - 1] + k;
                pistucakno2[ucaksayisi2] = ucakno[i];
                gecikme2 += pist2[ucaksayisi2] - kalkisaat[i];
                ucaksayisi2++;
            }
        }
    }

    printf("\nPist1_Ucaklar: ");
    for (i = 0; i < ucaksayisi1; i++) {
        printf("%d ", pistucakno1[i]);
    }
    printf("\nPist1_Saatler: ");
    for (i = 0; i < ucaksayisi1; i++) {
        printf("%d ", pist1[i]);
    }
    printf("\nOrtalama Gecikme: %.4f\n", gecikme1 / ucaksayisi1);

    printf("\nPist2_Ucaklar: ");
    for (i = 0; i < ucaksayisi2; i++) {
        printf("%d ", pistucakno2[i]);
    }
    printf("\nPist2_Saatler: ");
    for (i = 0; i < ucaksayisi2; i++) {
        printf("%d ", pist2[i]);
    }
    printf("\nOrtalama Gecikme: %.4f\n", gecikme2 / ucaksayisi2);

    return 0;
}

