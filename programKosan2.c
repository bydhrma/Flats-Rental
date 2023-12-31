#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_KAMAR 50

typedef struct {
    int nomerKamar;
    int terisi;
    char namaPenyewa[50];
} Kamar;

struct tenantInfo{
    char name[80];
    char idNumber[20];
    char phoneNumber[20];
};

struct tenantInfo infoPenyewa;

int isNameEntered = 0;
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
void bacaDataKamar();
void tulisDataKamar();
void tampilkanStatusKamar();
void isiKamar();
void tambahKamar();
void roomInfo();

//jea,bayu,karin
int main (){
    do{
        
    system("cls"); 
    title();
    selectType();
    roomInfo();
    tenant();
    struk();
    printToStrukFile();
    printf("Apakah anda ingin mengulang?\n");
    printf("YA (Y) \n");
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

void bacaDataKamar(Kamar dataKamar[], int *jumlahKamar) {
    FILE *file = fopen("data_kamar.txt", "r");
    if (file == NULL) {
        printf("File tidak ditemukan, membuat file baru...\n");
        file = fopen("data_kamar.txt", "w");
        fclose(file);
        return;
    }

    while (fscanf(file, "%d %d %[^\n]", &dataKamar[*jumlahKamar].nomerKamar, &dataKamar[*jumlahKamar].terisi, dataKamar[*jumlahKamar].namaPenyewa) != EOF) {
        (*jumlahKamar)++;
    }
    fclose(file);
}

void tulisDataKamar(Kamar dataKamar[], int jumlahKamar) {
    FILE *file = fopen("data_kamar.txt", "w");
    if (file == NULL) {
        printf("File tidak dapat dibuka.\n");
        return;
    }

    for (int i = 0; i < jumlahKamar; i++) {
        if (dataKamar[i].terisi == 1) {
            fprintf(file, "%d %d %s\n", dataKamar[i].nomerKamar, dataKamar[i].terisi, dataKamar[i].namaPenyewa);
        } else {
            fprintf(file, "%d %d\n", dataKamar[i].nomerKamar, dataKamar[i].terisi);
        }
    }

    fclose(file);
}

void tampilkanStatusKamar(Kamar dataKamar[], int jumlahKamar) {
    printf("Nomer Kamar\tStatus\n");
    for (int i = 0; i < jumlahKamar; i++) {
        printf("%d\t\t%s\n", dataKamar[i].nomerKamar, (dataKamar[i].terisi == 1) ? "Terisi" : "Tersedia");
    }
}

void isiKamar(Kamar dataKamar[], int jumlahKamar, int nomorKamar) {
    if (!isNameEntered) {
        // If the name hasn't been entered, allow the user to input it
        printf("Masukkan nama penyewa untuk kamar nomor %d: ", nomorKamar);
        scanf(" %[^\n]", infoPenyewa.name);
        isNameEntered = 1; // Set the flag to indicate that the name has been entered
    }

    char namaPenyewa[50];
    for (int i = 0; i < jumlahKamar; i++) {
        if (dataKamar[i].nomerKamar == nomorKamar) {
            if (dataKamar[i].terisi == 0) {
                dataKamar[i].terisi = 1;
                strcpy(dataKamar[i].namaPenyewa, infoPenyewa.name);
                printf("Kamar nomor %d berhasil diisi oleh %s.\n", nomorKamar, infoPenyewa.name);
                tulisDataKamar(dataKamar, jumlahKamar);
                return;
            } else {
                printf("Kamar nomor %d sudah terisi.\n", nomorKamar);
                return;
            }
        }
    }
    printf("Kamar nomor %d tidak ditemukan.\n", nomorKamar);
}

void tambahKamar(Kamar dataKamar[], int *jumlahKamar) {
    if (*jumlahKamar >= MAX_KAMAR) {
        printf("Jumlah kamar maksimal telah tercapai.\n");
        return;
    }

    int nomorKamar;
    printf("Masukkan nomor kamar yang ingin ditambahkan: ");
    scanf("%d", &nomorKamar);

    for (int i = 0; i < *jumlahKamar; i++) {
        if (dataKamar[i].nomerKamar == nomorKamar) {
            printf("Kamar nomor %d sudah ada dalam sistem.\n", nomorKamar);
            return;
        }
    }

    dataKamar[*jumlahKamar].nomerKamar = nomorKamar;
    dataKamar[*jumlahKamar].terisi = 0;
    (*jumlahKamar)++;
    printf("Kamar nomor %d berhasil ditambahkan.\n", nomorKamar);
    tulisDataKamar(dataKamar, *jumlahKamar);
}

void roomInfo() {
    Kamar dataKamar[MAX_KAMAR];
    int jumlahKamar = 0;
    char goBack;

    bacaDataKamar(dataKamar, &jumlahKamar);

    int pilihanMenu;
    int nomorKamar;

    do {
        printf("\nPilih Menu:\n");
        printf("1. Tampilkan Status Kamar\n");
        printf("2. Isi Kamar\n");
        printf("3. Tambah Kamar\n");
        printf("0. Keluar\n");
        printf("Masukkan pilihan: ");
        scanf("%d", &pilihanMenu);

        switch (pilihanMenu) {
            case 1:
                tampilkanStatusKamar(dataKamar, jumlahKamar);
                break;
            case 2:
                printf("Masukkan nomor kamar yang ingin diisi: ");
                scanf("%d", &nomorKamar);
                isiKamar(dataKamar, jumlahKamar, nomorKamar);
                break;
            case 3:
                tambahKamar(dataKamar, &jumlahKamar);
                break;
            case 0:
                printf("Keluar dari program.\n");
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    if (pilihanMenu == 0) {
            break;
        }
    
        printf("Kembali ke Menu?\n");
        printf("YA (Y) \n");
        printf("TIDAK (N)\n");
        scanf(" %c", &goBack);
    } while (goBack == 'y' || goBack == 'Y');
    system ("cls");
}
    
//jea
void tenant() {
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
    system("cls");
     getTime(); 
     printf("\n");
     printf("==================================================================\n");
     printf("                     TOTAL PEMBAYARAN KOS                         \n");
     printf("==================================================================\n");
     printf("   Nama Penyewa           : %s \n", infoPenyewa.name);
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