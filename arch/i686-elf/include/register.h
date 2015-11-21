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
