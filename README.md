# Vampire-Deauther
Pentesting 2.4ghz 5ghz
# BW16 y Flipper Zero
⚠️ **ADVERTENCIA**: Solo para pruebas éticas en redes propias o autorizadas.  
⚠️ **ADVERTENCIA**: El proyecto es mcon fines educativo y para pentesting.  
⚠️ **ADVERTENCIA**: esta en modo beta, apenas haciendo funcionar la aplicacion del flipper zero (con firmware Momentum).  

## Proyecto basado en estos repositorios:
https://github.com/tesa-klebeband/RTL8720dn-Deauther (para uso del firmware del BW16)  
https://github.com/dkyazzentwatwa/cypher-5G-deauther (para el uso del firmware del BW16)  
https://github.com/ultramarinez/RTL8720dn-5GHz-Wifi-Deauther/tree/main (para el uso del firmware del BW16)  
https://github.com/0xchocolate/flipperzero-wifi-marauder/tree/feature_wifi_marauder_app (para asimilar opciones del menu en el flipper zero)

## Características  
- Deauth 2.4GHz y 5ghz(Por el BW16 que es dual band).  
- Bluetooth Jammer (BLE Spam + Classic). (ya que exista libreria de bt para el SW16)  
- Control via Flipper Zero (.fap).  (basado en el menu de wifi marauder)  

## Uso  
1. Carga el firmware en el BW16.  
2. Abre la app en el Flipper Zero.  
3. Selecciona el modo (deauther / sniff etc.).  

## Contribuir  
Envía PRs con mejoras o reporta issues.  

Estructura del Menu en Flipper Zero:  
applications_user/  
└── vampire_deauther/  
    ├── vampire_deauther.c    # Punto de entrada principal  
    ├── vampire_deauther.h    # Definiciones principales  
    ├── views/  
    │   ├── view_main.c       # Lógica de la interfaz  
    │   └── view_main.h       # Definiciones de la vista  
    ├── bw16_commands.h       # Comandos BW16  
    └── application.fam       # Configuración de compilación  
    
  

    
##Estructura del firmware:

/Vampire-Deauther/  
└── BW16-Firmware/  
    ├── bw16_uart_firmware.ino        # Archivo principal  
    ├── debug.h                   # Configuraciones globales  
    ├── wifi_cust_tx.cpp  
    ├── wifi_cust_tx.h  
    
