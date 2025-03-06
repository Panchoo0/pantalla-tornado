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
    static int getShiftedData(char startPos, char length, uchar* receivedData);
    static std::vector<std::string> split(std::string& s, const std::string& delimiter);
    static std::tuple<int, int, int> fromMsToHoursMinutesSeconds(int ms);
};

#endif // UTILS_H
