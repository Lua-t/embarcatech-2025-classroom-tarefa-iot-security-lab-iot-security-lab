
# Tarefa: IoT Security Lab - EmbarcaTech 2025

Author: **Laura Gomes**

Program : Residência Tecnológica em Sistemas Embarcados

Institution: EmbarcaTech - HBr

Brasília, May 2025

---
This project demonstrates how to use the Raspberry Pi Pico W (BitDogLab board) to connect to Wi-Fi, communicate via MQTT, and securely exchange messages using a simple XOR cipher.

The system publishes encrypted sensor data (simulated as a fixed temperature value) when a button is pressed, and subscribes to the same MQTT topic when the button is released.

**Features**

- 🔗 Wi-Fi connection with SSID and password.

- 📩 MQTT communication (publish/subscribe).

- 🔒 XOR encryption for message payloads.

- ⏱️ 5-second interval between each publish/subscribe.

- 🎛️ Button-controlled logic:

Pressed → Publishes encrypted JSON message.

Released → Subscribes to the same topic.

**Technologies**

- Board: BitDogLab + Raspberry Pi Pico W

- Language: C/C++

**Libraries:**

- pico/stdlib.h (GPIO, timing, etc.)

- pico/cyw43_arch.h (Wi-Fi driver)

- wifi_conn.h (custom Wi-Fi connection functions)

- mqtt_comm.h (custom MQTT functions)

- xor_cipher.h (simple XOR cipher implementation)

---

## 📜 Licença
GNU GPL-3.0.
