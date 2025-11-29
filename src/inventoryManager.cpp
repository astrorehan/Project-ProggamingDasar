#include <iostream>
#include <algorithm>
#include "InventoryManager.h"
using namespace std;

int InventoryManager::getLastId() const {
    int maxId = 0;
    for (const auto& b : data) {
        if (b.getId() > maxId) {
            maxId = b.getId();
        }
    }
    return maxId;
}

void InventoryManager::tampilData() {
    cout << "\n=== DAFTAR INVENTORY ===\n";
    cout << "ID | KODE | NAMA | KATEGORI | STOK\n";
    for (auto& b : data) {
        cout << b.getId() << " | " << b.getKode() << " | "
             << b.getNama() << " | " << b.getKategori()
             << " | Stok: " << b.getStok() << endl;
    }
}

void InventoryManager::tambahBarang() {
    int stok;
    string kode, nama, kategori;

    cout << "Kode  : "; getline(cin, kode);
    cout << "Nama  : "; getline(cin, nama);
    cout << "Kategori : "; getline(cin, kategori);
    cout << "Stok  : "; cin >> stok;
    cin.ignore();  // Clear newline from input buffer

    int newId = getLastId() + 1;
    data.push_back(Barang(newId, kode, nama, kategori, stok));
    cout << "Barang berhasil ditambahkan dengan ID: " << newId << ".\n";
}

void InventoryManager::keluarkanBarang() {
    int id, jumlah;
    cout << "Masukkan ID barang: ";
    cin >> id;

    for (auto& b : data) {
        if (b.getId() == id) {
            cout << "Jumlah keluar: ";
            cin >> jumlah;
            cin.ignore();  // Clear newline from input buffer
            
            if (jumlah > b.getStok()) {
                cout << "Error: Stok tidak cukup! Stok saat ini: " << b.getStok() << "\n";
                return;
            }
            
            b.setStok(b.getStok() - jumlah);
            cout << "Stok diperbarui. Stok tersisa: " << b.getStok() << "\n";
            return;
        }
    }
    cout << "Barang tidak ditemukan.\n";
}

void InventoryManager::ubahBarang() {
    int id;
    cout << "ID barang yang ingin diubah: ";
    cin >> id;
    cin.ignore();  // Clear newline from input buffer

    for (auto& b : data) {
        if (b.getId() == id) {
            string nama, kategori;
            int stok;

            cout << "Nama baru: "; 
            getline(cin, nama);
            cout << "Kategori baru: "; 
            getline(cin, kategori);
            cout << "Stok baru: "; 
            cin >> stok;

            b = Barang(id, b.getKode(), nama, kategori, stok);
            cout << "Data diubah.\n";
            return;
        }
    }
    cout << "Barang tidak ditemukan.\n";
}

void InventoryManager::hapusBarang() {
    int id;
    cout << "ID barang yang ingin dihapus: ";
    cin >> id;

    data.erase(remove_if(data.begin(), data.end(),
        [=](Barang b) { return b.getId() == id; }), data.end());

    cout << "Data dihapus.\n";
}
