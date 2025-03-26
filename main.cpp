#include<iostream>
#include<fstream>
#include<string>
#include<iomanip>
#include<vector>
#include "DMThuoc.hpp"
#include "DMChuNuoi.hpp"
#include "PhieuKhamBenh.hpp"
#include "PhieuKhamBenh.cpp"
#include "NhacLichTiem.cpp"

#include <thread>
#include <chrono>

using namespace std;

// Hàm tạo hiệu ứng gõ chữ
void typingEffect(const string& text, int delay = 50) {
    for (char c : text) {
        cout << c << flush;
        this_thread::sleep_for(chrono::milliseconds(delay));
    }
}

// Hàm hiển thị banner tiêu đề hệ thống
void hienThiBanner() {
    cout << R"(
   █████████  ██████    ██████   ████████   ████████  ████████
  ██░░░░░░░░  ██░░░██   ██░░░░██  ░░░██░░░  ██░░░░██  ██░░░░██
 ░██          ███████░  ██░   ██    ░██     ██    ██ ░██    ██    ░██
 ░████████░   ██░░░░██░ ████████    ░██     ██   ░██  ██   ░██
 ░██░░░░░░░   ██   ░██░ ██░░░░██    ░██     ██   ░██  ██   ░██
 ░██      ░   ██   ░██░ ██   ░██    ░██     ██   ░██  ██   ░██
 ░████████░   ██   ░██░ ██   ░██    ░██     ███████  ░███████
  ░░░░░░░░    ░░    ░░  ░░    ░░     ░░     ░░░░░░░   ░░░░░░░

)";
}

// Hàm hiển thị menu hệ thống

   
void hienThiMenu() {
cout<<   "-------------------------------------------------------------\n";
cout<<   "|         🏥 HỆ THỐNG QUẢN LÝ PHÒNG KHÁM THÚ Y 🐶🐱         |\n";
cout<<   "-------------------------------------------------------------\n";
    cout << "==================================================\n";
    cout << "|  [1]  ➕ Nhập thêm dữ liệu mới                  |\n";
    cout << "|  [2]  📂 In danh sách chủ nuôi                  |\n";
    cout << "|  [3]  💊 In danh sách thuốc                     |\n";
    cout << "|  [4]  📜 In danh sách phiếu khám bệnh           |\n";
    cout << "|  [5]  🔍 Tìm kiếm phiếu khám bệnh               |\n";
    cout << "|  [6]  💰 Thống kê doanh thu                     |\n";
    cout << "|  [7]  📈 Thống kê thuốc sử dụng nhiều nhất      |\n";
    cout << "|  [8]  📝 Tạo báo cáo khám bệnh cá nhân          |\n";
    cout << "|  [9]  📤 Xuất phiếu khám bệnh ra file           |\n";
    cout << "|  [10] 🗓️  Lịch nhắc tiêm phòng                   |\n";
    cout << "|  [0]  🚪 Thoát chương trình                     |\n";
    cout << "==================================================\n";
    cout << "🔹 Nhập lựa chọn của bạn: ";
}


// Hàm hiển thị khung viền động khi mở chương trình
void hieuUngVien() {
    string border = "----------------------------------------------";
    for (int i = 0; i <= border.length(); i++) {
        cout << "\r" << border.substr(0, i) << flush;
        this_thread::sleep_for(chrono::milliseconds(30));
    }
    cout << endl;
}

