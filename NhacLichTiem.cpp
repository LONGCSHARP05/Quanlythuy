#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class LichTiemPhong {
private:
    string MaChuNuoi;
    string ThongTinThuCung;
    string NgayTiem;
    string LoaiVacXin;
    string GhiChu;

public:
    LichTiemPhong() {}
    
    LichTiemPhong(string maChuNuoi, string thongTinThuCung, string ngayTiem, string loaiVacXin, string ghiChu)
        : MaChuNuoi(maChuNuoi), ThongTinThuCung(thongTinThuCung), NgayTiem(ngayTiem), LoaiVacXin(loaiVacXin), GhiChu(ghiChu) {}
    
    void hienThiThongTin() const {
        cout << "Ma Chu Nuoi: " << MaChuNuoi
             << "\nThong Tin Thu Cung: " << ThongTinThuCung
             << "\nNgay Tiem: " << NgayTiem
             << "\nLoai Vac Xin: " << LoaiVacXin
             << "\nGhi Chu: " << GhiChu
             << "\n-------------------------\n";
    }
    
    string getMaChuNuoi() const { return MaChuNuoi; }
    string getNgayTiem() const { return NgayTiem; }
    void capNhatThongTin();

    void ghiVaoFile(ofstream &file) {
    file << MaChuNuoi << "\n" << ThongTinThuCung << "\n" << NgayTiem << "\n"
         << LoaiVacXin << "\n" << GhiChu << "\n";
}

static void docDuLieuTuFile(vector<LichTiemPhong> &danhSachLichTiem, const string &tenFile) {
    ifstream file(tenFile);
    if (file.is_open()) {
        string MaChuNuoi, ThongTinThuCung, NgayTiem, LoaiVacXin, GhiChu;
        while (getline(file, MaChuNuoi) && getline(file, ThongTinThuCung) &&
               getline(file, NgayTiem) && getline(file, LoaiVacXin) &&
               getline(file, GhiChu)) {
            danhSachLichTiem.push_back(LichTiemPhong(MaChuNuoi, ThongTinThuCung, NgayTiem, LoaiVacXin, GhiChu));
        }
        file.close();
    }
}

static void themLichTiem(vector<LichTiemPhong> &danhSachLichTiem) {
    string maChuNuoi, thongTinThuCung, ngayTiem, loaiVacXin, ghiChu;
    cout << "Nhap ma chu nuoi: ";
    cin >> maChuNuoi;
    cin.ignore();
    cout << "Nhap thong tin thu cung: ";
    getline(cin, thongTinThuCung);
    cout << "Nhap ngay tiem (yyyy-mm-dd): ";
    getline(cin, ngayTiem);
    cout << "Nhap loai vac xin: ";
    getline(cin, loaiVacXin);
    cout << "Nhap ghi chu: ";
    getline(cin, ghiChu);
    danhSachLichTiem.push_back(LichTiemPhong(maChuNuoi, thongTinThuCung, ngayTiem, loaiVacXin, ghiChu));
    string tenFile = "LichTiemPhong.txt";
    ofstream file(tenFile, ios::trunc);
    if (!file.is_open()) {
        cout << "Khong the mo file de ghi du lieu.\n";
        return;
    }
    for ( auto &lichTiem : danhSachLichTiem) {
        lichTiem.ghiVaoFile(file);
    }
        file.close();
    }


static void hienThiDanhSach(const vector<LichTiemPhong> &danhSachLichTiem) {
    cout << "\n--- Danh sach lich tiem ---\n";
    for (int i = 0; i < danhSachLichTiem.size(); i++) {
        danhSachLichTiem[i].hienThiThongTin();
    }
}

static void timKiemLichTiem(const vector<LichTiemPhong> &danhSachLichTiem) {
    string maChuNuoi;
    cout << "Nhap ma chu nuoi can tim: ";
    cin >> maChuNuoi;
    cin.ignore();
    for (int i = 0; i < danhSachLichTiem.size(); i++) {
        if (danhSachLichTiem[i].getMaChuNuoi() == maChuNuoi) {
            danhSachLichTiem[i].hienThiThongTin();
        }
    }
}

static void nhacNhoLichTiem(const vector<LichTiemPhong> &danhSachLichTiem) {
    string ngayHienTai;
    cout << "Nhap ngay hien tai (yyyy-mm-dd): ";
    cin >> ngayHienTai;
    cout << "\n--- Lich tiem sap den ---\n";
    bool found = false;
    for (int i = 0; i < danhSachLichTiem.size(); i++) {
        if (danhSachLichTiem[i].getNgayTiem() >= ngayHienTai) { 
            danhSachLichTiem[i].hienThiThongTin();
            found = true;
        }
    }
    if (!found) {
        cout << "Khong co lich tiem nao sap den!\n";
    }
}

static void lichNhacTiemPhong(vector<LichTiemPhong> &danhSachLichTiem) {
    

    int luaChon;
    do {
        cout << "\n------ QUAN LY LICH TIEM PHONG ------\n";
        cout << "1. Them lich tiem moi\n";
        cout << "2. Hien thi danh sach lich tiem\n";
        cout << "3. Tim kiem lich tiem theo ma chu nuoi\n";
        cout << "4. Nhac nho lich tiem sap den\n";
        cout << "5. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> luaChon;
        cin.ignore();
        
        switch (luaChon) {
            case 1:
                themLichTiem(danhSachLichTiem);
                break;
            case 2:
                hienThiDanhSach(danhSachLichTiem);
                break;
            case 3:
                timKiemLichTiem(danhSachLichTiem);
                break;
            case 4:
                nhacNhoLichTiem(danhSachLichTiem);
                break;
            case 5:
                cout << "Thoat chuong trinh.\n";
                break;
            default:
                cout << "Lua chon khong hop le, vui long nhap lai!\n";
        }
    } while (luaChon != 5);
    
    return ;
}

};