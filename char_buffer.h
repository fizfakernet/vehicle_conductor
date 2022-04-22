#pragma once

#include <list>
#include <iterator>
#include <mutex>

using namespace std;

class CharBuffer
{
public:
    ~CharBuffer();
    void add(const char *s, size_t len);
    size_t getMessage(char *messageString);
private:
    list<char> listStr;
    list<char>::iterator head_position{ listStr.begin() };
    mutex mut_list;

    void clearAld();
    size_t findMessage(char *str);
};