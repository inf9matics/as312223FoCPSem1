/**
 * @file tCollectionUtilities.h
 * @author Adam Strączek (as312223@student.polsl.pl)
 * @brief Header file containing static methods handling collections.
 * @version 1.0
 */

#include <vector>

#pragma once

/**
 * @brief Namespace containing collection utility functions.
 * @details @todo Fill details
 */
namespace TCollectionUtilities {
    /**
     * @brief Function converting a number to a vector of bits.
     * @param x Number to convert.
     * @return std::vector<char> Vector containing the number bits.
     */
    std::vector<char> bitVectorFromNumber(long x);

    /**
     * @brief Function flipping a std::vector.
     * @tparam T Type of values in the std::vector.
     * @param vector std::vector to be flipped
     */
    template<typename T>
    void flipVector(std::vector<T>& vector);

    /**
     * @brief 
     * 
     * @param bitVector 
     * @return long 
     */
    long longFromBitVector(std::vector<char>& bitVector);
    };