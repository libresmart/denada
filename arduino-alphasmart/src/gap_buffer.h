#ifndef GAP_BUFFER_H
#define GAP_BUFFER_H
#include "config.h"
#include <assert.h>
#include <algorithm>
#include <cstdint>

// Implementation Techniques: https://www.finseth.com/craft/#c6
/******************************************************************
  0   1   2   3   4   5   6   7   8                       9  10  11  <-- text location
  | M | i | n | n | e | a | p | o |   |   |   |   |   | l | i | s |
  -----------------------------------------------------------------
  0   1   2   3   4   5   6   7   8   9  10  11  12  13  14  15  16  <-- buffer location
   30  31  32  33  34  35  36  37  38  39  40  41  42  43  44  45    <-- storage location
                  P              GS                  GE              <-- references {P: point, GS: gap start, GE: gap end}
******************************************************************/
#define GAP_BUFFER_VERSION 1
#define GAP_BUFFER_HEADER_SIZE 8
#define GAP_BUFFER_DATA_SIZE (GAP_BUFFER_RAW_SIZE - GAP_BUFFER_HEADER_SIZE)

struct GapBufferRaw
{
    uint16_t version;   /* 2 bytes */
    uint16_t capacity;  /* 2 bytes */
    uint16_t gap_start; /* 2 bytes */
    uint16_t gap_end;   /* 2 bytes */
    /* 8 bytes taken above */
    char data[GAP_BUFFER_DATA_SIZE];
};
static_assert(sizeof(struct GapBufferRaw) == GAP_BUFFER_RAW_SIZE,
              "Unexpected Gap Buffer Definition Size");

class GapBuffer
{
public:
    struct GapBufferRaw buffer;

    GapBuffer();
    void clear();
    int gap_size();
    int content_size();
    int max_index();
    bool insert_character(int, char);
    char get_character(int);
    char delete_char(int);
    int buffer_index_from_content(int);

private:
    int content_index_from_buffer(int);
    void move_gap(int);
};
#endif // GAP_BUFFER_H