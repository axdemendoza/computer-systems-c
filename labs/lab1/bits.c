/* 
 * CS:APP Data Lab 
 * 
 * Axel De Mendoza (ademendoza)
 * 
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.  
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:
 
  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code 
  must conform to the following style:
 
  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>
    
  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.

 
  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to 
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies 
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 * 
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce 
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2020 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <https://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* glibc's intent is to support the IEC 559 math functionality, real
   and complex.  If the GCC (4.9 and later) predefined macros
   specifying compiler intent are available, use them to determine
   whether the overall intent is to support these features; otherwise,
   presume an older compiler has intent to support these features and
   define these macros by default.  */
/* wchar_t uses Unicode 10.0.0.  Version 10.0 of the Unicode Standard is
   synchronized with ISO/IEC 10646:2017, fifth edition, plus
   the following additions from Amendment 1 to the fifth edition:
   - 56 emoji characters
   - 285 hentaigana
   - 3 additional Zanabazar Square characters */
// Spring 2026
// Rating 2 - integer
/* 
 * isEqual - return 1 if x == y, and 0 otherwise 
 *   Examples: isEqual(5,5) = 1, isEqual(4,5) = 0
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int isEqual(int x, int y) {
  return !(x ^ y);
}
/* 
 * isNegative - return 1 if x < 0, return 0 otherwise 
 *   Example: isNegative(-1) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNegative(int x) {
  /*
  1. Shift the MSB 31 bits to the right. This ends up being 00...00 or 11...11
  2. Take the 2's complement of the result to get the return value 
  */
  x = x >> 31;
  return ~x + 1; // 2's complement
}
/* 
 * isPositive - return 1 if x > 0, return 0 otherwise 
 *   Example: isPositive(-1) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 2
 */
int isPositive(int x) {
  /*
  1. identifies zero by using the !(NOT) operator on the input int
  2. uses negative logic to identify negative values
  3. returns !(neg or zero)
  */
  int zero = !x; // ! returns 0 for non-zero or 1 if zero
  int neg = (~(x >> 31))+1; // is_negative logic
  return !(neg | zero);
}
/*
 * distinctNegation - returns 1 if x != -x.
 *     and 0 otherwise 
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 5
 *   Rating: 2
 */
int distinctNegation(int x) {
  /*
  1. Take the 2's compliment of x
  2, check for any bits that don't match with XOR. Since the only way a 2's 
      compliment doesn't equal its negation is if it's the smallest int value
      (0x 8000 0000) and the negation of that is itself. 
  3. Return 0 if bits are all the same, return 1 if bits differ 
  */
  int y = (~x) + 1;
  return !!(x ^ y);
}
// Rating 3 - integer
/* 
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  /*
  1. Checks if x is >= 0x30 by adding negation of 0x30 to x
  2. Checks if x is <= 0x39 by adding negation of x to 0x39
  3. bit shift results >>31 to make the MSB the LSB. 00..00 or 11..11
  4. If not an Ascii digit then 1 or 2 would be negative
  4. Ascii digits should make both checks = 0
  5. check if a or b is negative 
  6. return negation of 5
  */
  int y = x + ((~0x30)+1); // checks if greater than or = 0x30
  int z = 0x39 + (~x)+1; // checks if less than or = 0x39
  int a = y >> 31;
  int b = z >> 31;
  int c = a | b;
  return !c;
}
/* 
 * rotateRight - Rotate x to the right by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateRight(0x87654321,4) = 0x187654321
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3 
 */
