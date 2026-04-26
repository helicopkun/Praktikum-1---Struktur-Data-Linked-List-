#ifndef FILES_H
#define FILES_H

#include "Linked_List.h"
#include <fstream>

// Files + Linked_list Helper

void ReadFiles() {
        ifstream data_customer("../data_customer.txt"); // FIFO
    string namaC, umur, gender, nomor_teleponC, alamat, kosong1;
    while (getline(data_customer, namaC) && namaC != "") {
        getline(data_customer, umur);
        getline(data_customer, gender);
        getline(data_customer, nomor_teleponC);
        getline(data_customer, alamat);
        getline(data_customer, kosong1);
        
        Customer *baruCustomer = new Customer;

        baruCustomer->nama = namaC;
        baruCustomer->umur = umur;
        baruCustomer->gender = gender;
        baruCustomer->nomor_telepon = nomor_teleponC;
        baruCustomer->alamat = alamat;
        if (headCustomer == NULL) {
            headCustomer = tailCustomer = baruCustomer;
        } else {
            baruCustomer->prev = tailCustomer;
            tailCustomer->next = baruCustomer;
            tailCustomer = baruCustomer;
        }
    }
    data_customer.close();

    //link data servis -> data customer
    ifstream data_DueService("../data_DueService.txt"); //FIFO - queue
    string namaSdue, model_mobil_due, merek_mobil_due, deskripsi_kendala_due, nama_montir_due, tanggaldue, kepentingan, kosong3;
    while (getline(data_DueService, namaSdue) && namaSdue != "") {  
        getline(data_DueService, model_mobil_due);  
        getline(data_DueService, merek_mobil_due);
        getline(data_DueService, deskripsi_kendala_due);
        getline(data_DueService, nama_montir_due);
        getline(data_DueService, tanggaldue);
        getline(data_DueService, kepentingan);
        getline(data_DueService, kosong3);

        Service *newDue = new Service;
        
        newDue->model_mobil = model_mobil_due;
        newDue->merek_mobil = merek_mobil_due;
        newDue->deskripsi_kendala = deskripsi_kendala_due;
        newDue->nama_montir = nama_montir_due;
        newDue->tanggal = tanggaldue;
        newDue->kepentingan = kepentingan;

        Customer* cur = headCustomer; //cur = cursor customer 
        while(cur != NULL){
            if (cur->nama == namaSdue) {
                AddDueList(newDue, cur);
                break;
            }
            cur = cur->next;
        }
    }
    data_DueService.close();

    ifstream data_DoneService("../data_DoneService.txt"); //LIFO - stack
    string namaSdone, model_mobil_done, merek_mobil_done, deskripsi_kendala_done, nama_montir_done, tanggaldone, kosong2;
    while (getline(data_DoneService, namaSdone) && namaSdone != "") {
        getline(data_DoneService, model_mobil_done);    
        getline(data_DoneService, merek_mobil_done);
        getline(data_DoneService, deskripsi_kendala_done);
        getline(data_DoneService, nama_montir_done);
        getline(data_DoneService, tanggaldone);
        getline(data_DoneService, kosong2);
        
        Service *newDone = new Service;
        
        newDone->model_mobil = model_mobil_done;
        newDone->merek_mobil = merek_mobil_done;
        newDone->deskripsi_kendala = deskripsi_kendala_done;
        newDone->nama_montir = nama_montir_done;
        newDone->tanggal = tanggaldone;

        Customer* cur = headCustomer; //cur = cursor customer
        while(cur != NULL){
            if (cur->nama == namaSdone) {
                AddDoneList(newDone, cur);
                break;
            }
            cur = cur->next;
        }
    }
    data_DoneService.close();

}

void NewMontirFile(string nama) {
    ofstream nama_montir ("../Nama_Montir.txt", ios::app);
    nama_montir << nama << endl;
    nama_montir.close();
}

void AddCustomerFile(Customer* customer) {
    if (headCustomer == NULL) {
        headCustomer = tailCustomer = customer;
    } else {
        customer->prev = tailCustomer;
        tailCustomer->next = customer;
        tailCustomer = customer;
    }
    ofstream data_customer("../data_customer.txt", ios::app);
    data_customer 
    << customer->nama << endl 
    << customer->umur << endl 
    << customer->gender << endl 
    << customer->nomor_telepon << endl 
    << customer->alamat << endl << endl;
    data_customer.close();
}

void AddDueFile(Service* baru, Customer* Pelanggan){
    AddDueList(baru, Pelanggan);

    ofstream data_DueService("../data_DueService.txt", ios::app);
    data_DueService 
    << baru->dataCustomer->nama << endl 
    << baru->model_mobil << endl 
    << baru->merek_mobil << endl 
    << baru->deskripsi_kendala << endl 
    << baru->nama_montir << endl
    << baru->tanggal << endl 
    << baru->kepentingan << endl << endl;
    data_DueService.close();
}

void RewriteDue() {
    ofstream data_DueService("../data_DueService.txt", ios::trunc); //rewrite file due
    Service* cur = headHistoryDue;
    while (cur != NULL) {
        data_DueService << cur->dataCustomer->nama << endl
            << cur->model_mobil << endl
            << cur->merek_mobil << endl
            << cur->deskripsi_kendala << endl
            << cur->nama_montir << endl
            << cur->tanggal << endl
            << cur->kepentingan << endl << endl;
        cur = cur->allnext; // Jalan ke servis berikutnya di antrean
    }
    data_DueService.close();
}

void RemoveDue(Service* servis){
    ReLinkDue(servis);
    RewriteDue();
}

void AddDoneFile(Service* selesai){
    AddDoneList(selesai, selesai->dataCustomer);

    ofstream data_DoneService ("../data_DoneService.txt", ios::app); //terbaru di akhir data
    data_DoneService << 
    selesai->dataCustomer->nama << endl <<
    selesai->model_mobil << endl <<
    selesai->merek_mobil << endl <<
    selesai->deskripsi_kendala << endl <<
    selesai->nama_montir << endl <<
    selesai->tanggal << endl << endl;
}

void ReadAllMontir() { //baca semua nama montir dalam file dan di simpan ke linkedlist
    ResetMontir();
    ifstream data_montir ("../Nama_Montir.txt");
    string namaMontir, space;
    while (getline(data_montir, namaMontir) && namaMontir != "") {
        getline(data_montir, space);
        NewMontirToList(namaMontir); //tambah montir
    }
    data_montir.close();
}

#endif