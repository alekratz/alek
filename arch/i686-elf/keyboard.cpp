#include <types.h>
#include "register.h"
#include "cpu_io.h"
#include "terminal.h"
#include "keyboard.h"
#include "irq.h"

static void keyboard_handler(Registers *regs);

static u8 keyboard_us[128] = 
{
  0, 27,
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
  '-', '=',
  '\b', '\t',
  'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',
  0, /* ctrl */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'',
  '`', 0, /* left shift */
  '\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/',
  0, /* right shift */
  '*',
  0, /* alt */
  ' ',
  0, /* caps */
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* F1-F10 */
  0, /* num lock */
  0, /* scrlk */
  0, /* home */
  0, /* up arrow */
  0, /* pgup */
  '-',
  0, /* left arrow */
  0,
  0, /* right arrow */
  '+',
  0, /* end*/
  0, /* down arrow */
  0, /* pgdown */
  0, /* insert */
  0, /* delete */
  0, 0, 0,
  0, /* F11 */
  0, /* F12 */
  0,
};

static void keyboard_handler(Registers *regs)
{
  u8 scancode = inb(0x60); // 0x60 is the keyboard data buffer
  if(scancode & 0x80)
  {
    // this is for control characters like shift, alt, etc
  }
  else
  {
    // forward the key to the right place
    // TERMINST().putc(keyboard_us[scancode]);
  }
}

void init_keyboard()
{
  register_irq_handler(1, keyboard_handler);
}