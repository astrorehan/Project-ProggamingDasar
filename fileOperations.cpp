// Implementasi operasi file inventory.txt

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
            // Trim whitespace
            auto trim = [](const string &s)->string{
                const auto strBegin = s.find_first_not_of(" \t\r\n");
                if (strBegin == string::npos) return string();
                const auto strEnd = s.find_last_not_of(" \t\r\n");
                return s.substr(strBegin, strEnd - strBegin + 1);
            };

            idStr = trim(idStr);
            stokStr = trim(stokStr);
            kode = trim(kode);
            nama = trim(nama);
            kat = trim(kat);

            // Validate numeric fields safely
            try {
                int id = stoi(idStr);
                int stok = stoi(stokStr);
                data.push_back(inventory(id, kode, nama, kat, stok));
            } catch (const std::exception &e) {
                // Skip malformed lines but notify user
                cerr << "Peringatan: melewati baris tidak valid: '" << line << "' (" << e.what() << ")\n";
                continue;
            }
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

// Import data dari file eksternal (format sama dengan inventory.txt)
void inventory::ImportDariFile(const string &namaFileEksternal, vector<inventory> &data){
    // Load semua data dari file eksternal menggunakan fungsi yang sama
    vector<inventory> ekst = LoadSemuaData(namaFileEksternal);

    if (ekst.empty()){
        cout << "Tidak ada data untuk diimpor dari " << namaFileEksternal << "\n";
        return;
    }

    // Meneentukan next ID
    int nextId = data.empty() ? 1 : data.back().getId() + 1;
    int processed = 0;

    for (auto &item : ekst){
        bool found = false;
        for (auto &d : data){
            if (d.getKode() == item.getKode() || d.getNama() == item.getNama()){
                // jika duplikat menurut kode atau nama, tambahkan stok
                d.setStok(d.getStok() + item.getStok());
                found = true;
                break;
            }
        }
        if (!found){
            item.setId(nextId++);
            data.push_back(item);
        }
        processed++;
    }

    cout << "Import selesai: " << processed << " record diproses dari " << namaFileEksternal << "\n";
}
