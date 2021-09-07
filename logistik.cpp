#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

struct pelanggan{
    char nama [255]; // nama pelanggan
    char destinasi[255]; // lokasi tujuan
    char nomer[100]; // nomor telepon
};

struct barang {
    char barang [100]; // nama barang
    int n;  // jumlah barang 
    float panjang; //panjang barang
    double berat; // berat barang
    char kirim; // pemilihan cara mengirim barang
};

struct penerima{
    char nama[255];
    long long int telp[100];
};

//menunjuk ke suatu posisi x dan y di console
void gotoxy(int x, int y){
    COORD P;
    P.X = 2*x;
    P.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), P);
}

//menginput nama pelanggan dan no pelanggan, lalu dimasukkan ke database (pelanggan.txt)
void dataPelanggan(){

    struct pelanggan plg;
    Sleep(500);

    printf("Masukkan nama Anda: ");
    scanf("%s", &plg.nama);
    printf("Masukkan destinasi Anda: ");
    scanf("%s", &plg.destinasi);
    printf("Masukkan Nomer telepon: ");
    scanf("%s", &plg.nomer);

    // verifikasi nomer biar ga ngasal
    if(strlen(plg.nomer) <= 12 && strlen(plg.nomer) >=10 && 
        plg.nomer[0] == '0' && plg.nomer[1] == '8'){

        printf("wait....\n");
        Sleep(500);
        printf("\n");

        printf("%s telah ditambahkan dengan nomor telepon %s\n", plg.nama, plg.nomer);
        printf("Destinasi yang dituju: %s\n", plg.destinasi);

    FILE *fileplg = fopen("./pelanggan.txt", "a"); // menyimpan data disebuah file txt
    fprintf(fileplg, "%s$%s$%s\n", plg.nama, plg.destinasi, plg.nomer);
    fclose(fileplg);

    } else{
        printf("Nomor telepon anda salah!\n");
    }

}

// untuk membaca data pelanggan
void profil(){
    printf("wait....\n");
    Sleep(500);

    FILE *fileplg = fopen("./pelanggan.txt", "r");
    struct pelanggan plg;
    while(fscanf(fileplg, "%[^$]$%[^$]$%s\n", plg.nama, plg.destinasi,plg.nomer) != EOF){

        printf("Nama: %s\n", plg.nama);
        printf("Destinasi: %s\n", plg.destinasi);
        printf("Nomor: %s\n", plg.nomer);
        printf("\n");
    }
    
    char udah = 'B';
    printf("(U)dahan\n");
    printf("Input: ");
    do{
        scanf("%c", &udah);
    } while (udah != 'U');
}

//menginput nama barang, jumlah barang, dan berat barang, lalu dimasukkan ke database (barang.txt)
void dataBarang(){
    printf("wait....\n");
    Sleep(500);

    system("CLS");

    struct barang brg;
    printf("Ongkir = Rp.10.000/kg\n");
    printf("\n");

    printf("Masukkan Jenis Barang: ");
    scanf("%s", &brg.barang);
    printf("Masukkan Jumlah Barang: ");
    scanf("%d", &brg.n);
    printf("Berat Barang(dalam Kg): ");
    scanf("%lf", &brg.berat);
    printf("Panjang Barang (dalam m): ");
    scanf("%f", &brg.panjang);

    system("CLS");

    printf("Pilih jangka waktu pengiriman (Ketik huruf lain untuk pengiriman normal)\n");
    printf("[S]uper cepat (1 hari) + Rp.20000\n");
    printf("[C]epat (2-4 hari) + Rp.10000\n");
    printf("[D]ah santai aja (14 hari) lebih hemat Rp.5000\n");
    printf("Input: ");
    scanf("%s", &brg.kirim); // pemilihan kecepatan pengiriman
    
    printf("wait....\n");
    Sleep(500); 
    
    printf("Jenis barang : %s\n", brg.barang);
    printf("Jumlah barang: %d\n", brg.n);
    printf("Berat barang: %.3lf kg\n", brg.berat);
    printf("Panjang barang: %.2f m\n", brg.panjang);
    
    int harga; // menentukan harga ongkir
    if(brg.kirim == 'S' || brg.kirim == 's'){
        harga = brg.berat * 10000 + 20000;
    } else if(brg.kirim == 'C' || brg.kirim == 'c'){
        harga = brg.berat * 10000 + 10000;
    } else if (brg.kirim == 'D' || brg.kirim == 'd'){
         harga = brg.berat * 10000 - 5000;
    } else{
       harga = brg.berat * 10000;
    }

    system("CLS");

    // harga total
    (brg.n <= 5) ? printf("Harga total: Rp. %d\n", harga + brg.n * 5000) : printf("Harga total: Rp. %d\n", harga + brg.n * 7000 ); 

    srand(time(NULL)); // generate random number
    printf("Nomer pesanan anda: %d\n", rand()*2021); // to give 8 digits number
    printf("Jangan sampai lupa!\n");

    FILE *fileplg = fopen("./barang.txt", "a"); // menyimpan data disebuah file txt
    fprintf(fileplg, "%s$%d$%.3lf$%f\n", brg.barang, brg.n, brg.berat, brg.panjang);
    fclose(fileplg);

    printf("\n");
    char udah = 'B';
    printf("(U)dahan\n");
    printf("Input: ");
    do{
        scanf("%c", &udah);
    } while (udah != 'U');
}

