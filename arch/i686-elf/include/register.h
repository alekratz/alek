#ifndef ALEK_REGISTER_H
#define ALEK_REGISTER_H

#include <types.h>
#include "terminal.h"

struct Registers
{
  u32 gs, fs, es, ds;
  u32 edi, esi, ebp, esp, ebx, edx, ecx, eax; /* pushed by pusha */
  u32 int_no, err_code;
  u32 eip, cs, eflags; /*, useresp, ss; */

  void printall()
  {
    TERMINST().printf("gs: %\n", gs); 
    TERMINST().printf("fs: %\n", fs); 
    TERMINST().printf("es: %\n", es); 
    TERMINST().printf("ds: %\n", ds); 
    TERMINST().printf("edi: %\n", edi); 
    TERMINST().printf("esi: %\n", esi); 
    TERMINST().printf("ebp: %\n", ebp); 
    TERMINST().printf("esp: %\n", esp); 
    TERMINST().printf("ebx: %\n", ebx); 
    TERMINST().printf("edx: %\n", edx); 
    TERMINST().printf("ecx: %\n", ecx); 
    TERMINST().printf("eax: %\n", eax); 
    TERMINST().printf("int_no: %\n", int_no); 
    TERMINST().printf("err_code: %\n", err_code); 
    TERMINST().printf("eip: %\n", eip); 
    TERMINST().printf("cs: %\n", cs); 
    TERMINST().printf("eflags: %\n", eflags); 
    /*
    TERMINST().printf("ss: %\n", ss); 
    TERMINST().printf("esp: %\n", esp); 
    */
  }
};

#endif
