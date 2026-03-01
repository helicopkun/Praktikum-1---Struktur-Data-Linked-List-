#include <iostream>
#include <fstream>
using namespace std;

struct Service;
struct Customer;

struct Customer {
    string nama, umur, gender, nomor_telepon, alamat;
    Service* HeadService = NULL;
    Customer* next = NULL;
    Customer* prev = NULL;
}; //rupanya bisa deklarasi NULL dari awal bruh

struct Service {
    string model_mobil, merek_mobil, deskripsi_kendala, nama_montir;
    Customer* dataCustomer = NULL;
    Service* next = NULL; //servis per customer
    Service* allnext = NULL; //semua servis 
};

Customer* headCustomer = NULL;
Customer* tailCustomer = NULL;
Service *headHistory = NULL;
string namaInput;

void NewCustomer() { //tambah di belakang list - queue
    Customer *baruCustomer = new Customer;
    
    cout << "No Telp Pelanggan: ";
    getline(cin, baruCustomer->nomor_telepon);
    cout << "Alamat: ";
    getline(cin, baruCustomer->alamat);
    cout << "Umur: ";
    getline(cin, baruCustomer->umur);
    cout << "Gender: ";
    getline(cin, baruCustomer->gender);

    if (headCustomer == NULL) {
        headCustomer = tailCustomer = baruCustomer;
    } else {
        baruCustomer->prev = tailCustomer;
        tailCustomer->next = baruCustomer;
        tailCustomer = baruCustomer;
    }
    cout << "\n\nPelanggan baru telah terdaftar dan servis berhasil dicatat\n\n\n";

    ofstream data_customer("data_customer.txt", ios::app);
    data_customer << namaInput << endl 
    << baruCustomer->umur << endl 
    << baruCustomer->gender << endl 
    << baruCustomer->nomor_telepon << endl 
    << baruCustomer->alamat << endl;
    data_customer.close();
}

void NewService() { //tambah di awal list - stack
    Service *baruService = new Service;

    cout << "Model Mobil: ";
    getline(cin, baruService->model_mobil);
    cout << "Merek Mobil: ";
    getline(cin, baruService->merek_mobil);
    cout << "Kendala: ";
    getline(cin, baruService->deskripsi_kendala);
    cout << "Montir | Suby | Farhan | Dimas | Aldo | : ";
    getline(cin, baruService->nama_montir);
    cout << "Nama Pelanggan: ";
    getline(cin, namaInput);

    Customer* cur = headCustomer; //cur = cursor customer
    while(cur != NULL) {
        if (cur->nama == namaInput) break;
        cur = cur->next;
    }
    if (cur == NULL) { //customer baru :D
        NewCustomer();
        tailCustomer->nama = namaInput;
        tailCustomer->HeadService = baruService;
        baruService->dataCustomer = tailCustomer;
    } else { //customer lama
        baruService->next = cur->HeadService;
        cur->HeadService = baruService;
        baruService->dataCustomer = cur;
        cout << "\n\nPelanggan sudah terdaftar dan servis berhasil dicatat\n\n\n";
    }
    
    baruService->allnext = headHistory; //save ke history
    headHistory = baruService;

    ofstream data_service("data_service.txt", ios::app);
    data_service << baruService->model_mobil << endl 
    << baruService->merek_mobil << endl 
    << baruService->deskripsi_kendala << endl 
    << baruService->nama_montir << endl 
    << namaInput << endl 
    << baruService->dataCustomer->nomor_telepon << endl;
    data_service.close();
}

void FindMechanic(string nama) {
    Service* Cur = headHistory;
    cout << "====== " << nama << "'s Jobs ======\n\n";
    if (Cur == NULL) {
        cout << "Empti :c\n\n";
        return;
    }
    while (Cur != NULL) {
        if (Cur->model_mobil != "" && Cur->dataCustomer != NULL && Cur->nama_montir == nama) {
            cout << "-----------------------\n" << 
            "Model Mobil: " << Cur->model_mobil << endl << 
            "Merek Mobil: " << Cur->merek_mobil << endl <<
            "Kendala: " << Cur->deskripsi_kendala << endl << 
            "Montir: " << Cur->nama_montir << endl << 
            "Nama Pelanggan: " << Cur->dataCustomer->nama << endl << 
            "No Telp Pelanggan: " << Cur->dataCustomer->nomor_telepon << 
            "\n-----------------------\n\n";   
        }
        Cur = Cur->allnext;
    }
}

void Servis(char submenu) {
    Service* bantu = headHistory;
    switch (submenu)
    {
    case '1':
        cout << "\n====== All Services ======\n\n";
        if (bantu != NULL) { 
            cout << "Empti :c\n\n";
            return;
        }
        while (bantu != NULL) {
            if (bantu->model_mobil != "" && bantu->dataCustomer != NULL ) {
                cout << "-----------------------\n" << 
                "Model Mobil: " << bantu->model_mobil << endl << 
                "Merek Mobil: " << bantu->merek_mobil << endl <<
                "Kendala: " << bantu->deskripsi_kendala << endl << 
                "Montir: " << bantu->nama_montir << endl << 
                "Nama Pelanggan: " << bantu->dataCustomer->nama << endl << 
                "No Telp Pelanggan: " << bantu->dataCustomer->nomor_telepon << 
                "\n-----------------------\n\n";                    
            };
            bantu = bantu->allnext;
        }
        break;
    
    case '2':
        cout << "\n====== New Service ======\n\n";
        NewService();
        break;

    case '3':
        int pilihan;
        do {
            cout << "\n====== Mechanic's Job History ======\n\n" 
            << R"(Pilih montir?
1. Suby
2. Farhan|
3. Dimas
4. Aldo
Pilihan: )";
        
            cin >> pilihan;
            cin.ignore();
            system("cls");
            if (pilihan == 1) FindMechanic("Suby");
            else if (pilihan == 2) FindMechanic("Farhan");
            else if (pilihan == 3) FindMechanic("Dimas");
            else if (pilihan == 4) FindMechanic("Aldo");
            } while (pilihan < 1 || pilihan > 4);
        
        break;

    default:
        break;
    }
}

