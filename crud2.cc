#include <iostream>
#include <mysql/mysql.h>
#include <sstream>

using namespace std;

const char* hostname = "127.0.0.1";
const char* user = "root";
const char* pass = "123";
const char* dbname = "mahasiswa";
unsigned int port = 31236;
const char* unixsocket = NULL;
unsigned long clientflag = 0;

MYSQL* connect_db() {
    MYSQL* conn = mysql_init(0);
    if (conn) {
        conn = mysql_real_connect(conn, hostname, user, pass, dbname, port, unixsocket, clientflag);
        if (conn) {
            cout << "Connected to the database successfully." << endl;
        } else {
            cerr << "Connection failed: " << mysql_error(conn) << endl;
        }
    } else {
        cerr << "mysql_init failed" << endl;
    }
    return conn;
}

void create_user(const string& nama, const string& nim, const string& fakultas, const string& jurusan, const string& judul_buku, const string& jumlah_buku, const string& tgl_pinjam, const string& tgl_kembali) {
    MYSQL* conn = connect_db();
    if (conn) {
        string query = "INSERT INTO perpustakaan (nama, nim, fakultas, jurusan, judul_buku, jumlah_buku, tgl_pinjam, tgl_kembali) VALUES ('" + nama + "', '" + nim + "', '" + fakultas + "', '" + jurusan + "', '" + judul_buku + "', '" + jumlah_buku + "', '" + tgl_pinjam + "', '" + tgl_kembali + "')";
        if (mysql_query(conn, query.c_str())) {
            cerr << "INSERT failed: " << mysql_error(conn) << endl;
        } else {
            cout << "User successfully added." << endl;
        }
        mysql_close(conn);
    }
}

void get_users() {
    MYSQL* conn = connect_db();
    if (conn) {
        if (mysql_query(conn, "SELECT * FROM perpustakaan")) {
            cerr << "SELECT failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_RES* res = mysql_store_result(conn);
        if (res == nullptr) {
            cerr << "mysql_store_result failed: " << mysql_error(conn) << endl;
            mysql_close(conn);
            return;
        }

        MYSQL_ROW row;
        while ((row = mysql_fetch_row(res))) {
            cout << "ID: " << row[0] << ", Nama: " << row[1] << ", NIM: " << row[2] << ", Fakultas: " << row[3] << ", Jurusan: " << row[4] << ", Judul Buku: " << row[5] << ", Jumlah Buku: " << row[6] << ", Tgl Pinjam: " << row[7] << ", Tgl Kembali: " << row[8] << endl;
        }

        mysql_free_result(res);
        mysql_close(conn);
    }
}

void update_user(int user_id, const string& nama, const string& nim, const string& fakultas, const string& jurusan, const string& judul_buku, const string& jumlah_buku, const string& tgl_pinjam, const string& tgl_kembali) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "UPDATE perpustakaan SET nama = '" << nama << "', nim = '" << nim << "', fakultas = '" << fakultas << "', jurusan = '" << jurusan << "', judul_buku = '" << judul_buku << "', jumlah_buku = '" << jumlah_buku << "', tgl_pinjam = '" << tgl_pinjam << "', tgl_kembali = '" << tgl_kembali << "' WHERE id = " << user_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "UPDATE failed: " << mysql_error(conn) << endl;
        } else {
            cout << "User successfully updated." << endl;
        }
        mysql_close(conn);
    }
}

void delete_user(int user_id) {
    MYSQL* conn = connect_db();
    if (conn) {
        stringstream query;
        query << "DELETE FROM perpustakaan WHERE id = " << user_id;
        if (mysql_query(conn, query.str().c_str())) {
            cerr << "DELETE failed: " << mysql_error(conn) << endl;
        } else {
            cout << "User successfully deleted." << endl;
        }
        mysql_close(conn);
    }
}

int main() {
    int choice;
    while (true) {
        cout << "\n~~ SELAMAT DATANG DI PERPUSTAKAAN ESA UNGGUL ~~:\n";
        cout << "\nMenu:\n";
        cout << "1. Tambah Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Ubah Data\n";
        cout << "4. Hapus Data\n";
        cout << "5. Keluar\n";
        cout << "Masukkan Pilihan : ";
        cin >> choice;

        if (choice == 1) {
            string nama, nim, fakultas, jurusan, judul_buku, jumlah_buku, tgl_pinjam, tgl_kembali;
            cout << "Masukkan Nama: ";
            cin.ignore();
            getline(cin, nama);
            cout << "Masukkan NIM: ";
            getline(cin, nim);
            cout << "Masukkan Fakultas: ";
            getline(cin, fakultas);
            cout << "Masukkan Jurusan: ";
            getline(cin, jurusan);
            cout << "Masukkan Judul Buku: ";
            getline(cin, judul_buku);
            cout << "Masukkan Jumlah Buku: ";
            getline(cin, jumlah_buku);
            cout << "Tanggal Pinjam: ";
            getline(cin, tgl_pinjam);
            cout << "Tanggal Kembali: ";
            getline(cin, tgl_kembali);
            create_user(nama, nim, fakultas, jurusan, judul_buku, jumlah_buku, tgl_pinjam, tgl_kembali);
        } else if (choice == 2) {
            get_users();
        } else if (choice == 3) {
            int user_id;
            string nama, nim, fakultas, jurusan, judul_buku, jumlah_buku, tgl_pinjam, tgl_kembali;
            cout << "Masukkan ID yang diUbah: ";
            cin >> user_id;
            cin.ignore();
            cout << "Masukkan Nama Baru: ";
            getline(cin, nama);
            cout << "Masukkan NIM baru: ";
            getline(cin, nim);
            cout << "Masukkan Fakultas: ";
            getline(cin, fakultas);
            cout << "Masukkan Jurusan: ";
            getline(cin, jurusan);
            cout << "Masukkan Judul Buku: ";
            getline(cin, judul_buku);
            cout << "Masukkan Jumlah Buku: ";
            getline(cin, jumlah_buku);
            cout << "Tanggal Pinjam: ";
            getline(cin, tgl_pinjam);
            cout << "Tanggal Kembali: ";
            getline(cin, tgl_kembali);
            update_user(user_id, nama, nim, fakultas, jurusan, judul_buku, jumlah_buku, tgl_pinjam, tgl_kembali);
        } else if (choice == 4) {
            int user_id;
            cout << "Masukkan ID untuk diHapus: ";
            cin >> user_id;
            delete_user(user_id);
        } else if (choice == 5) {
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }
    return 0;
}