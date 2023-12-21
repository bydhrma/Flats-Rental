#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct tenantInfo{
    char name[80];
    char idNumber[20];
    char phoneNumber[20];
};

struct tenantInfo infoPenyewa;

float rental_price, electricityPrice, waterPrice, total_price, total_electric, total_water, penalty, discount;
int month, roomType;
char type, electricity, water;
char payment_date[80];
char filename[80];
char repeat;

void title();
void tenant();
int calculatePrice();
void selectType();
void getTime();
void struk();
void printToStrukFile();

//jea,bayu,karin
int main (){
    do{
        system("cls");
        
    title();
    tenant();
    selectType();
    struk();
    printToStrukFile();


        printf("Apakah anda ingin mengulang?\n");
        printf("YA (Y) ");
        printf("TIDAK (N)\n");
        scanf(" %c", &repeat);
        } while (repeat == 'y' || repeat == 'Y');
    return 0;
}

//karin
void title() {
    printf("==============================================\n");
    printf("|                                            |\n");
    printf("|    SSSS  EEEE  RRRR   NN  N  III  AAA      |\n");
    printf("|   S      E     R   R  N N N   I  A   A     |\n");
    printf("|    SSS   EEE   RRRR   N  NN   I  AAAAA     |\n");
    printf("|       S  E     R  R   N   N   I  A   A     |\n");
    printf("|   SSSS   EEEE  R   R  N   N  III A   A     |\n");
    printf("|                                            |\n");
    printf("|                Sernia Kost                 |\n");
    printf("|    JL. Jimbaran Kiri, Kanan Dikit,Bali     |\n");
    printf("==============================================\n");
    system("pause");
    };
    
//jea
void tenant(){
    system("cls");
    printf("Nama Penyewa: ");
    fgets(infoPenyewa.name, 80, stdin);
    printf("NIK Penyewa: ");
    scanf("%s", infoPenyewa.idNumber);
    printf("No.Hp Penyewa: ");
    scanf("%s", infoPenyewa.phoneNumber);
 }

//bayu
int calculatePrice() {

    printf("   Masukkan Jumlah Bulan Yang Akan Dibayar : ");
    scanf("%d", &month);

    if (month > 12) {
        discount = 0.01 * month * rental_price;
        total_price = (month * rental_price) - discount;

        discount = 0.01 * month * electricityPrice;
        total_electric = (month * electricityPrice) - discount;

        discount = 0.01 * month * waterPrice;
        total_water = (month * waterPrice) - discount;
    }

    total_price = month * rental_price;
    total_electric = month * electricityPrice;
    total_water = month * waterPrice;

    return total_price, total_electric;
 }   

//jea
void electricAndWaterCondition() {
    printf("==============================================\n");
    printf("|  1. Termasuk Listrik                       |\n");
    printf("|  2. Tidak Termasuk Listrik                 |\n");
    printf("==============================================\n");
    printf("   Masukkan Pilihan:   ");
    scanf(" %c", &electricity);

    switch (electricity) {
        case '1':
            electricityPrice = 200000;
            break;

        case '2':
            electricityPrice = 0;
            break;

        default: 
        printf("Input Tidak Valid. Jalankan Program Ulang");
    }

    printf("==============================================\n");
    printf("|  1. Termasuk Air PDAM                      |\n");
    printf("|  2. Tidak Termasuk Air PDAM                |\n");
    printf("==============================================\n");
    printf("   Masukkan Pilihan:   ");
    scanf(" %c", &water);

    switch (water){
    case '1' :
        waterPrice = 100000;
        break;
    
    case '2':
        waterPrice = 0;
        break;
    default:
        printf("Input Tidak Valid. Jalankan Program Ulang");
    }


    calculatePrice();
}

