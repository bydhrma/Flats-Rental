#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_KOS 5

struct Penyewa {
    char nama[50];
    int umur;
    char no_identitas[20];
};

enum TipeKos {
    STANDARD,
    DELUXE,
    GRAND_DELUXE
};

struct Kos {
    int nomorKamar;
    float harga;
    int tersedia;
    enum TipeKos tipe;
    struct Penyewa penyewa;
};

struct Kos kos;
struct Penyewa penyewa;

int isNameEntered = 0;
float electricityPrice, waterPrice, total_price, total_electric, total_water, penalty, discount;
int roomType, jumlahBulan;
char type, electricity, water;
char payment_date[80];
char filename[80];
char repeat;

// Function prototypes
void title();
void tampilkanInfoKos(struct Kos kos[], int jumlah, enum TipeKos tipe);
int infoKos();
int calculatePrice();
void electricAndWaterCondition();
void selectType();
void getTime();
void struk();
void printToStrukFile(struct Penyewa penyewa);
//jea,bayu,karin


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

void tampilkanInfoKos(struct Kos kos[], int jumlah, enum TipeKos tipe) {
    printf("Kos yang Tersedia (Tipe ");
    switch (tipe) {
        case STANDARD:
            printf("Standard");
            break;
        case DELUXE:
            printf("Deluxe");
            break;
        case GRAND_DELUXE:
            printf("Grand Deluxe");
            break;
    }
    printf("):\nNomor Kamar\tHarga\tStatus\n");

    for (int i = 0; i < jumlah; ++i) {
        if (kos[i].tipe == tipe) {
            printf("%d\t\t%.2f\t%s\n", kos[i].nomorKamar, kos[i].harga, (kos[i].tersedia ? "Tersedia" : "Terisi"));
        }
    }
}

int infoKos() {
    FILE *fileKos = fopen("daftar_kos.txt", "r+");
    if (fileKos == NULL) {
        printf("File tidak dapat dibuka.\n");
        return 1;
    }

    struct Kos daftarKos[MAX_KOS];
    int nomorKamar, harga, tersedia, tipe;
    for (int i = 0; i < MAX_KOS; ++i) {
        int result = fscanf(fileKos, "%d %d %d %d", &nomorKamar, &harga, &tersedia, &tipe);
        if (result != 4) {
            fprintf(stderr, "Error reading room data from the file. Expected 4 values, but got %d.\n", result);
            return 1;  // Exit with an error code
        }

        daftarKos[i].nomorKamar = nomorKamar;
        daftarKos[i].harga = harga;
        daftarKos[i].tersedia = tersedia;
        daftarKos[i].tipe = tipe;

        // Check if tenant data is present before reading
        if (tersedia == 1) {
            result = fscanf(fileKos, "%s %d %s", daftarKos[i].penyewa.nama, &daftarKos[i].penyewa.umur, daftarKos[i].penyewa.no_identitas);
            if (result != 3) {
                fprintf(stderr, "Error reading tenant data from the file. Expected 3 values, but got %d.\n", result);
                return 1;  // Exit with an error code
            }
        } else {
            // If the room is not occupied, consume the newline character
            fscanf(fileKos, "\n");
        }
    }

    fseek(fileKos, 0, SEEK_SET);

    enum TipeKos tipePilihan;
    printf("Pilih tipe kos (0: Standard, 1: Deluxe, 2: Grand Deluxe): ");
    scanf("%d", &tipePilihan);

    if (tipePilihan >= STANDARD && tipePilihan <= GRAND_DELUXE) {
        tampilkanInfoKos(daftarKos, MAX_KOS, tipePilihan);

        int nomorKamarPilihan;
        printf("Pilih nomor kamar: ");
        scanf("%d", &nomorKamarPilihan);

        if (nomorKamarPilihan >= 1 && nomorKamarPilihan <= MAX_KOS) {
            if (daftarKos[nomorKamarPilihan - 1].tersedia && daftarKos[nomorKamarPilihan - 1].tipe == tipePilihan) {
                printf("Masukkan informasi penyewa:\n");
                printf("Nama: ");
                scanf("%s", daftarKos[nomorKamarPilihan - 1].penyewa.nama);
                printf("Umur: ");
                scanf("%d", &daftarKos[nomorKamarPilihan - 1].penyewa.umur);
                printf("Nomor Identitas: ");
                scanf("%s", daftarKos[nomorKamarPilihan - 1].penyewa.no_identitas);

                int jumlahBulan;
                printf("Masukkan jumlah bulan sewa: ");
                scanf("%d", &jumlahBulan);

                // Mengubah status kamar menjadi tidak tersedia
                daftarKos[nomorKamarPilihan - 1].tersedia = 0;

                // Menulis kembali data ke file
                fseek(fileKos, 0, SEEK_SET);
                for (int i = 0; i < MAX_KOS; ++i) {
                    fprintf(fileKos, "%d %d %d %d\n", daftarKos[i].nomorKamar, daftarKos[i].harga, daftarKos[i].tersedia, daftarKos[i].tipe);
                    if (daftarKos[i].tersedia == 1) {
                        fprintf(fileKos, "%s %d %s\n", daftarKos[i].penyewa.nama, daftarKos[i].penyewa.umur, daftarKos[i].penyewa.no_identitas);
                    } else {
                        fprintf(fileKos, "\n");
                    }
                }

                printf("Penyewaan kamar berhasil.\n");
            } else {
                printf("Kamar tidak tersedia atau tidak sesuai dengan tipe yang dipilih.\n");
            }
        } else {
            printf("Nomor kamar tidak valid.\n");
        }
    } else {
        printf("Pilihan tipe kos tidak valid.\n");
    }

    fclose(fileKos);

    return 0;
}

