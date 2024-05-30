#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cucimobil.h"

queue_mobil fast[1];
queue_mobil reguler[1];

void mainmenu(int *pilihan) {
    
    system("cls");
    title();
    printf("\nSELAMAT DATANG DI 3R CARWASH\n");
    printf("1. Masuk antrian\n");
    printf("2. Lihat antrian\n");
    printf("3. Checkout\n");
    printf("4. Riwayat\n");
    printf("5. Keluar\n");
    printf("Masukan pilihan: ");
    scanf("%d", pilihan);
}

void buat_queue() {
    fast[0].depan = NULL;
    fast[0].belakang = NULL;
    reguler[0].depan = NULL;
    reguler[0].belakang = NULL;
}

void masuk_antrian(int *pilihan) {
    int jenis_paket = 0, jenis_pelayanan = 0, golongan = 0;
    char c;
    char plat[10];
    waktu_datang waktu;

    system("cls");
    title();
    printf("\nJenis pelayanan:\n");
    printf("1. Fast track\n");
    printf("2. Reguler\n");
    printf("Pilih jenis pelayanan: ");
    if (scanf("%d", &jenis_pelayanan) != 1 || (jenis_pelayanan < 1 || jenis_pelayanan > 2)) {
        printf("Pilihan tidak valid. Harus antara 1 atau 2.\n");
        enter_to_continue();
        return;
    }

    system("cls");
    title();
    printf("\nApakah anda ingin menggunakan layanan tambahan? (y/n): ");
    scanf(" %c", &c);

    if (c == 'y' || c == 'Y') {
        system("cls");
        title();
        printf("\nLayanan tambahan:\n");
        printf("1. Interior\n");
        printf("2. Coating\n");
        printf("3. Cuci mesin\n");
        printf("4. Paket lengkap\n");
        printf("Pilih layanan tambahan anda: ");
        if (scanf("%d", &jenis_paket) != 1 || (jenis_paket < 1 || jenis_paket > 4)) {
            printf("Pilihan tidak valid. Harus antara 1 sampai 4.\n");
            enter_to_continue();
            return;
        }
    } else if (c == 'n' || c == 'N') {
        printf("Anda tidak menggunakan layanan tambahan\n");
    } else {
        printf("Pilihan tidak valid. Harus 'y' atau 'n'.\n");
        enter_to_continue();
        return;
    }

    system("cls");
    title();
    printf("\nGolongan mobil:\n");
    printf("1. Golongan 1: sedan, lcgc, city car, hatchback\n");
    printf("2. Golongan 2: mpv\n");
    printf("3. Golongan 3: suv, minibus\n");
    printf("Pilih golongan mobil anda: ");
    if (scanf("%d", &golongan) != 1 || (golongan < 1 || golongan > 3)) {
        printf("Pilihan tidak valid. Harus antara 1 sampai 3.\n");
        enter_to_continue();
        return;
    }

    printf("Masukkan nopol mobil anda: ");
    fflush(stdin);
    scanf("%[^\n]", plat);

    printf("Masukkan waktu kedatangan (Jam:Menit): ");
    if (scanf("%d:%d", &waktu.jam, &waktu.menit) != 2) {
        printf("Format waktu tidak valid. Gunakan format Jam:Menit.\n");
        enter_to_continue();
        return;
    }

    if (!validasi_waktu_datang(waktu.jam, waktu.menit)) {
        printf("Waktu kedatangan di luar jam operasional (9:00 - 15:00). Tidak bisa menambahkan antrian.\n");
        enter_to_continue();
        return;
    }

    queue_mobil *q = (jenis_pelayanan == 1) ? fast : reguler;
    waktu_datang last_finish = get_last_finish_time(q);

    if ((waktu.jam < last_finish.jam) || (waktu.jam == last_finish.jam && waktu.menit < last_finish.menit)) {
        waktu = last_finish;
    }

    sesuaikan_waktu_istirahat(&waktu);
    system("cls");
    title();
    bikin_struk(plat, golongan, jenis_paket, jenis_pelayanan, waktu);
    tambah_mobil(jenis_pelayanan, golongan, jenis_paket, plat, waktu);
    enter_to_continue();
}

void tambah_mobil(int jenis_pelayanan, int golongan, int jenis_paket, char *plat, waktu_datang waktu) {
    data_mobil *baru = (data_mobil *)malloc(sizeof(data_mobil));
    strcpy(baru->plat, plat);
    baru->jenis_paket = jenis_paket;
    baru->jenis_pelayanan = jenis_pelayanan;
    baru->golongan = golongan;
    baru->next = NULL;

    queue_mobil *q = (jenis_pelayanan == 1) ? fast : reguler;
    if (q->depan == NULL) {
        q->depan = baru;
        q->belakang = baru;
    } else {
        q->belakang->next = baru;
        q->belakang = baru;
    }
}

