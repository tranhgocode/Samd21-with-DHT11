# Samd21-with-DHT11
 this github will guide how to connect SAMD21G17D with DHT11

## Bước 1 : set up với mircrochip studio
* kết nối với board
* ấn vào file -> project -> GCC C ASF Board Project
  * đổi tên ở name 
  * đổi địa chỉ file ở local
    
<img src="img/buoc11.png" alt="bước 1" width="800" height="600">
 
* chọn Board SAMD21G17D
<img src="img/buoc12.png" alt="bước 2" width="800" height="600">
* ấn ok thì ta sẽ có 1 project

## bước 2 : set up asf
* chọn những thư viện asf mà ta dùng để có thể sử dụng cho samd21
* ấn vào ASF -> chọn ASF Wizard -> add các modules sau
  * **GENERIC BOARD SUPPORT**: Hỗ trợ cơ bản cho board SAMD21, khởi tạo phần cứng.
  * **IOPORT - GENERAL PURPOSE I/O SERVICE**: Điều khiển chân I/O cho giao tiếp ngoại vi.
  * **USART - SERIAL INTERFACE**: Giao tiếp UART để gửi/nhận dữ liệu nối tiếp.
  * **DELAY ROUTINES**: Tạo độ trễ chính xác bằng SysTick.
  * **PORT - GPIO PIN CONTROL**: Quản lý chi tiết chân GPIO ở mức phần cứng.
  * **SYSTEM - CORE SYSTEM DRIVER**: Khởi tạo và quản lý hệ thống, clock, nguồn.
  * **STANDARD SERIAL I/O (STDIO)**: In/nhận dữ liệu qua UART bằng printf, scanf.
<img src="img/buoc21.png" alt="bước 3" width="800" height="600">

## bước 3 : viết hàm cho USART để debug

## bước 4 : viết hàm lấy dữ liệu từ DHT11

## bước 5 : kết nối với Tera Term để hiện thị qua cổng COM