//bayu
int calculatePrice() {

    if (jumlahBulan > 12) {
        discount = 0.01 * jumlahBulan * kos.harga;
        total_price = (jumlahBulan * kos.harga) - discount;

        discount = 0.01 * jumlahBulan * electricityPrice;
        total_electric = (jumlahBulan * electricityPrice) - discount;

        discount = 0.01 * jumlahBulan * waterPrice;
        total_water = (jumlahBulan * waterPrice) - discount;
    }

    total_price = jumlahBulan * kos.harga;
    total_electric = jumlahBulan * electricityPrice;
    total_water = jumlahBulan * waterPrice;

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
     printf("   Nama Penyewa           : %s \n", penyewa.nama);
     printf("   NIK Penyewa            : %s \n", penyewa.no_identitas);
     printf("   Umur Penyewa           : %d \n", penyewa.umur);
     printf("   Tipe                   : %c \n", type);
     printf("   Tanggal                : %s \n", payment_date);
     printf("   Jumlah Bulan           : %d \n", jumlahBulan);
     printf("   Harga Kamar Perbulan   : Rp.%2.f  \n", total_price);
     printf("   Biaya Kuota Listrik    : Rp.%2.f  \n", total_electric);
     printf("   Biaya Kuota Air        : Rp.%2.f  \n", total_water);
     printf("==================================================================\n");
     printf("   Total Biaya            : Rp.%2.f   \n", total_price + total_electric + total_water);
     printf("==================================================================\n");
}

//bayu
void printToStrukFile(struct Penyewa penyewa) {
    time_t current_time = time(NULL);
    getTime();

    strftime(filename, sizeof(filename), "struk_pembayaran_%Y%m%d_%H%M%S.txt", localtime(&current_time));

    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        fprintf(file, "==================================================================\n");
        fprintf(file, "                     TOTAL PEMBAYARAN KOS                         \n");
        fprintf(file, "==================================================================\n");
        fprintf(file, "   Nama Penyewa           : %s \n", penyewa.nama);
        fprintf(file, "   NIK Penyewa            : %s \n", penyewa.no_identitas);
        fprintf(file, "   No Hp Penyewa          : %d \n", penyewa.umur);
        fprintf(file, "   Tipe                   : %c \n", type);
        fprintf(file, "   Tanggal                : %s \n", payment_date);
        fprintf(file, "   Jumlah Bulan           : %d \n", jumlahBulan);
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

int main (){
    do{
        system("cls");

    title();
    selectType();
    infoKos();
    calculatePrice();
    struk();
    printToStrukFile(penyewa);


        printf("Apakah anda ingin mengulang?\n");
        printf("YA (Y) \n");
        printf("TIDAK (N)\n");
        scanf(" %c", &repeat);
        } while (repeat == 'y' || repeat == 'Y');
    return 0;
}