void show_queue(queue_mobil *q) {
    if (q->depan == NULL) {
        printf("Kosong\n");
        return;
    }
    printf("Isi antrian:\n");
    data_mobil *current = q->depan;
    while (current != NULL) {
        printf("Nopol: %s, Golongan: %d, Jenis Paket: %d, Jenis Pelayanan: %d\n", current->plat, current->golongan, current->jenis_paket, current->jenis_pelayanan);
        current = current->next;
    }
}

/*void show_queue(queue_mobil *q) {
    if (q->depan == NULL) {
        printf("Kosong\n");
        return;
    }
    printf("Isi antrian:\n");
    data_mobil *current = q->depan;
    while (current != NULL) {
        printf("Nopol: %s, Golongan: %d, Jenis Paket: %d, Jenis Pelayanan: %d\n", current->plat, current->golongan, current->jenis_paket, current->jenis_pelayanan);
        current = current->next;
    }

    printf("\nStruk dari file:\n");
    show_struk_from_file();
}*/


void bikin_struk(char *plat, int golongan, int jenis_paket, int jenis_pelayanan, waktu_datang waktu) {
    struk s;
    strcpy(s.plat, plat);
    s.golongan = golongan;
    s.jenis_paket = jenis_paket;
    s.jenis_pelayanan = jenis_pelayanan;
    s.waktu = waktu;

    if (golongan == 1) {
        s.harga = 50000;
    } else if (golongan == 2) {
        s.harga = 75000;
    } else if (golongan == 3) {
        s.harga = 100000;
    }

    if (jenis_paket == 1) {
        s.harga += 25000;
    } else if (jenis_paket == 2) {
        s.harga += 50000;
    } else if (jenis_paket == 3) {
        s.harga += 75000;
    } else if (jenis_paket == 4) {
        s.harga += 100000;
    }

    s.estimasi_selesai = hitung_estimasi_selesai(s.waktu, s.jenis_pelayanan, s.golongan);

    printf("\t Struk: \n");
    printf("Nopol: %s\n", s.plat);
    printf("Golongan: %d\n", s.golongan);
    printf("Jenis paket: %d\n", s.jenis_paket);
    printf("Jenis pelayanan: %d\n", s.jenis_pelayanan);
    printf("Harga: %d\n", s.harga);

    save_struk_to_file(s);
    save_riwayat_to_file(s);
}

void save_struk_to_file(struk s) {
    FILE *fptr;
    fptr = fopen("struk.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fptr, "Nopol: %s, Golongan: %d, Jenis Paket: %d, Jenis Pelayanan: %d, Harga: %d, Waktu: %02d:%02d, Estimasi Selesai: %02d:%02d\n",
            s.plat, s.golongan, s.jenis_paket, s.jenis_pelayanan, s.harga, s.waktu.jam, s.waktu.menit, s.estimasi_selesai.jam, s.estimasi_selesai.menit);
    fclose(fptr);
}

void save_riwayat_to_file(struk s) {
    FILE *fptr;
    fptr = fopen("riwayat.txt", "a");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    fprintf(fptr, "Nopol: %s, Golongan: %d, Jenis Paket: %d, Jenis Pelayanan: %d, Harga: %d, Waktu: %02d:%02d, Estimasi Selesai: %02d:%02d\n",
            s.plat, s.golongan, s.jenis_paket, s.jenis_pelayanan, s.harga, s.waktu.jam, s.waktu.menit, s.estimasi_selesai.jam, s.estimasi_selesai.menit);
    fclose(fptr);
}

//void checkout() {
//    char plat[10];
//    printf("Masukkan nopol mobil yang ingin checkout: ");
//    fflush(stdin);
//    scanf("%s", plat);
//
//    data_mobil *mobil = cari_mobil(plat);
//    if (mobil == NULL) {
//        printf("Mobil tidak ditemukan dalam antrian.\n");
//        return;
//    }
//
//    int total_harga = hitung_total_harga(plat);
//    printf("Total harga untuk mobil dengan nopol %s adalah %d\n", plat, total_harga);
//
//    hapus_mobil(plat);
//    hapus_struk_dari_file(plat);
//}


