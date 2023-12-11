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
    printf("  Masukkan Jumlah Bulan Yang Akan Dibayar : ");
    scanf("%d", &month);

    if (month < 12){
    total_price = month * rental_price;
    } else {
    discount = 0.01 * month * rental_price;
    total_price = (month * rental_price) - discount;
    }
 }    
 
finePrice(){
    printf("  \nMasukkan Tanggal Bayar : "); 
    scanf("%d", &day);

    if (day >= 15){
        penalty = 0.15 * total_price;
        printf(" Denda: %lf", penalty);
    } else {
        printf(" Tidak Terdapat Denda");
    }
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

    finePrice();

    totalWFine = total_price - penalty;

    printf("\nHarga %lf", totalWFine);

    // printf("\n");
    // printf("==================================================================\n");
    // printf("                     TOTAL PEMBAYARAN KOS                         \n");
    // printf("==================================================================\n");
    // printf("   Tipe                   : %c \n", pelanggan);
    // printf("   GOLONGAN               : %c \n", RT);
    // printf("   TEGANGAN               : %c \n", tegangan);
    // printf("   TANGGAL                : %s \n", tanggal_bayar);
    // printf("   Biaya Pemeliharaan     : Rp.%d  \n", bpm);
    // printf("   Biaya Pemakaian        : Rp.%d  \n", biaya);
    // printf("   Biaya Administrasi     : Rp.%d  \n", admin);
    // printf("   Biaya Denda            : Rp.%d  \n", denda);
    // printf("==================================================================\n");
    // printf("   Total Biaya            : Rp.%d   \n", bpm + biaya + admin + denda);
    // printf("==================================================================\n");

}