// untuk melihat data barang
void lihatbarang(){

    printf("wait....\n");
    Sleep(500);
    system("CLS");

    FILE *fileplg = fopen("./barang.txt", "r");
    struct barang brg;

    while(fscanf(fileplg, "%[^$]$%d$%lf$%f\n", brg.barang, &brg.n, &brg.berat, &brg.panjang) != EOF){
        printf("Jenis barang: %s\n", brg.barang);
        printf("Jumlah barang: %d\n", brg.n);
        printf("Berat barang: %.3lf kg\n", brg.berat);
        printf("Panjang barang: %.2f m\n", brg.panjang);
        printf("\n");
    }

    char udah = 'B';
    printf("(U)dahan\n");
    printf("Input: ");
    do{
        scanf("%c", &udah);
    } while (udah != 'U');
}

// untuk mencari barang kita
struct barang caribarang(){
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);

    printf("wait....\n");
    Sleep(500);

    system("CLS");

    char name[100];
    printf("Masukkan nama barang yang Anda cari: ");
    scanf("%s", &name);
    FILE *fileplg = fopen("./barang.txt", "r");
    struct barang brg;

    while(fscanf(fileplg, "%[^$]$%d$%lf$%f\n", brg.barang, &brg.n, &brg.berat, &brg.panjang) != EOF){
        if (strcmp(name, brg.barang) == 0){
            printf("wait....\n");
            Sleep(500);
            system("CLS");
            SetConsoleTextAttribute(hand, 11);
            printf("%s ditemukan\n", brg.barang);
            SetConsoleTextAttribute(hand, 2);

            int waktu = 3;
            printf("\n");
            printf("Exitting in ");
            while(waktu--){
                gotoxy(6, 2);
                printf("%d", waktu);
                Sleep(1000);
            }

            return brg;
        } 
    }    
    printf("wait....\n");
    Sleep(500);
    system("CLS");

    SetConsoleTextAttribute(hand, 12);
    printf("Barang tidak ditemukan\n");
    SetConsoleTextAttribute(hand, 2);

    printf("\n");
    char udah = 'B';
    printf("(U)dahan\n");
    printf("Input: ");
    do{
        scanf("%c", &udah);
    } while (udah != 'U');

    struct barang temp;
    return temp;
}

// untuk memasukkan data penerima
void penerima(){

    printf("wait....\n");
    Sleep(500);

    char hasil[255];
    struct penerima pnr;
    printf("Masukkan nama penerima Anda: ");
    scanf("%s", &pnr.nama);
    printf("Masukkan nomor telepon penerima: ");
    scanf("%lld", &pnr.telp);
    FILE *fileplg = fopen("./penerima.txt", "a");
    fprintf(fileplg, "%s#%lld\n", pnr.nama, pnr.telp);
    fclose(fileplg);

    printf("wait....\n");
    Sleep(500);

}

// untuk melihat data penerima
void lihatpenerima(){

    printf("wait....\n");
    Sleep(500);

    FILE *fileplg = fopen("./penerima.txt", "r");
    struct penerima pnr;
    
    while(fscanf(fileplg, "%[^#]#%lld\n", pnr.nama, &pnr.telp) != EOF){
        printf("Nama Penerima: %s\n", pnr.nama);
        printf("No.telepon: %lld\n", pnr.telp);
        printf("\n");
    }

    printf("\n");
    char udah = 'B';
    printf("(U)dahan\n");
    printf("Input: ");
    do{
        scanf("%c", &udah);
    } while (udah != 'U');

}

