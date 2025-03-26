#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>

#ifndef DMCHUNUOI_HPP
#define DMCHUNUOI_HPP

using namespace std;

//DMChuNuoi: với các thông tin như mã chủ nuôi, tên chủ nuôi, địa chỉ, số điện thoại, thông tin thú cưng.

class DMChuNuoi {
    protected:
    string maChuNuoi;
    string tenChuNuoi;
    string diaChi;
    string soDienThoai;
    string thongTinThuCung;
    
    public:
    // Hàm tạo mặc định
    DMChuNuoi() : maChuNuoi(""), tenChuNuoi(""), diaChi(""), soDienThoai(""), thongTinThuCung("") {}

    // phương thức setter
    void setMaChuNuoi( string& ma) { maChuNuoi = ma; }
    void setTenChuNuoi(string& ten) { tenChuNuoi = ten; }
    void setDiaChi( string& dia) { diaChi = dia; }
    void setSoDienThoai( string& sdt) { soDienThoai = sdt; }
    void setThongTinThuCung( string& thuCung) { thongTinThuCung = thuCung; }

    // Getter
    string getMaChuNuoi()  { return maChuNuoi; }
    string getTenChuNuoi()  { return tenChuNuoi; }
    string getDiaChi()  { return diaChi; }
    string getSoDienThoai()  { return soDienThoai; }
    string getThongTinThuCung()  { return thongTinThuCung; }

    // Hàm nhập thông tin chủ nuôi
    void nhap(vector<DMChuNuoi>& danhSachChuNuoi) {
        DMChuNuoi cn;
        cout << "Nhập mã chủ nuôi: "; getline(cin, cn.maChuNuoi);
        cout << "Nhập tên chủ nuôi: "; getline(cin, cn.tenChuNuoi);
        cout << "Nhập địa chỉ: "; getline(cin, cn.diaChi);
        cout << "Nhập số điện thoại: "; getline(cin, cn.soDienThoai);
        cout << "Nhập thông tin thú cưng: "; getline(cin, cn.thongTinThuCung);
    }

    // Đọc dữ liệu từ file vào vector
    static void docFile(vector<DMChuNuoi>& ds) {
        ifstream file("DMChuNuoi.txt");
        if (!file.is_open()) {
            cout << "Không thể mở file để đọc" << endl;
            return;
        }
    
        DMChuNuoi cn;
        while (getline(file, cn.maChuNuoi)) {
            getline(file, cn.tenChuNuoi);
            getline(file, cn.diaChi);
            getline(file, cn.soDienThoai);
            getline(file, cn.thongTinThuCung);
            file.ignore();
            ds.push_back(cn);
        }
        file.close();
    }

    // Hàm hiển thị thông tin chủ nuôi
    void hienThi() const {
        cout << left << setw(10) << maChuNuoi
             << setw(20) << tenChuNuoi
             << setw(50) << diaChi
             << setw(15) << soDienThoai
             << setw(15) << thongTinThuCung << endl;
    }

    // Hàm hiển thị danh sách chủ nuôi
    static void inDanhSachChuNuoi(const vector<DMChuNuoi> &danhSachChuNuoi) {
        cout << left << setw(10) << "MaKH"
             << setw(20) << "TenChuNuoi"
             << setw(50) << "DiaChi"
             << setw(15) << "SoDienThoai"
             << setw(15) << "ThongTinThuCung" << endl;
        cout << string(115, '-') << endl;
    
        for (const auto &chuNuoi : danhSachChuNuoi) {
            chuNuoi.hienThi();
        }
    }
};
   
    

#endif 