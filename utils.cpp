#include "utils.h"
#include <QDebug>
#include <cmath>

// Dado un char retorna su representación como string en formato binario
QString Utils::toBitString(char byte) {
    QString res = "";
    int mask = 0b1;
    for (int i = 0; i < 8; i++) {
        int bitChar = (byte >> (7 - i)) & mask;
        res += QString::number(bitChar);
    }
    return res;
}

// Dado un int retorna su representación como string en formato binario
QString Utils::toBitString(int byte) {
    QString res = "";
    int mask = 0b1;
    for (int i = 0; i < 32; i++) {
        int bitChar = (byte >> (31 - i)) & mask;
        res += QString::number(bitChar);
    }
    return res;
}

// Dado una lista de bytes retorna su representación como string en formato hex
QString Utils::toHexString(uchar* bytes, int length) {
    char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
    QString result = "";

    for( int i = 0; i < length; ++i )
    {
        char const byte = bytes[i];

        result += hex_chars[ ( byte & 0xF0 ) >> 4 ];
        result += hex_chars[ ( byte & 0x0F ) >> 0 ] + QString(" ");
    }

    return result;
}

// Dado un int retortna su representación como hex
QString Utils::toHexString(int number) {
    uchar b1 = number >> 24;
    uchar b2 = number >> 16;
    uchar b3 = number >> 8;
    uchar b4 = number & 0xFF;
    uchar bytes[] = {b1, b2, b3, b4};
    return toHexString(bytes, 4);
}


// Función que dado una posición inicial en bits y un largo en bits retorna el entero contenido en el array de chars
// en ese rango de bits
int Utils::getShiftedData(char startPos, char length, uchar* receivedData) {
    uchar startChar = startPos / 8;
    char offsetChars = startPos % 8;
    int res = 0;
    char copiedBits = 0;
    uchar mask = 0b11111111;
    // Cantidad de bits a copiar en cada iteración
    // en la primera se considera los bits que pueden queda a la izquierda del primer bit
    char toBeCopiedBits = length > 8 - offsetChars ? 8 - offsetChars : length;

    while (copiedBits < length) {
        uchar data = receivedData[startChar];

        // Eliminamos los bits en la mascara que no pertenezcan al rango buscado
        mask <<= 8 - toBeCopiedBits - offsetChars;
        mask = mask >> offsetChars;

        // Aplicamos la mascara y alineamos a la derecha
        data = data & mask;
        data = data >> (8 - toBeCopiedBits - offsetChars);

        // Shifteamos para hacer espacio y copiamos los bits
        res <<= toBeCopiedBits;
        res |= data;
        copiedBits += toBeCopiedBits;
        startChar += 1;
        mask = 0b11111111;
        offsetChars = 0;

        toBeCopiedBits = std::min(8, length - copiedBits);
    }

    return res;
}

// Retorna en un vector los strings que se encuentran entre el delimitador en el string dado.
// Muta el string dado
std::vector<std::string> Utils::split(std::string& s, const std::string& delimiter) {
    std::vector<std::string> tokens;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        tokens.push_back(token);
        s.erase(0, pos + delimiter.length());
    }
    tokens.push_back(s);

    return tokens;
}

// Dado un valor en milisegundos (int) retorna la cantidad de horas, minutos y segundos correspondientes respectivamente.
std::tuple<int, int, int> Utils::fromMsToHoursMinutesSeconds(int ms) {
    int toSeconds = ms / 1000;
    int seconds = toSeconds % 60;
    int minutes = (toSeconds / 60) % 60;
    int hours = (toSeconds / 60) / 60;
    return {hours, minutes, seconds};
}

float Utils::round(int val, float factor, float offset) {
    return std::ceil(((float)(val * factor)) * 100.0) / 100.0 - offset;;
}
