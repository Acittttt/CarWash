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
                printf("Antrian Fast Track:\n");
                show_queue(&fast[0]);
                printf("Antrian Reguler:\n");
                show_queue(&reguler[0]);
                space_to_continue();
                break;
            }
            case 3:{
                checkout();
                space_to_continue();
                break;
            }
            case 4:{
                show_struk_from_file();
                space_to_continue();
                break;
            }
            case 5:{
                printf("Terima kasih\n");
                break;
            }
            default:
                printf("Pilihan tidak valid\n");
                space_to_continue();
                break;
        }
    }
    return 0;
}
