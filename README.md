# DeNada
Free  and Open Source AlphaSmart Neo alternative.

There's a wiki
https://github.com/libresmart/denada/wiki

Would you like to be a project maintainer?
Open an issue requesting maintainer privileges

## Instructions?
Installation/Setup:
* Arduino IDE from https://www.arduino.cc/en/software
* Open arduino-alphasmart/arduino-alphasmart.ino
* Install Keypad Library
  * Sketch -> Include Library -> Manage Librarires -> "Keypad" -> Install
* Install Board Library
  * Arduino -> Preferences -> Additional Boards Manager URLs: URL_HERE -> OK
    * "https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json"
  * Tools -> Board: -> Boards Manager -> "esp32" -> Install
  * Tools -> Board: -> ESP32 Arduino -> "ESP32 Dev Module"
* Upload Code to ESP32
  * Connect ESP32 to computer via USB.
  * Select Port
    * Tools -> Port: -> /dev/cu.usbserial-0001
    * Your port may be different
  * Hold "BOOT" button on ESP32 board
  * Click the "Upload" button in the Arduino IDE
  * Wait for "Connecting..."
  * Let go of "BOOT" button on ESP32
  * Wait for upload to complete
* Use Arduino IDE as a serial terminal
  * Tools -> Serial Monitor -> 115200 baud
* Connect keypad on pins 3,21,19,18,5,17,16,4
  * believe it or not, these are contiguous on the board
  * If the usb cable is down, and you are looking at the ESP32 Chip,
  these pins are on the right, skipping the first 3 from the top.
* Press keypad buttons to watch things change!
