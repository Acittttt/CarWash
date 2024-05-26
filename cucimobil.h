#ifndef CUCIMOBIL_H
#define CUCIMOBIL_H

typedef struct waktu_datang {
    int jam;
    int menit;
} waktu_datang;

typedef struct data_mobil {
    char plat[10];
    int golongan;
    int jenis_paket;
    int jenis_pelayanan;
    struct data_mobil *next;
} data_mobil;

typedef struct queue_mobil {
    data_mobil *depan;
    data_mobil *belakang;
} queue_mobil;

typedef struct struk {
    char plat[10];
    int golongan;
    int jenis_paket;
    int jenis_pelayanan;
    int harga;
    waktu_datang waktu;
    waktu_datang estimasi_selesai;
} struk;

// Function declarations
void mainmenu(int *pilihan);
void buat_queue();
void masuk_antrian(int *pilihan);
void show_queue(queue_mobil *q);
void checkout();
void show_struk_from_file();
void show_riwayat_from_file();
void space_to_continue();
int validasi_waktu_datang(int jam, int menit);
void sesuaikan_waktu_istirahat(waktu_datang *waktu);
void bikin_struk(char *plat, int golongan, int jenis_paket, int jenis_pelayanan, waktu_datang waktu);
void save_struk_to_file(struk s);
void save_riwayat_to_file(struk s);
data_mobil *cari_mobil(char *plat);
int hitung_total_harga(char *plat);
void hapus_mobil(char *plat);
void hapus_struk_dari_file(const char *plat);
waktu_datang hitung_estimasi_selesai(waktu_datang waktu, int jenis_pelayanan, int golongan);

extern queue_mobil fast[1];
extern queue_mobil reguler[1];

#endif
