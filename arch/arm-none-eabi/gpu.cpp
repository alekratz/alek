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

#include <gpu.h>
#include <mailbox.h>
#include <types.h>

// Actual definition of FramebufferInfo here. However, what it /points/ to
// is perpetually on the stack. Specifically, kmain's stack.
FramebufferInfo *fb_info = nullptr;

Graphics::Graphics()
{

}

Graphics::~Graphics()
{

}

result_t framebuffer_init(FramebufferInfo *fb_info)
{
  fb_info = (FramebufferInfo*)FB_BASE_ADDR;
  *fb_info = FramebufferInfo(); // initialize to the default values
  
  u32 fb_address = FB_BASE_ADDR + GPU_FLUSH_CACHE;
  // Tell the GPU where the framebuffer base address is
  write_mailbox(fb_address, 1);
  // Confirm we got it
  if(read_mailbox(1) != 0)
    return R_FAIL;

  return R_OK;
}