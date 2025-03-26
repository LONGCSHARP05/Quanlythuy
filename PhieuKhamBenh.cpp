#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include "PhieuKhamBenh.hpp"
#include "DMChuNuoi.hpp"
#include "DMThuoc.hpp"

using namespace std;
// sử dụng file cpp để mở rộng các định nghĩa, hàm.. từ file hpp


/*3. Thống kê doanh thu theo ngày tháng năm*/


// đọc dữ liệu, và in vào vector
// cắt chuỗi ngày khám thành năm, năm tháng, năm tháng ngày. Và nhóm chúng theo 3 vector 
// tính doanh thu theo năm: duyệt từng vector nếu cùng năm thì cộng dồn doanh thu năm đó

// Struct lưu doanh thu theo ngày/tháng/năm
struct DoanhThu {  //tạo struct doanh thu để lưu doanh thu, có thuộc tính ngày và tongTien
    string ngay;
    int tongTien;
};

// Tìm giá thuốc từ danh sách `DMThuoc`
int layGiaThuoc(vector<DMThuoc>& danhSachThuoc, const string& maThuoc) {
    for (auto& thuoc : danhSachThuoc) {
        if (thuoc.getMaThuoc() == maThuoc) {
            return thuoc.getGiaBan();
        }
    }
    return 0;
}

// Tìm vị trí của ngày/tháng/năm trong vector `DoanhThu`
int timViTri(vector<DoanhThu>& ds, const string& ngay) {
    for (int i = 0; i < ds.size(); i++) {
        if (ds[i].ngay == ngay) {
            return i;
        }
    }
    return -1;
}

// Tính doanh thu theo ngày, tháng, năm
void tinhDoanhThu(vector<PhieuKhamBenh>& danhSachPhieu, vector<DMThuoc>& danhSachThuoc,
                   vector<DoanhThu>& doanhThuNgay, vector<DoanhThu>& doanhThuThang, vector<DoanhThu>& doanhThuNam) {
    for (auto& pk : danhSachPhieu) {
        int giaThuoc = layGiaThuoc(danhSachThuoc, pk.getMaThuoc());
        int thanhTien = giaThuoc * pk.getSoLuongThuoc();

        string ngay = pk.getNgayKham();
        string thangNam = ngay.substr(0, 7); // "YYYY-MM"
        string nam = ngay.substr(0, 4); // "YYYY"

        // Cộng dồn doanh thu theo ngày
        int viTriNgay = timViTri(doanhThuNgay, ngay);
        if (viTriNgay != -1) {
            doanhThuNgay[viTriNgay].tongTien += thanhTien;
        } else {
            doanhThuNgay.push_back({ngay, thanhTien});
        }

        // Cộng dồn doanh thu theo tháng
        int viTriThang = timViTri(doanhThuThang, thangNam);
        if (viTriThang != -1) {
            doanhThuThang[viTriThang].tongTien += thanhTien;
        } else {
            doanhThuThang.push_back({thangNam, thanhTien});
        }

        // Cộng dồn doanh thu theo năm
        int viTriNam = timViTri(doanhThuNam, nam);
        if (viTriNam != -1) {
            doanhThuNam[viTriNam].tongTien += thanhTien;
        } else {
            doanhThuNam.push_back({nam, thanhTien});
        }
    }
}

// Hàm in thống kê doanh thu
void inThongKeDoanhThu(const vector<DoanhThu>& ds, const string& loai) {
    cout << "=== DOANH THU THEO " << loai << " ===\n";
    for (const auto& item : ds) {
        cout << loai << ": " << item.ngay << " | Doanh thu: " << item.tongTien << " VND\n";
    }
    cout << endl;
}


/*4. Thống kê loại thuốc sử dụng nhiều nhất*/

