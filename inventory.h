// inventory.h
// Header file untuk class inventory (TEXT FILE VERSION)

#ifndef INVENTORY_H
#define INVENTORY_H

#include <fstream>
#include <string>
#include <vector>

using namespace std;

class inventory {
private:
    int id;
    string kodeBarang;
    string namaBarang;
    string kategori;
    int stok;

public:
    // Constructor
    inventory();
    inventory(int i, string kode, string nama, string kat, int s);

    // Getter
    int getId() const { return id; }
    string getKode() const { return kodeBarang; }
    string getNama() const { return namaBarang; }
    string getKategori() const { return kategori; }
    int getStok() const { return stok; }

    // Setter
    void setId(int i) { id = i; }
    void setStok(int s) { stok = s; }

    // === File Operations (fileOperations.cpp) ===
    vector<inventory> LoadSemuaData(const string &namaFile);
    void SaveSemuaData(const vector<inventory> &data, const string &namaFile);

    // === CRUD Operations (crudOperations.cpp) ===
    void tambahdata(vector<inventory> &data);
    void keluarbarang(vector<inventory> &data);
    void TampilData(const vector<inventory> &data);
    void UbahData(vector<inventory> &data);
    void HapusData(vector<inventory> &data);

    // === Menu Interface (menuInterface.cpp) ===
    int menu();
    void tampil_menu();
};

#endif // INVENTORY_H