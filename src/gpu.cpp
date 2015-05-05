#include "gpu.h"
#include "types.h"
#include "mailbox.h"

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