#include <pybind11/pybind11.h>
#include <aes.h>
#include <aes.c>
#include <string>
using namespace std;

// code from https://github.com/wx1183618058/HuaWei-Optical-Network-Terminal-Decoder/blob/master/huawei/aescrypt.cpp
uint32_t aes_enh_sys_to_long(const uint8_t* plain)
{
    uint32_t result = 0;
    uint32_t y = 1;
    for (int x = 0; x < 5; ++x) {
        result += y * plain[x];
        y *= 93;
    }
    return result;
}

void aes_plain_to_bin(const uint8_t* plain, uint8_t* bin)
{
    uint32_t y;
    for (int x = 0; x < 16; x += 4, plain += 5) {
        y = aes_enh_sys_to_long(plain);
        memcpy(bin + x, &y, 4);
    }
}

void aes_ascii_unvisible(uint8_t* str, size_t str_len)
{
    for (size_t x = 0; x < str_len; ++x) {
        (str[x] == 126) ? (str[x] = 30) : (str[x] = str[x] - 33);
    }
}

// https://stackoverflow.com/a/14678800
void ReplaceStringInPlace(std::string& subject, const std::string& search,
    const std::string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != std::string::npos) {
        subject.replace(pos, search.length(), replace);
        pos += replace.length();
    }
}


string decrypt_2(string text_)
{
    if (text_[1] != '2' || text_[0] != '$' || text_[text_.length() - 1] != '$') {
        return "Error";
    }
    aes_context aes_ctx;
    uint8_t cbc_key[32] = {
        0x6F, 0xC6, 0xE3, 0x43,
        0x6A, 0x53, 0xB6, 0x31,
        0xD , 0xC0, 0x9A, 0x47,
        0x54, 0x94, 0xAC, 0x77,
        0x4E, 0x7A, 0xFB, 0x21,
        0xB9, 0xE5, 0x8F, 0xC8,
        0xE5, 0x8B, 0x56, 0x60,
        0xE4, 0x8E, 0x24, 0x98
    };
    uint8_t buffer_pw[16];
    uint8_t buffer_pw_IV[16];
    uint8_t buffer_plain_pw[25];
    uint8_t buffer_cipher_pw[512];
    char buffer_plain[512];

    ReplaceStringInPlace(text_, "&quot;", "\"");
    ReplaceStringInPlace(text_, "&apos;", "\'");
    ReplaceStringInPlace(text_, "&amp;", "&");
    ReplaceStringInPlace(text_, "&lt;", "<");
    ReplaceStringInPlace(text_, "&gt;", ">");

    size_t len = text_.length() - 3;

    strcpy((char*)buffer_cipher_pw, text_.substr(2, text_.length() - 3).c_str());
    aes_ascii_unvisible(buffer_cipher_pw, len);

    int len_ = len / 20;
    if (len != 20 * (len / 20))
        ++len_;
    aes_plain_to_bin(buffer_cipher_pw + (20 * len_ - 20), buffer_pw_IV);
    for (int x = 0; x < len_ - 1; ++x) {
        aes_plain_to_bin(buffer_cipher_pw + x * 20, buffer_pw);
        aes_setkey_dec(&aes_ctx, cbc_key, 256);
        aes_crypt_cbc(&aes_ctx, 0, 16, buffer_pw_IV, buffer_pw, buffer_plain_pw);
        memcpy((char*)buffer_plain + x * 16, (char*)buffer_plain_pw, 16);
    }
    return (char*)buffer_plain;
}


namespace py = pybind11;


PYBIND11_MODULE(decoder, m) {
    m.doc() = "Decode password Huawei";
    m.def("decoder", &decrypt_2);
}