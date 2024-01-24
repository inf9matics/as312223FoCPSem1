#include <vector>

#pragma once

/**
 * @brief Namespace containing collection utility functions.
 * @details @todo Fill details
 */
namespace TCollectionUtilities {
    /**
     * @brief 
     * 
     * @param x 
     * @return std::vector<char> 
     */
    std::vector<char> bitVectorFromNumber(long x);

    /**
     * @brief 
     * 
     * @param vector 
     */
    void flipCharVector(std::vector<char>& vector);

    /**
     * @brief 
     * 
     * @param vector 
     */
    void flipIntVector(std::vector<int>& vector);

    /**
     * @brief 
     * 
     * @param bitVector 
     * @return long 
     */
    long longFromBitVector(std::vector<int>& bitVector);
    };