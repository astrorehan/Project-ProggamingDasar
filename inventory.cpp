// inventory.cpp
// Implementasi semua method dari class inventory

#include "inventory.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <cstdio>
#include <limits>
#include <sstream>

using namespace std;

// === File Operations ===

void inventory::Cekfile(fstream &data){
    data.open("inventory.bin", ios::in | ios::out | ios::binary);
    if (!data.is_open()) {
        // Buat file kosong, kemudian buka ulang untuk operasi in/out
        ofstream create("inventory.bin", ios::binary);
        create.close();
        data.open("inventory.bin", ios::in | ios::out | ios::binary);
    }
}

int inventory::ukuranData(fstream &data){
    if (!data.is_open()) return 0;
    data.seekg(0, ios::end);
    streampos akhir = data.tellg();
    return static_cast<int>(akhir / sizeof(inventory));
}

void inventory::MenulisFile(fstream &data, const inventory &item, int posisi){
    if (!data.is_open()) return;
    streamoff offset = static_cast<streamoff>((posisi - 1) * sizeof(inventory));
    data.seekp(offset, ios::beg);
    data.write(reinterpret_cast<const char*>(&item), sizeof(inventory));
    data.flush();
}

inventory inventory::BacaData(fstream &data, int posisi){
    inventory item{};
    if (!data.is_open()) return item;
    int size = ukuranData(data);
    if (posisi < 1 || posisi > size) return item;
    data.seekg((posisi - 1) * sizeof(inventory), ios::beg);
    data.read(reinterpret_cast<char*>(&item), sizeof(inventory));
    return item;
}

// === CRUD Operations ===

void inventory::tambahdata(fstream &data){
    inventory itemBaru, itemLama{};

    cout << "Kode Barang  : ";
    cin.getline(itemBaru.kodeBarang, sizeof(itemBaru.kodeBarang));
    cout << "Nama Barang  : ";
    cin.getline(itemBaru.namaBarang, sizeof(itemBaru.namaBarang));
    cout << "Kategori     : ";
    cin.getline(itemBaru.kategori, sizeof(itemBaru.kategori));
    cout << "Stok Masuk   : ";
    cin >> itemBaru.stok;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int size = ukuranData(data);

    // Cek apakah barang sudah ada (berdasarkan kode atau nama)
    for (int i = 1; i <= size; ++i){
        itemLama = BacaData(data, i);
        if (strcmp(itemLama.kodeBarang, itemBaru.kodeBarang) == 0 ||
            strcmp(itemLama.namaBarang, itemBaru.namaBarang) == 0)
        {
            cout << "\nBarang sudah ada. Menambahkan stok...\n";
            itemLama.stok += itemBaru.stok;
            MenulisFile(data, itemLama, i);
            return;
        }
    }

    // Barang baru, tambahkan di akhir file
    int posisi = size + 1;
    itemBaru.id = posisi;
    MenulisFile(data, itemBaru, posisi);

    cout << "\nBarang baru berhasil ditambahkan!\n";
}

void inventory::keluarbarang(fstream &data){
    inventory itemLama{};
    int itemId, jumlahKeluar;

    cout << "ID Barang    : ";
    cin >> itemId;
    cout << "Stok Keluar  : ";
    cin >> jumlahKeluar;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Validasi ID
    int size = ukuranData(data);
    if (itemId < 1 || itemId > size){
        cout << "ID tidak valid. Gunakan ID antara 1 dan " << size << "\n";
        return;
    }

    // Baca data berdasarkan ID
    itemLama = BacaData(data, itemId);
    
    // Cek stok mencukupi
    if (itemLama.stok < jumlahKeluar){
        cout << "GAGAL: Stok tidak mencukupi. Stok saat ini: " << itemLama.stok << "\n";
        return;
    }
    
    // Kurangi stok
    itemLama.stok -= jumlahKeluar;
    MenulisFile(data, itemLama, itemId);
    cout << "\nStok berhasil dikurangi! Sisa stok: " << itemLama.stok << "\n";
}