int rotateRight(int x, int n) {
  int left_shift = (32 + (~n + 1)) & 31; // how many bits to shift by (0-31)
  int is_zero = !n; // 1 if n is zero; 0 otherwise - will be used in the next step
  int leading_zeros = ((1+(~is_zero + 1)) << left_shift) + (~1 + 1); // n 0s followed by all 1s
  int y = x >> n;
  int shifted_right = leading_zeros & y;
  int shifted_left = x << left_shift;
  return shifted_right | shifted_left;
}
/*
 * satMul3 - multiplies by 3, saturating to Tmin or Tmax if overflow
 *  Examples: satMul3(0x10000000) = 0x30000000
 *            satMul3(0x30000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0x70000000) = 0x7FFFFFFF (Saturate to TMax)
 *            satMul3(0xD0000000) = 0x80000000 (Saturate to TMin)
 *            satMul3(0xA0000000) = 0x80000000 (Saturate to TMin)
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 3
 */
int satMul3(int x) {
  /*
  Multiply by 3 is just: multiply by 2 + itself
  */
  int TMIN = 1 << 31;
  int TMAX = ~TMIN;
  // Multiply by 2 and check for overflow
  int x_2 = x << 1; // multiply by 2
  int x_sign_bits = x >> 31;
  int x_2_sign_bits = x_2 >> 31;
  int overflow_1 = x_sign_bits ^ x_2_sign_bits; // all 0s if no overflow, all 1s if overflow

  int x_3 = x_2 + x; // add x + 2x
  int x_3_sign_bits = x_3 >> 31;
  int overflow_2 = x_3_sign_bits ^ x_2_sign_bits; // all 0s if no overflow, all 1s if overflow
  
  int overflow = overflow_1 | overflow_2;

  int saturated_result = (x_sign_bits & TMIN) | (~x_sign_bits & TMAX);

  return (saturated_result & overflow) | (~overflow & x_3);
}
/* 
 * isLess - if x < y  then return 1, else return 0 
 *   Example: isLess(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLess(int x, int y) {
  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int sign_change = sign_x ^ sign_y;

  int result_1 = (sign_x & sign_change) & 1; // 1 if sign changed AND x was negative

  int result_2 = x + (~y + 1); // negative if x < y
  result_2 = (result_2 >> 31) & 1;

  // if sign changed then return result 1; otherwise return result 2
  return (sign_change & result_1) | (result_2 & ~sign_change);
}
// Rating 4 - integer
/* 
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4 
 */
