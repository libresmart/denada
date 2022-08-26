const char CHAR_NUL   =  '.';
const char CHAR_EOL   =  '=';
const char CHAR_SPC   =  '_';
const char CHAR_TAB   =  '~';


void dev_buffer_init() {
  buffer_clear();
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 80; j++) {
      char num = '0' + (j + 1) % 10;
      num = (num == '0') ? ' ' : num;
      insert_char(num);
    }
    insert_char('\n');
  }
}

char dev_debug_char(int location, char character){
  char char_to_print = dev_safe_print(character);
  int i = location;
  char_to_print = (i == buffer.gap_end - 1)               ? 'e' : char_to_print;
  char_to_print = (i == buffer.gap_start)                 ? 's' : char_to_print;
  char_to_print = (i == buff_loc_from_text(buffer.point)) ? '*' : char_to_print;
  return char_to_print;
}

char dev_safe_print(char inChar) {
  switch (inChar) {
    case '\n' : return CHAR_EOL;
    case ' '  : return CHAR_SPC;
    case '\t' : return CHAR_TAB;
    case NULL : return CHAR_NUL;
    default   : return inChar;
  }
}

void dev_hr(int len) {
  for (int i = 0; i < len; i++) {
    Serial.print('-');
  }
}

void dev_print_buffer() {
  Serial.print("|");
  dev_hr(81);
  Serial.print("|\n|");
  char char_to_print = NULL;
  for (int i = 0; i < BUFF_SIZE; i++) {
    Serial.print(dev_debug_char(i, buffer.contents[i]));
    if (i + 1 == BUFF_SIZE) {
      for (; (i + 1) % 81 != 0; i++) {
        Serial.print(dev_debug_char(i+1, '<'));
      }
    }
    if ( (i + 1) % 81 == 0) {
      Serial.print("|\n|");
    }
  }
  dev_hr(81);
  Serial.println("|");
}

void dev_print_status_line() {
  int bs = 0;
  int be = BUFF_SIZE - 1;
  int gs = buffer.gap_start;
  int ge = buffer.gap_end;
  int point = buffer.point;
  Serial.printf(
    "Buffer Status: point=%d (%d), buffer={%d, %d, %d, %d}, gap_size=%d\n",
    point, buff_loc_from_text(point), bs, gs, ge, be, gap_size()
  );
}

void dev_print_state() {
  dev_print_buffer();
  dev_print_status_line();
  Serial.println("\n");
}