void inventory::TampilData(fstream &data){
    inventory item{};
    int size = ukuranData(data);

    if (size == 0){
        cout << "(Tidak ada data inventory)\n";
        return;
    }

    cout << left << setw(5) << "NO"
         << setw(5) << "ID"
         << setw(10) << "KODE"
         << setw(20) << "NAMA"
         << setw(15) << "KATEGORI"
         << setw(6) << "STOK" << right << "\n";
    cout << string(61, '-') << "\n";

    for (int i = 0; i < size; ++i){
        data.seekg(i * sizeof(inventory), ios::beg);
        data.read(reinterpret_cast<char*>(&item), sizeof(inventory));
        cout << left << setw(5) << i + 1
             << setw(5) << item.id
             << setw(10) << item.kodeBarang
             << setw(20) << item.namaBarang
             << setw(15) << item.kategori
             << setw(6) << item.stok << right << "\n";
    }
}

void inventory::UbahData(fstream &data){
    inventory item{};
    int posisi;

    cout << "Ubah data nomor : ";
    cin >> posisi;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int size = ukuranData(data);
    if (posisi < 1 || posisi > size){
        cout << "Posisi tidak valid. Gunakan nomor antara 1 dan " << size << "\n";
        return;
    }

    cout << "Kode Barang  : ";
    cin.getline(item.kodeBarang, sizeof(item.kodeBarang));
    cout << "Nama Barang  : ";
    cin.getline(item.namaBarang, sizeof(item.namaBarang));
    cout << "Kategori     : ";
    cin.getline(item.kategori, sizeof(item.kategori));
    cout << "Stok         : ";
    cin >> item.stok;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    item.id = posisi;
    MenulisFile(data, item, posisi);
    cout << "\nData berhasil diubah!\n";
}

void inventory::HapusData(fstream &data){
    if (!data.is_open()) return;

    cout << "Pilih data yang dihapus : ";
    int hapusIndex;
    cin >> hapusIndex;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    int size = ukuranData(data);
    if (hapusIndex < 1 || hapusIndex > size){
        cout << "Index tidak valid.\n";
        return;
    }

    // Buka file temporary untuk menulis record yang dipadatkan
    fstream datatemp("tempinv.bin", ios::in | ios::out | ios::trunc | ios::binary);
    if (!datatemp.is_open()){
        cout << "Gagal membuka file sementara.\n";
        return;
    }

    inventory item;
    int writePos = 0;
    for (int i = 1; i <= size; ++i){
        item = BacaData(data, i);
        if (i == hapusIndex) continue; // skip record yang dihapus
        ++writePos;
        item.id = writePos; // assign ulang id secara berurutan
        MenulisFile(datatemp, item, writePos);
    }

    // Tutup kedua file dan ganti file asli dengan file yang sudah dipadatkan
    datatemp.close();
    data.close();

    if (std::remove("inventory.bin") != 0){
        cout << "Peringatan: tidak dapat menghapus inventory.bin lama.\n";
    }
    if (std::rename("tempinv.bin", "inventory.bin") != 0){
        cout << "Peringatan: tidak dapat mengganti file inventory (rename gagal).\n";
    }

    // Buka ulang file `data` agar pemanggil bisa melanjutkan operasi
    data.open("inventory.bin", ios::in | ios::out | ios::binary);
    if (!data.is_open()){
        cout << "Gagal membuka kembali inventory.bin setelah penghapusan.\n";
    } else {
        cout << "\nData berhasil dihapus!\n";
    }
}

// === Import/Export Text File ===

