#pragma once

//RG_List<RG_ENCODE_TYPE> RG_ENCODE 

//декодирование из ASCII в utf8
namespace RG {

    wstring utf8_decode(const string& str) {
        if (str.empty()) return wstring();
        int SizeWstr = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
        std::wstring str_to_wstr(SizeWstr, 0);
        MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &str_to_wstr[0], SizeWstr);
        return str_to_wstr;
    }

    string utf8_encode(const wstring& wstr) {
        if (wstr.empty()) return string();
        int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
        string strTo(size_needed, 0);
        WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
        return strTo;
    }


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
