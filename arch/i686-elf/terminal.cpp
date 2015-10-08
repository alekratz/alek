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
  m_term_color = make_color(VgaColor::BLACK, VgaColor::WHITE);
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
  switch(c)
  {
    case '\n':
      goto new_line;
    case '\t':
      do
        putentry(' ', m_term_color, m_term_col++, m_term_row);
      while(m_term_col % TERM_TAB_WIDTH);
      break;
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

void Terminal::printf(const char *str)
{
  puts(str);
}

void Terminal::scroll(u32 amount)
{
  const u16 BLANK = make_vga_entry(' ', m_term_color);
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

//template<typename Head, typename ... Tail>
//void Terminal::printf(const char *str, Head& head, Tail& ... tail);

template<>
void Terminal::printf(const char *s, const char *t)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    puts(t);
    s++;
  }
  for(; (*s); s++) putc(*s);
}

template<>
void Terminal::printf(const char *s, s8 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789");
    s++;
  }
  for(; (*s); s++) putc(*s);
}

template<>
void Terminal::printf(const char *s, s16 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789");
    s++;
  }
  for(; (*s); s++) putc(*s);
}

template<>
void Terminal::printf(const char *s, s32 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789");
    s++;
  }
  for(; (*s); s++) putc(*s);
}


template<>
void Terminal::printf(const char *s, s64 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789");
    s++;
  }
  for(; (*s); s++) putc(*s);
}

template<>
void Terminal::printf(const char *s, u8 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789");
    s++;
  }
  for(; (*s); s++) putc(*s);
}

template<>
void Terminal::printf(const char *s, u16 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789", false);
    s++;
  }
  for(; (*s); s++) putc(*s);
}

template<>
void Terminal::printf(const char *s, u32 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789", false);
    s++;
  }
  for(; (*s); s++) putc(*s);
}

template<>
void Terminal::printf(const char *s, u64 n)
{
  for(; (*s) && (*s) != c_fmt_char; s++) putc(*s);
  if(*s)
  {
    print_int(n, "0123456789", false);
    s++;
  }
  for(; (*s); s++) putc(*s);
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
