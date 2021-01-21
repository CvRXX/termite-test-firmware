//
// Created by carlos on 1/21/21.
//

void writeByte(uint8_t byte, hwlib::i2c_bus_bit_banged_scl_sda &i2cbus) {
    i2cbus.primitives.write_start();
    i2cbus.primitives.write((uint8_t) 0b10100010);
    while (!i2cbus.primitives.read_ack());
    i2cbus.primitives.write(0);
    i2cbus.primitives.read_ack();
    i2cbus.primitives.write(1);
    i2cbus.primitives.read_ack();
    i2cbus.primitives.write(byte);
    i2cbus.primitives.read_ack();
    i2cbus.primitives.write_stop();
}

uint8_t readByte(hwlib::i2c_bus_bit_banged_scl_sda &i2cbus) {
    i2cbus.primitives.write_start();
    i2cbus.primitives.write((uint8_t) 0b10100010);
    while (!i2cbus.primitives.read_ack());
    i2cbus.primitives.write(0);
    i2cbus.primitives.read_ack();
    i2cbus.primitives.write(1);
    i2cbus.primitives.read_ack();
    i2cbus.primitives.write_stop();
    i2cbus.primitives.write_start();
    i2cbus.primitives.write((uint8_t) 0b10100011);
    while (!i2cbus.primitives.read_ack());
    auto byte = i2cbus.primitives.read_byte();
    i2cbus.primitives.write_nack();
    i2cbus.primitives.write_stop();
    return byte;
}