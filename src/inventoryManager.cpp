#include <iostream>
#include <algorithm>
#include <iomanip>
#include "InventoryManager.h"
using namespace std;

int InventoryManager::getNextId() {
    return ++lastId;
}

void InventoryManager::tampilData() {
    cout << "\n=== DAFTAR INVENTORY ===\n";
    cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
         << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
    cout << string(60, '-') << endl;
    for (auto& b : data) {
        cout << left << setw(5) << b.getId() 
             << setw(10) << b.getKode() 
             << setw(20) << b.getNama() 
             << setw(15) << b.getKategori()
             << setw(10) << b.getStok() << endl;
    }
    cout << endl;
}

void InventoryManager::tambahBarang() {
    int stok;
    string kode, nama, kategori;

    cout << "Kode  : "; getline(cin, kode);
    cout << "Nama  : "; getline(cin, nama);
    cout << "Kategori : "; getline(cin, kategori);
    cout << "Stok  : "; cin >> stok;
    cin.ignore();

    // Cek apakah kode sudah ada
    for (auto& b : data) {
        if (b.getKode() == kode) {
            b.setStok(b.getStok() + stok);
            cout << "Barang sudah ada! Stok ditambahkan. Stok sekarang: " << b.getStok() << "\n";
            filemgr.saveData("data/inventory.txt", data);
            return;
        }
    }

    int newId = getNextId();
    data.push_back(Barang(newId, kode, nama, kategori, stok));
    cout << "Barang berhasil ditambahkan dengan ID: " << newId << ".\n";
    filemgr.saveData("data/inventory.txt", data);
    filemgr.saveLastId(lastId);
}

void InventoryManager::keluarkanBarang() {
    tampilData();
    
    int id, jumlah;
    cout << "Masukkan ID barang: ";
    cin >> id;

    for (auto& b : data) {
        if (b.getId() == id) {
            cout << "\n=== SEBELUM BARANG KELUAR ===\n";
            cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
                 << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
            cout << string(60, '-') << endl;
            cout << left << setw(5) << b.getId() 
                 << setw(10) << b.getKode() 
                 << setw(20) << b.getNama() 
                 << setw(15) << b.getKategori()
                 << setw(10) << b.getStok() << endl << endl;
            
            cout << "Jumlah keluar: ";
            cin >> jumlah;
            cin.ignore();
            
            if (jumlah > b.getStok()) {
                cout << "Error: Stok tidak cukup! Stok saat ini: " << b.getStok() << "\n";
                return;
            }
            
            b.setStok(b.getStok() - jumlah);
            
            cout << "\n=== SETELAH BARANG KELUAR ===\n";
            cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
                 << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
            cout << string(60, '-') << endl;
            cout << left << setw(5) << b.getId() 
                 << setw(10) << b.getKode() 
                 << setw(20) << b.getNama() 
                 << setw(15) << b.getKategori()
                 << setw(10) << b.getStok() << endl << endl;
            
            cout << "Stok diperbarui. Stok tersisa: " << b.getStok() << "\n";
            filemgr.saveData("data/inventory.txt", data);
            return;
        }
    }
    cout << "Barang tidak ditemukan.\n";
}

void InventoryManager::ubahBarang() {
    tampilData();
    
    int id;
    cout << "ID barang yang ingin diubah: ";
    cin >> id;
    cin.ignore();

    for (auto& b : data) {
        if (b.getId() == id) {
            cout << "\n=== SEBELUM DIUBAH ===\n";
            cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
                 << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
            cout << string(60, '-') << endl;
            cout << left << setw(5) << b.getId() 
                 << setw(10) << b.getKode() 
                 << setw(20) << b.getNama() 
                 << setw(15) << b.getKategori()
                 << setw(10) << b.getStok() << endl << endl;
            
            string nama, kategori;
            int stok;
            
            string oldNama = b.getNama();
            string oldKategori = b.getKategori();

            cout << "Nama baru (kosongkan untuk tidak mengubah): "; 
            getline(cin, nama);
            cout << "Kategori baru (kosongkan untuk tidak mengubah): "; 
            getline(cin, kategori);
            cout << "Stok baru: "; 
            cin >> stok;
            cin.ignore();

            // Jika kosong, gunakan nilai lama
            if (nama.empty()) nama = oldNama;
            if (kategori.empty()) kategori = oldKategori;

            b = Barang(id, b.getKode(), nama, kategori, stok);
            
            cout << "\n=== SESUDAH DIUBAH ===\n";
            cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
                 << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
            cout << string(60, '-') << endl;
            cout << left << setw(5) << b.getId() 
                 << setw(10) << b.getKode() 
                 << setw(20) << b.getNama() 
                 << setw(15) << b.getKategori()
                 << setw(10) << b.getStok() << endl << endl;
            
            cout << "Data diubah.\n";
            filemgr.saveData("data/inventory.txt", data);
            return;
        }
    }
    cout << "Barang tidak ditemukan.\n";
}

void InventoryManager::hapusBarang() {
    tampilData();
    
    int id;
    cout << "ID barang yang ingin dihapus: ";
    cin >> id;
    cin.ignore();

    auto it = find_if(data.begin(), data.end(),
        [=](const Barang& b) { return b.getId() == id; });
    
    if (it != data.end()) {
        cout << "\n=== DATA YANG AKAN DIHAPUS ===\n";
        cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
             << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
        cout << string(60, '-') << endl;
        cout << left << setw(5) << it->getId() 
             << setw(10) << it->getKode() 
             << setw(20) << it->getNama() 
             << setw(15) << it->getKategori()
             << setw(10) << it->getStok() << endl << endl;
        
        data.erase(it);
        
        cout << "=== SETELAH DIHAPUS ===\n";
        cout << left << setw(5) << "ID" << setw(10) << "KODE" << setw(20) << "NAMA" 
             << setw(15) << "KATEGORI" << setw(10) << "STOK" << endl;
        cout << string(60, '-') << endl;
        for (auto& b : data) {
            cout << left << setw(5) << b.getId() 
                 << setw(10) << b.getKode() 
                 << setw(20) << b.getNama() 
                 << setw(15) << b.getKategori()
                 << setw(10) << b.getStok() << endl;
        }
        cout << endl;
        
        cout << "Data dihapus.\n";
        filemgr.saveData("data/inventory.txt", data);
    } else {
        cout << "Barang tidak ditemukan.\n";
    }
}
