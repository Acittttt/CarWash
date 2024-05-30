#include <stdio.h>
#include "cucimobil.h"

// Main function
int main(){
	int id;
    int pilih = 0;
    buat_queue();
    while (pilih != 5) {
        mainmenu(&pilih);
        switch (pilih) {
            case 1:{
                masuk_antrian(&pilih);
                break;
            }
            case 2:{
            	system("cls");
            	title();
                printf("\nAntrian Mobil:\n");
				show_struk_from_file();
                enter_to_continue();
                break;
            }
            case 3:{
            	system("cls");
                checkout();
                break;
            }
            case 4:{
            	system("cls");
            	title();
                show_riwayat_from_file();
                enter_to_continue();
                break;
            }
            case 5:{
            	system("cls");
                printf("Terima kasih\n");
                break;
            }
            default:
                printf("Pilihan tidak valid\n");
                enter_to_continue();
                fflush(stdin);
                break;
        }
    }
    return 0;
}
