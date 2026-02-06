
#include <stdio.h>
#include <stdlib.h>

/*
 * Dosya Formatı varsayımı:
 * Satır 1: Sunucu Sayısı (N)
 * Satır 2..N+1: SunucuAdı Güç Isı
 * Satır 2..N+1: ServerID Güç Isı
 * Sonraki Satır: Kabin Sayısı (M)
 * Sonraki Satır: Kapasite
 * Sonraki Satır: K Sayısı
 */

typedef struct {
  int id;
  int guc;
  int isi;
  float performans; // Isı / Güç oranı
} Sunucu;

int main() {
  FILE *fp = fopen("veriler.txt", "r");
  if (fp == NULL) {
    printf("Dosya acilamadi!\n");
    return 1;
  }

  int sunucu_sayisi;
  fscanf(fp, "%d", &sunucu_sayisi);
  printf("Sunucu Sayisi: %d\n", sunucu_sayisi);

  Sunucu *sunucular = (Sunucu *)malloc(sunucu_sayisi * sizeof(Sunucu));

  for (int i = 0; i < sunucu_sayisi; i++) {
    fscanf(fp, "%d %d %d", &sunucular[i].id, &sunucular[i].guc,
           &sunucular[i].isi);
    sunucular[i].performans = (float)sunucular[i].isi / sunucular[i].guc;
    printf("Sunucu ID: %d, Guc: %d, Isi: %d, Isi/Guc: %.2f\n", sunucular[i].id,
           sunucular[i].guc, sunucular[i].isi, sunucular[i].performans);
  }

  int kabin_sayisi;
  fscanf(fp, "%d", &kabin_sayisi);
  printf("Kabin Sayisi: %d\n", kabin_sayisi);

  int kapasite;
  fscanf(fp, "%d", &kapasite);
  printf("Kapasite: %d\n", kapasite);

  float k_sayisi;
  fscanf(fp, "%f", &k_sayisi);
  printf("K Sayisi: %.2f\n", k_sayisi);

  fclose(fp);
  free(sunucular);

  return 0;
}
