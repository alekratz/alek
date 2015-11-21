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

#define TERM_TAB_WIDTH 4

Terminal::Terminal()
  : m_term_row(0)
  , m_term_col(0)
  , m_term_buffer(reinterpret_cast<u16*>(0xB8000))
{
  m_term_color = DEFAULT_COL;
  clear();
}

void Terminal::putentry(char c, u8 color, coord_t x, coord_t y)
{
  const coord_t index = y * VGA_WIDTH + x;
  m_term_buffer[index] = MKVGA(c, color);
}

void Terminal::putc(char c)
{
  switch(c)
  {
    case '\n':
      goto new_line;
    case '\t':
      do
        putentry(' ', m_term_color, m_term_col++, m_term_row);
      while(m_term_col % TERM_TAB_WIDTH);
      break;
    case 0:
      return;
    default:
      putentry(c, m_term_color, m_term_col++, m_term_row);
      if(m_term_col == VGA_WIDTH)
      {
new_line:
        m_term_col = 0;
        if((++m_term_row) == VGA_HEIGHT)
          // TODO : scroll up
          scroll(1);
          //m_term_row = 0;
      }
      break;
  }
}

void Terminal::puts(const char *str)
{
  while(*str)
    putc(*str++);
}

void Terminal::scroll(u32 amount)
{
  const u16 BLANK = MKVGA(' ', m_term_color);
  while(amount--)
  {
    // move everything up one line
    for(size_t row = 0; row < VGA_HEIGHT - 1; row++)
    {
      for(size_t col = 0; col < VGA_WIDTH; col++)
      {
        coord_t dest_index = row * VGA_WIDTH + col;
        coord_t src_index = (row + 1) * VGA_WIDTH + col;
        m_term_buffer[dest_index] = m_term_buffer[src_index];
      }
    }
    // write a completely blank line at the end
    for(size_t col = 0; col < VGA_WIDTH; col++)
    {
      coord_t index = (VGA_HEIGHT - 1) * VGA_WIDTH + col;
      m_term_buffer[index] = BLANK;
    }
  }
  m_term_row = VGA_HEIGHT - 1;
}

void Terminal::clear(u8 color)
{
  u16 entry = MKVGA(' ', color);
  for(coord_t row = 0; row < VGA_HEIGHT; row++)
  {
    for(coord_t col = 0; col < VGA_WIDTH; col++)
    {
      coord_t index = row * VGA_WIDTH + col;
      m_term_buffer[index] = entry;
    }
  }
}

template<>
void Terminal::print(s8 n)
{
  print_int(n, "0123456789");
}

template<>
void Terminal::print(s16 n)
{
  print_int(n, "0123456789");
}

template<>
void Terminal::print(s32 n)
{
  print_int(n, "0123456789");
}


template<>
void Terminal::print(s64 n)
{
  print_int(n, "0123456789");
}

template<>
void Terminal::print(u8 n)
{
  print_int(n, "0123456789");
}

template<>
void Terminal::print(u16 n)
{
  print_int(n, "0123456789", false);
}

template<>
void Terminal::print(u32 n)
{
  print_int(n, "0123456789", false);
}

template<>
void Terminal::print(u64 n)
{
  print_int(n, "0123456789", false);
}
