#ifndef MENU_H
#define MENU

#include "Display.h"

bool keluarAdmin = false, 
     keluar = false;

//------------------------------------------ Menus ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- 
void MenuServisAdmin() {
    string pilihan;
            cout << R"(====== Services ======
Pilih menu?
1. Semua Servis Singkat
2. Servis Baru
3. Selesaikan Pekerjaan
4. Riwayat Kerja Montir
5. Ganti Tanggal Ambil

Pilihan: )";
    cin >> pilihan;
    cin.ignore();
    system("cls");
    if (pilihan == "1") AntrianDisplay();
    else if (pilihan == "2") NewService();
    else if (pilihan == "3") DisplayFinishJob();
    else if (pilihan == "4") DisplayJobsHistory();
    else if (pilihan == "5") DisplayReschedule();
    else cout << "Pilihan tidak valid!\n\n";
}

void MenuAdmin() {
    system("cls");
    string pilihan;
    cout << R"(====== Welcome To Lognuts ======
Pilih Menu?

1. Servis
2. Pelanggan Baru
3. Montir Baru
4. Keluar

Pilihan : )";
    cin >> pilihan;
    cin.ignore();
    system("cls");
    if (pilihan == "1") MenuServisAdmin();
    else if (pilihan == "2") 
        if (!NewCustomer(true))
            cout << "\nPelanggan telah terdaftar\n\n";
    else if (pilihan == "3") NewMontir();
    else if (pilihan == "4") {
        keluarAdmin = true;
        return;
    }
    else cout << "Pilihan tidak valid!\n\n";
    
    cout << "Press enter to go back...";
    cin.ignore();
}

void MenuCustomer(string namaCustomer) {
    Customer* curCustomer = headCustomer;
    while(curCustomer != NULL) { //cek customer yang mana
        if (curCustomer->nama == namaCustomer) break;
        curCustomer = curCustomer->next;
    }

    system("cls");
    string pilihan;
    cout << "====== Welcome " << namaCustomer << " ======";
    cout << R"(
Pilih menu!

1. Antrian Anda
2. Booking Servis
3. Batalkan Servis
4. Undo Pembatalan
5. Riwayat Servis
6. Keluar

Pilihan: )";
    cin >> pilihan;
    cin.ignore();
    cout << endl;
    
    if (pilihan == "1") AntrianDisplay(curCustomer);
    else if (pilihan == "2") NewService(curCustomer);
    else if (pilihan == "3") {
        CancelService(curCustomer);
        return;
    }
    else if (pilihan == "4") UndoCancelService(curCustomer);
    else if (pilihan == "5") RiwayatCustomer(curCustomer);
    else if (pilihan == "6") {
        while (headUndo != NULL) { //reset list Undo
        Service* temp = headUndo;
        headUndo = headUndo->next;
        delete temp;
    }
        keluar = true;
        return;
    }
    else cout << "Pilihan tidak valid!\n\n";

    cout << "Press enter to go back...";
    cin.get();
}

#endif