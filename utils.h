#ifndef UTILS_H
#define UTILS_H

#include <qstring.h>
#include <vector>

class Utils
{
public:
    static QString toBitString(char byte);
    static QString toBitString(int byte);
    static QString toHexString(uchar* bytes, int length);
    static QString toHexString(int number);
    static int getShiftedData(char startPos, char length, uchar* receivedData);
    static std::vector<std::string> split(std::string& s, const std::string& delimiter);
    static std::tuple<int, int, int> fromMsToHoursMinutesSeconds(int ms);
    static float round(int val, float factor = 1.0, float offset = 0);
};

#endif // UTILS_H
