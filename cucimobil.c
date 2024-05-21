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

void tambah_mobil(int jenis_pelayanan, int golongan, int jenis_paket) {
    data_mobil *baru = (data_mobil *)malloc(sizeof(data_mobil));
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
    system("cls");
    printf("Jenis pelayanan:\n");
    printf("1. Fast track\n");
    printf("2. Reguler\n");
    printf("Pilih jenis pelayanan: ");
    scanf("%d", &jenis_pelayanan);
    
    system("cls");
    printf("Apakah anda ingin menggunakan layanan tambahan? (y/n): ");
    scanf(" %c", &c); 

    if(c == 'y' || c == 'Y') {
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
			printf("Pilihan tidak valid");
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
    printf("Nopol :");
    scanf("%[^\n]", &plat);
    
    bikin_struk(plat, golongan, jenis_paket, jenis_pelayanan);

    tambah_mobil(jenis_pelayanan, golongan, jenis_paket);
    space_to_continue();
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

                   
void bikin_struk(char *plat, int golongan, int jenis_paket, int jenis_pelayanan) {
    struk s;
    strcpy(s.plat, plat);
    s.golongan = golongan;
    s.jenis_paket = jenis_paket;
    s.jenis_pelayanan = jenis_pelayanan;

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

    // Input waktu kedatangan
    waktu_datang waktu;
    printf("Masukkan waktu kedatangan (Jam:Menit): ");
    scanf("%d:%d", &waktu.jam, &waktu.menit);

    printf("\t Struk: \n");
    printf("Nopol: %s\n", s.plat);
    printf("Golongan: %d\n", s.golongan);
    printf("Jenis paket: %d\n", s.jenis_paket);
    printf("Jenis pelayanan: %d\n", s.jenis_pelayanan);
    printf("Harga: %d\n", s.harga);
    printf("Waktu kedatangan: %02d:%02d\n", waktu.jam, waktu.menit);

    // Buka file untuk menulis
    FILE *file = fopen("struk.txt", "a");
    if (file == NULL) {
        printf("Gagal membuka file!\n");
        return;
    }

    // Tulis data ke file
    fprintf(file, "%s,%d,%d,%d,%d,%02d:%02d\n", s.plat, s.golongan, s.jenis_paket, s.jenis_pelayanan, s.harga, waktu.jam, waktu.menit);

    // Tutup file
    fclose(file);
}


void show_struk_from_file() {
    FILE *file = fopen("struk.txt", "r"); // Open file in read mode
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100]; // Assuming each line in the file is no longer than 100 characters
    printf("Struk Data:\n");
    while (fgets(line, sizeof(line), file) != NULL) {
        // Split the line into tokens based on the delimiter (comma in this case)
        char *plat = strtok(line, ",");
        int golongan = atoi(strtok(NULL, ","));
        int jenis_paket = atoi(strtok(NULL, ","));
        int jenis_pelayanan = atoi(strtok(NULL, ","));
        int harga = atoi(strtok(NULL, ","));
        char *waktu_kedatangan = strtok(NULL, ",");

        // Print the struk data
        printf("Nopol: %s, Golongan: %d, Jenis Paket: %d, Jenis Pelayanan: %d, Harga: %d, Waktu Kedatangan: %s\n", plat, golongan, jenis_paket, jenis_pelayanan, harga, waktu_kedatangan);
    }

    fclose(file); // Close the file
}

void space_to_continue() {
    printf("Tekan spasi untuk melanjutkan\n");
    while(getch() != ' ');
    // Loop until the user presses the space bar
}

// Fungsi untuk mencari data cucian berdasarkan nomor polisi
data_mobil *cari_mobil(char *plat) {
    // Cari pada antrian fast track
    data_mobil *current = fast[0].depan;
    while (current != NULL) {
        if (strcmp(current->plat, plat) == 0) {
            return current;
        }
        current = current->next;
    }

    // Cari pada antrian reguler
    current = reguler[0].depan;
    while (current != NULL) {
        if (strcmp(current->plat, plat) == 0) {
            return current;
        }
        current = current->next;
    }

    return NULL; // Data tidak ditemukan
}

// Fungsi untuk menghitung total harga cucian berdasarkan nomor polisi
int hitung_total_harga(char *plat) {
    data_mobil *mobil = cari_mobil(plat);
    if (mobil != NULL) {
        // Hitung total harga berdasarkan jenis paket dan golongan
        int harga = 0;
        if (mobil->golongan == 1) {
            harga += 50000;
        } else if (mobil->golongan == 2) {
            harga += 75000;
        } else if (mobil->golongan == 3) {
            harga += 100000;
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
    return -1; // Mobil tidak ditemukan
}

// Fungsi untuk menghapus data cucian dari antrian setelah proses checkout
void hapus_mobil(char *plat) {
    data_mobil *prev = NULL;
    data_mobil *current = fast[0].depan;
    while (current != NULL) {
        if (strcmp(current->plat, plat) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                fast[0].depan = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }

    prev = NULL;
    current = reguler[0].depan;
    while (current != NULL) {
        if (strcmp(current->plat, plat) == 0) {
            if (prev != NULL) {
                prev->next = current->next;
            } else {
                reguler[0].depan = current->next;
            }
            free(current);
            return;
        }
        prev = current;
        current = current->next;
    }
}

void checkout() {
    char plat[10];
    int jumlah_bayar;

    system("cls");
    printf("Masukkan nomor polisi: ");
    fflush(stdin);
    scanf("%[^\n]", plat);

    FILE *file = fopen("struk.txt", "r"); // Buka file dalam mode baca
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    int found = 0;
    while (fgets(line, sizeof(line), file) != NULL) { // Membaca setiap baris dari file
        char plat_file[10]; // Menyimpan nomor polisi dari file
        char *token = strtok(line, ",");
        strcpy(plat_file, token); // Menyalin nomor polisi dari file
        if (strcmp(plat, plat_file) == 0) { // Jika nomor polisi cocok
            found = 1;
            int golongan = atoi(strtok(NULL, ","));
            int jenis_paket = atoi(strtok(NULL, ","));
            int jenis_pelayanan = atoi(strtok(NULL, ","));
            int harga = atoi(strtok(NULL, ","));
            char *waktu_kedatangan = strtok(NULL, ",");

            printf("Nopol: %s, Golongan: %d, Jenis Paket: %d, Jenis Pelayanan: %d, Harga: %d, Waktu Kedatangan: %s\n", plat_file, golongan, jenis_paket, jenis_pelayanan, harga, waktu_kedatangan);

            // Input jumlah bayar
            printf("Masukkan jumlah bayar: ");
            scanf("%d", &jumlah_bayar);
            // Hitung kembalian
            int kembalian = jumlah_bayar - harga;
            if (kembalian >= 0) {
                printf("Kembalian: %d\n", kembalian);
                printf("Checkout berhasil.\n");
                fclose(file); // Tutup file sebelum menghapus struk
                hapus_struk_dari_file(plat); // Hapus struk dari file
                return; // Keluar dari fungsi setelah checkout berhasil
            } else {
                printf("Jumlah bayar kurang.\n");
                fclose(file); // Tutup file sebelum keluar dari fungsi
                return; // Keluar dari fungsi jika jumlah bayar kurang
            }
        }
    }

    if (!found) {
        printf("Nomor polisi tidak ditemukan.\n");
    }

    fclose(file); // Tutup file setelah selesai membaca
}

void hapus_struk_dari_file(const char *plat) {
    FILE *file = fopen("struk.txt", "r");
    FILE *temp = fopen("temp.txt", "w");

    if (file == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        char plat_file[10];
        char *token = strtok(line, ",");
        strcpy(plat_file, token);
        if (strcmp(plat, plat_file) != 0) {
            fprintf(temp, "%s", line); // Tulis baris ke file temp jika plat tidak cocok
        }
    }

    fclose(file);
    fclose(temp);

    remove("struk.txt"); // Hapus file asli
    rename("temp.txt", "struk.txt"); // Ganti nama file temp ke nama file asli
}

