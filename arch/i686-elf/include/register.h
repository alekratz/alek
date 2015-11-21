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
 
#ifndef ALEK_REGISTER_H
#define ALEK_REGISTER_H

#include <types.h>
#include "terminal.h"

struct Registers
{
  u32 gs, fs, es, ds;
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by pusha */
  u32 int_no, err_code;
  u32 eip, cs, eflags, useresp, ss;

  void printall()
  {
    TERMINST().println("gs: ", gs);
    TERMINST().println("fs: ", fs);
    TERMINST().println("es: ", es);
    TERMINST().println("ds: ", ds);
    TERMINST().println("edi: ", edi);
    TERMINST().println("esi: ", esi);
    TERMINST().println("ebp: ", ebp);
    TERMINST().println("esp: ", esp);
    TERMINST().println("ebx: ", ebx);
    TERMINST().println("edx: ", edx);
    TERMINST().println("ecx: ", ecx);
    TERMINST().println("eax: ", eax);
    TERMINST().println("int_no: ", int_no);
    TERMINST().println("err_code: ", err_code);
    TERMINST().println("eip: ", eip);
    TERMINST().println("cs: ", cs);
    TERMINST().println("eflags: ", eflags);
    /*
    TERMINST().println("ss: ", ss); 
    TERMINST().println("esp: ", esp); 
    */
  }
};

#endif
