#include <stdio.h>

int main(){
    int satir,sutun,i,j,temp,uzunluk,x,y,flag,yolNo=1,xOnceki,yOnceki;

    printf("Matrisin satir ve sutun sayisini sirasiyla giriniz:");
    scanf("%d %d",&satir,&sutun);

    int matris[satir][sutun];
    int gezilenler[satir][sutun];

    for(i=0;i<satir;i++){
        for(j=0;j<sutun;j++){
            printf("Matrisin %d.satir %d.sutun elemanini giriniz:" , i+1 , j+1);
            scanf("%d", &matris[i][j]);
            gezilenler[i][j] = 0;
        }
    }

    for(i=0;i<satir;i++){
        if(matris[i][0]!=0 && gezilenler[i][0] == 0){
                temp=matris[i][0];
                gezilenler[i][0]=1;
                uzunluk=1;
                x=i;
                y=0;

            while(y<sutun-1){
                flag=0;
                if(y+1<sutun && matris[x][y+1]==temp && gezilenler[x][y+1]==0){//sag
                    gezilenler[x][y+1]=1;
                    uzunluk++;
                    y++;                        
                    flag=1;
                }else if(y>0 && matris[x][y-1]==temp && gezilenler[x][y-1]==0){//sol
                    gezilenler[x][y-1]=1;
                    uzunluk++;
                    y--;
                    flag=1;
                }else if(x+1<satir && matris[x+1][y]==temp && gezilenler[x+1][y]==0){//asagi
                    gezilenler[x+1][y]=1;
                    uzunluk++;
                    x++;
                    flag=1;
                }else if(x>0 && matris[x-1][y]==temp && gezilenler[x-1][y]==0){//yukari
                    gezilenler[x-1][y]=1;
                    uzunluk++;
                    x--;
                    flag=1;
                }else if(x>0 && y>0 && matris[x-1][y-1]==temp && gezilenler[x-1][y-1]==0){//sol yukarı 
                    gezilenler[x-1][y-1]=1;
                    uzunluk++;
                    x--;
                    y--;
                    flag=1;
                }else if(x>0 && y+1<sutun && matris[x-1][y+1]==temp && gezilenler[x-1][y+1]==0){//sag yukari
                    gezilenler[x-1][y+1]=1;
                    uzunluk++;
                    x--;
                    y++;
                    flag=1;
                }else if(x+1<satir && y-1>0 && matris[x+1][y-1]==temp && gezilenler[x+1][y-1]==0){//sol asagi
                    gezilenler[x+1][y-1]=1;
                    uzunluk++;
                    x++;
                    y--;
                    flag=1;
                }else if(x+1<satir && y+1>0 && matris[x+1][y+1]==temp && gezilenler[x+1][y+1]==0){//sag asagi
                    gezilenler[x+1][y+1]=1;
                    uzunluk++;
                    x++;
                    y++;
                    flag=1;
                }
                if(flag==0){
                    y=sutun+1;
                }
            }
            if(flag == 1 && y == sutun - 1) {
                printf("----------------------------------------------------\n");
                printf("Yol %d -> Uzunluk %d\n", yolNo, uzunluk);
                yolNo++;
            }
        }
    }
    return 0;
}
