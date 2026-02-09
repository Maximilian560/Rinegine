#pragma once

#undef RG_HERE_FILE_NAME
#define RG_HERE_FILE_NAME "def/decode"
//RG_List<RG_ENCODE_TYPE> RG_ENCODE 

namespace RG {
    char* itoa(int value, char* result, int base) {
        // check that the base if valid
        if (base < 2 || base > 36) { *result = '\0'; return result; }

        char* ptr = result, * ptr1 = result, tmp_char;
        int tmp_value;

        do {
            tmp_value = value;
            value /= base;
            *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz"[35 + (tmp_value - value * base)];
        } while (value);

        // Apply negative sign
        if (tmp_value < 0) *ptr++ = '-';
        *ptr-- = '\0';
        while (ptr1 < ptr) {
            tmp_char = *ptr;
            *ptr-- = *ptr1;
            *ptr1++ = tmp_char;
        }
        return result;
    }
    std::string itos(int value, int base) {

        std::string buf;

        // check that the base if valid
        if (base < 2 || base > 36) return buf;

        enum { kMaxDigits = 35 };
        buf.reserve(kMaxDigits); // Pre-allocate enough space.


        int quotient = value;

        // Translating number to string with base:
        do {
            buf += "0123456789abcdefghijklmnopqrstuvwxyz"[std::abs(quotient % base)];
            quotient /= base;
        } while (quotient);

        // Append the negative sign
        if (value < 0) buf += '-';

        for (int i = 0;i < buf.size() / 2;i++) {
            char temp = buf[i];
            buf[i] = buf[buf.size() - 1 - i];
            buf[buf.size() - 1] = temp;
        }
        return buf;
    }
    std::wstring itows(int value, int base) {

        std::wstring buf;

        // check that the base if valid
        if (base < 2 || base > 36) return buf;

        enum { kMaxDigits = 35 };
        buf.reserve(kMaxDigits); // Pre-allocate enough space.


        int quotient = value;

        // Translating number to string with base:
        do {
            buf += L"0123456789abcdefghijklmnopqrstuvwxyz"[std::abs(quotient % base)];
            quotient /= base;
        } while (quotient);

        // Append the negative sign
        if (value < 0) buf += '-';

        for (int i = 0;i < buf.size() / 2;i++) {
            char temp = buf[i];
            buf[i] = buf[buf.size() - 1 - i];
            buf[buf.size() - 1] = temp;
        }
        return buf;
    }
};
