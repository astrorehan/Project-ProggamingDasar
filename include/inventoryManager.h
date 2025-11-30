#ifndef INVENTORYMANAGER_H
#define INVENTORYMANAGER_H

#include <vector>
#include "Barang.h"
#include "FileManager.h"
using namespace std;

// Kelas untuk mengelola logika bisnis inventory (CRUD operations)
class InventoryManager {
private:
    vector<Barang> data;
    FileManager filemgr;
    int lastId;
    
    // Dapatkan ID berikutnya dengan increment lastId
    int getNextId();

public:
    // Getter untuk data vector
    vector<Barang>& getData() {
        return data;
    }
    
    // Setter untuk lastId saat startup
    void setLastId(int id) {
        lastId = id;
    }

    // Tampilkan semua data inventory dalam format tabel
    void tampilData();

    // CRUD Operations
    void tambahBarang();      // Tambah barang baru (merge jika kode sama)
    void keluarkanBarang();   // Kurangi stok barang
    void ubahBarang();        // Edit data barang
    void hapusBarang();       // Hapus barang
};

#endif
