#ifndef BARANG_H
#define BARANG_H

#include <string>
using namespace std;

class Barang {
private:
    int id;
    string kode;
    string nama;
    string kategori;
    int stok;

public:
    Barang() : id(0), stok(0) {}
    Barang(int id, string kode, string nama, string kategori, int stok)
        : id(id), kode(kode), nama(nama), kategori(kategori), stok(stok) {}

    // Getter
    int getId() const { return id; }
    string getKode() const { return kode; }
    string getNama() const { return nama; }
    string getKategori() const { return kategori; }
    int getStok() const { return stok; }

    // Setter
    void setId(int i) { id = i; }
    void setStok(int s) { stok = s; }
    void setKode(string k) { kode = k; }
    void setNama(string n) { nama = n; }
    void setKategori(string k) { kategori = k; }
};

#endif