int isNonZero(int x) {
  int sign_bit = x | (~x + 1);
  sign_bit = sign_bit >> 31;
  return sign_bit & 1;
}
/* 
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int twos_compliment = ~x + 1;
  int sign = x >> 31;
  return (twos_compliment & sign) | (x & ~sign);
}
// Rating 2 - floating point
/* 
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  unsigned abs = uf & (~(1 << 31)); // sets the MSB to 0 
  unsigned exp_bits = (uf >> 23) & 0x000000FF;
  unsigned frac_bits = uf & 0x007FFFFF;
  if ((exp_bits == 255) && (frac_bits != 0)){
    return uf;
  }
  return abs;
}
/* 
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  if ((((uf >> 23) & 0x000000FF) == 255) && ((uf & 0x007FFFFF) != 0)){
    return uf;
  }
  return uf ^ 0x80000000;
}
// Rating 3 - floating point
/* 
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug) {
    // check for NaN and return 0 if either is NaN
    unsigned uf_exp = (uf >> 23) & 0x000000FF;
    unsigned ug_exp = (ug >> 23) & 0x000000FF;

    unsigned uf_frac = uf & 0x007FFFFF;
    unsigned ug_frac = ug & 0x007FFFFF;

    unsigned uf_sign = uf >> 31;
    unsigned ug_sign = ug >> 31;
    
    int negative_compare = 0;

    // return 0 if either is NaN
    if (((uf_exp == 255) && (uf_frac != 0)) || ((ug_exp == 255) && (ug_frac != 0))){
      return 0;
    }

    // if both are 0 return 0 regardless of sign
    if (((uf << 1) | (ug << 1)) == 0) {
      return 0;
    }

    // check sign and return 0 or 1 if signs are different
    
    if (uf_sign != ug_sign){
      return uf_sign > ug_sign;
    }

    // check if both floats are negative
    
    if ((uf & ug & 0x80000000) == 0x80000000){
      negative_compare = 1;
    }

    // if signs are the same compare exp bits
    if (uf_exp < ug_exp) {
      return !negative_compare;
    } else if (uf_exp > ug_exp){
      return negative_compare;
    }

    // if exp bits are the same compare fractional bits
    if (uf_frac < ug_frac) {
      return !negative_compare;
    } else if (uf_frac > ug_frac) {
      return negative_compare;
    }

    return 0;

}
// Rating 4 - floating point
/* 
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  unsigned exp_bits = (uf >> 23) & 0x000000FF;
  unsigned frac_bits = uf & 0x007FFFFF;
  unsigned sign = uf >> 31;
  int exp = exp_bits - 127;
  unsigned value;
  unsigned M = frac_bits | 0x00800000;

  // check for inf and NaN
  if (exp_bits == 0xFF){
    return 0x80000000u;
  }

  // check for negative exponent or denorm
  if (exp_bits <= 126){
    return 0;
  }

  // check for out of range value
  if (exp_bits > 31+127){
    return 0x80000000u;
  } else if ((exp_bits == 31+127) && (sign > 0)) {
    if (frac_bits > 0) {
      return 0x80000000u;
    } else {
      return 0x80000000;
    }
  } else if ((exp_bits == 31+127) && (sign == 0)){
    return 0x80000000u;
  }

  // normalized
  
  if (exp >= 23){
    value = M << (exp - 23);
  } else {
    value = M >> (23 - exp);
  }

  if (sign) {
    return -value;
  } else {
    return value;
  }
}
/* 
 * floatUnsigned2Float - Return bit-level equivalent of expression (float) u
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatUnsigned2Float(unsigned u) {
  unsigned exp = 0;
  unsigned M;
  unsigned w;
  unsigned E;

  // check if 0
  if (u == 0){
    return 0;
  }

  // find the position of the highest 1 bit by bit shifting right until we hit 0
  
  for (w = u; w > 0; w = w >> 1){
      exp++;
  }
  exp--; // if 1 in pos 4, we want exp=3

  // if exp > 23 then we have discarded bits and have to round
  
  if (exp > 23) {
      // if bits need to be discarded we have to round
      int num_discarded_bits = exp - 23;
      // left shift discarded bits to the 0-7 positions and zero out bits to the left
      // we will be left with discarded bits with a range of 0-255
      // 10000000 (128) is the halfway point. Anything less should round down, anything greater rounds up
      unsigned discarded_bits = (u << (8-num_discarded_bits)) & 0x000000FF; // 8 is the max # of discarded bits
      // right shift fractional bits to the 0-22 position
      M = u >> num_discarded_bits;
      M = M & 0x007FFFFF; // zeros out left 9 bits leaving M in the 0-22 positions
      if (discarded_bits > 128) {
          // round up
          M += 1; // add one to round up
      } else if (discarded_bits < 128) {
          // round down, do nothing
      } else {
          // if discarded_bits = 128 then 0.5 is right in the middle and we round to nearest even
          // if LSB is 1 number is odd and we round up; if 0 then even and we round down
          int LSB = 1 & M;
          if (LSB == 1) {
              M += 1;
          } else {
              // round down to nothing
          }
      }
      // we have to check for overflow and increase EXP if overflow
      if (M > 0x007FFFFF){
          exp += 1;
          M = M & 0x007FFFFF; // reset back to 23 bits if overflow
      }
  } else {
      // EXP <= 23 then no discarded bits and no rounding
      // fractional bits (mantissa)
      M = u << (23-exp);
      M = M & 0x007FFFFF; // zeros out left 9 bits leaving M in the 0-22 positions
  }
  
  // encode the exp bits
  E = exp + 127; // but exp needs to be encoded as e - 127
  E = E << 23; // sets the exp bits in the 2-9 positions

  return 0x0 | E | M;
}