void AllData() {
    Customer* cur = headCustomer;

    cout << "\n====== All Customers ======\n\n";
    if (cur == NULL) {
        cout << "Empty :c\n\n";
        return;
    }
    while (cur != NULL) {
        cout << "-----------------------\n" 
        << "Nama: " << cur->nama << endl 
        << "Nomor telepon: " << cur->nomor_telepon << endl 
        << "Alamat: " << cur->alamat << endl 
        << "___Servis Terakhir___" << endl
        << "Mobil: " << cur->HeadService->merek_mobil << endl 
        << "Kendala: " << cur->HeadService->deskripsi_kendala << endl
        << "Montir: " << cur->HeadService->nama_montir
        << "\n-----------------------\n\n";
        cur = cur->next;
    }
}

void Data() {
    if (headCustomer == NULL) {
        cout << "\nEmpti :c\n\n";
        cout << "Press enter to go back...";
        cin.get();
        return;
    }

    Customer* curC = headCustomer;
    char pilihan;

    do {
        system("cls");
        cout << "\n====== Customer Data ======\n\n" <<
        "Nama: " << curC->nama << endl <<
        "Nomor telepon: " << curC->nomor_telepon << endl <<
        "Umur: " << curC->umur << endl <<
        "Gender: " << curC->gender << endl <<
        "Alamat: " << curC->alamat << endl << endl <<
        "   3 Servis Terakhir   " << endl <<
        "-----------------------" << endl;

        Service* curS = curC->HeadService;
        for (int i = 0; i < 3 && curS != NULL; i++) {
            cout << "Mobil: " << curS->merek_mobil << endl
            << "Kendala: " << curS->deskripsi_kendala << endl
            << "Montir: " << curS->nama_montir << endl
            << "-----------------------" << endl;
            curS = curS->next;
        }
        
        cout << "[N]ext, [P]revious, [E]xit\n" 
            << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();
        pilihan = (char)toupper(pilihan);
        if (pilihan == 'N') {
            if (curC->next != NULL) {
                curC = curC->next;
            } else { //akhir tail
                cout << "\n============================\n\n" <<
                "Akhir dari list...\n\n\n" <<
                "Press enter to go back...";
                cin.get();
            }
        }
        if (pilihan == 'P') {
            if (curC->prev != NULL) {
                curC = curC->prev;
            } else {
                cout << "\n============================\n\n" <<
                "Awal dari list...\n\n\n" <<
                "Press enter to go back...";
                cin.get();
            }
        }
        
    } while (pilihan != 'E');
}

bool keluar = false;
void Menu () {
    system("cls");
    char pilihan;
    cout << R"(====== Welcome To Lognuts ======
Pilih Menu?
1. Servis
2. Semua Data Pelanggan
3. Data Pelanggan
4. Keluar

Pilihan : )";
    cin >> pilihan;
    cin.ignore();
    system("cls");
    switch(pilihan) {
        case '1':
            char submenu;
            cout << R"(====== Services ======
Pilih menu?
1. Semua Servis Singkat
2. Servis Baru
3. Riwayat Kerja Montir

Pilihan: )";
            cin >> submenu;
            cin.ignore();
            system("cls");
            Servis(submenu);
            break;

        case '2':
            AllData();
            break;
            
        case '3':
            Data();
            return;
            break;

        case '4':
            keluar = true;
            return;
            break;

        default:
            Menu();
            return;
    }
    cout << "Press enter to go back...";
    cin.ignore();
}

int main() {
    ifstream data_customer("data_customer.txt");
    string namaC, umur, gender, nomor_teleponC, alamat;
    while (getline(data_customer, namaC) && namaC != "") {
        getline(data_customer, umur);
        getline(data_customer, gender);
        getline(data_customer, nomor_teleponC);
        getline(data_customer, alamat);
        
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


    ifstream data_service("data_service.txt");
    string model_mobil, merek_mobil, deskripsi_kendala, nama_montir, namaS, nomor_teleponS;
    while (getline(data_service, model_mobil) && model_mobil != "") {    
        getline(data_service, merek_mobil);
        getline(data_service, deskripsi_kendala);
        getline(data_service, nama_montir);
        getline(data_service, namaS);
        getline(data_service, nomor_teleponS);

        Service *baruService = new Service;
        
        baruService->model_mobil = model_mobil;
        baruService->merek_mobil = merek_mobil;
        baruService->deskripsi_kendala = deskripsi_kendala;
        baruService->nama_montir = nama_montir;

        Customer* cur = headCustomer; //cur = cursor customer
        while(cur != NULL){
            if (cur->nama == namaS) break;
            cur = cur->next;
        }
        // save to customer
        if (cur != NULL) {
            baruService->next = cur->HeadService;
            cur->HeadService = baruService;
            baruService->dataCustomer = cur;
        }
        
        //save to history
        baruService->allnext = headHistory;
        headHistory = baruService;
        
    }
    data_service.close();

    while (!keluar) Menu();
    cout << "Bye! \n\n";

}