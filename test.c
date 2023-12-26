void menuInformasi() {
    int pilihan;
    printf("/n");

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
                pembayaran(&penyewa[jumlahPenyewa], kamar, jumlahKamar, &jumlahPenyewa);
                cetakStruk(kamar, penyewa, jumlahPenyewa - 1); // Menampilkan struk untuk penyewa terakhir
                break;
            case 0:
               menuAwal();
                break;
            default:
                printf("Pilihan tidak valid. Silakan pilih lagi.\n");
                break;
        }
    } while (pilihan != 0);
}

void menuAwal() {
    int pilihan;

    printf("==============================================\n");
    printf("|                SERNIA KOST                 |\n");
    printf("==============================================\n");
    printf("|                                            |\n");
    printf("|  1. Kelola Informasi Data Kos              |\n");
    printf("|  2. Pembayaran Kos                         |\n");
    printf("|                                            |\n");
    printf("----------------------------------------------\n");
    printf("Masukkan Pilihan : ");
    scanf("%d", &pilihan);

    switch(pilihan) {
        case 1:
            menuInformasi();
            break;
        case 2:
            pembayaran(&penyewa[jumlahPenyewa], kamar, jumlahKamar, &jumlahPenyewa);
            cetakStruk(kamar, penyewa, jumlahPenyewa - 1); // Menampilkan struk untuk penyewa terakhir
            break;
        default:
            printf("Pilihan tidak valid\n");
            break;
    }


}

int main() {
    printf("\n");
    title();
    menuAwal();
    bacaKamarDariFile(kamar, &jumlahKamar);
    bacaPenyewaDariFile(penyewa, &jumlahPenyewa);
    
    return 0;
}
