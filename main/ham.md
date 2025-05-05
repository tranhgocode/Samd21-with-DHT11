## 1. giải thích các hàm sử dụng GPIO trong ASF của microchip

* `port_get_config_defaults` : có tác dụng khởi tạo một cấu trúc cấu hình chân GPIO (đối tượng `struct port_config`)
  * Chế độ ngõ ra/ngõ vào (direction).
  * Trạng thái pull-up/pull-down (input pull).
  * Các thiết lập khác như mức đầu ra ban đầu (output level).

* `port_pin_set_config` :  áp dụng cấu hình từ một đối tượng `struct port_config` lên một chân GPIO cụ thể, tức là ghi các thiết lập (hướng, pull‑up/pull‑down, drive strength, multiplexing, sense….) vào thanh ghi điều khiển của chân đó

```c
struct port_config cfg;
port_get_config_defaults(&cfg);       // Lấy các giá trị mặc định vào cfg
cfg.direction = PORT_PIN_DIR_OUTPUT;  // Thay đổi nếu cần (ví dụ: output)
cfg.input_pull = PORT_PIN_PULL_UP;    // Bật pull‑up nếu muốn
port_pin_set_config(PIN_PA21, &cfg);  // Áp dụng cấu hình cho chân PA21
```

* `port_pin_set_output_level` : dùng để đặt mức logic (cao/thấp) cho một chân GPIO đã được cấu hình ở chế độ ***output***
```c
    // 1. Đưa PA21 lên mức cao (bật LED)
    port_pin_set_output_level(PIN_PA21, true);

    // 2. Đưa PA21 về mức thấp (tắt LED)
    port_pin_set_output_level(PIN_PA17, false);
```
  
* `port_pin_get_input_level` : dùng để đọc mức logic hiện tại (HIGH/LOW) của một chân GPIO đã được cấu hình ở chế độ ***input***

```c
  // 3. Đọc trạng thái input của PA17
    while (1) {
        bool is_high = port_pin_get_input_level(PIN_PA21);
        if (is_high) {
            // Chân đang ở mức HIGH (ví dụ nút nhấn không được nhấn)
        } else {
            // Chân đang ở mức LOW (ví dụ nút nhấn được nhấn xuống)
        }
        delay_ms(100);
    }
```

