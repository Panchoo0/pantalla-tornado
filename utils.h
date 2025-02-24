#ifndef UTILS_H
#define UTILS_H

#include <qstring.h>

class Utils
{
public:
    static QString toBitString(char byte);
    static QString toHexString(uchar* bytes, int length);
    static int getShiftedData(char startPos, char length, uchar* receivedData);
};

#endif // UTILS_H
