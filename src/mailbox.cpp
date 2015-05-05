#include "mailbox.h"
#include "types.h"
#include "mem.h"

// assert that u32s are the same size as addr_ts
static_assert(sizeof(u32) == sizeof(addr_t), "Address type is not the same size as u32");

enum class MailboxAddr : u32
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
  mem_barrier();
  put32((void*)(MailboxAddr::Write), value | chan);
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