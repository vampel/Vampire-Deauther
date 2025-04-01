# Vampire-Deauther
Pentesting 2.4ghz 5ghz
# BW16 y Flipper Zero
⚠️ **ADVERTENCIA**: Solo para pruebas éticas en redes propias o autorizadas.  
⚠️ **ADVERTENCIA**: esta en modo beta, apenas funciona la aplicacion del flipper zero

Proyecto basado en estos repositorios:
https://github.com/tesa-klebeband/RTL8720dn-Deauther
https://github.com/dkyazzentwatwa/cypher-5G-deauther
https://github.com/ultramarinez/RTL8720dn-5GHz-Wifi-Deauther/tree/main
https://github.com/0xchocolate/flipperzero-wifi-marauder/tree/feature_wifi_marauder_app

## Características  
- Deauth 2.4GHz y 5ghz(Por el BW16 que es dual band).  
- Bluetooth Jammer (BLE Spam + Classic). (ya que exista libreria de wifi para el SW16)  
- Control via Flipper Zero (.fap).  (basado en el menu de wifi marauder)  

## Uso  
1. Carga el firmware en el BW16.  
2. Abre la app en el Flipper Zero.  
3. Selecciona el modo (deauther / sniff etc.).  

## Contribuir  
Envía PRs con mejoras o reporta issues.  

Estructura del Menu en Flipper Zero:  
Vampire-Deauther/  
├── application.fam  
├── vampire_deauther.c  
├── wifi_deauther.h  
├── wifi_deauther.c  
├── bw16_protocol.h  
├── bw16_protocol.c  
├── scan_manager.h  
├── scan_manager.c  
└── assets/  
    └── icon.png   
    
  

    
##Estructura del firmware:

/Vampire-Deauther/  
└── BW16-Firmware/  
    ├── Vampire-Deauther.ino        # Archivo principal  
    ├── config.h                    # Configuraciones globales  
    ├── wifi_scan.h              # Escaneo WiFi  
    ├── wifi_scan.cpp  
    ├── wifi_attack.h             # Ataques WiFi  
    ├── wifi_attack.cpp  
    ├── flipper_serial.h            # Comunicación con Flipper  
    ├── flipper_serial.cpp  
    ├── platformio.ini              # Configuración de compilación  
    ├── flipper.h
    ├── flipper.cpp
