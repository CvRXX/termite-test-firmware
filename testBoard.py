from pyocd.core.helpers import ConnectHelper
from pyocd.debug.elf import decoder
from elftools.elf.elffile import ELFFile
import logging
logging.basicConfig(level=logging.ERROR)

def getSymbol(symbol):
    file = open("cmake-build-debug-arm-toolchain/testFirmware_f103.elf","rb")
    ELF = ELFFile(file)
    decode = decoder.ElfSymbolDecoder(ELF)
    return decode.get_symbol_for_name(symbol)

def writeMemory(address, value):
    with ConnectHelper.session_with_chosen_probe() as session:

        board = session.board
        target = board.target
        target.write8(address, value)

def readMemory(address):
    with ConnectHelper.session_with_chosen_probe() as session:
        board = session.board
        target = board.target
        return target.read8(address)

def testEeprom():
    flashCheckSymbol = getSymbol("debuggerFlashOke")
    if readMemory(flashCheckSymbol.address)==0:
        print("false")
        return False
    return True

def testLed(led):
    colors = ["red","green","blue"]
    ledSymbol = getSymbol("debuggerLed")
    color = colors[led-1]
    writeMemory(ledSymbol.address, 0)
    print("is the " + color + " led off? y/n")
    userInput = input()
    while not (userInput == "y" or  userInput == "n"):
        print("is the " + color + " led off? y/n")
        userInput = input()
    if userInput == "n":
        return False
    writeMemory(ledSymbol.address, led)
    print("is the " + color + " led on? y/n")
    userInput = input()
    while not (userInput == "y" or  userInput == "n"):
        print("is the " + color + " led on? y/n")
        userInput = input()
    if userInput == "y":
        return True
    return False

def testResetButton():
    resetTest = getSymbol("resetTest")
    if readMemory(resetTest.address)==0:
        return True
    return False

def zeroResetTest():
    resetTest = getSymbol("resetTest")
    writeMemory(resetTest.address, 1);

def passedFailed(boolean):
    if boolean:
        return "PASSED"
    return "FAILED"


print ("TERMITE TESTING SOFTWARE")
print ("Connecting to board....")
print("Connected!")

print("checking eeprom chip")
flashPassed = testEeprom()
print("check completed")
print("LED checking:")
rledPased = testLed(1)
gledPased = testLed(2)
bledPased = testLed(3)



print("Resetbutton testing")
zeroResetTest()
print("Please press the reset button and press enter")
input()
resetPassed = testResetButton()


print("TESTREPORT:")
print("EEPROM: " + passedFailed(flashPassed))
print("RED LED: " + passedFailed(rledPased))
print("GREEN LED: " + passedFailed(gledPased))
print("BLUE LED: " + passedFailed(bledPased))
print("RESET BUTTON: " + passedFailed(resetPassed))