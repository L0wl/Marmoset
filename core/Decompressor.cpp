#include "Decompressor.h"
#include <stdexcept>

std::vector<uint8_t> Decompressor::decompress(const std::vector<uint8_t>& input, size_t outputSize) {
    if (input.empty()) {
        throw std::runtime_error("Decompress: Input data is empty");
    }

    std::vector<uint8_t> output(outputSize, 0); // Выходной массив
    size_t d = 0;                                    // Индекс для записи в output
    std::vector<uint32_t> dictOffsets(4096);       // Словарь смещений
    std::vector<uint32_t> dictLengths(4096);       // Словарь длин
    size_t dictSize = 256;                           // Текущий размер словаря
    size_t inputLength = input.size();               // Длина входного массива
    size_t k = 0;                                    // Предыдущий offset
    size_t n = 1;                                    // Длина предыдущего элемента
    size_t m = 0;                                    // Временная переменная для offset
    size_t l = 1;                                    // Временная переменная для длины

    // Копируем первый байт
    output[d++] = input[0];

    for (size_t p = 1;; p++) {
        l = p + (p >> 1); // Позиция для извлечения 12-битного значения
        if (l + 1 >= inputLength)
            break;

        uint8_t mVal = input[l + 1];
        uint8_t lVal = input[l];
        uint16_t r = (p & 1) ? (mVal << 4 | (lVal >> 4)) : ((mVal & 15) << 8 | lVal);

        if (r < dictSize) {
            if (r < 256) {
                m = d;
                l = 1;
                output[d++] = static_cast<uint8_t>(r);
            } else {
                m = d;
                l = dictLengths[r];
                size_t rOffset = dictOffsets[r];
                size_t rEnd = rOffset + l;
                for (; rOffset < rEnd; rOffset++) {
                    output[d++] = output[rOffset];
                }
            }
        } else if (r == dictSize) {
            m = d;
            l = n + 1;
            size_t rOffset = k;
            size_t rEnd = k + n;
            for (; rOffset < rEnd; rOffset++) {
                output[d++] = output[rOffset];
            }
            output[d++] = output[k];
        } else {
            break;
        }

        dictOffsets[dictSize] = k;
        dictLengths[dictSize++] = n + 1;

        k = m;
        n = l;
        dictSize = (dictSize >= 4096) ? 256 : dictSize;
    }

    return (d == outputSize) ? output : std::vector<uint8_t>();
}
