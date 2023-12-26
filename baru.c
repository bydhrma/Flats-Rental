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

int isFileKosong(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return 1; // Return 1 jika file tidak ditemukan
    }

    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0) {
        fclose(file);
        return 1; // Return 1 jika file kosong
    }

    fclose(file);
    return 0; // Return 0 jika file berisi data
}

// Fungsi untuk membaca data kamar kos dari file
void bacaKamarDariFile(struct Kamar kamar[], int *jumlahKamar) {
    FILE *file = fopen("daftar_kos.txt", "r");
    if (file == NULL) {
        printf("File daftar_kos.txt tidak ditemukan.\n");
        return;
    }

    *jumlahKamar = 0; // Reset jumlah kamar sebelum membaca file
    while (fscanf(file, "%d\t%s\t%f\t%d", &kamar[*jumlahKamar].nomor, kamar[*jumlahKamar].tipe, &kamar[*jumlahKamar].harga, &kamar[*jumlahKamar].isTerisi) != EOF) {
        (*jumlahKamar)++;
    }

    fclose(file);
}

void bacaPenyewaDariFile(struct Penyewa penyewa[], int *jumlahPenyewa) {
    FILE *file = fopen("data_penyewa.txt", "r");
    if (file == NULL) {
        printf("File data_penyewa.txt tidak ditemukan.\n");
        return;
    }

    *jumlahPenyewa = 0; // Reset jumlah penyewa sebelum membaca file
    while (fscanf(file, "%s\t%s\t%s\t%d\t%d\t%f\t%d\t%d", penyewa[*jumlahPenyewa].nama, penyewa[*jumlahPenyewa].NIK, penyewa[*jumlahPenyewa].noTelepon, &penyewa[*jumlahPenyewa].kamarSewa, &penyewa[*jumlahPenyewa].lamaSewa, &penyewa[*jumlahPenyewa].totalPembayaran, &penyewa[*jumlahPenyewa].gunaAir, &penyewa[*jumlahPenyewa].gunaListrik) != EOF) {
        (*jumlahPenyewa)++;
    }

    fclose(file);
}


void tulisHeaderDaftarKos(FILE *file) {
    fprintf(file, "Nomor Kamar\tTipe\tHarga\tStatus\n");
}

// Fungsi untuk menyimpan data kamar kos ke file
void simpanKamarKeFile(struct Kamar kamar[], int jumlahKamar) {
    FILE *file = fopen("daftar_kos.txt", "w");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    if (isFileKosong("daftar_kos.txt")) {
        tulisHeaderDaftarKos(file); // Menulis header jika file kosong
    }

    for (int i = 0; i < jumlahKamar; ++i) {
        fprintf(file, "%d\t%s\t%.2f\t%d\n", kamar[i].nomor, kamar[i].tipe, kamar[i].harga, kamar[i].isTerisi);
    }

    fclose(file);
}

// Fungsi untuk menulis header ke file data_penyewa.txt
void tulisHeaderDataPenyewa(FILE *file) {
    fprintf(file, "Nama\tNIK\tNo. Telepon\tKamar\tLama Sewa\tTotal Pembayaran\n");
}

void simpanPenyewaKeFile(struct Penyewa penyewa[], int jumlahPenyewa) {
    FILE *file = fopen("data_penyewa.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file.\n");
        return;
    }

    if (isFileKosong("data_penyewa.txt")) {
        fprintf(file, "Nama\tNIK\tNo. Telepon\tKamar\tLama Sewa\tTotal Pembayaran\tGuna Air\tGuna Listrik\n");
    }

    fprintf(file, "%s\t%s\t%s\t%d\t%d\t%.2f\t%d\t%d\n",
            penyewa[jumlahPenyewa - 1].nama,
            penyewa[jumlahPenyewa - 1].NIK,
            penyewa[jumlahPenyewa - 1].noTelepon,
            penyewa[jumlahPenyewa - 1].kamarSewa,
            penyewa[jumlahPenyewa - 1].lamaSewa,
            penyewa[jumlahPenyewa - 1].totalPembayaran,
            penyewa[jumlahPenyewa - 1].gunaAir,
            penyewa[jumlahPenyewa - 1].gunaListrik);

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
            printf("\nKamar ditemukan:\n");
            printf("\nNomor Kamar: %d\t", kamar[i].nomor);
            printf("Tipe Kamar: %s\t", kamar[i].tipe);
            printf("Harga: %.2f\t", kamar[i].harga);
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