// Hàm chính
int main() {
    

    

    int luaChon;
    do {
        hieuUngVien();   // Hiệu ứng viền mở đầu
        hienThiBanner(); // Hiển thị banner hệ thống
        hienThiMenu();   // Hiển thị menu chức năng // Hiển thị giao diện người dùng
        cin>>luaChon;


        vector <PhieuKhamBenh> danhSachPhieu;
        // Đọc file vào vector
        PhieuKhamBenh::docFile(danhSachPhieu);

        vector<DMThuoc> danhSachThuoc;
        DMThuoc::docFile(danhSachThuoc);

        vector<DMChuNuoi> danhSachChuNuoi;
        DMChuNuoi::docFile(danhSachChuNuoi);

        vector<LichTiemPhong> danhSachLichTiem;
        LichTiemPhong::docDuLieuTuFile(danhSachLichTiem, "LichTiemPhong.txt");
        
        // Khai báo vector doanh thu
        vector<DoanhThu> doanhThuNgay, doanhThuThang, doanhThuNam;

        switch (luaChon) {
            case 1:
                //nhập thêm dữ liệu mới
                break;
            case 2:
                DMChuNuoi::inDanhSachChuNuoi(danhSachChuNuoi);
                break;
            case 3:
                DMThuoc:: inDanhSachThuoc(danhSachThuoc);
                break;
            case 4:
                PhieuKhamBenh::inDanhSachPhieu(danhSachPhieu);
                break;
            case 5:
                PhieuKhamBenh::inPhieuCanTim(danhSachPhieu);
                break;
            case 6:
            

            // Tính doanh thu
            tinhDoanhThu(danhSachPhieu, danhSachThuoc, doanhThuNgay, doanhThuThang, doanhThuNam);

            // Hiển thị thống kê doanh thu
            inThongKeDoanhThu(doanhThuNgay, "NGÀY");
            inThongKeDoanhThu(doanhThuThang, "THÁNG");
            inThongKeDoanhThu(doanhThuNam, "NĂM");
                break;
            case 7:
            
            thongKeLoaiThuoc(danhSachPhieu, danhSachThuoc);
                break;
            case 8: {
                // tạo báo cáo khám bệnh
                    inBaoCaoKhamBenh(danhSachPhieu);
                    break;
                }
            case 9: {
                //xuất phiếu khám bệnh ra file
                    PhieuKhamBenh::xuatPhieuKhamBenhRaFile(danhSachPhieu, "PhieuKhamBenh.csv");
                    break;
                }
            case 10:
            // lịch nhắc tiêm phòng
                LichTiemPhong::lichNhacTiemPhong(danhSachLichTiem);
                break;
            case 0:
                cout << "Thoát chương trình.\n";
                break;
            default:
                cout << "Lựa chọn không hợp lệ! Vui lòng thử lại.\n";
                break;
            
        }
        cout << "Nhấn phím bất kỳ để tiếp tục...\n";
        cin.ignore();
        cin.get();
    } while (luaChon != 0);

    
// int chon;
// cin>>chon;
// switch(chon)
// {
// case 1:
/*1. in danh sách phiếu khám theo thời gian*/
//     vector <PhieuKhamBenh> danhSachPhieu;
//     // Đọc file vào vector
//     PhieuKhamBenh::docFile(danhSachPhieu);

//     // In danh sách
//     PhieuKhamBenh::inPhieuKhamBenh(danhSachPhieu);

// //     break;
// // case 2:

// /*2. tìm kiếm và in phiếu theo số phiếu đã nhập*/
//     PhieuKhamBenh:: inPhieuCanTim(danhSachPhieu);

// //     break;
// // case 3:

// /*3. thống kê doanh thu theo ngày tháng năm*/

// vector<DMThuoc> danhSachThuoc;

// // Đọc dữ liệu từ file
// DMThuoc::docFile(danhSachThuoc);


// // Khai báo vector doanh thu
// vector<DoanhThu> doanhThuNgay, doanhThuThang, doanhThuNam;

// // Tính doanh thu
// tinhDoanhThu(danhSachPhieu, danhSachThuoc, doanhThuNgay, doanhThuThang, doanhThuNam);

// // Hiển thị thống kê doanh thu
// inThongKe(doanhThuNgay, "NGÀY");
// inThongKe(doanhThuThang, "THÁNG");
// inThongKe(doanhThuNam, "NĂM");

    
// //     break;    

// // default:
// // cout <<"Thoát!";
// //  break;
// // }

// /*4. Thống kê loại thuốc được sử dụng nhiều nhất*/
// thongKeLoaiThuoc(danhSachPhieu, danhSachThuoc);



return 0;

}