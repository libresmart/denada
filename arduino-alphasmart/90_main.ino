const byte LED_PIN    =    2;

//// SETUP
void setup() {
  Serial.begin(115200);  // Allow serial output
  Serial.println("----------------------------------------");
  Serial.println("Setting up the ESP32...");
  pinMode(LED_PIN, OUTPUT);
  dev_buffer_init();
  Serial.println("Setup complete.");
}

//// LOOP
void loop() {
  char key = keypad.getKey();
  if (key) {
    switch (key) {
      case '*' : move_point(-1); break;
      case '#' : move_point(+1); break;
      case 'A' : del_chars(-1); break;
      case 'B' : del_chars(+1); break;
      case 'C' : set_point(0); break;
      case 'D' : dev_buffer_init(); break;
      case '1' : insert_char('A'); break;
      case '2' : insert_char('B'); break;
      case '3' : insert_char('C'); break;
      case '4' : insert_char('D'); break;
      case '5' : insert_char('E'); break;
      case '6' : insert_char('F'); break;
      case '7' : insert_char('G'); break;
      case '8' : insert_char('H'); break;
      case '9' : insert_char('I'); break;
      case '0' : insert_char('Z'); break;
      default  : insert_char(key);
    }
    Serial.println("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    dev_print_state();
  }
}
