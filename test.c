#include <stdio.h>
#include <string.h>

#define MAX_KOS 5 // Jumlah maksimum kos yang tersedia

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
    int harga;
    int tersedia;
    enum TipeKos tipe;
    struct Penyewa penyewa;
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
            printf("%d\t\t%d\t%s\n", kos[i].nomorKamar, kos[i].harga, (kos[i].tersedia ? "Tersedia" : "Terisi"));
        }
    }
}
void tulisDataKeFile(struct Kos daftarKos[], FILE *fileKos) {
    for (int i = 0; i < MAX_KOS; ++i) {
        fprintf(fileKos, "%d %d %d %d\n", daftarKos[i].nomorKamar, daftarKos[i].harga, daftarKos[i].tersedia, daftarKos[i].tipe);
        if (daftarKos[i].tersedia == 1) {
            fprintf(fileKos, "%s %d %s\n", daftarKos[i].penyewa.nama, daftarKos[i].penyewa.umur, daftarKos[i].penyewa.no_identitas);
        } else {
            fprintf(fileKos, "\n");
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



void main (){
    infoKos();
}