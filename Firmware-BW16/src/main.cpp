#include <Core.h>

void setup() {
    Core::begin();
    Serial.begin(115200);
}

void loop() {
    if (Serial.available()) {
        String cmd = Serial.readStringUntil('\n');
        if (cmd == "ATTACK") Core::wifi_attack(true);
        else if (cmd == "BTJAM") Core::bt_jam(true);
    }
}
