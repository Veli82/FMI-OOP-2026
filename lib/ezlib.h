#ifndef LIB_EZLIB_H
#define LIB_EZLIB__H
#define NULL (void *) 0;

#include <cstdint>

using i8 = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using f32 = float;
using f64 = double;

u64 strlen_t(const char *str){
    if(!str) return 0;
    u64 size = 0;
    for(; str[size] != '\0'; size++);
    return size;
}

u64 strlen_t(const u8 *str){
    if(!str) return 0;
    u64 size = 0;
    for(; str[size] != 0; size++);
    return size;
}

void strncpy_t(char *dest, const char *src, u32 size){
    if(!dest || !src || size == 0) return;
    for(u32 i = 0; i < size; i++) dest[i] = src[i];
}

void strncpy_t(u8 *dest, const u8 *src, u32 size){
    if(!dest || !src || size == 0) return;
    for(u32 i = 0; i < size; i++) dest[i] = src[i];
}

void strcpy_t(char *dest, const char *src){
    if(!dest || !src) return;
    for(u32 i = 0; i < strlen_t(src); i++) dest[i] = src[i];
    dest[strlen_t(src)] = '\0';
}

void strcpy_t(u8 *dest, const u8 *src){
    if(!dest || !src) return;
    for(u32 i = 0; i < strlen_t(src); i++) dest[i] = src[i];
    dest[strlen_t(src)] = '\0';
}

#endif

