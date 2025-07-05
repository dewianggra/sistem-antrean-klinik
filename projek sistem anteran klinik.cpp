#include <iostream>
#include <queue>
#include <stack>
#include <map>
#include <string>
using namespace std;

struct Pasien {
    int id;
    string nama;
    stack<string> riwayatTindakan;
};

queue<int> antrianPasien; // Antrian berdasarkan ID
map<int, Pasien> dataPasien; // Simpan pasien berdasarkan ID
int idCounter = 1;

void tambahPasien() {
    string nama;
    cout << "Masukkan nama pasien: ";
    getline(cin, nama);

    int id = idCounter++;
    antrianPasien.push(id);
    dataPasien[id] = Pasien{id, nama};
    cout << "Pasien " << nama << " ditambahkan ke antrian dengan ID " << id << ".\n";
}

void tambahTindakan() {
    int id;
    string tindakan;
    cout << "Masukkan ID pasien: ";
    cin >> id;
    cin.ignore(); // bersihkan newline

    if (dataPasien.find(id) != dataPasien.end()) {
        cout << "Masukkan tindakan medis: ";
        getline(cin, tindakan);
        dataPasien[id].riwayatTindakan.push(tindakan);
        cout << "Tindakan ditambahkan ke riwayat pasien " << dataPasien[id].nama << ".\n";
    } else {
        cout << "Pasien dengan ID tersebut tidak ditemukan.\n";
    }
}

void layaniPasien() {
    if (antrianPasien.empty()) {
        cout << "Tidak ada pasien dalam antrian.\n";
        return;
    }

    int id = antrianPasien.front();
    antrianPasien.pop();

    Pasien& p = dataPasien[id];
    cout << "Melayani pasien: " << p.nama << " (ID: " << p.id << ")\n";
    cout << "Riwayat tindakan:\n";

    stack<string> tindakan = p.riwayatTindakan;
    if (tindakan.empty()) {
        cout << "- (Belum ada tindakan)\n";
    } else {
        while (!tindakan.empty()) {
            cout << "- " << tindakan.top() << endl;
            tindakan.pop();
        }
    }
}

void tampilAntrian() {
    if (antrianPasien.empty()) {
        cout << "Antrian kosong.\n";
        return;
    }

    cout << "Daftar antrian pasien:\n";
    queue<int> temp = antrianPasien;
    while (!temp.empty()) {
        int id = temp.front();
        cout << "- " << dataPasien[id].nama << " (ID: " << id << ")\n";
        temp.pop();
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n=== Menu Sistem Antrian Pasien ===\n";
        cout << "1. Tambah Pasien\n";
        cout << "2. Tambah Tindakan ke Pasien (berdasarkan ID)\n";
        cout << "3. Layani Pasien (berdasarkan urutan antrian ID)\n";
        cout << "4. Tampilkan Antrian\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore(); // Bersihkan newline

        switch (pilihan) {
            case 1: tambahPasien(); break;
            case 2: tambahTindakan(); break;
            case 3: layaniPasien(); break;
            case 4: tampilAntrian(); break;
            case 0: cout << "Keluar dari program.\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 0);

    return 0;
}

