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

#include "mem.h"
#include "string.h"
#include "terminal.h"

Terminal::Terminal()
  : m_term_row(0)
  , m_term_col(0)
  , m_term_buffer(reinterpret_cast<u16*>(0xB8000))
{
  m_term_color = make_color(VgaColor::LIGHT_GREY, VgaColor::BLACK);
  u16 entry = make_vga_entry(' ', m_term_color);
  memset<u16>(m_term_buffer, entry, VGA_WIDTH * VGA_HEIGHT);
}

void Terminal::putentry(char c, u8 color, coord_t x, coord_t y)
{
  const coord_t index = y * VGA_WIDTH + x;
  m_term_buffer[index] = make_vga_entry(c, color);
}

void Terminal::putc(char c)
{
  putentry(c, m_term_color, m_term_col, m_term_row);
  if((++m_term_col) == VGA_WIDTH)
  {
    m_term_col = 0;
    if((++m_term_row) == VGA_HEIGHT)
      m_term_row = 0;
  }
}

void Terminal::puts(const char *str)
{
  size_t len = strlen(str);
  for(size_t i = 0; i < len; i++)
    putc(str[i]);
}

u8 make_color(VgaColor fg, VgaColor bg)
{
  return fg | (bg << 4);
}

u16 make_vga_entry(char c, u8 color)
{
  u16 c16 = c;
  u16 color16 = color;
  return c16 | (color16 << 8);
}
