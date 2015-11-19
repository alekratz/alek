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

#include "process.h"

Process::Process(u16 id)
  : m_id(id)
  , m_state(ProcessState::Embryo)
  , m_mem_start(nullptr)
  , m_mem_size(0)
{
}

Process::~Process()
{

}

void Process::calculate_heap_and_stack()
{
  m_heap_start = m_stack_start = reinterpret_cast<addr_t>(
    reinterpret_cast<u32>(m_mem_start) + (m_mem_size / 2));
}