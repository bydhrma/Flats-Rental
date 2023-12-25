#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct {
    int roomNumber;
    char roomType[10];
    int avaiable;
    
} RommInfo;
float storePrice[3] = {800000, 1000000, 1200000 };
float storeElectric[2] = {0, 200000};
float storeWater[2] = {0, 150000};
float rental_price, electricityPrice, waterPrice, total_price, total_electric, total_water, penalty, discount;
int month;
char type, electricity, water;
char payment_date[80];
char filename[80];

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

//bayu
 void electricAndWaterCondition() {
    printf("==============================================\n");
    printf("|  1. Termasuk Listrik                       |\n");
    printf("|  2. Tidak Termasuk Listrik                 |\n");
    printf("==============================================\n");
    printf("   Masukkan Pilihan:   ");
    scanf(" %c", &electricity);

    switch (electricity) {
        case '1':
            electricityPrice = storeElectric[1];
            break;

        case '2':
            electricityPrice = storeElectric[0];
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
        waterPrice = storeWater[1];
        break;
    
    case '2':
        waterPrice = storeWater[0];
        break;
    default:
        printf("Input Tidak Valid. Jalankan Program Ulang");
    }

    calculatePrice();
}


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
     rental_price = storePrice[0];
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
     rental_price = storePrice[1];
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
     rental_price = storePrice[2];
     electricAndWaterCondition();
     break;
    }
}





void payment() {
 
}

int main() {
    title();
    selectType();

    return 0;
}