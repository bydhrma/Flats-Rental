#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

float rental_price, electricityPrice, total_price, total_electric, penalty, discount;
int month, roomType;
char type, electricity;
char payment_date[80];
char filename[80];

void title();
int calculatePrice();
void selectType();
void getTime();
void struk();
void printToStrukFile();

//jea,bayu,karin
int main (){
    title();
    selectType();
    struk();
    printToStrukFile();
    return 0;

}

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
    system("pause");
    };

//bayu
int calculatePrice() {

    printf("   Masukkan Jumlah Bulan Yang Akan Dibayar : ");
    scanf("%d", &month);

    if (month > 12) {
        discount = 0.01 * month * rental_price;
        total_price = (month * rental_price) - discount;

        discount = 0.01 * month * electricityPrice;
        total_electric = (month * electricityPrice) - discount;
    }

    total_price = month * rental_price;
    total_electric = month * electricityPrice;

    return total_price, total_electric;
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

//karin
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

    strftime(payment_date, sizeof(payment_date), "%Y-%m-%d %H:%M:%S", info);
}

//bayu
void struk() {
     getTime(); 
     printf("\n");
     printf("==================================================================\n");
     printf("                     TOTAL PEMBAYARAN KOS                         \n");
     printf("==================================================================\n");
     printf("   Tipe                   : %c \n", type);
     printf("   Tanggal                : %s \n", payment_date);
     printf("   Jumlah Bulan           : %d \n", month);
     printf("   Harga Kamar Perbulan   : Rp.%2.f  \n", total_price);
     printf("   Biaya Kouta Listrik    : Rp.%2.f  \n", total_electric);
     printf("==================================================================\n");
     printf("   Total Biaya            : Rp.%2.f   \n", total_price + total_electric);
     printf("==================================================================\n");
}

//bayu
void printToStrukFile() {
    time_t current_time = time(NULL);

    getTime();

    strftime(filename, sizeof(filename), "struk_pembayaran_%Y%m%d_%H%M%S.txt", localtime(&current_time));

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "==================================================================\n");
        fprintf(file, "                     TOTAL PEMBAYARAN KOS                         \n");
        fprintf(file, "==================================================================\n");
        fprintf(file, "   Tipe                   : %c \n", type);
        fprintf(file, "   Tanggal                : %s \n", payment_date);
        fprintf(file, "   Jumlah Bulan           : %d \n", month);
        fprintf(file, "   Harga Kamar Perbulan   : Rp.%.2f  \n", total_price);
        fprintf(file, "   Biaya Kouta Listrik    : Rp.%.2f  \n", total_electric);
        fprintf(file, "==================================================================\n");
        fprintf(file, "   Total Biaya            : Rp.%.2f   \n", total_price + total_electric);
        fprintf(file, "==================================================================\n");

        fclose(file);
        printf("Struk pembayaran telah disimpan dalam file: %s\n", filename);
    } else {
        printf("Gagal menyimpan struk pembayaran.\n");
    }
}