//karin
void selectType() {
    printf("==============================================\n");
    printf("|                SERNIA KOST                 |\n");
    printf("==============================================\n");
    printf("|                                            |\n");
    printf("|  TIPE KAMAR                                |\n");
    printf("|  1. Standard                               |\n");
    printf("|  2. Deluxe                                 |\n");
    printf("|  3. Grand Deluxe                           |\n");
    printf("|                                            |\n");
    printf("----------------------------------------------\n");
    printf("   Pilihan Tipe Kamar:   ");
    scanf(" %c", &type);

    switch (type)
    {
     case '1':
    printf("==============================================\n");
    printf("|                  Fasilitas                 |\n");
    printf("==============================================\n");
    printf("|                                            |\n");
    printf("|    - Kamar Mandi Dalam                     |\n");
    printf("|    - Dapur                                 |\n");
    printf("----------------------------------------------\n");
     rental_price = 800000;
     electricAndWaterCondition();
     break;

     case '2':
    printf("==============================================\n");
    printf("|                  Fasilitas                 |\n");
    printf("==============================================\n");
    printf("|                                            |\n");
    printf("|    - Kamar Mandi Dalam                     |\n");
    printf("|    - Dapur                                 |\n");
    printf("|    - Kasur                                 |\n");
    printf("|    - Meja Belajar                          |\n");
    printf("|    - Lemari                                |\n");
    printf("----------------------------------------------\n");
     rental_price = 1000000;
     electricAndWaterCondition();
     break;

     case '3':
    printf("==============================================\n");
    printf("|                  Fasilitas                 |\n");
    printf("==============================================\n");
    printf("|                                            |\n");
    printf("|    - Kamar Mandi Dalam                     |\n");
    printf("|    - Dapur                                 |\n");
    printf("|    - Kasur                                 |\n");
    printf("|    - Meja Belajar                          |\n");
    printf("|    - Lemari                                |\n");
    printf("|    - Televisi                              |\n");
    printf("|    - AC                                    |\n");
    printf("----------------------------------------------\n");
     rental_price = 1200000;
     electricAndWaterCondition();
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
     printf("   Nama Penyewa           : %s", infoPenyewa.name);
     printf("   NIK Penyewa            : %s \n", infoPenyewa.idNumber);
     printf("   No Hp Penyewa          : %s \n", infoPenyewa.phoneNumber);
     printf("   Tipe                   : %c \n", type);
     printf("   Tanggal                : %s \n", payment_date);
     printf("   Jumlah Bulan           : %d \n", month);
     printf("   Harga Kamar Perbulan   : Rp.%2.f  \n", total_price);
     printf("   Biaya Kuota Listrik    : Rp.%2.f  \n", total_electric);
     printf("   Biaya Kuota Air        : Rp.%2.f  \n", total_water);
     printf("==================================================================\n");
     printf("   Total Biaya            : Rp.%2.f   \n", total_price + total_electric + total_water);
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
        fprintf(file, "   Nama Penyewa           : %s \n", infoPenyewa.name);
        fprintf(file, "   NIK Penyewa            : %d \n", infoPenyewa.idNumber);
        fprintf(file, "   No Hp Penyewa          : %d \n", infoPenyewa.phoneNumber);
        fprintf(file, "   Tipe                   : %c \n", type);
        fprintf(file, "   Tanggal                : %s \n", payment_date);
        fprintf(file, "   Jumlah Bulan           : %d \n", month);
        fprintf(file, "   Harga Kamar Perbulan   : Rp.%2.f  \n", total_price);
        fprintf(file, "   Biaya Kuota Listrik    : Rp.%2.f  \n", total_electric);
        fprintf(file, "   Biaya Kuota Air        : Rp.%2.f  \n", total_water);
        fprintf(file, "==================================================================\n");
        fprintf(file, "   Total Biaya            : Rp.%2.f   \n", total_price + total_electric + total_water);
        fprintf(file, "==================================================================\n");

        fclose(file);
        printf("Struk pembayaran telah disimpan dalam file: %s\n", filename);
    } else {
        printf("Gagal menyimpan struk pembayaran.\n");
    }
}