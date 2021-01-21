#include "stm32f103xb.h"
#include "hwlib.hpp"
#include "flash.cpp"
#include "rgbled.cpp"


#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"


//These volatile variables are the interface between the testscript and the testfirmware.
//They are read and written to by the debugger as well as the testfirmware.
volatile uint8_t debuggerFlashOke = 0;
volatile uint8_t debuggerLed = 0;
volatile uint8_t resetTest = 0;


namespace target = hwlib::target;

auto rled = target::pin_out(hwlib::target::pins::led_red);
auto gled = target::pin_out(hwlib::target::pins::led_green);
auto bled = target::pin_out(hwlib::target::pins::led_blue);
auto rgbled = RgbLed(rled, gled, bled);

auto scl = hwlib::target::pin_oc{hwlib::target::pins::eeprom_scl};
auto sda = hwlib::target::pin_oc{hwlib::target::pins::eeprom_sda};
auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);

// To check the flashchip we write 0x00 and 0xFF to it and check the writes with a read.
// This is mostly done to verify the connection between the mcu and the flash chip.
bool performFlashCheck() {
    writeByte(0x00, i2c_bus);
    hwlib::wait_ms(100);
    if (readByte(i2c_bus) == 0x00) {
        hwlib::wait_ms(100);
        writeByte(0xFF, i2c_bus);
        hwlib::wait_ms(100);
        if (readByte(i2c_bus) == 0xFF) {
            hwlib::wait_ms(100);
            writeByte(0x00, i2c_bus);
            hwlib::wait_ms(100);
            if (readByte(i2c_bus) == 0x00) {
                return true;
            }
        }
    }
    return false;
}

int main() {
    rgbled.set(RgbLed::black);
    debuggerFlashOke = performFlashCheck();

    // Depending on the debuggerled variable which is written by the debugger
    // the rgb led is set to a certain color.
    while (true) {
        if (debuggerLed == 1) {
            rgbled.set(RgbLed::red);
        } else if (debuggerLed == 2) {
            rgbled.set(RgbLed::green);
        } else if (debuggerLed == 3) {
            rgbled.set(RgbLed::blue);
        } else {
            rgbled.set(RgbLed::black);
        }

    }
}

#pragma clang diagnostic pop
