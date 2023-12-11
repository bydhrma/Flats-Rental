#include <stdio.h>
#include <time.h>

float rental_price;
float total_price;
float penalty;
float discount;
float totalWFine;
float electricityPrice;
int month;
int day;
int roomType;
char type;
char electricity;
char tanggal_bayar[80];

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
int calculatePrice() {

    printf("   Masukkan Jumlah Bulan Yang Akan Dibayar : ");
    scanf("%d", &month);

    if (month > 12) {
        discount = 0.01 * month * rental_price;
        total_price = (month * rental_price) - discount;
    }

    total_price = month * rental_price;

    return total_price;
 }   

//jea
void electricityCondition() {
    printf("|  1. Include Listrik                   |\n");
    printf("|  2. Tidak Include Listrik             |\n");
    printf("-----------------------------------------\n");
    printf("   Masukkan Pilihan:   ");
    scanf(" %c", &electricity);

    switch (electricity) {
        case '1':
            electricityPrice = 200000;
            break;

        case '2':
            electricityPrice = 0;
            break;
    }
    calculatePrice();
}

//bayu
void selectType() {
    printf("=========================================\n");
    printf("|              SERNIA KOST              |\n");
    printf("=========================================\n");
    printf("|  TIPE KAMAR                           |\n");
    printf("|  1. Standard                          |\n");
    printf("|  2. Deluxe                            |\n");
    printf("|  3. Grand Deluxe                      |\n");
    printf("-----------------------------------------\n");
    printf("   Pilihan Tipe Kamar:   ");
    type = getchar();
    fflush(stdin);

    switch (type)
    {
     case '1':
     rental_price = 800000;
     electricityCondition();
     break;

     case '2':
     rental_price = 1000000;
     electricityCondition();
     break;

     case '3':
     rental_price = 1200000;
     electricityCondition();
     break;
    }
}

//bayu
void getTime() {
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);

    strftime(tanggal_bayar, sizeof(tanggal_bayar), "%Y-%m-%d %H:%M:%S", info);
}

//karin
void struk() {
    printf("\n");
     printf("==================================================================\n");
     printf("                     TOTAL PEMBAYARAN KOS                         \n");
     printf("==================================================================\n");
     printf("   Tipe                   : %c \n", type);
     printf("   Tanggal                : %s \n", tanggal_bayar);
     printf("   Jumlah Bulan           : %d \n", month);
     printf("   Harga Kamar Perbulan   : Rp.%2.f  \n", total_price);
     printf("   Biaya Listrik Tambahan : Rp.%2.f  \n", electricityPrice);
     printf("==================================================================\n");
     printf("   Total Biaya            : Rp.%2.f   \n", total_price + electricityPrice);
     printf("==================================================================\n");
}

//jea,bayu,karin
int main (){
    title();
    selectType();
    getTime();
    struk();
    return 0;

}