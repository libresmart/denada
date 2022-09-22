#ifndef TEXT_BUFFER_H
#define TEXT_BUFFER_H
#include "gap_buffer.h"
#include <algorithm>

class TextBuffer {
    public:
    GapBuffer content;
    char buffer_name[BUFFER_NAME_SIZE];
    char file_name[BUFFER_FILENAME_SIZE];
    bool is_modified;
 
    TextBuffer();
    void clear();
    
    // Modification
    void insert_character(char);
    void delete_characters(int);

    // Navigation
    void move_point_left_explicit();
    void move_point_right_explicit();
    void move_point_up();
    void move_point_down();
    void move_point_home();
    void move_point_end();

    void window_move_point_up(int);
    void window_move_point_down(int);
    void window_move_point_page_up(int,int);
    void window_move_point_page_down(int,int);

    // Status
    char get_character(int);
    int get_point();
    int get_line_number();
    int get_column_number();
    int content_size();
    int window_get_line_number();
    int window_get_column_number();
    

    private:
    int point;
    int actual_line_offset;
    int actual_column_offset;
    int desired_column_offset;
    int window_line_offset;
    int window_column_offset;
    
    // Helpers
    int find_next_occurrence_forward(int, char);
    int find_next_occurrence_backward(int, char);
    int count_occurrences_forward(int, char);
    int count_occurrences_backward(int, char);
    int count_occurrences_all(char);
    int get_line_start_index(int);
    int get_line_end_index(int);
    int get_column_offset(int);
    void move_point_left_implicit();
    void move_point_right_implicit();
    void declare_column_desired();
};
#endif  // TEXT_BUFFER_H