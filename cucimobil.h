#include <stdio.h>
#include <string.h>
#include <malloc.h>
#ifndef CUCIMOBIL_H
#define CUCIMOBIL_H

typedef struct{
	int jam;
	int menit;
}waktu_datang;

typedef struct {
	char plat[10];
    int golongan;
    int jenis_paket;
    int jenis_pelayanan;
    struct data_mobil *next;
} data_mobil;

typedef struct {
	char plat[10];
	int golongan;
	int jenis_paket;
	int jenis_pelayanan;
	int harga;
	waktu_datang waktu;
	waktu_datang estimasi_selesai;
}struk;

typedef struct {
    data_mobil *depan;
    data_mobil *belakang;
} queue_mobil;

queue_mobil fast[1];
queue_mobil reguler[1];

void mainmenu(int *pilihan);
void masuk_antrian(int *pilihan);
void tambah_mobil(int jenis_pelayanan, int golongan, int jenis_paket, char *plat, waktu_datang waktu);
void space_to_continue();
void buat_queue();
void show_queue(queue_mobil *q);
void bikin_struk(char *plat, int golongan, int jenis_paket, int jenis_pelayanan, waktu_datang waktu);
void save_struk_to_file(struk s);
void show_struk_from_file();
data_mobil *cari_mobil(char *plat);
int hitung_total_harga(char *plat);
void hapus_mobil(char *plat);
void checkout();
void hapus_struk_dari_file(const char *plat);
void space_to_continue();
int validasi_waktu_datang(int jam, int menit);
void sesuaikan_waktu_istirahat(waktu_datang *waktu);
waktu_datang hitung_estimasi_selesai(waktu_datang waktu, int jenis_pelayanan, int golongan);

#endif
