# Vampire-Deauther
Pentesting 2.4ghz 5ghz and BT
# BW16 y Flipper Zero
⚠️ **ADVERTENCIA**: Solo para pruebas éticas en redes propias o autorizadas.  

## Características  
- Deauth 2.4GHz (canales personalizables).
- Deauth 5GHz  (canales personalizables).
- Bluetooth Jammer (BLE Spam + Classic).  
- Control via Flipper Zero (.fap).  

## Uso  
1. Carga el firmware en el BW16.  
2. Abre la app en el Flipper Zero.  
3. Selecciona el modo de ataque.  

## Contribuir  
Envía PRs con mejoras o reporta issues.  


Estructura del Código:

Vampire-Deauther/  
/Flipper-Zero/  
│  
├── applications_user/  
│   └── vampire_deauther/  
│       ├── vampire_deauther.c  
│       ├── vampire_deauther.h  
│       ├── application.fam  
│       └── icon.png  
│  
/Firmware_BW16/  
│  
└── Vampire_Deauther/  
    ├── Vampire_Deauther.ino  
    ├── RTWifi.h  
    └── RTBlue.h  
