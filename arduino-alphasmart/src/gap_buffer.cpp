#include "gap_buffer.h"

GapBuffer::GapBuffer()
{
    clear();
}
void GapBuffer::clear()
{
    buffer.version = GAP_BUFFER_VERSION;
    buffer.capacity = GAP_BUFFER_DATA_SIZE;
    buffer.gap_start = 0;
    buffer.gap_end = GAP_BUFFER_DATA_SIZE;
    std::fill_n(buffer.data, GAP_BUFFER_DATA_SIZE, CHAR_NUL);
};

int GapBuffer::gap_size()
{
    return buffer.gap_end - buffer.gap_start;
}

int GapBuffer::content_size()
{
    return buffer.capacity - gap_size();
}
int GapBuffer::max_index()
{
    return content_size() - 1;
};

int GapBuffer::content_index_from_buffer(int buffer_index)
{
    int error = -1;
    if (buffer_index < 0)
    {
        return error;
    }
    if (buffer_index < buffer.gap_start)
    {
        return buffer_index;
    }
    if (buffer_index < buffer.gap_end)
    {
        return -1;
    }
    if (buffer_index < buffer.capacity)
    {
        return buffer_index - gap_size();
    }
    return error;
}

int GapBuffer::buffer_index_from_content(int content_index)
{
    int error = -1;
    if (content_index < 0)
    {
        return error;
    }
    if (content_index < buffer.gap_start)
    {
        return content_index;
    }
    int buffer_index = content_index + gap_size();
    if (buffer_index < buffer.capacity)
    {
        return buffer_index;
    }
    return error;
}

void GapBuffer::move_gap(int content_insertion_index)
{
    if (content_insertion_index == buffer.gap_start)
    {
        return;
    }
    while (buffer.gap_start < content_insertion_index)
    {
        buffer.data[buffer.gap_start] = buffer.data[buffer.gap_end];
        buffer.data[buffer.gap_end] = CHAR_NUL;
        buffer.gap_start++;
        buffer.gap_end++;
    }
    while (buffer.gap_start > content_insertion_index)
    {
        buffer.gap_start--;
        buffer.gap_end--;
        buffer.data[buffer.gap_end] = buffer.data[buffer.gap_start];
        buffer.data[buffer.gap_start] = CHAR_NUL;
    }
}

bool GapBuffer::insert_character(int content_index, char content_value)
{
    if (content_size() >= buffer.capacity)
    {
        return false;
    }
    move_gap(content_index);
    buffer.data[buffer.gap_start] = content_value;
    buffer.gap_start++;
    return true;
}

char GapBuffer::get_character(int content_index)
{
    // -1 for out of bounds
    int buffer_index = buffer_index_from_content(content_index);
    if (buffer_index < 0)
    {
        return CHAR_NUL;
    }
    return buffer.data[buffer_index];
}

char GapBuffer::delete_char(int content_index)
{
    if (gap_size() >= buffer.capacity)
    {
        return CHAR_NUL;
    }
    move_gap(content_index);
    char deleted_character = buffer.data[buffer.gap_end];
    buffer.data[buffer.gap_end] = CHAR_NUL;
    buffer.gap_end++;
    return deleted_character;
}