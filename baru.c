#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_KAMAR 50
#define MAX_PENYEWA 50

// Struktur untuk data kamar kos
struct Kamar {
    int nomor;
    char tipe[20];
    float harga;
    int isTerisi;
};

// Struktur untuk data penyewa
struct Penyewa {
    char nama[50];
    char NIK[20];
    char noTelepon[15];
    int kamarSewa;
    int lamaSewa;
    float totalPembayaran;
    int gunaAir;
    int gunaListrik;
};

char payment_date[80];

// Fungsi untuk menyimpan data kamar kos ke file
void simpanKamarKeFile(struct Kamar kamar[], int jumlahKamar) {
    FILE *file = fopen("daftar_kos.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "Nomor Kamar\tTipe\tHarga\tStatus\n");
    for (int i = 0; i < jumlahKamar; ++i) {
        fprintf(file, "%d\t%s\t%.2f\t%s\n", kamar[i].nomor, kamar[i].tipe, kamar[i].harga, kamar[i].isTerisi ? "Terisi" : "Kosong");
    }

    fclose(file);
}

// Fungsi untuk menambahkan kamar baru
void tambahKamar(struct Kamar kamar[], int *jumlahKamar) {
    int nomor;
    char tipe[20];
    float harga;
    
    printf("Masukkan nomor kamar: ");
    scanf("%d", &nomor);
    printf("Masukkan tipe kamar (Standard/Deluxe/Grand Deluxe): ");
    scanf("%s", tipe);
    printf("Masukkan harga kamar: ");
    scanf("%f", &harga);

    kamar[*jumlahKamar].nomor = nomor;
    strcpy(kamar[*jumlahKamar].tipe, tipe);
    kamar[*jumlahKamar].harga = harga;
    kamar[*jumlahKamar].isTerisi = 0; // Kamar kosong
    (*jumlahKamar)++;
    simpanKamarKeFile(kamar, *jumlahKamar);
}

// Fungsi untuk mencari kamar berdasarkan nomor
void cariKamar(struct Kamar kamar[], int jumlahKamar, int nomor) {
    int found = 0;
    for (int i = 0; i < jumlahKamar; ++i) {
        if (kamar[i].nomor == nomor) {
            printf("Kamar ditemukan:\n");
            printf("Nomor Kamar: %d\n", kamar[i].nomor);
            printf("Tipe Kamar: %s\n", kamar[i].tipe);
            printf("Harga: %.2f\n", kamar[i].harga);
            printf("Status: %s\n", kamar[i].isTerisi ? "Terisi" : "Kosong");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Kamar tidak ditemukan.\n");
    }
}

// Fungsi untuk menghapus kamar berdasarkan tipe
void hapusKamar(struct Kamar kamar[], int *jumlahKamar, const char *tipe) {
    int found = 0;
    for (int i = 0; i < *jumlahKamar; ++i) {
        if (strcmp(kamar[i].tipe, tipe) == 0) {
            for (int j = i; j < *jumlahKamar - 1; ++j) {
                kamar[j] = kamar[j + 1];
            }
            (*jumlahKamar)--;
            found = 1;
            break;
        }
    }
    if (found) {
        printf("Kamar dengan tipe %s berhasil dihapus.\n", tipe);
        simpanKamarKeFile(kamar, *jumlahKamar);
    } else {
        printf("Kamar dengan tipe %s tidak ditemukan.\n", tipe);
    }
}

// Fungsi untuk menyimpan data penyewa ke file
void simpanPenyewaKeFile(struct Penyewa penyewa[], int jumlahPenyewa) {
    FILE *file = fopen("data_penyewa.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    fprintf(file, "Nama\tNIK\tNo. Telepon\tKamar\tLama Sewa\tTotal Pembayaran\n");
    for (int i = 0; i < jumlahPenyewa; ++i) {
        fprintf(file, "%s\t%s\t%s\t%d\t%d\t%.2f\n", penyewa[i].nama, penyewa[i].NIK, penyewa[i].noTelepon, penyewa[i].kamarSewa, penyewa[i].lamaSewa, penyewa[i].totalPembayaran);
    }

    fclose(file);
}

// Fungsi untuk melakukan pembayaran
void pembayaran(struct Penyewa *penyewa, struct Kamar kamar[], int jumlahKamar, int *jumlahPenyewa) {
    char jawaban[5];
    printf("Masukkan nama penyewa: ");
    scanf("%s", penyewa[*jumlahPenyewa].nama);
    printf("Masukkan NIK: ");
    scanf("%s", penyewa[*jumlahPenyewa].NIK);
    printf("Masukkan nomor telepon: ");
    scanf("%s", penyewa[*jumlahPenyewa].noTelepon);
    
    int nomorKamar, lamaSewa, gunaAir = 0, gunaListrik = 0;
    printf("Masukkan nomor kamar yang disewa: ");
    scanf("%d", &nomorKamar);
    printf("Masukkan lama sewa (bulan): ");
    scanf("%d", &lamaSewa);

    printf("Apakah penyewa ingin menggunakan air? (ya/tidak): ");
    scanf("%s", jawaban);
    if (strcmp(jawaban, "ya") == 0) {
        printf("Masukkan pemakaian air (dalam m³): ");
        scanf("%d", &gunaAir);
    }

    printf("Apakah penyewa ingin menggunakan listrik? (ya/tidak): ");
    scanf("%s", jawaban);
    if (strcmp(jawaban, "ya") == 0) {
        printf("Masukkan pemakaian listrik (dalam kWh): ");
        scanf("%d", &gunaListrik);
    }

    int found = 0;
    for (int i = 0; i < jumlahKamar; ++i) {
        if (kamar[i].nomor == nomorKamar && !kamar[i].isTerisi) {
            penyewa[*jumlahPenyewa].kamarSewa = nomorKamar;
            penyewa[*jumlahPenyewa].lamaSewa = lamaSewa;
            penyewa[*jumlahPenyewa].gunaAir = gunaAir;
            penyewa[*jumlahPenyewa].gunaListrik = gunaListrik;
            penyewa[*jumlahPenyewa].totalPembayaran = (kamar[i].harga * lamaSewa) + (100000 * gunaAir) + (200000 * gunaListrik * lamaSewa);
            kamar[i].isTerisi = 1;
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Pembayaran berhasil.\n");
        simpanPenyewaKeFile(penyewa, *jumlahPenyewa + 1);
        simpanKamarKeFile(kamar, jumlahKamar);
        (*jumlahPenyewa)++;
    } else {
        printf("Gagal melakukan pembayaran. Kamar tidak tersedia atau sudah terisi.\n");
    }
}

int main() {
    struct Kamar kamar[MAX_KAMAR];
    struct Penyewa penyewa[MAX_PENYEWA];
    int jumlahKamar = 0;
    int jumlahPenyewa = 0;

    // Implementasi logika untuk membaca data kamar dan penyewa dari file jika ada

    int pilihan;
    do {
        printf("\nMenu:\n");
        printf("1. Cari Kamar\n");
        printf("2. Tambah Kamar\n");
        printf("3. Hapus Kamar\n");
        printf("4. Pembayaran\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                {
                    int nomor;
                    printf("Masukkan nomor kamar yang ingin dicari: ");
                    scanf("%d", &nomor);
                    cariKamar(kamar, jumlahKamar, nomor);
                    break;
                }
            case 2:
                tambahKamar(kamar, &jumlahKamar);
                break;
            case 3:
                {
                    char tipe[20];
                    printf("Masukkan tipe kamar yang ingin dihapus: ");
                    scanf("%s", tipe);
                    hapusKamar(kamar, &jumlahKamar, tipe);
                    break;
                }
            case 4:
                pembayaran(&penyewa[jumlahPenyewa], kamar, jumlahKamar, &jumlahPenyewa);
                break;
            case 0:
                printf("Program selesai.\n");
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                break;
        }
    } while (pilihan != 0);

    return 0;
}

void getTime() {
    time_t rawtime;
    struct tm *info;
    time(&rawtime);
    info = localtime(&rawtime);
    
    strftime(payment_date, sizeof(payment_date), "%Y-%m-%d %H:%M:%S", info);
}

//bayu
void struk(struct Kamar kamar[], struct Penyewa penyewa[], int roomIndex) {
    char tipe[20];
    system("cls");
     getTime(); 
     printf("\n");
     printf("==================================================================\n");
     printf("                     TOTAL PEMBAYARAN KOS                         \n");
     printf("==================================================================\n");
     printf("   Nama Penyewa           : %s \n", penyewa[roomIndex].nama);
     printf("   NIK Penyewa            : %s \n", penyewa[roomIndex].NIK);
     printf("   No Telepon Penyewa     : %s \n", penyewa[roomIndex].noTelepon);
     strcpy(tipe, kamar[roomIndex].tipe);
     printf("   Tipe                   : %s \n", tipe);
     printf("   Tanggal                : %s \n", payment_date);
     printf("   Jumlah Bulan           : %d \n", penyewa[roomIndex].lamaSewa);
     printf("   Harga Kamar Perbulan   : Rp.%2.f  \n", kamar[roomIndex].harga);
     printf("   Biaya Kuota Listrik    : Rp.%2.f  \n", penyewa[roomIndex].gunaListrik);
     printf("   Biaya Kuota Air        : Rp.%2.f  \n", penyewa[roomIndex].gunaAir);
     printf("==================================================================\n");
     printf("   Total Biaya            : Rp.%2.f  \n", penyewa[roomIndex].totalPembayaran);
     printf("==================================================================\n");
}

//bayu
/* void printToStrukFile() {
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
*/