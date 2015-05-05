#ifndef AAA_GPU_H
#define AAA_GPU_H

#include "types.h"

#define GPU_FLUSH_CACHE 0x40000000
#define FB_BASE_ADDR 0x2000

struct FramebufferInfo
{
  u32 p_width = 1024;   // physical width
  u32 p_height = 768;   // physical height
  u32 v_width = 1024;   // virtual width
  u32 v_height = 786;   // virtual height
  u32 gpu_pitch = 0;    // gpu pitch
  u32 bit_depth = 16;   // bit depth
  u32 x = 0;            // x offset
  u32 y = 0;            // y offset
  void* gpu_ptr = 0;    // frame pointer
  u32 gpu_size = 0;     // buffer size
};

class Graphics
{
public:
  Graphics();
  ~Graphics();
};

extern FramebufferInfo *fb_info;
result_t framebuffer_init(FramebufferInfo *fb_info);

#endif