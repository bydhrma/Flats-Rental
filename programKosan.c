#include <stdio.h>
#include <time.h>

float rental_price;
float total_price;
float penalty;
int month;
char type;

void title() {
    printf("=========================================\n");
    printf("|                                        |\n");
    printf("|  SSSS  EEEE  RRRR   NN  N  III  AAA    |\n");
    printf("| S      E     R   R  N N N   I  A   A   |\n");
    printf("|  SSS   EEE   RRRR   N  NN   I  AAAAA   |\n");
    printf("|     S  E     R  R   N   N   I  A   A   |\n");
    printf("| SSSS   EEEE  R   R  N   N  III A   A   |\n");
    printf("|                                        |\n");
    printf("|              Sernia Kost               |\n");
    printf("|  JL. Jimbaran Kiri, Kanan Dikit,Bali   |\n");
    printf("=========================================\n");
    printf("            Enter To Continue             ");
    getchar();
    };

 calculatePrice() {
    printf("Masukkan Jumlah Bulan Yang Akan Dibayar : ");
    scanf("%d", &month);

    total_price = month * rental_price;
    printf("Harga Yang Dibayarkan Untuk %d Bulan Adalah %.2f", month, total_price);
 }    

int main (){
    title();

    printf("=========================================\n");
    printf("|              SERNIA KOST              |\n");
    printf("=========================================\n");
    printf("|  TIPE KAMAR                           |\n");
    printf("|  1. Standard                          |\n");
    printf("|  2. Deluxe                            |\n");
    printf("|  3. Grand Deluxe                      |\n");
    printf("-----------------------------------------\n");
    printf("  Pilihan Tipe Kamar:   ");
    type = getchar();
    fflush(stdin);
    
    switch (type)
    {
     case '1':
     rental_price += 800000;
     calculatePrice();
     break;

     case '2':
     rental_price += 1000000;
     calculatePrice();
     break;

     case '3':
     rental_price += 1200000;
     calculatePrice();
     break;

    }


}