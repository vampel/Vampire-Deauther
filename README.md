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
│   ├── WiFi 2.4GHz Deauth  
│   │    └── estructura como wifi marauder  
│   └── WiFi 5GHz Deauth  
│        └── estructura como wifi marauder  
├── BT Jammer  
│   ├── BT Jammer All (solo iniciar y parar)  
│   ├── BT Jammer Classic (solo iniciar y parar)  
│   └── BT Jammer BLE (solo iniciar y parar)  
└── Settings
    
##Estructura del Código:

Vampire-Deauther/
├── flipper_app/          # App para Flipper (C/Python)  
│   ├── assets/           # Iconos, gráficos  
│   └── vampire_deauther.c # Lógica principal  
├── bw16_firmware/       # Código para BW16  
│   ├── deauth_5ghz/     # Basado en ultramarinez  
│   ├── ble_spam/        # Adaptado de ESP32-BlueJammer  
│   └── main.ino         # Firmware principal  
├── docs/  
│   ├── wiring.md        # Conexión Flipper-BW16  
│   └── commands.md      # Protocolo UART  
└── README.md            # Instrucciones + vídeo demo  
