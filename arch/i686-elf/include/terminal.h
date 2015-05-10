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

#include "singleton.h"
#include "types.h"

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