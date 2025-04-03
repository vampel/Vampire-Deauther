
#ifndef WIFI_CUST_TX_H
#define WIFI_CUST_TX_H

void wifi_cust_tx_init();
void wifi_scan();
void deauth_attack(const char* target_mac);
void beacon_spam(const char* ssid);

#endif
