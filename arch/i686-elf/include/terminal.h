/*
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Little Endian Kernel.
 * 
 * Alek's Little Endian Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Little Endian Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Little Endian Kernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ALEK_TERMINAL_H
#define ALEK_TERMINAL_H

#include "pattern/singleton.h"
#include "types.h"

#include <string.h>
#include <math.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25

enum VgaColor
{
  BLACK = 0,
  BLUE = 1,
  GREEN = 2,
  CYAN = 3,
  RED = 4,
  MAGENTA = 5,
  BROWN = 6,
  LIGHT_GREY = 7,
  DARK_GREY = 8,
  LIGHT_BLUE = 9,
  LIGHT_GREEN = 10,
  LIGHT_CYAN = 11,
  LIGHT_RED = 12,
  LIGHT_MAGENTA = 13,
  LIGHT_BROWN = 14,
  WHITE = 15,
};

class Terminal
  : public Singleton<Terminal>
{
private:
  Terminal();
  ~Terminal() = default;

public:

  u32 get_term_row() { return m_term_row; }
  void set_term_row(u32 row) { m_term_row = row; }

  u32 get_term_col() { return m_term_col; }
  void set_term_col(u32 col) { m_term_col = col; }

  void putentry(char c, u8 color, coord_t x, coord_t y);
  void putc(char c);
  void puts(const char *str);

  void printf(const char *str);


  /*
   %[flags][width][.precision][length]specifier

  specifier | Output                                             |  Example
  d or i    | Signed decimal integer                             |  392
  u         | Unsigned decimal integer                           |  7235
  o         | Unsigned octal                                     |  610
  x         | Unsigned hexadecimal integer                       |  7fa
  X         | Unsigned hexadecimal integer (uppercase)           |  7FA
  f         | Decimal floating point, lowercase                  |  392.65
  F         | Decimal floating point, uppercase                  |  392.65
  e         | Scientific notation (mantissa/exponent), lowercase |  3.9265e+2
  E         | Scientific notation (mantissa/exponent), uppercase |  3.9265E+2
  g         | Use the shortest representation: %e or %f          |  392.65
  G         | Use the shortest representation: %E or %F          |  392.65
  a         | Hexadecimal floating point, lowercase              |  -0xc.90fep-2
  A         | Hexadecimal floating point, uppercase              |  -0XC.90FEP-2
  c         | Character                                          |  a
  s         | String of characters                               |  sample
  p         | Pointer address                                    |  b8000000
  n         | Nothing printed.                                   |
  The corresponding argument must be a pointer to a signed int.
  The number of characters written so far is stored in the pointed location.  
  % A % followed by another % character will write a single % to the stream.  %
   */
  template<typename Head, typename ... Tail>
  void printf(const char *str, Head head, Tail ... tail)
  {

  }

  template<typename Head>
  void printf(const char *str, Head head)
  {
    while(*str)
    {
      if(*str == '%')
      {
        str++;

        bool left_justify = false;
        bool force_polarity_sign = false;
        bool hash_flag = false;
        char pad_char = ' ';

        bool flags_done = false;
        while(!flags_done)
        {
          // get if it's a flag
          switch(*str)
          {
            case '-':
              left_justify = true;
              break;
            case '+':
              force_polarity_sign = true;
              break;
            // maybe ignore the "space case", it makes parsing hard :(
            //case ' ':
            case '#':
              hash_flag = true;
              break;
            case '0':
              pad_char = '0';
              break;
            default:
              flags_done = true;
              break;
          }
          str++;
        }


        // old impl
        /*
        str++;
        switch(*str)
        {
          case 'd': // decimal number
            str++; // TODO : more integer options
            print_int(head, "0123456789");
            break;
          case 'x': // hex
            str++;
            print_int(head, "0123456789abcdef", false);
            break;
          case 'X': // hex, upper case
            str++;
            print_int(head, "0123456789ABCDEF", false);
            break;
          case 'p': // pointer
            str++;
            // if we're printing a pointer, then convert it to the appropriate int
#if defined(__i386)
            print_num((u32)head, "0123456789abcdef");
#elif defined(__x86_64__)
            print_num((u64)head, "0123456789abcdef");
#else
#error ("Unknown architecture")
#endif
            break;
          case 'P': // pointer, upper case
            str++;
#if defined(__i386)
            print_num((u32)head, "0123456789ABCDEF");
#elif defined(__x86_64__)
            print_num((u64)head, "0123456789ABCDEF");
#else
#error ("Unknown architecture")
#endif
            break;
          // nothing; just print out the %
          default:
            putc('%');
            putc(*str++);
            break;
        }
        */
      }
      else
      {
        putc(*str++);
      }

    }
  }

  /**
   * Prints an integer (as opposed to a pointer). This will print the negative sign (if applicable)
   * and no problems will arise.
   */
  template<typename num_t>
  void print_int(num_t num, const char* alphabet, bool print_neg=true)
  {
    if(num < 0 && print_neg)
    {
      putc('-');
      num *= -1;
    }
    print_num(num, alphabet);
  }

  template<typename num_t>
  void print_num(num_t num, const char* alphabet)
  {
    if(num == 0)
      putc(alphabet[0]);
    u32 base = strlen(alphabet);
    u32 power = floor(logbase(num, static_cast<num_t>(base)));
    
    while(power)
    {
      u64 exp = pow(base, power);
      u64 index = ((u64)num) / exp;
      putc(alphabet[index]);
      num -= exp * index;
      power--;
    }
    putc(alphabet[(u64)num]);
  }

//  template<typename Head, typename ... Tail>
//  void printf(const char *str, Head& head, Tail& ... tail);
private:
  u32 m_term_row;
  u32 m_term_col;
  u8 m_term_color;
  u16 *m_term_buffer;

private:
  friend class Singleton<Terminal>;
};

u8 make_color(VgaColor fg, VgaColor bg);
u16 make_vga_entry(char c, u8 color);


#endif /* ALEK_TERMINAL_H */
