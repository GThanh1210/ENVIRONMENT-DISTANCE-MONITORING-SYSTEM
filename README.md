# ĐỒ ÁN: HỆ THỐNG GIÁM SÁT MÔI TRƯỜNG VÀ KHOẢNG CÁCH THỜI GIAN THỰC (STM32 & FreeRTOS)
1. Giới Thiệu Chung

Dự án nghiên cứu, thiết kế và chế tạo **Hệ thống giám sát môi trường và khoảng cách thời gian thực** dựa trên vi điều khiển STM32F103 kết hợp hệ điều hành thời gian thực FreeRTOS. 

Hệ thống cho phép thu thập tự động các thông số nhiệt độ, độ ẩm môi trường và đo khoảng cách vật cản, xử lý dữ liệu đa nhiệm theo thời gian thực, hiển thị trực quan lên màn hình LCD 2004 và truyền dữ liệu giám sát/chẩn đoán qua cổng nối tiếp UART.

 2. Mục Tiêu Đồ Án

- Về phần cứng:
  - Thiết kế và kết nối thành công mạch vi điều khiển STM32F103C8T6 với các cảm biến thực tế (DHT11, HC-SR04) và màn hình hiển thị LCD 2004 qua giao tiếp I2C.

- Về phần mềm & thuật toán:
  - Ứng dụng hệ điều hành thời gian thực FreeRTOS để quản lý đa nhiệm (Multi-tasking), tối ưu hóa thời gian phản hồi của hệ thống.
  - Sử dụng cơ chế Message Queue truyền dữ liệu an toàn giữa các task (Thread-safe) tránh xung đột bộ nhớ.
  - Sử dụng Hardware Timer đo độ rộng xung ở mức microsecond để xuất tín hiệu bắt đầu đọc và đo xung Echo.
  - Xây dựng module xuất log kiểm thử (Debug) linh hoạt qua UART .

---

 3. Kiến Trúc Hệ Thống & Sơ Đồ Khối

Sơ Đồ Luồng Xử Lý FreeRTOS
Task DHT11 (Priority: High) & Task HC-SR04 (Priority: Medium) ➔ FreeRTOS Queue ➔ Task LCD (Priority: Low)

<img width="1920" height="2560" alt="8600eeb315d69588ccc73" src="https://github.com/user-attachments/assets/3e84a61e-545f-4c06-9e08-e0ce850e8695" />
<img width="1920" height="2560" alt="71d7866a7d0ffd51a41e2" src="https://github.com/user-attachments/assets/f7125d75-7876-4ea6-9bd1-30c96ff23281" />
<img width="1920" height="2560" alt="5050e6ef1d8a9dd4c49b1" src="https://github.com/user-attachments/assets/1e41355c-b940-4d8c-b3dd-1679dd0f0b29" />
