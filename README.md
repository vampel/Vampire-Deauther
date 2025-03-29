# Vampire-Deauther
Pentesting 2.4ghz 5ghz and BT
# BW16 y Flipper Zero
⚠️ **ADVERTENCIA**: Solo para pruebas éticas en redes propias o autorizadas.  
⚠️ **ADVERTENCIA**: esta en modo beta, apenas funciona la aplicacion del flipper zero

## Características  
- Deauth 2.4GHz y 5ghz(canales personalizables).
- Bluetooth Jammer (BLE Spam + Classic).  
- Control via Flipper Zero (.fap).  

## Uso  
1. Carga el firmware en el BW16.  
2. Abre la app en el Flipper Zero.  
3. Selecciona el modo de ataque.  

## Contribuir  
Envía PRs con mejoras o reporta issues.  

Estructura del Menu en Flipper Zero:
Apps/Vampire deauther  
├── Wifi deauther  
│   ├── WiFi All Deauth  
│   │    └── estructura como wifi marauder  
  

    
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
