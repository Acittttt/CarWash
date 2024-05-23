#include <stdio.h>
#include <stdlib.h>
#include "cucimobil.h"

queue_mobil fast[1];
queue_mobil reguler[1];

void mainmenu(int *pilihan) {
    system("cls");
    printf("SELAMAT DATANG DI TEMPAT CUCI MOBIL ...\n");
    printf("1. Masuk antrian\n");
    printf("2. Lihat antrian\n");
    printf("3. Checkout\n");
    printf("4. Riwayat\n");
    printf("5. Keluar\n");
    printf("Masukan pilihan: ");
    scanf("%d", pilihan);
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

void masuk_antrian(int *pilihan) {
    int jenis_paket = 0, jenis_pelayanan = 0, golongan = 0;
    char c;
    char plat[10];
    waktu_datang waktu;

    system("cls");
    printf("Jenis pelayanan:\n");
    printf("1. Fast track\n");
    printf("2. Reguler\n");
    printf("Pilih jenis pelayanan: ");
    scanf("%d", &jenis_pelayanan);

    system("cls");
    printf("Apakah anda ingin menggunakan layanan tambahan? (y/n): ");
    scanf(" %c", &c);

    if (c == 'y' || c == 'Y') {
        system("cls");
        printf("Layanan tambahan:\n");
        printf("1. Interior\n");
        printf("2. Coating\n");
        printf("3. Cuci mesin\n");
        printf("4. Paket lengkap\n");
        printf("Pilih layanan tambahan anda: ");
        scanf("%d", &jenis_paket);
    } else if (c == 'n' || c == 'N') {
        printf("Anda tidak menggunakan layanan tambahan\n");
    } else {
        printf("Pilihan tidak valid\n");
        return;
    }

    system("cls");
    printf("Golongan mobil\n");
    printf("1. Golongan 1 : sedan, lcgc, city car, hatchback\n");
    printf("2. Golongan 2 : mpv\n");
    printf("3. Golongan 3 : suv, minibus\n");
    printf("Pilih golongan mobil anda: ");
    scanf("%d", &golongan);
    printf("Masukkan nopol mobil anda\n");
    fflush(stdin);
    printf("Nopol: ");
    scanf("%[^\n]", plat);

    printf("Masukkan waktu kedatangan (Jam:Menit): ");
    scanf("%d:%d", &waktu.jam, &waktu.menit);

    if (!validasi_waktu_datang(waktu.jam, waktu.menit)) {
        printf("Waktu kedatangan di luar jam operasional (9:00 - 15:00). Tidak bisa menambahkan antrian.\n");
        space_to_continue();
        return;
    }

    sesuaikan_waktu_istirahat(&waktu);
    bikin_struk(plat, golongan, jenis_paket, jenis_pelayanan, waktu);
    tambah_mobil(jenis_pelayanan, golongan, jenis_paket, plat, waktu);
    space_to_continue();
}

waktu_datang hitung_estimasi_selesai(waktu_datang waktu, int jenis_pelayanan, int golongan) {
    waktu_datang selesai = waktu;
    int durasi = 0;

    // Asumsi durasi berdasarkan jenis pelayanan dan golongan
    if (jenis_pelayanan == 1) { // Fast track
        if (golongan == 1) durasi = 30;
        else if (golongan == 2) durasi = 45;
        else if (golongan == 3) durasi = 60;
    } else if (jenis_pelayanan == 2) { // Reguler
        if (golongan == 1) durasi = 60;
        else if (golongan == 2) durasi = 90;
        else if (golongan == 3) durasi = 120;
    }

    selesai.menit += durasi;
    if (selesai.menit >= 60) {
        selesai.jam += selesai.menit / 60;
        selesai.menit %= 60;
    }

    if (selesai.jam == 12 && selesai.menit <= 15) {
        // Jika estimasi waktu selesai tidak lebih dari pukul 12:15, kembalikan estimasi tersebut
        return selesai;
    } else {
        // Jika melewati waktu 12:15, set waktu kedatangan menjadi 13:00
        selesai.jam = 13;
        selesai.menit = 0;
        return selesai;
    }
}

int validasi_waktu_datang(int jam, int menit) {
    if (jam < 9 || (jam >= 15 && menit > 0) || jam > 15) {
        return 0; // Tidak valid, di luar jam operasional
    }
    return 1; // Valid
}

void sesuaikan_waktu_istirahat(waktu_datang *waktu) {
    if (waktu->jam == 12 || (waktu->jam == 13 && waktu->menit == 0)) {
        waktu->jam = 13;
        waktu->menit = 0; // Set waktu kedatangan ke 13:00 jika datang pada jam istirahat
    }
}

void buat_queue() {
	int i;
    for (i = 0; i < 1; i++) {
        fast[i].depan = NULL;
        fast[i].belakang = NULL;
        reguler[i].depan = NULL;
        reguler[i].belakang = NULL;
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
        printf("Golongan:  %d, Jenis Pelayanan: %d\n", current->golongan, current->jenis_paket);
        current = current->next;
    }
}

                   
void bikin_struk(char *plat, int golongan, int jenis_paket, int jenis_pelayanan, waktu_datang waktu) {
    struk s;
    strcpy(s.plat, plat);
    s.golongan = golongan;
    s.jenis_paket = jenis_paket;
    s.jenis_pelayanan = jenis_pelayanan;
    s.waktu = waktu;

    // Hitung harga berdasarkan golongan dan jenis paket
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

    // Hitung estimasi waktu selesai
    s.estimasi_selesai = hitung_estimasi_selesai(s.waktu, s.jenis_pelayanan, s.golongan);

    printf("\t Struk: \n");
    printf("Nopol: %s\n", s.plat);
    printf("Golongan: %d\n", s.golongan);
    printf("Jenis paket: %d\n", s.jenis_paket);
    printf("Jenis pelayanan: %d\n", s.jenis_pelayanan);
    printf("Harga: %d\n", s.harga);
    printf("Waktu kedatangan: %02d:%02d\n", s.waktu.jam, s.waktu.menit);
    printf("Estimasi selesai: %02d:%02d\n", s.estimasi_selesai.jam, s.estimasi_selesai.menit);

    // Buka file untuk menulis
    FILE *file = fopen("struk.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    // Tulis data ke file
    fprintf(file, "%s,%d,%d,%d,%d,%02d:%02d,%02d:%02d\n", s.plat, s.golongan, s.jenis_paket, s.jenis_pelayanan, s.harga, s.waktu.jam, s.waktu.menit, s.estimasi_selesai.jam, s.estimasi_selesai.menit);

    // Tutup file
    fclose(file);
}

void save_struk_to_file(struk s) {
    FILE *file = fopen("struk.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    fprintf(file, "%s,%d,%d,%d,%d,%02d:%02d,%02d:%02d\n", s.plat, s.golongan, s.jenis_paket, s.jenis_pelayanan, s.harga, s.waktu.jam, s.waktu.menit, s.estimasi_selesai.jam, s.estimasi_selesai.menit);
    fclose(file);
}

void show_struk_from_file() {
    FILE *file = fopen("struk.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void space_to_continue() {
    printf("Tekan spasi untuk melanjutkan\n");
    while(getch() != ' ');
    // Loop until the user presses the space bar
}

// Fungsi untuk mencari data cucian berdasarkan nomor polisi
data_mobil *cari_mobil(char *plat) {
    data_mobil *current;
    int i = 0;
    while (i < 1) {
        current = fast[i].depan;
        while (current != NULL) {
            if (strcmp(current->plat, plat) == 0) {
                return current;
            }
            current = current->next;
        }

        current = reguler[i].depan;
        while (current != NULL) {
            if (strcmp(current->plat, plat) == 0) {
                return current;
            }
            current = current->next;
        }
        i++;
    }
    return NULL;
}

// Fungsi untuk menghitung total harga cucian berdasarkan nomor polisi
int hitung_total_harga(char *plat) {
    data_mobil *mobil = cari_mobil(plat);
    if (mobil == NULL) {
        printf("Mobil dengan nopol %s tidak ditemukan\n", plat);
        return 0;
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
    int i = 0;
    while (i < 1) {
        data_mobil *current = fast[i].depan;
        data_mobil *prev = NULL;
        while (current != NULL) {
            if (strcmp(current->plat, plat) == 0) {
                if (prev == NULL) {
                    fast[i].depan = current->next;
                } else {
                    prev->next = current->next;
                }
                if (current == fast[i].belakang) {
                    fast[i].belakang = prev;
                }
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }

        current = reguler[i].depan;
        prev = NULL;
        while (current != NULL) {
            if (strcmp(current->plat, plat) == 0) {
                if (prev == NULL) {
                    reguler[i].depan = current->next;
                } else {
                    prev->next = current->next;
                }
                if (current == reguler[i].belakang) {
                    reguler[i].belakang = prev;
                }
                free(current);
                return;
            }
            prev = current;
            current = current->next;
        }
        i++;
    }
}

void checkout() {
    char plat[10];
    printf("Masukkan nopol mobil: ");
    scanf("%s", plat);

    int total_harga = hitung_total_harga(plat);
    if (total_harga == 0) {
        printf("Mobil tidak ditemukan\n");
        return;
    }

    printf("Total harga: %d\n", total_harga);
    printf("Checkout berhasil\n");

    hapus_mobil(plat);
    hapus_struk_dari_file(plat);
}

void hapus_struk_dari_file(const char *plat) {
    FILE *file = fopen("struk.txt", "r");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Gagal membuka file!\n");
        fclose(file);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        if (strstr(line, plat) == NULL) {
            fputs(line, temp);
        }
    }

    fclose(file);
    fclose(temp);

    remove("struk.txt");
    rename("temp.txt", "struk.txt");
}
