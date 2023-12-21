#include <stdio.h>
#include <string.h>

#define MAX_KAMAR 50

typedef struct {
    int nomerKamar;
    int terisi;
    char namaPenyewa[50];
} Kamar;

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
    char namaPenyewa[50];
    for (int i = 0; i < jumlahKamar; i++) {
        if (dataKamar[i].nomerKamar == nomorKamar) {
            if (dataKamar[i].terisi == 0) {
                dataKamar[i].terisi = 1;
                printf("Masukkan nama penyewa untuk kamar nomor %d: ", nomorKamar);
                scanf(" %[^\n]", namaPenyewa);
                strcpy(dataKamar[i].namaPenyewa, namaPenyewa);
                printf("Kamar nomor %d berhasil diisi oleh %s.\n", nomorKamar, namaPenyewa);
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

int main() {
    Kamar dataKamar[MAX_KAMAR];
    int jumlahKamar = 0;

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
    } while (pilihanMenu != 0);

    return 0;
}
