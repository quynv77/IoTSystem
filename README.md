# IoTSystem
Các version của tool dùng để phát triển Project:
- TouchGFX Desginer: 4.25.0
- STM32CubeIDE: 1.18.1
  Cách cài đặt:
  1. vào TouchGFX Desginer chọn thêm Flex Button và cấu hình Interactions (như trong file docx hướng dẫn)
  2. sau khi thiết lập giao diện và cấu hình rồi, nhấn Generate Code
  3. vào STM32CubeIDE mở source code từ C:\TouchGFXProjects
  4. chỉnh sửa file Screen1View.cpp và Screen1View.hpp như mẫu trong source code
  5. ở dòng STM32F429I_DISCO_REV_D01 (in STM32CubeIDE) click chuột phải, build và run as, nếu STM32CubeIDE có báo lỗi thiếu thư viện gì, thiếu file nào, thì chỉ cần truy cập đúng đường dẫn, và dán file vào từ source code mẫu
