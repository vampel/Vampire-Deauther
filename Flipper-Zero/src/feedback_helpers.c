#include <furi.h>
#include <furi_hal.h>

void vibrate(uint8_t duration_ms) {
    furi_hal_vibro_on(true);
    furi_delay_ms(duration_ms);
    furi_hal_vibro_on(false);
}

void blink_led() {
    furi_hal_light_set(LightGreen, 0xFF);
    furi_delay_ms(100);
    furi_hal_light_set(LightGreen, 0x00);
}

void provide_feedback(bool success) {
    if (success) {
        furi_hal_vibro_on(true);
        furi_hal_light_set(LightGreen, 0xFF);
        furi_delay_ms(150);
        furi_hal_vibro_on(false);
        furi_hal_light_set(LightGreen, 0x00);
    } else {
        furi_hal_light_set(LightRed, 0xFF);
        furi_delay_ms(300);
        furi_hal_light_set(LightRed, 0x00);
    }
}
