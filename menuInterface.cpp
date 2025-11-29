// Implementasi user interface dan menu interaktif

#include "inventory.h"
#include <iostream>
#include <limits>
using namespace std;

int inventory::menu(){
    int input;
    cout << "\n===== MENU INVENTORY =====\n";
    cout << "1. Barang Masuk\n";
    cout << "2. Barang Keluar\n";
    cout << "3. Tampilkan Barang\n";
    cout << "4. Ubah Barang\n";
    cout << "5. Hapus Barang\n";
    cout << "6. Import dari file eksternal\n";
    cout << "7. Selesai\n";
    cout << "Pilih menu : ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

void inventory::tampil_menu(){
    const string namaFile = "inventory.txt";
    
    // Load data dari file
    vector<inventory> data = LoadSemuaData(namaFile);
    
    cout << "Data berhasil dimuat dari " << namaFile << "\n";
    cout << "Total " << data.size() << " item.\n";

    while (true){
        int pilih = menu();
        if (pilih == 7){
            // Save data sebelum keluar
            SaveSemuaData(data, namaFile);
            cout << "Data berhasil disimpan ke " << namaFile << "\n";
            break;
        }

        switch (pilih){
            case 1:
                tambahdata(data);
                SaveSemuaData(data, namaFile); // Auto-save
                TampilData(data);
                break;
            case 2:
                keluarbarang(data);
                SaveSemuaData(data, namaFile);
                TampilData(data);
                break;
            case 3:
                TampilData(data);
                break;
            case 4:
                TampilData(data);
                UbahData(data);
                SaveSemuaData(data, namaFile); 
                TampilData(data);
                break;
            case 5:
                TampilData(data);
                HapusData(data);
                SaveSemuaData(data, namaFile); 
                TampilData(data);
                break;
            case 6: {
                // Import dari file eksternal (file terletak di folder project ini)
                cout << "Nama file eksternal (contoh: file.txt): ";
                string namaEksternal;
                getline(cin, namaEksternal);
                if (namaEksternal.empty()){
                    cout << "Nama file tidak boleh kosong.\n";
                } else {
                    ImportDariFile(namaEksternal, data);
                    SaveSemuaData(data, namaFile);
                    TampilData(data);
                }
                break;
            }
            default:
                cout << "Pilihan tidak valid!\n";
        }

        char lanjut;
        cout << "\nLanjutkan? (y/n): ";
        cin >> lanjut;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (lanjut == 'n' || lanjut == 'N'){
            SaveSemuaData(data, namaFile);
            cout << "Data berhasil disimpan ke " << namaFile << "\n";
            break;
        }
    }

    cout << "Program selesai.\n";
}
