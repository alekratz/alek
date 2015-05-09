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

.global init
.extern kmain

init:
  mov sp,#0x8000
  bl kmain
  b hang$
hang$:
  b hang$
