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


## Características  
- Deauth 2.4GHz y 5ghz(Por el BW16 que es dual band).  se debe usar el BW16 de 22 pins (negro), el BW16e de 30 pines no funciona (azul)  
  
- Control via Flipper Zero (.fap).

## Uso  
1. Carga el firmware en el BW16.  
2. Abre la app en el Flipper Zero.  
3. Selecciona el modo (deauther / sniff etc.).

## Conexiones
BW16 (22 pines)                Flipper Zero GPIO Header
================              =========================

Pin 1  - 3V3   (Rojo)     --->   Pin 9   - 3.3V (salida) ✅  
Pin 2  - GND   (Negro)    --->   Pin 18  - GND ✅  
  
Pin 3  - PA07_TXD (Amarillo) --> Pin 14  - RX (Flipper recibe datos) ✅ //no se ocupara?  
Pin 4  - PA08_RXD (Blanco)   <-- Pin 13  - TX (Flipper transmite datos) ✅ // no se ocupara?  
  
Estamos usando UART0 (lo mismo que en USB-C
  
  
##Estructura del Menu en Flipper Zero:  
applications_user/  
└── vampire_deauther/  
    ├── vampire_deauther.c    # Punto de entrada principal  
    ├── vampire_deauther.h    # Definiciones principales  
    ├── views/  
    │   ├── view_main.c       # Lógica de la interfaz  
    │   └── view_main.h       # Definiciones de la vista  
    └── application.fam       # Configuración de compilación  
    
  

    
##Estructura del firmware:

/Vampire-Deauther/  
└── BW16-Firmware/  
    ├── bw16_uart_firmware.ino        # Archivo principal  
    ├── debug.h                   # Configuraciones globales  
    ├── wifi_cust_tx.cpp  
    ├── wifi_cust_tx.h  
    
