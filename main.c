#include <stdio.h>

// Dinh nghia cau truc kien hang
typedef struct {
    char ma_kien_hang[20];
    float trong_luong;      // Don vi: kg
    float nhiet_do_yeu_cau; // Don vi: do C
} PalletItem;

// Dinh nghia cau truc ke kho
typedef struct {
    char ma_ke[20];
    float trong_luong_hien_tai; // Don vi: kg
    float tai_trong_toi_da;     // Don vi: kg (co dinh 500.0 kg)
    int la_kho_lanh;            // 1: Kho lanh, 0: Kho thuong
} WarehouseShelf;

// Ham kiem tra an toan khi nhap kien hang vao ke kho
// Tra ve 1 neu hop le, tra ve 0 neu vi pham quy tac an toan
int kiem_tra_nhap_kho(WarehouseShelf ke, PalletItem kien) {
    // Kiem tra tai trong toi da
    if (ke.trong_luong_hien_tai + kien.trong_luong > ke.tai_trong_toi_da) {
        return 0; // Vi pham tai trong
    }

    // Kiem tra dieu kien kho lanh
    if (ke.la_kho_lanh == 1) {
        // DA SUA LOI LOGIC: Chuyen || thanh &&
        // Nhiet do phai DONG THOI >= -18.0 VA <= 5.0
        if (kien.nhiet_do_yeu_cau >= -18.0 && kien.nhiet_do_yeu_cau <= 5.0) {
            return 1; // Cho phep nhap kho
        } else {
            return 0; // Khong phu hop nhiet do
        }
    }

    return 1; // Hop le cho kho thuong
}

// Ham phu tro de in ket qua kiem thu
void in_ket_qua_kiem_thu(WarehouseShelf ke, PalletItem kien, const char* ten_test) {
    printf("--- %s ---\n", ten_test);
    printf("Ma kien: %s | Trong luong: %.1f kg | Nhiet do yeu cau: %.1f C\n",
           kien.ma_kien_hang, kien.trong_luong, kien.nhiet_do_yeu_cau);
           
    int ket_qua = kiem_tra_nhap_kho(ke, kien);
    if (ket_qua == 1) {
        printf("=> KET QUA: CHO PHEP NHAP KHO!\n\n");
    } else {
        printf("=> KET QUA: TU CHOI NHAP KHO (Vi pham an toan)!\n\n");
    }
}

int main() {
    // Khoi tao ke lanh A1 (Da chua 350.0 kg)
    WarehouseShelf ke_lanh_A1 = {"KE-COLD-01", 350.0, 500.0, 1};
    
    printf("THONG TIN KE KHO: Ma ke: %s | Tai trong hien tai: %.1f kg | Tai trong toi da: %.1f kg | Kho lanh: %s\n\n", 
           ke_lanh_A1.ma_ke, ke_lanh_A1.trong_luong_hien_tai, ke_lanh_A1.tai_trong_toi_da,
           ke_lanh_A1.la_kho_lanh ? "Co" : "Khong");

    // Test Case 1: Kien hang hop le vao kho lanh (Hop le nhiet do & tai trong)
    PalletItem kien_hop_le = {"PL-OK-01", 100.0, -10.0};
    in_ket_qua_kiem_thu(ke_lanh_A1, kien_hop_le, "TEST CASE 1: Kien hang hop le vao kho lanh");

    // Test Case 2: Kien hang khong du dieu kien nhiet do kho lanh
    PalletItem kien_sai_nhiet_do = {"PL-HOT-02", 80.0, 25.0};
    in_ket_qua_kiem_thu(ke_lanh_A1, kien_sai_nhiet_do, "TEST CASE 2: Kien hang vi pham nhiet do");

    // Test Case 3: Kien hang vuot qua tai trong toi da cua o ke
    PalletItem kien_qua_tai = {"PL-HEAVY-03", 200.0, 0.0}; // 350 + 200 = 550 > 500
    in_ket_qua_kiem_thu(ke_lanh_A1, kien_qua_tai, "TEST CASE 3: Kien hang vi pham tai trong");

    return 0;
}