void inventory::LoadDariFile(fstream &data, const string &namaFile){
    ifstream inputFile(namaFile);
    if (!inputFile.is_open()){
        cout << "Gagal membuka file " << namaFile << "\n";
        return;
    }

    inventory item;
    string line;
    int jumlahDibaca = 0;

    // Skip header jika ada
    if (getline(inputFile, line)){
        // Cek apakah baris pertama adalah header
        if (line.find("KODE") != string::npos || line.find("ID") != string::npos){
            // Skip header line
        } else {
            // Baris pertama adalah data, proses
            inputFile.seekg(0);
        }
    }

    // Format file: KODE|NAMA|KATEGORI|STOK (dipisah dengan '|' atau tab)
    while (getline(inputFile, line)){
        if (line.empty()) continue;

        stringstream ss(line);
        string kode, nama, kat, stokStr;

        // Parsing dengan delimiter '|'
        if (getline(ss, kode, '|') && 
            getline(ss, nama, '|') && 
            getline(ss, kat, '|') && 
            getline(ss, stokStr, '|'))
        {
            // Copy ke struct
            strncpy(item.kodeBarang, kode.c_str(), sizeof(item.kodeBarang) - 1);
            item.kodeBarang[sizeof(item.kodeBarang) - 1] = '\0';
            
            strncpy(item.namaBarang, nama.c_str(), sizeof(item.namaBarang) - 1);
            item.namaBarang[sizeof(item.namaBarang) - 1] = '\0';
            
            strncpy(item.kategori, kat.c_str(), sizeof(item.kategori) - 1);
            item.kategori[sizeof(item.kategori) - 1] = '\0';
            
            item.stok = stoi(stokStr);

            // Cek apakah barang sudah ada
            int size = ukuranData(data);
            bool ditemukan = false;
            
            for (int i = 1; i <= size; ++i){
                inventory itemLama = BacaData(data, i);
                if (strcmp(itemLama.kodeBarang, item.kodeBarang) == 0){
                    // Update stok yang sudah ada
                    itemLama.stok += item.stok;
                    MenulisFile(data, itemLama, i);
                    ditemukan = true;
                    break;
                }
            }

            if (!ditemukan){
                // Tambah barang baru
                int posisi = ukuranData(data) + 1;
                item.id = posisi;
                MenulisFile(data, item, posisi);
            }

            jumlahDibaca++;
        }
    }

    inputFile.close();
    cout << "\nBerhasil load " << jumlahDibaca << " item dari " << namaFile << "\n";
}

void inventory::SaveKeFile(fstream &data, const string &namaFile){
    ofstream outputFile(namaFile);
    if (!outputFile.is_open()){
        cout << "Gagal membuat file " << namaFile << "\n";
        return;
    }

    int size = ukuranData(data);
    if (size == 0){
        cout << "Tidak ada data untuk disimpan.\n";
        outputFile.close();
        return;
    }

    // Tulis header
    outputFile << "ID|KODE|NAMA|KATEGORI|STOK\n";

    // Tulis semua data
    for (int i = 1; i <= size; ++i){
        inventory item = BacaData(data, i);
        outputFile << item.id << "|"
                   << item.kodeBarang << "|"
                   << item.namaBarang << "|"
                   << item.kategori << "|"
                   << item.stok << "\n";
    }

    outputFile.close();
    cout << "\nBerhasil menyimpan " << size << " item ke " << namaFile << "\n";
}

// === Menu Interface ===

int inventory::menu(){
    int input;
    cout << "\n===== MENU INVENTORY =====\n";
    cout << "1. Barang Masuk\n";
    cout << "2. Barang Keluar\n";
    cout << "3. Tampilkan Barang\n";
    cout << "4. Ubah Barang\n";
    cout << "5. Hapus Barang\n";
    cout << "6. Load dari File (input.txt)\n";
    cout << "7. Save ke File (output.txt)\n";
    cout << "8. Selesai\n";
    cout << "Pilih menu : ";
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return input;
}

void inventory::tampil_menu(){
    fstream data;
    Cekfile(data);

    while (true){
        int pilih = menu();
        if (pilih == 8) break; // keluar program

        switch (pilih){
            case 1:
                tambahdata(data);
                TampilData(data);
                break;
            case 2:
                keluarbarang(data);
                TampilData(data);
                break;
            case 3:
                TampilData(data);
                break;
            case 4:
                TampilData(data);
                UbahData(data);
                TampilData(data);
                break;
            case 5:
                TampilData(data);
                HapusData(data);
                TampilData(data);
                break;
            case 6:
                LoadDariFile(data, "input.txt");
                TampilData(data);
                break;
            case 7:
                SaveKeFile(data, "output.txt");
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }

        char lanjut;
        cout << "\nLanjutkan? (y/n): ";
        cin >> lanjut;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (lanjut == 'n' || lanjut == 'N') break;
    }

    cout << "Program selesai.\n";
    if (data.is_open()) data.close();
}