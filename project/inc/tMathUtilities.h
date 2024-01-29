/**
 * @file tMathUtilities.h
 * @author Adam Strączek (as312223@student.polsl.pl)
 * @brief Header file containing static methods handling mathematic operations.
 * @version 1.0
 */

#pragma once

/**
 * @brief Namespace containing math utilities
 */
namespace TMathUtilities {
    /**
     * @brief Function returning a clamped int value; n in |min; ∞|.
     * @param x Number to clamp.
     * @param min Lower bound.
     * @return int Clamped number.
     */
    int minOrHigher(int x, int min);

    /**
     * @brief Function returning a clamped int value; n in |-∞; max|.
     * @param n Number to clamp.
     * @param max Higher bound.
     * @return int Clamped number.
     */
    int maxOrLower(int x, int max);

    /**
     * @brief Function returning a clamped int value; n in |min; max|.
     * @param x Number to clamp
     * @param min Lower bound.
     * @param max Higher bound.
     * @return int Clamped number.
     */
    int containInRange(int x, int min, int max);

    /**
     * @brief Function returning the of bits to represent number in binary form.
     * @details This function assumes an integer value.
     * @param x Number to work on.
     * @return int Number of bits required to represent.
     */
    int bitLengthToRepresentX(long x);

    /**
     * @brief Function returning the bit at a certain position of x.
     * @details This function returns the value by shifting bits.
     * @param x Number to work on.
     * @param n Bit number to get.
     * @return int Bit in integer form.
     */
    int bitAtN(long x, int n);
    };