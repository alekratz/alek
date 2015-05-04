#ifndef AAA_MAILBOX_H
#define AAA_MAILBOX_H

#include "types.h"

/**
 * Writes a 28-bit integer to the mailbox.
 * @param value a 28-bit integer. The bottom four bits /must/ be cleared (0).
 * @param chan a channel to write to.
 * @return 0 on sucess, -1 on failure.
 */
result_t write_mailbox(u32 value, u8 chan);

/**
 * Reads a 28-bit integer from the mailbox.
 * @param chan a channel to read from.
 * @return value read from that channel.
 */
u32 read_mailbox(u8 chan);

#endif /* AAA_MAILBOX_H */