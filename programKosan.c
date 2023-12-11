#include <stdio.h>
#include <time.h>

float rental_price;
float total_price;
float penalty;
float discount;
float totalWFine;
float withElectricity;
int month;
int day;
int roomType;
char type;
char electricity;

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

electricityCondition() {
    printf("|  1. Include Listrik                   |\n");
    printf("|  2. Tidak Include Listrik             |\n");
    printf("-----------------------------------------\n");
    printf("   Masukkan Pilihan:   ");
    scanf(" %c", &electricity);  // Use & to get the address of the variable

    switch (electricity) {
        case '1':
            withElectricity = rental_price + 200000;
            break;

        case '2':
            withElectricity = rental_price;
            break;
    }
    calculatePrice();
}

//bayu
 calculatePrice() {

    printf("  Masukkan Jumlah Bulan Yang Akan Dibayar : ");
    scanf("%d", &month);

    if (month <= 12){
    total_price = month * withElectricity;
    } else {
    discount = 0.01 * month * withElectricity;
    total_price = (month * withElectricity) - discount;
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
    printf("|  2. Deluxe                            |\n");
    printf("|  3. Grand Deluxe                      |\n");
    printf("-----------------------------------------\n");
    printf("   Pilihan Tipe Kamar:   ");
    type = getchar();
    fflush(stdin);

//bayu
    switch (type)
    {
     case '1':
     rental_price += 800000;
     electricityCondition();
     break;

     case '2':
     rental_price += 1000000;
     electricityCondition();
     break;

     case '3':
     rental_price += 1200000;
     electricityCondition();
     break;

    }

     printf("\n");
     printf("==================================================================\n");
     printf("                     TOTAL PEMBAYARAN KOS                         \n");
     printf("==================================================================\n");
     printf("   Tipe                   : %c \n", type);
     printf("   Tanggal                : %d \n", day);
     printf("   Jumlah Bulan           : %d \n", month);
     printf("   Harga Kamar Perbulan   : Rp.%2.lf  \n", total_price);
     printf("==================================================================\n");
     printf("   Total Biaya            : Rp.%2.lf   \n", totalWFine = total_price);
     printf("==================================================================\n");

}