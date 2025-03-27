#include <RTWifi.h>
#include <RTBlue.h>

// En Vampire_Deauther.ino
void handleSerialCommands() {
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        cmd.trim();
        
        // Comandos WiFi
        if (cmd == "WIFI_DEAUTH_ALL") {
            deauthAllNetworks();
        } else if (cmd == "WIFI_DEAUTH_24") {
            deauth24GHz();
        } else if (cmd == "WIFI_DEAUTH_5") {
            deauth5GHz();
        }
        
        // Comandos BT Jammer
        else if (cmd == "BT_JAM_ALL") {
            btJamAll();
        } else if (cmd == "BT_JAM_CLASSIC") {
            btJamClassic();
        } else if (cmd == "BT_JAM_BLE") {
            btJamBLE();
        }
    }
}
