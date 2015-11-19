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

#ifndef ALEK_PROCESS_H
#define ALEK_PROCESS_H

#include <types.h>

enum class ProcessState 
{
  Unused,
  Embryo,
  Running,
  Ready,
  Blocked,
  Zombie,
};

class Process
{
  /* ctor/dtor */
public:
  Process(u16 id);
  ~Process();

public:
  u16 get_id() const { return m_id; }

  ProcessState get_state() const { return m_state; }
  void set_state(ProcessState state) { m_state = state; }

  addr_t mem_start() const { return m_mem_start; }
  void set_mem_start(addr_t mem_start)
  {
    if(m_state != ProcessState::Embryo)
    {
      // print an error message and exit
      return;
    }
    m_mem_start = mem_start;
    calculate_heap_and_stack();
  }

  size_t get_mem_size() const { return m_mem_size; }
  addr_t get_kstack() const { return m_kstack; }
  Process* get_parent() const { return m_parent; }

private:
  void calculate_heap_and_stack();

private:
  u16           m_id;         // process id
  ProcessState  m_state;      // process state

  addr_t        m_mem_start;  // memory start address
  size_t        m_mem_size;   // memory size

  addr_t        m_stack_start;// stack start
  addr_t        m_heap_start; // heap start

  addr_t        m_kstack;     // bottom of the kernel stack
  Process*      m_parent;     // parent of this process
  //File*         m_files[NFILES]; // open files
  
};

#endif
