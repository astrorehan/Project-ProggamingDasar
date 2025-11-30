#include "FileManager.h"
#include <sstream>

void FileManager::loadData(string file, vector<Barang>& data) {
    ifstream in(file);
    if (!in) {
        cerr << "Error: File tidak ditemukan: " << file << "\n";
        return;
    }

    string line;
    // Lewati baris header
    getline(in, line);

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, kode, nama, kategori, stokStr;

        try {
            // Parse nilai pipe-separated
            getline(ss, idStr, '|');
            getline(ss, kode, '|');
            getline(ss, nama, '|');
            getline(ss, kategori, '|');
            getline(ss, stokStr);

            int id = stoi(idStr);
            int stok = stoi(stokStr);
            data.push_back(Barang(id, kode, nama, kategori, stok));
        } catch (const exception& e) {
            cerr << "Warning: Baris tidak valid dilewati: " << line << " (" << e.what() << ")\n";
        }
    }
    in.close();
}

void FileManager::saveData(string file, vector<Barang>& data) {
    ofstream out(file);
    if (!out) {
        cerr << "Error: Tidak bisa menulis ke file: " << file << "\n";
        return;
    }

    // Tulis header
    out << "ID|KODE|NAMA|KATEGORI|STOK\n";

    // Tulis data dalam format pipe-separated
    for (auto& b : data) {
        out << b.getId() << "|"
            << b.getKode() << "|"
            << b.getNama() << "|"
            << b.getKategori() << "|"
            << b.getStok() << "\n";
    }
    out.close();
}

void FileManager::importData(string fileEksternal, vector<Barang>& data) {
    ifstream in(fileEksternal);
    if (!in) {
        cerr << "Error: File tidak ditemukan: " << fileEksternal << "\n";
        return;
    }

    string line;
    // Lewati baris header
    getline(in, line);

    int imported = 0, merged = 0;
    int maxId = 0;
    
    // Cari ID maksimal dari data yang ada
    for (const auto& b : data) {
        if (b.getId() > maxId) {
            maxId = b.getId();
        }
    }

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, kode, nama, kategori, stokStr;

        try {
            // Parse nilai pipe-separated
            getline(ss, idStr, '|');
            getline(ss, kode, '|');
            getline(ss, nama, '|');
            getline(ss, kategori, '|');
            getline(ss, stokStr);

            int stok = stoi(stokStr);
            
            // Cek apakah kode sudah ada
            bool found = false;
            for (auto& b : data) {
                if (b.getKode() == kode) {
                    // Merge: tambahkan stok ke item yang ada
                    b.setStok(b.getStok() + stok);
                    merged++;
                    found = true;
                    break;
                }
            }

            if (!found) {
                // Item baru: assign ID baru dan tambahkan
                int newId = ++maxId;
                data.push_back(Barang(newId, kode, nama, kategori, stok));
                imported++;
            }
        } catch (const exception& e) {
            cerr << "Warning: Baris tidak valid dilewati: " << line << " (" << e.what() << ")\n";
        }
    }
    in.close();
    
    cout << "Import selesai: " << imported << " barang baru ditambahkan, "
         << merged << " barang diperbarui stoknya.\n";
    saveData("data/inventory.txt", data);
}

int FileManager::loadLastId() {
    ifstream in("data/lastId.txt");
    if (!in) {
        return 0;  // Default jika file tidak ada
    }
    
    int lastId = 0;
    in >> lastId;
    in.close();
    return lastId;
}

void FileManager::saveLastId(int lastId) {
    ofstream out("data/lastId.txt");
    if (!out) {
        cerr << "Error: Tidak bisa menulis ke file: data/lastId.txt\n";
        return;
    }
    
    out << lastId;
    out.close();
}
