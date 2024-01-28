#include <string>

#pragma once

/**
 * @brief Namespace containing string utility functions.
 * @details @todo Fill details.
 */
namespace TStringUtilities {
    /**
     * @brief Function converting a CString to a std::string.
     * @param basic_string CString to convert.
     * @return std::string Converted string.
     */
    std::string basicStringToString(char* basic_string);

    /**
     * @brief Function converting a byte to a string of bits.
     * @param byte Byte to convert.
     * @return std::string Converted string of bits.
     */
    std::string byteToBitString(char byte);
    };