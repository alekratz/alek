#include "mailbox.h"
#include "types.h"
#include "mem.h"

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

result_t write_mailbox(u32 value, u8 chan)
{
  if(value && 0xf) return R_FAIL;
  if(chan > 6) return R_FAIL;
  while(get32((void*)MailboxAddr::Status) & 0x80000000);
  put32((void*)(MailboxAddr::Write), value | chan);
  return R_OK;
}