// Fungsi untuk melakukan pembayaran
void pembayaran(struct Penyewa *penyewa, struct Kamar kamar[], int jumlahKamar, int *jumlahPenyewa) {
    printf("Masukkan nama penyewa: ");
    scanf("%s", penyewa[*jumlahPenyewa].nama);
    printf("Masukkan NIK: ");
    scanf("%s", penyewa[*jumlahPenyewa].NIK);
    printf("Masukkan nomor telepon: ");
    scanf("%s", penyewa[*jumlahPenyewa].noTelepon);
    
    int nomorKamar, lamaSewa, gunaAir, gunaListrik;
    printf("Masukkan nomor kamar yang disewa: ");
    scanf("%d", &nomorKamar);
    printf("Masukkan lama sewa (bulan): ");
    scanf("%d", &lamaSewa);
    printf("Apakah ingin menggunakan kouta air? (1 untuk Ya, 0 untuk Tidak): ");
    scanf("%d", &gunaAir);
    printf("Apakah ingin menggunakan kouta listrik? (1 untuk Ya, 0 untuk Tidak): ");
    scanf("%d", &gunaListrik);

    int found = 0;
    for (int i = 0; i < jumlahKamar; ++i) {
        if (kamar[i].nomor == nomorKamar && !kamar[i].isTerisi) {
            penyewa[*jumlahPenyewa].kamarSewa = nomorKamar;
            penyewa[*jumlahPenyewa].lamaSewa = lamaSewa;
            penyewa[*jumlahPenyewa].gunaAir = gunaAir;
            penyewa[*jumlahPenyewa].gunaListrik = gunaListrik;

            // Menghitung total pembayaran
            float hargaKamar = kamar[i].harga * lamaSewa;
            float biayaAir = gunaAir ? 150000 * lamaSewa : 0; // Biaya air per bulan
            float biayaListrik = gunaListrik ? 250000 * lamaSewa : 0; // Biaya listrik per bulan

            penyewa[*jumlahPenyewa].totalPembayaran = hargaKamar + biayaAir + biayaListrik;

            // Ubah status kamar menjadi terisi
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

void cetakStruk(struct Kamar kamar[], struct Penyewa penyewa[], int jumlahPenyewa) {
    time_t rawtime;
    struct tm *timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(payment_date, sizeof(payment_date), "%Y-%m-%d", timeinfo);

    float total_price = penyewa[jumlahPenyewa - 1].totalPembayaran - (150000 * penyewa[jumlahPenyewa - 1].lamaSewa) - (250000 * penyewa[jumlahPenyewa - 1].lamaSewa);
    float total_electric = penyewa[jumlahPenyewa - 1].gunaListrik ? (250000 * penyewa[jumlahPenyewa - 1].lamaSewa) : 0;
    float total_water = penyewa[jumlahPenyewa - 1].gunaAir ? (150000 * penyewa[jumlahPenyewa - 1].lamaSewa) : 0;

   printf("\n");
   printf("==================================================================\n");
   printf("                     TOTAL PEMBAYARAN KOS                         \n");
   printf("==================================================================\n");
   printf("   Nama Penyewa           : %s \n", penyewa[jumlahPenyewa - 1].nama);
   printf("   NIK Penyewa            : %s \n", penyewa[jumlahPenyewa - 1].NIK);
   printf("   No Hp Penyewa          : %s \n", penyewa[jumlahPenyewa - 1].noTelepon);
   printf("   Tipe                   : %s \n", kamar[penyewa[jumlahPenyewa - 1].kamarSewa - 1].tipe);
   printf("   Tanggal                : %s \n", payment_date);
   printf("   Jumlah Bulan           : %d \n", penyewa[jumlahPenyewa - 1].lamaSewa);
   printf("   Harga Kamar Perbulan   : Rp. %.2f  \n", penyewa[jumlahPenyewa - 1].totalPembayaran - penyewa[jumlahPenyewa - 1].gunaAir * 150000 - penyewa[jumlahPenyewa - 1].gunaListrik * 250000);
   printf("   Biaya Kuota Listrik    : Rp. %.2f  \n", penyewa[jumlahPenyewa - 1].gunaListrik * 250000);
   printf("   Biaya Kuota Air        : Rp. %.2f  \n", penyewa[jumlahPenyewa - 1].gunaAir * 150000);
   printf("==================================================================\n");
   printf("   Total Biaya            : Rp. %.2f   \n", penyewa[jumlahPenyewa - 1].totalPembayaran);
   printf("==================================================================\n");
   

    FILE *file = fopen("struk_pembayaran.txt", "w");
    if (file == NULL) {
        printf("Gagal membuat file struk pembayaran.\n");
        return;
    }

    fprintf(file, "\n");
    fprintf(file, "==================================================================\n");
    fprintf(file, "                     TOTAL PEMBAYARAN KOS                         \n");
    fprintf(file, "==================================================================\n");
    fprintf(file, "   Nama Penyewa           : %s \n", penyewa[jumlahPenyewa - 1].nama);
    fprintf(file, "   NIK Penyewa            : %s \n", penyewa[jumlahPenyewa - 1].NIK);
    fprintf(file, "   No Hp Penyewa          : %s \n", penyewa[jumlahPenyewa - 1].noTelepon);
    fprintf(file, "   Tipe                   : %s \n", kamar[penyewa[jumlahPenyewa - 1].kamarSewa - 1].tipe);
    fprintf(file, "   Tanggal                : %s \n", payment_date);
    fprintf(file, "   Jumlah Bulan           : %d \n", penyewa[jumlahPenyewa - 1].lamaSewa);
    fprintf(file, "   Harga Kamar Perbulan   : Rp.%2.f  \n", total_price);
    fprintf(file, "   Biaya Kuota Listrik    : Rp.%2.f  \n", total_electric);
    fprintf(file, "   Biaya Kuota Air        : Rp.%2.f  \n", total_water);
    fprintf(file, "==================================================================\n");
    fprintf(file, "   Total Biaya            : Rp.%2.f   \n", penyewa[jumlahPenyewa - 1].totalPembayaran);
    fprintf(file, "==================================================================\n");

    fclose(file);
    printf("Struk pembayaran telah dicetak ke dalam file 'struk_pembayaran.txt'.\n");
}




int main() {
    struct Kamar kamar[MAX_KAMAR];
    struct Penyewa penyewa[MAX_PENYEWA];
    int jumlahKamar = 0;
    int jumlahPenyewa = 0;

    // bacaKamarDariFile(kamar, &jumlahKamar);
    // bacaPenyewaDariFile(penyewa, &jumlahPenyewa);



    // Implementasi logika untuk membaca data kamar dan penyewa dari file jika ada

    int pilihan;
    do {
        printf("\nMenu:\n");
        printf("1. Cari Kamar\n");
        printf("2. Tambah Kamar\n");
        printf("3. Hapus Kamar\n");
        printf("4. Pembayaran Dan Struk\n");
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
                pembayaran(penyewa, kamar, jumlahKamar, &jumlahPenyewa);
                cetakStruk(kamar, penyewa, jumlahPenyewa);
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
