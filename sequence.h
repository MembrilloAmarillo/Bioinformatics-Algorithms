/* date = December 13th 2022 10:33 pm */

#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <cstdio>
#include <cstdint>

#include <tchar.h>
#include <strsafe.h>
#include <Windows.h>
#include <fileapi.h>

struct Sequence
{   
    char   *sequence_set;
    char   *sequence_suffix;
    size_t buffer_size;
    size_t suffix_size;
    HANDLE file_handler;
    
    explicit Sequence( LPCWSTR path_file, const char* suffix );
    ~Sequence();
    
};

#endif //SEQUENCE_H
