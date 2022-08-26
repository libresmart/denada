const int  BUFF_SIZE  = 1024;  // in bytes


//// Buffer
struct Buffer {
  int point;
  int gap_start;
  int gap_end;
  int cur_line;
  int num_lines;
  int num_chars;
  char contents[BUFF_SIZE];
};
Buffer buffer = {0,0,BUFF_SIZE,0,0,0,{NULL}};

void buffer_clear() {
  buffer.point = 0;
  buffer.gap_start = 0;
  buffer.gap_end = BUFF_SIZE;
  buffer.cur_line = 0;
  buffer.num_lines = 0;
  buffer.num_chars = 0;
  for (int i = 0; i < BUFF_SIZE; i++) {
    buffer.contents[i] = NULL;
  }
}

void move_point(int move_distance) {
  buffer.point += move_distance;
  buffer.point = (buffer.point < 0 ) ? 0 : buffer.point;
  buffer.point = (buffer.point > max_text_loc()) ? max_text_loc() : buffer.point;
}
void set_point(int location) {
  buffer.point = location;
  move_point(0);
}

void move_gap_to_point() {
  // if buffer.gap_start == buffer.point, this will just return.
  while (buffer.gap_start < buffer.point) {
    buffer.contents[buffer.gap_start] = buffer.contents[buffer.gap_end];
    buffer.contents[buffer.gap_end] = NULL;
    buffer.gap_start++;
    buffer.gap_end++;
  }
  while (buffer.gap_start > buffer.point) {
    buffer.gap_start--;
    buffer.gap_end--;
    buffer.contents[buffer.gap_end] = buffer.contents[buffer.gap_start];
    buffer.contents[buffer.gap_start] = NULL;
  }
}

void insert_char(char inChar) {
  insert_chars(1, &inChar);
}
void insert_chars(int len, char *characters) {
  for (int i = 0; i < len; i++) {
    move_gap_to_point();
    if (gap_size() > 0) {
      buffer.contents[buffer.gap_start++] = characters[i];
      move_point(+1);
    }
  }
}

void del_chars(int num_chars_to_delete) {
  move_gap_to_point();
  int i = num_chars_to_delete;
  for (; i > 0 && buffer.gap_end < BUFF_SIZE; i--) {
    buffer.contents[buffer.gap_end++] = NULL;
  }
  for (; i < 0 && buffer.gap_start > 0; i++) {
    buffer.contents[--buffer.gap_start] = NULL;
    move_point(-1);
  }
}

int text_loc_from_buff(int buff_location) {  // location is assumed to be outside of the gap
  return (buff_location <= buffer.gap_start) ? buff_location : buff_location - gap_size();
}
int buff_loc_from_text(int text_location) {
  return (text_location <= buffer.gap_start) ? text_location : text_location + gap_size();
}
int gap_size() {
  return buffer.gap_end - buffer.gap_start;
}
int max_text_loc() {
  return BUFF_SIZE - gap_size();
}
