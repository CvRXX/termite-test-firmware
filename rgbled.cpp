//
// Created by carlos on 1/21/21.
//
class RgbLed {
public:
    hwlib::target::pin_out &red_led;
    hwlib::target::pin_out &green_led;
    hwlib::target::pin_out &blue_led;

    RgbLed(hwlib::target::pin_out &red_led, hwlib::target::pin_out &green_led, hwlib::target::pin_out &blue_led) :
            red_led(red_led),
            green_led(green_led),
            blue_led(blue_led) {}

    enum Color {
        red,
        green,
        blue,
        magenta,
        yellow,
        cyan,
        white,
        black
    };

    void set(bool r, bool g, bool b) {
        red_led.write(!r);
        green_led.write(!g);
        blue_led.write(!b);
    }

    void set(Color color) {
        if (color == Color::magenta) {
            set(1, 0, 1);
        } else if (color == Color::yellow) {
            set(1, 1, 0);
        } else if (color == Color::cyan) {
            set(0, 1, 1);
        } else if (color == Color::red) {
            set(1, 0, 0);
        } else if (color == Color::green) {
            set(0, 1, 0);
        } else if (color == Color::blue) {
            set(0, 0, 1);
        } else if (color == Color::white) {
            set(1, 1, 1);
        } else if (color == Color::black) {
            set(0, 0, 0);
        }
    }
};
