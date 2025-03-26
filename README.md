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
├── firmware/  
│   ├── lib/  
│   │   └── WiFiDeauth/
│   │       ├── WiFiDeauth.h          # Interfaz Deauth  
│   │       └── WiFiDeauth.cpp        # Implementación Low-Level  
│   ├── src/  
│   │   ├── uart/  
│   │   │   ├── uart_handler.h        # Gestión UART  
│   │   │   ├── uart_handler.cpp      # Parser de comandos  
│   │   │   ├── mac_parser.h          # Validación MAC  
│   │   │   └── mac_parser.cpp        # Parseo hexadecimal  
│   │   ├── commands.h                # Definición de comandos  
│   │   └── main.cpp                  # Punto de entrada  
│   └── platformio.ini                # Configuración BW16  
└── flipper/  
    ├── resources/  
    │   └── icons/                    # Assets gráficos  
    ├── src/  
    │   ├── uart_helpers.c            # Comunicación UART  
    │   ├── feedback_helpers.c        # Vibración/LED  
    │   ├── views/  
    │   │   ├── menu_view.c           # Menú principal  
    │   │   └── attack_view.c         # Pantalla de ataque  
    │   └── vampire_deauther.c        # App principal  
    └── application.fam               # Metadata Flipper  