// duyệt tất cả những phiếu khám unique trong danh sách phiếu khám vào 1 vector khác(trước đó đã vector đọc dữ liệu phiếu khám từ file PhieuKhamBenh.txt)
// nếu phiếu khám đã tồn tại trong vector thì cộng dồn số lượng thuốc vào số lượng thuốc đã có
// sau đó sắp xếp vector theo số lượng thuốc giảm dần
// tìm max của số lượng thuốc và in ra mã thuốc, tên thuốc và số lượng thuốc của thuốc đó
void thongKeLoaiThuoc(vector<PhieuKhamBenh>& danhSachPhieu, vector<DMThuoc>& danhSachThuoc) {
    // Tạo vector chứa các phiếu khám unique
    vector<PhieuKhamBenh> dsPhieuUnique;
   
// thêm các phiếu khám vào vector dsPhieuUnique
    for (auto& pk : danhSachPhieu) {
        bool found = false;
        for (int i = 0; i < dsPhieuUnique.size(); i++) {
            if (dsPhieuUnique[i].getMaThuoc() == pk.getMaThuoc()) {  //  So sánh theo MaThuoc
                dsPhieuUnique[i].setSoLuongThuoc(dsPhieuUnique[i].getSoLuongThuoc() + pk.getSoLuongThuoc());
                found = true;
                break;
            }
        }
        if (!found) {
            dsPhieuUnique.push_back(pk);
        }
    }
    
 
    // Sắp xếp theo số lượng thuốc giảm dần

    for (int i = 0; i < dsPhieuUnique.size(); i++) {
        for (int j = i + 1; j < dsPhieuUnique.size(); j++) {
            if (dsPhieuUnique[i].getSoLuongThuoc() < dsPhieuUnique[j].getSoLuongThuoc()) { //so sánh 2 giá trị(soLuongThuoc) liên tiếp
                PhieuKhamBenh temp = dsPhieuUnique[i];
                dsPhieuUnique[i] = dsPhieuUnique[j];
                dsPhieuUnique[j] = temp;
            }
        }
    }
    

    
    cout << "=== THỐNG KÊ LOẠI THUỐC SỬ DỤNG NHIỀU NHẤT ===\n";

    if (dsPhieuUnique.empty()) { //nếu vector rỗng thì in ra không có dữ liệu để thống kê
        cout << "Không có dữ liệu để thống kê.\n";
        return;
    }

    // Lấy số lượng thuốc lớn nhất sau khi sắp xếp
    int maxSoLuong = dsPhieuUnique[0].getSoLuongThuoc();

    for (auto& pk : dsPhieuUnique) {
        if (pk.getSoLuongThuoc() == maxSoLuong) {
            string tenThuoc = "Không tìm thấy"; // gán Mặc định nếu không tìm thấy mã thuốc giống với mã trong DMThuoc

            // Tìm tên thuốc từ danh sách thuốc
            for (auto& thuoc : danhSachThuoc) {
                if (thuoc.getMaThuoc() == pk.getMaThuoc()) {
                    tenThuoc = thuoc.getTenThuoc();
                    break;
                }
            }

            cout << "Mã thuốc: " << pk.getMaThuoc() << " | Tên thuốc: " << tenThuoc << " | Số lượng: " << pk.getSoLuongThuoc() << endl;
        }
    }
    cout << endl;

}



    /* Tạo báo cáo khám bệnh theo ngày */
    void inBaoCaoKhamBenh(const vector<PhieuKhamBenh>& danhSachPhieu){
        string ngayKham;
        cout << "Nhập ngày khám cần tạo báo cáo: ";
        cin >> ngayKham;
        cout << "\n====== BÁO CÁO KHÁM BỆNH NGÀY   " << ngayKham<<"  =======" << endl;
        cout << "| Ngày khám | Số phiếu | Mã chủ nuôi | Mã thuốc | Slg thuốc |     Triệu chứng   |   Chẩn đoán        |" << endl;
        for (const auto& phieu : danhSachPhieu){
            if (phieu.getNgayKham() == ngayKham){
                cout << left << setw(15) << phieu.getNgayKham() << setw(10) << phieu.getSoPhieu() << setw(13) << phieu.getMaChuNuoi()
                     << setw(15) << phieu.getMaThuoc() << setw(12) << phieu.getSoLuongThuoc() << setw(25) << phieu.getTrieuChung()
                     << setw(25) << phieu.getChanDoan() << endl;
                cout << "========================================================================================================" << endl;
            } else cout<<"Không có dữ liệu ngày báo cáo.";
        }
    }





