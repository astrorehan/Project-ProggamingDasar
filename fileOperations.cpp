// fileOperations.cpp
// Implementasi operasi file TEXT (inventory.txt)

#include "inventory.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

inventory::inventory() : id(0), kodeBarang(""), namaBarang(""), kategori(""), stok(0) {}

inventory::inventory(int i, string kode, string nama, string kat, int s) 
    : id(i), kodeBarang(kode), namaBarang(nama), kategori(kat), stok(s) {}

// Load semua data dari file text
vector<inventory> inventory::LoadSemuaData(const string &namaFile){
    vector<inventory> data;
    ifstream file(namaFile);
    
    if (!file.is_open()){
        // File belum ada, return vector kosong
        return data;
    }

    string line;
    // Skip header jika ada
    if (getline(file, line)){
        if (line.find("ID") == string::npos){
            // Baris pertama bukan header, proses sebagai data
            file.seekg(0);
        }
    }

    // Baca semua data
    while (getline(file, line)){
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, kode, nama, kat, stokStr;

        if (getline(ss, idStr, '|') && 
            getline(ss, kode, '|') && 
            getline(ss, nama, '|') && 
            getline(ss, kat, '|') && 
            getline(ss, stokStr))
        {
            int id = stoi(idStr);
            int stok = stoi(stokStr);
            data.push_back(inventory(id, kode, nama, kat, stok));
        }
    }

    file.close();
    return data;
}

// Save semua data ke file text
void inventory::SaveSemuaData(const vector<inventory> &data, const string &namaFile){
    ofstream file(namaFile);
    
    if (!file.is_open()){
        cout << "Gagal membuat file " << namaFile << "\n";
        return;
    }

    // Tulis header
    file << "ID|KODE|NAMA|KATEGORI|STOK\n";

    // Tulis semua data
    for (const auto &item : data){
        file << item.getId() << "|"
             << item.getKode() << "|"
             << item.getNama() << "|"
             << item.getKategori() << "|"
             << item.getStok() << "\n";
    }

    file.close();
}