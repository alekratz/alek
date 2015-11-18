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

#include <types.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define DEFAULT_COL MKCOL(BLACK, WHITE)

#define MKCOL(fg,bg) (static_cast<u8>(fg | (bg << 4)))
#define MKVGA(c,col) (c | (static_cast<u16>(col) << 8))

#define TERMINST Terminal::get_instance

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
  /* typedefs */
private:
  typedef Terminal this_t;
  typedef Singleton<this_t> base_t;

  /* ctor, dtor */
private:
  Terminal();
  ~Terminal() = default;

  /* operations */
public:
  /* This is going to be the new "print" function - similar to printf, but... not */
  template<typename ... T>
  void print(T ... );

  template<typename ... T>
  void println(T ... );

  template<typename Head, typename ... Tail>
  void print(Head head, Tail ... tail)
  {
    print(head);
    print(tail ... );
  }

  template<typename Head, typename ... Tail>
  void println(Head head, Tail ... tail)
  {
    print(head);
    print(tail ... );
    putc('\n');
  }

  template<typename Head>
  void println(Head head)
  {
    print(head);
    putc('\n');
  }

  template<typename Head>
  void print(Head head);

  void print(const char *str)
  {
    puts(str);
  }

  template<typename Head>
  void print(Head* head)
  {
    print_int(reinterpret_cast<u32>(head), "0123456789abcdef", false);
  }
  
  void putentry(char c, u8 color, coord_t x, coord_t y);
  void putc(char c);
  void puts(const char *str);
  
  void scroll(u32 amount=1);
  void clear(u8 color=DEFAULT_COL);
protected:
  u32 m_get_term_row() { return m_term_row; }
  void m_set_term_row(u32 row) { m_term_row = row; }

  u32 m_get_term_col() { return m_term_col; }
  void m_set_term_col(u32 col) { m_term_col = col; }

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

private:
  u32 m_term_row;
  u32 m_term_col;
  u8 m_term_color;
  u16 *m_term_buffer;
  const char c_fmt_char = '%';

private:
  friend class Singleton<Terminal>;
};

#endif /* ALEK_TERMINAL_H */