//void checkout() {
//    char plat[10];
//    printf("Masukkan nopol mobil yang ingin checkout: ");
//    fflush(stdin);
//    scanf("%s", plat);
//
//    data_mobil *mobil = cari_mobil(plat);
//    if (mobil == NULL) {
//        printf("Mobil tidak ditemukan dalam antrian.\n");
//        printf("Anda yakin ingin menghapus struk untuk mobil dengan nopol %s? (y/n): ", plat);
//        char confirm;
//        scanf(" %c", &confirm);
//        if (confirm == 'y' || confirm == 'Y') {
//            hapus_struk_dari_file(plat);
//            printf("Struk untuk mobil dengan nopol %s berhasil dihapus.\n", plat);
//        }
//        return;
//    }
//
//    int total_harga = hitung_total_harga(plat);
//    if (total_harga == -1) {
//        printf("Terjadi kesalahan dalam menghitung total harga.\n");
//        return;
//    }
//    printf("Total harga untuk mobil dengan nopol %s adalah %d\n", plat, total_harga);
//
//    hapus_mobil(plat);
//    hapus_struk_dari_file(plat);
//    printf("Mobil dengan nopol %s berhasil di-checkout.\n", plat);
//}

//void checkout() {
//    char plat[10];
//    printf("Masukkan nopol mobil yang ingin checkout: ");
//    fflush(stdin);
//    scanf("%[^\n]", plat);
//
//    data_mobil *mobil = cari_mobil(plat);
//    if (mobil == NULL) {
////        printf("Mobil tidak ditemukan dalam antrian.\n");
//        printf("Anda yakin ingin menghapus struk untuk mobil dengan nopol %s? (y/n): ", plat);
//        char confirm;
//        scanf(" %c", &confirm);
//        if (confirm == 'y' || confirm == 'Y') {
//        	hapus_mobil(plat);
//            hapus_struk_dari_file(plat);
//            printf("Struk untuk mobil dengan nopol %s berhasil dihapus.\n", plat);
//        }
//        return;
//    }
//
//    int total_harga = hitung_total_harga(plat);
//    if (total_harga == -1) {
//        printf("Terjadi kesalahan dalam menghitung total harga.\n");
//        return;
//    }
//    printf("Total harga untuk mobil dengan nopol %s adalah %d\n", plat, total_harga);
//
//    hapus_mobil(plat);
//    hapus_struk_dari_file(plat);
//    printf("Mobil dengan nopol %s berhasil di-checkout.\n", plat);
//    enter_to_continue();
//}
//

void checkout() {
    char plat[10];
    title();
    printf("\nMasukkan nopol mobil yang ingin checkout: ");
    fflush(stdin);
    scanf("%[^\n]", plat);

    data_mobil *mobil = cari_mobil(plat);
    if (mobil == NULL) {
        printf("Mobil dengan nopol %s tidak ditemukan dalam antrian. Checkout gagal.\n", plat);
        enter_to_continue();
        return;
    }

    int total_harga = hitung_total_harga(plat);
    if (total_harga == -1) {
        printf("Terjadi kesalahan dalam menghitung total harga.\n");
        enter_to_continue();
        return;
    }
    printf("Total harga untuk mobil dengan nopol %s adalah %d\n", plat, total_harga);

    hapus_mobil(plat);
    hapus_struk_dari_file(plat);
    printf("Mobil dengan nopol %s berhasil di-checkout.\n", plat);
    enter_to_continue();
}


void show_struk_from_file() {
	FILE *fptr;
    char c;
    fptr = fopen("struk.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while ((c = fgetc(fptr)) != EOF) {
        putchar(c);
    }
    fclose(fptr);
}

void show_riwayat_from_file() {
    printf("\n");
	FILE *fptr;
    char c;
    fptr = fopen("riwayat.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return;
    }
    while ((c = fgetc(fptr)) != EOF) {
        putchar(c);
    }
    fclose(fptr);
}

void enter_to_continue() {
    printf("Tekan enter untuk melanjutkan...");
    while (getchar() != '\n');
    getchar();
}

int validasi_waktu_datang(int jam, int menit) {
    if (jam < 9 || jam > 15 || (jam == 15 && menit > 0)) {
        return 0;
    }
    return 1;
}

void sesuaikan_waktu_istirahat(waktu_datang *waktu) {
    if (waktu->jam >= 12 && waktu->jam < 13) {
        waktu->jam = 13;
        waktu->menit = 0;
    }
}

//data_mobil *cari_mobil(char *plat) {
//    data_mobil *current = fast[0].depan;
//    while (current != NULL) {
//        if (strcmp(current->plat, plat) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//
//    current = reguler[0].depan;
//    while (current != NULL) {
//        if (strcmp(current->plat, plat) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//    return NULL;
//}

//data_mobil *cari_mobil(char *plat) {
//    data_mobil *current;
//
//    // Cari di antrian fast
//    current = fast[0].depan;
//    while (current != NULL) {
//        if (strcmp(current->plat, plat) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//
//    // Cari di antrian reguler
//    current = reguler[0].depan;
//    while (current != NULL) {
//        if (strcmp(current->plat, plat) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//
//    return NULL;
//}

