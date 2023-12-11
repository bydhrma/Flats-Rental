#include <stdio.h>
#include <time.h>

float rental_price;
float total_price;
float penalty;
float discount;
float totalWFine;
int month;
int day;
char type;

//karin
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

//bayu
 calculatePrice() {
    printf("  Masukkan Jumlah Bulan Yang Akan Dibayar : ");
    scanf("%d", &month);

    if (month < 12){
    total_price = month * rental_price;
    } else {
    discount = 0.01 * month * rental_price;
    total_price = (month * rental_price) - discount;
    }
 }    
 
 //jea
finePrice(){
    printf("  Masukkan Tanggal Bayar : "); 
    scanf("%d", &day);

    if (day >= 15){
        penalty = 0.15 * total_price;
        printf(" Denda: %lf", penalty);
    } else {
        penalty = 0;
        printf(" Tidak Terdapat Denda");
    }
}

int main (){
    title();
//jea
    printf("=========================================\n");
    printf("|              SERNIA KOST              |\n");
    printf("=========================================\n");
    printf("|  TIPE KAMAR                           |\n");
    printf("|  1. Standard                          |\n");
    printf("|  2. Deluxe                            |\n"); //include aer
    printf("|  3. Grand Deluxe                      |\n"); //include aer sama listrik
    printf("-----------------------------------------\n");
    printf("  Pilihan Tipe Kamar:   ");
    type = getchar();
    fflush(stdin);

//bayu
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

    finePrice();

    system("cls");
     printf("\n");
     printf("==================================================================\n");
     printf("                     TOTAL PEMBAYARAN KOS                         \n");
     printf("==================================================================\n");
     printf("   Tipe                   : %c \n", type);
     printf("   Tanggal                : %d \n", day);
     printf("   Harga Kamar Perbulan   : Rp.%2.lf  \n", total_price);
     printf("   Denda                  : Rp.%2.lf  \n", penalty);
     printf("==================================================================\n");
     printf("   Total Biaya            : Rp.%2.lf   \n", totalWFine = total_price - penalty);
     printf("==================================================================\n");

}