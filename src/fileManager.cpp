#include "FileManager.h"
#include <sstream>

void FileManager::loadData(string file, vector<Barang>& data) {
    ifstream in(file);
    if (!in) {
        cerr << "Error: File not found: " << file << "\n";
        return;
    }

    string line;
    // Skip header line
    getline(in, line);

    while (getline(in, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string idStr, kode, nama, kategori, stokStr;

        try {
            // Parse pipe-separated values
            getline(ss, idStr, '|');
            getline(ss, kode, '|');
            getline(ss, nama, '|');
            getline(ss, kategori, '|');
            getline(ss, stokStr);

            int id = stoi(idStr);
            int stok = stoi(stokStr);
            data.push_back(Barang(id, kode, nama, kategori, stok));
        } catch (const exception& e) {
            cerr << "Warning: Skipping malformed line: " << line << " (" << e.what() << ")\n";
        }
    }
    in.close();
}

void FileManager::saveData(string file, vector<Barang>& data) {
    ofstream out(file);
    if (!out) {
        cerr << "Error: Cannot write to file: " << file << "\n";
        return;
    }

    // Write header
    out << "ID|KODE|NAMA|KATEGORI|STOK\n";

    // Write data in pipe-separated format
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
        cerr << "Error: File not found: " << fileEksternal << "\n";
        return;
    }

    string line;
    // Skip header line
    getline(in, line);

    int imported = 0, merged = 0;
    int maxId = 0;
    
    // Find max ID from existing data
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
            // Parse pipe-separated values
            getline(ss, idStr, '|');
            getline(ss, kode, '|');
            getline(ss, nama, '|');
            getline(ss, kategori, '|');
            getline(ss, stokStr);

            int stok = stoi(stokStr);
            
            // Check if kode already exists
            bool found = false;
            for (auto& b : data) {
                if (b.getKode() == kode) {
                    // Merge: add stock to existing item
                    b.setStok(b.getStok() + stok);
                    merged++;
                    found = true;
                    break;
                }
            }

            if (!found) {
                // New item: assign new ID and add
                int newId = ++maxId;
                data.push_back(Barang(newId, kode, nama, kategori, stok));
                imported++;
            }
        } catch (const exception& e) {
            cerr << "Warning: Skipping malformed line: " << line << " (" << e.what() << ")\n";
        }
    }
    in.close();
    
    cout << "Import selesai: " << imported << " barang baru ditambahkan, "
         << merged << " barang diperbarui stoknya.\n";
}