//data_mobil *cari_mobil(char *plat) {
//    data_mobil *current;
//
//    // Cari di antrian fast
//    current = fast[0].depan;
//    while (current != NULL) {
//        if (strcmp(current->plat, plat) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//
//    // Cari di antrian reguler
//    current = reguler[0].depan;
//    while (current != NULL) {
//        if (strcmp(current->plat, plat) == 0) {
//            return current;
//        }
//        current = current->next;
//    }
//
//    return NULL;
//}

data_mobil *cari_mobil(char *plat) {
    data_mobil *current;

    // Cari di antrian fast
    current = fast[0].depan;
    while (current != NULL) {
        if (strcmp(current->plat, plat) == 0) {
            return current;
        }
        current = current->next;
    }

    // Cari di antrian reguler
    current = reguler[0].depan;
    while (current != NULL) {
        if (strcmp(current->plat, plat) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL;
}


int hitung_total_harga(char *plat) {
    data_mobil *mobil = cari_mobil(plat);
    if (mobil == NULL) {
        return -1;
    }

    int harga = 0;
    if (mobil->golongan == 1) {
        harga = 50000;
    } else if (mobil->golongan == 2) {
        harga = 75000;
    } else if (mobil->golongan == 3) {
        harga = 100000;
    }

    if (mobil->jenis_paket == 1) {
        harga += 25000;
    } else if (mobil->jenis_paket == 2) {
        harga += 50000;
    } else if (mobil->jenis_paket == 3) {
        harga += 75000;
    } else if (mobil->jenis_paket == 4) {
        harga += 100000;
    }

    return harga;
}

void hapus_mobil(char *plat) {
    data_mobil *current = fast[0].depan;
    data_mobil *prev = NULL;
    while (current != NULL && strcmp(current->plat, plat) != 0) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        if (prev == NULL) {
            fast[0].depan = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
        return;
    }

    current = reguler[0].depan;
    prev = NULL;
    while (current != NULL && strcmp(current->plat, plat) != 0) {
        prev = current;
        current = current->next;
    }
    if (current != NULL) {
        if (prev == NULL) {
            reguler[0].depan = current->next;
        } else {
            prev->next = current->next;
        }
        free(current);
    }
}

void hapus_struk_dari_file(const char *plat) {
    FILE *fptr, *temp;
    char buffer[256];
    fptr = fopen("struk.txt", "r");
    temp = fopen("temp.txt", "w");

    if (fptr == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fgets(buffer, 256, fptr) != NULL) {
        if (strstr(buffer, plat) == NULL) {
            fputs(buffer, temp);
        }
    }

    fclose(fptr);
    fclose(temp);

    remove("struk.txt");
    rename("temp.txt", "struk.txt");
}

waktu_datang hitung_estimasi_selesai(waktu_datang waktu, int jenis_pelayanan, int golongan) {
    int waktu_cuci = (golongan == 1) ? 30 : (golongan == 2) ? 45 : 60;
    if (jenis_pelayanan == 1) {
        waktu_cuci /= 2;
    }

    waktu.menit += waktu_cuci;
    if (waktu.menit >= 60) {
        waktu.jam += waktu.menit / 60;
        waktu.menit %= 60;
    }

    if (waktu.jam >= 12 && waktu.jam < 13) {
        waktu.jam = 13;
        waktu.menit = 0;
    }

    return waktu;
}

waktu_datang get_last_finish_time(queue_mobil *q) {
    if (q->belakang == NULL) {
        waktu_datang no_mobil = {0, 0}; // If no car is present, return 00:00
        return no_mobil;
    }

    // Read struk.txt to find the finish time of the last car in the queue
    FILE *fptr;
    char buffer[256];
    waktu_datang last_finish = {0, 0};

    fptr = fopen("struk.txt", "r");
    if (fptr == NULL) {
        printf("Error opening file!\n");
        return last_finish;
    }

    while (fgets(buffer, 256, fptr) != NULL) {
        // Assuming the format "..., Estimasi Selesai: hh:mm\n"
        char *pos = strstr(buffer, "Estimasi Selesai: ");
        if (pos != NULL) {
            sscanf(pos, "Estimasi Selesai: %d:%d\n", &last_finish.jam, &last_finish.menit);
        }
    }

    fclose(fptr);
    return last_finish;
}

void title(){
	FILE *file = fopen("icon.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Gagal membuka file list_barang.txt.\n");
        return;
    }

    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
		printf(" %s", buffer);
    }
    printf("\n");

    fclose(file);
}