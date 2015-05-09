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

#ifndef ALEK_MAILBOX_H
#define ALEK_MAILBOX_H

#include <types.h>

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

#endif /* ALEK_MAILBOX_H */