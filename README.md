# Termite test firmware

This project is aimed at testing the [Termite board](https://github.com/CvRXX/termite) for production mistakes. 
A combination of automatic and manual controlled testing will take place via a python script. 

The python script will ask the firmware to execute certain tasks and checks if they were executed correctly. 
The communication between the firmware and the python script will take place via the debug interface with the use of 
volatile variables.

The script will test the following:
  * Eeprom (Only connectivity not the working of the whole memory range)
  * RGB led 
  * Reset button 

## How to use the test firmware
1. First make the c++ firmware and flash it to the board.
2. Run the board with the st-link v2 programmer connected. 

## What does it look like
The software in action:

    TERMITE TESTING SOFTWARE
    Connecting to board....
    Connected!
    checking eeprom chip
    check completed
    LED checking:
    is the red led off? y/n
    y
    y
    is the red led on? y/n
    n
    n
    is the green led off? y/n
    n
    n
    is the blue led off? y/n
    y
    y
    is the blue led on? y/n
    n
    n
    Resetbutton testing
    Please press the reset button and press enter                       


Test report:

    TESTREPORT:
    EEPROM: PASSED
    RED LED: FAILED
    GREEN LED: FAILED
    BLUE LED: FAILED
    RESET BUTTON: FAILED