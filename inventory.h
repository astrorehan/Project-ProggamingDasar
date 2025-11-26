// inventory.h
// Header file untuk class inventory
// Berisi deklarasi class dan method-method yang digunakan

#ifndef INVENTORY_H
#define INVENTORY_H

#include <fstream>
#include <string>

using namespace std;

class inventory {
private:
    int id;
    char kodeBarang[50];
    char namaBarang[50];
    char kategori[50];
    int stok;

public:
    // === File Operations ===
    void Cekfile(fstream &data); // Memastikan file inventory.bin ada dan membukanya
    int ukuranData(fstream &data); // Mengembalikan jumlah record dalam file
    void MenulisFile(fstream &data, const inventory &item, int posisi); // Menulis record pada posisi tertentu (1-based)
    inventory BacaData(fstream &data, int posisi); // Membaca record pada posisi tertentu (1-based)

    // === CRUD Operations ===
    void tambahdata(fstream &data);  // Menambah stok barang masuk atau barang baru
    void keluarbarang(fstream &data); // Mengeluarkan barang berdasarkan ID
    void TampilData(fstream &data); // Menampilkan semua record dalam bentuk tabel
    void UbahData(fstream &data); // Mengupdate record berdasarkan nomor posisi
    void HapusData(fstream &data);// Menghapus record berdasarkan index

    // === Import/Export Text File ===
    void LoadDariFile(fstream &data, const string &namaFile); // Load data dari file input.txt
    void SaveKeFile(fstream &data, const string &namaFile); // Save data ke file output.txt

    // === Menu Interface ===
    int menu(); // Menampilkan menu dan mengembalikan pilihan user
    void tampil_menu(); // Loop interaktif utama
};

#endif // INVENTORY_H