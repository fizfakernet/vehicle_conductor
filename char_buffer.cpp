#include "char_buffer.h"

CharBuffer::~CharBuffer()
{
    mut_list.lock();
    listStr.clear();
    mut_list.unlock();
}

void CharBuffer::add(const char *s, size_t len)
{
    mut_list.lock();
    for(int i=0;i<len;i++)
    listStr.push_back(s[i]);
    mut_list.unlock();
}
size_t CharBuffer::getMessage(char *messageString)
{
    if( NULL == messageString) return 0;
    size_t ret;

    mut_list.lock();
    ret = findMessage(messageString);
    mut_list.unlock();
    return ret;
}
void CharBuffer::clearAld()
{
    head_position = listStr.erase(listStr.begin(), head_position);
}

size_t CharBuffer::findMessage(char *str)
{
    list<char>::iterator finish{ listStr.end() };

    for(--finish; finish != head_position; --finish)
    {
        if( 'X' == *finish)  break;
    }

    if( finish == head_position ) return 0;
    head_position = finish;
    for(--head_position; head_position != listStr.begin(); --head_position )
    {
        if( 'X' == *head_position) break;
    }
    if( 'X' != *head_position) return 0;

    int i = 0;
    for( list<char>::iterator p{head_position}; p != finish; ++p )
    {
        str[i] = *p;
        i++;
    }
    str[i] = '\0';
    head_position = finish;
    --head_position;
    clearAld();

    return i;
}