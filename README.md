# lib_rf_stm32f1
Establish a wireless data transmission and reception system between two STM32 microcontrollers (STM32F103 and STM32F407) using RF modules operating at the 2.4GHz radio frequency band (e.g., nRF24L01).

Thiết lập hệ thống truyền nhận dữ liệu không dây giữa 2 vi điều khiển STM32 (STM32F103 và STM32F407) thông qua module RF sử dụng sóng vô tuyến tần số 2.4GHz (ví dụ: nRF24L01).


---

## ⚙️ Features

- SPI-based communication with nRF24L01+ modules
- HAL drivers used for portability and maintainability
- Basic TX/RX data exchange
- UART output for monitoring received data
- Easily portable to other STM32 devices

---

## 🔌 Hardware Requirements

| Device             | Quantity |
|--------------------|----------|
| STM32F103C8T6      | 1        |
| STM32F407VGT6      | 1        |
| nRF24L01+ Module   | 2        |
| 3.3V Regulated Power Supply | 2 |
| Jumper Wires       | Several  |
| Capacitor 10µF     | 2 (optional but recommended) |

⚠️ **Note:** nRF24L01+ modules are sensitive to unstable voltage. Ensure a clean 3.3V supply with decoupling capacitors near the VCC/GND pins.

---

## 🔗 Wiring (SPI Interface)

| nRF24L01+ | STM32 Pin (example) |
|-----------|---------------------|
| VCC       | 3.3V                |
| GND       | GND                 |
| CE        | PA0                 |
| CSN       | PA4 (SPI_NSS)       |
| SCK       | PA5 (SPI_SCK)       |
| MISO      | PA6 (SPI_MISO)      |
| MOSI      | PA7 (SPI_MOSI)      |
| IRQ       | Not connected       |

✅ You can change CE/CSN pins by modifying the `nrf24l01p.c/h` configuration.

---

## 🛠️ Build and Flash Instructions

1. Open STM32CubeIDE.
2. Import `Rf_f1` and `Rf_f4` as separate projects.
3. Connect each board via ST-Link or USB and build the project.
4. Flash each firmware to the correct board:
   - `Rf_f1` → STM32F103 (Transmitter)
   - `Rf_f4` → STM32F407 (Receiver)
5. Open UART terminal on PC to monitor receiver output.

---

## 🧪 Expected Behavior

- **F103** sends a data packet periodically (e.g., `"Hello F4"`).
- **F407** receives the packet and prints it to UART.
- You can verify the result using PuTTY, TeraTerm, or Serial Monitor at 115200 baud.

---

## 🚀 Future Improvements

- Add two-way communication
- Support for more payload types (e.g., sensor data)
- Interrupt-based RX handling
- Use of FreeRTOS
- Display received data on OLED or LCD

---

## 📄 License

This project is licensed under the MIT License.  
Feel free to use and modify for your own projects.

---

## 🙋‍♂️ Author

vjezxje 
GitHub: [https://github.com/vjezxje](https://github.com/vjezxje)

---



