#ifndef MAILBOX_H
#define MAILBOX_H
#ifdef __cplusplus
extern "C" {
#endif

#include "types.h"

/**
 * Writes a 28-bit integer to the mailbox.
 * @param value a 28-bit integer. The bottom four bits /must/ be cleared (0).
 * @param chan a 3-bit integer, 0-6, that represents the channel.
 * @returns 0 on sucess, -1 on failure.
 */
result_t write_mailbox(u32 value, u8 chan);

#ifdef __cplusplus
}
#endif /* extern C */
#endif /* MAILBOX_H */