#include "Decompressor.h"
#include <stdexcept>

std::vector<uint8_t> Decompressor::decompress(const std::vector<uint8_t>& input, size_t outputSize) {
    if (input.empty()) {
        throw std::runtime_error("Decompress: Input data is empty");
    }

    std::vector<uint8_t> output(outputSize, 0); // Выходной массив
    size_t writeIndexOutput = 0;                     // Индекс для записи в output
    std::vector<uint32_t> dictOffsets(4096);       // Словарь смещений
    std::vector<uint32_t> dictLengths(4096);       // Словарь длин
    size_t dictSize = 256;                           // Текущий размер словаря
    size_t inputLength = input.size();               // Длина входного массива
    size_t previousOffset = 0;                       // Предыдущий offset
    size_t previousElemLength = 1;                   // Длина предыдущего элемента
    size_t temporaryOffset = 0;                      // Временная переменная для offset
    size_t temporaryLength = 1;                      // Временная переменная для длины
    output[writeIndexOutput++] = input[0];           // Копируем первый байт
    for (size_t p = 1;; p++) {
        temporaryLength = p + (p >> 1); // Позиция для извлечения 12-битного значения
        if (temporaryLength + 1 >= inputLength)
            break;
        uint8_t mVal = input[temporaryLength + 1];
        uint8_t lVal = input[temporaryLength];
        uint16_t r = (p & 1) ? (mVal << 4 | (lVal >> 4)) : ((mVal & 15) << 8 | lVal);
        if (r < dictSize) {
            if (r < 256) {
                temporaryOffset = writeIndexOutput;
                temporaryLength = 1;
                output[writeIndexOutput++] = static_cast<uint8_t>(r);
            } else {
                temporaryOffset = writeIndexOutput;
                temporaryLength = dictLengths[r];
                size_t rOffset = dictOffsets[r];
                size_t rEnd = rOffset + temporaryLength;
                for (; rOffset < rEnd; rOffset++) {
                    output[writeIndexOutput++] = output[rOffset];
                }
            }
        } else if (r == dictSize) {
            temporaryOffset = writeIndexOutput;
            temporaryLength = previousElemLength + 1;
            size_t rOffset = previousOffset;
            size_t rEnd = previousOffset + previousElemLength;
            for (; rOffset < rEnd; rOffset++) {
                output[writeIndexOutput++] = output[rOffset];
            }
            output[writeIndexOutput++] = output[previousOffset];
        } else {
            break;
        }
        dictOffsets[dictSize] = previousOffset;
        dictLengths[dictSize++] = previousElemLength + 1;
        previousOffset = temporaryOffset;
        previousElemLength = temporaryLength;
        dictSize = (dictSize >= 4096) ? 256 : dictSize;
    }
    return (writeIndexOutput == outputSize) ? output : std::vector<uint8_t>();
}