int main(){

    // judul
    HANDLE hand = GetStdHandle(STD_OUTPUT_HANDLE);
    system("CLS");
    gotoxy(0, 2);

    SetConsoleTextAttribute(hand, 14);
    printf("CCCC   OOOO   BBB    OOOO   X  X");
    gotoxy(0, 3);
    printf("C      O  O   B  B   O  O    XX");
    gotoxy(0, 4);
    printf("C      O  O   BBB    O  O    XX");
    gotoxy(0, 5);
    printf("C      O  O   B  B   O  O    XX");
    gotoxy(0, 6);
    printf("CCCC   OOOO   BBB    OOOO   X  X");
    printf("\n");
    Sleep(1000);
    system("CLS");

    // warna dan pembukaan
    SetConsoleTextAttribute(hand, 2);

    char menu; // halaman utama
    do{
        system("CLS");
        puts("Silakan memilih salah satu menu dibawah (ditulis dalam huruf kapital)");
        puts("(M)enu Utama");
        puts("(P)rofil");
        puts("(B)arang Kamu");
        puts("(U)dahan");
        printf("\n");
        printf("Input: ");
        scanf("%s", &menu);
        printf("\n");
        system("CLS");

        switch(menu){
            case 'M':{
                char choice;
                Sleep(500);

                do{
                    system("CLS");
                    printf("Pilihlah menu yang anda inginkan\n");
                    puts("(D)ata Pelanggan");
                    puts("(A)dd Barang");
                    puts("(I)nfo Barang");
                    puts("(U)dahan");
                    printf("\n");
                    printf("Input: ");
                    scanf("%s", &choice);
                    system("CLS");
                    switch(choice){
                        case 'D':{
                            Sleep(500);
                            char person;
                            do{
                                system("CLS");
                                printf("Pilihlah menu yang anda inginkan\n");
                                puts("(N)girim");
                                puts("(P)enerima");
                                puts("(U)dahan");
                                printf("\n");
                                printf("Input: ");
                                scanf("%s", &person);
                                system("CLS");

                                switch(person){
                                    case 'N':{
                                        dataPelanggan();
                                        break;
                                    } 
                                    case 'P':{
                                        penerima();
                                        break;
                                    }   
                                    case 'U':{
                                        printf("Wait......\n");
                                        Sleep(500);
                                        break;
                                    }
                                    default:{
                                        puts("You are in direct violation of Code 12, please refer to the violation code textbook.");
                                        break;
                                    }  
                                
                                }
                            
                            } while (person != 'U'); 
                            
                            break; // case break in D
                        } 
                
                        case 'A':{
                            dataBarang();
                            break;
                        }

                        case 'I':{
                            lihatbarang();
                            break;
                        }

                        case 'U':{
                            printf("Wait......\n");
                            Sleep(500);
                            break;
                        }
                        default:{
                            puts("You are in direct violation of Code 12, please refer to the violation code textbook.");
                            break;
                        }
                    }
                } while (choice != 'U'); 

                break; // case break in M
            }
            case 'P':{
                char profil1;
                Sleep(500);
                do{
                    system("CLS");
                    printf("Pilihlah menu yang anda inginkan\n");
                    puts("(N)girim");
                    puts("(P)enerima");
                    puts("(U)dahan");
                    printf("\n");
                    printf("Input: ");
                    scanf("%s", &profil1);
                    printf("\n");
                    system("CLS");

                switch(profil1){
                    case 'N':{
                        profil();
                        break;
                    }
                    case 'P':{
                        lihatpenerima();
                        break;
                    }
                    case 'U':{
                        printf("wait....\n");
                        Sleep(500);
                    }
                }

            }while (profil1 != 'U'); 
                
                break; // case break in P
            }
            case 'B':{
                struct barang temp = caribarang();
                // struct barang temp = caribarang();
                // printf("%s ditemukan\n", temp.barang);
                break;
            }
            case 'U':{
                printf("Exiting.....");
                Sleep(1000);
                system("CLS");
                break;
            }
            default:{
                puts("You are in direct violation of Code 12, please refer to the violation code textbook.");
                break;
            }

            
        }
    } while (menu != 'U');
    

    return 0;
}