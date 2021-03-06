#pragma once
#include "inc/types.h"

#include <optional>
#include <vector>
#include <algorithm>
#include <locale>

struct Color {
    int R;
    int G;
    int B;
    int A;
};

const Color solidWhite = {
    255, 255, 255, 255
};

// Natives called
void showText(float x, float y, float scale, const char* text, int font = 0, const Color &rgba = solidWhite, bool outline = false);
void showNotification(std::string message, int *prevNotification = nullptr);
void showSubtitle(std::string message, int duration = 2500);

std::optional<std::pair<uint32_t, uint32_t>> GetIMGDimensions(const std::string& path);

std::optional<std::pair<uint32_t, uint32_t>> GetPNGDimensions(const std::string& path);
std::optional<std::pair<uint32_t, uint32_t>> GetJPGDimensions(const std::string& path);
std::optional<std::pair<uint32_t, uint32_t>> GetWebPDimensions(const std::string& path);

Hash joaat(std::string s);
std::string removeSpecialChars(std::string input);
std::string getGxtName(Hash hash); // gxt name from model
std::string to_lower(std::string data);

/*
* stl search thingy for checking if a *thing* is in a vector of *things*,
* based on the public member named "HashedName".
*/
template<typename T>
bool isHashInImgVector(Hash hash, std::vector<T> things, T *result) {
    auto addonImage = std::find_if(things.begin(), things.end(), [&hash](const T& element) {
        return element.ModelHash == hash;
    });
    if (things.end() != addonImage) {
        if (result != nullptr)
            *result = *addonImage;
        return true;
    }
    return false;
}

bool FileExists(const std::string& name);

// https://stackoverflow.com/questions/3152241/case-insensitive-stdstring-find
// templated version of my_equal so it could work with both char and wchar_t
template<typename charT>
struct my_equal {
    my_equal(const std::locale& loc) : loc_(loc) {}
    bool operator()(charT ch1, charT ch2) {
        return std::toupper(ch1, loc_) == std::toupper(ch2, loc_);
    }
private:
    const std::locale& loc_;
};

// find substring (case insensitive)
template<typename T>
size_t findSubstring(const T& str1, const T& str2, const std::locale& loc = std::locale())
{
    typename T::const_iterator it = std::search(str1.begin(), str1.end(),
        str2.begin(), str2.end(), my_equal<typename T::value_type>(loc));
    if (it != str1.end()) return it - str1.begin();
    else return -1; // not found
}
