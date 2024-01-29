/**
 * @file tStringUtilities.h
 * @author Adam Strączek (as312223@student.polsl.pl)
 * @brief Header file containing static methods handling strings.
 * @version 1.0
 */

#include <string>

#pragma once

/**
 * @brief Namespace containing string utility functions.
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