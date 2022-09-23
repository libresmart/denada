#include "text_buffer_debug.h"

TextBufferDebug::TextBufferDebug(TextBuffer* buffer_pointer) {
    buffer = buffer_pointer;
}

void TextBufferDebug::dev_buffer_init() {
  buffer->clear();
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 80; j++) {
      char num = '0' + (j + 1) % 10;
      num = (num == '0') ? ' ' : num;
      buffer->insert_character(num);
    }
    buffer->insert_character('\n');
  }
}

char TextBufferDebug::dev_debug_char(int location, char character){
  char char_to_print = dev_safe_print(character);
  int buffer_gap_last_index = buffer->content.buffer.gap_end - 1;
  int buffer_gap_first_index = buffer->content.buffer.gap_start;
  int buffer_index_for_point = buffer->content.buffer_index_from_content(buffer->get_point());
  int i = location;
  char_to_print = (i == buffer_gap_last_index)  ? 'E' : char_to_print;
  char_to_print = (i == buffer_gap_first_index) ? 'S' : char_to_print;
  char_to_print = (i == buffer_index_for_point) ? '*' : char_to_print;
  return char_to_print;
}

char TextBufferDebug::dev_safe_print(char inChar) {
  switch (inChar) {
    case CHAR_EOL : return CHAR_EOL_DISPLAY;
    case CHAR_SPC : return CHAR_SPC_DISPLAY;
    case CHAR_TAB : return CHAR_TAB_DISPLAY;
    case CHAR_NUL : return CHAR_NUL_DISPLAY;
    default   : return inChar;
  }
}

void TextBufferDebug::dev_hr(int len) {
  for (int i = 0; i < len; i++) {
    Serial.print('-');
  }
}

void TextBufferDebug::dev_print_buffer() {
  Serial.print("+");
  dev_hr(81);
  Serial.println("+");
  char char_to_print = NULL;
  for (int i = 0; i < buffer->content.buffer.capacity; i++) {
    if ( i % 81 == 0) {
      Serial.print("|");
    }
    Serial.print(dev_debug_char(i, buffer->content.buffer.data[i]));
    if (i + 1 == buffer->content.buffer.capacity) {
      for (; (i + 1) % 81 != 0; i++) {
        Serial.print(dev_debug_char(i+1, '<'));
      }
    }
    if ( (i + 1) % 81 == 0) {
      Serial.print("|\n");
    }
  }
  Serial.print("+");
  dev_hr(81);
  Serial.println("+");
}

void TextBufferDebug::dev_print_status_line() {
  int bs = 0;
  int gs = buffer->content.buffer.gap_start;
  int ge = buffer->content.buffer.gap_end - 1;
  int be = buffer->content.buffer.capacity - 1;
  int gap_size = buffer->content.gap_size();
  int point = buffer->get_point();
  int point_raw = buffer->content.buffer_index_from_content(point);
  Serial.printf(
    "Buffer Status: point=%d (%d), buffer={%d, %d, %d, %d}, gap_size=%d\n",
    point, point_raw, bs, gs, ge, be, gap_size
  );
}

void TextBufferDebug::dev_print_state() {
  dev_print_buffer();
  dev_print_status_line();
  Serial.println();
}
