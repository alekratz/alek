/*
 * Copyright (C) 2015 Alek Ratzloff
 *
 * This file is part of Alek's Awesome Arm Kernel.
 * 
 * Alek's Awesome Arm Kernel is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Alek's Awesome Arm Kernel is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Alek's Awesome Arm Kernel.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "mailbox.h"
#include "types.h"
#include "mem.h"

// assert that u32s are the same size as addr_ts
static_assert(sizeof(u32) == sizeof(addr_t), "Address type is not the same size as u32");

enum MailboxAddr
{
  Base=0x2000B880,
  Read=Base+0,        // 2000B880
  Poll=Base+0x10,     // 2000B890
  Sender=Base+0x14,   // 2000B894
  Status=Base+0x18,   // 2000B898
  Config=Base+0x1c,   // 2000B89C
  Write=Base+0x20     // 2000B8A0
};

#define MAILBOX_FULL 0x80000000
#define MAILBOX_EMPTY 0x40000000

result_t write_mailbox(u32 value, u8 chan)
{
  if(value && 0xf) return R_FAIL;
  if(chan > 6) return R_FAIL;
  // wait to write data
  while(get32((void*)MailboxAddr::Status) & MAILBOX_FULL);
  put32((void*)(MailboxAddr::Write), value | chan);
  mem_barrier();
  return R_OK;
}

u32 read_mailbox(u8 chan)
{
  u32 value;
  for(;;)
  {
    // wait for something to exist in the mailbox
    while(get32((void*)MailboxAddr::Status) & MAILBOX_EMPTY);
    mem_barrier();
    value = get32((void*)MailboxAddr::Read);
    u8 rchan = value & 0xf;
    if(rchan == chan)
      return value >> 4;
  }
}