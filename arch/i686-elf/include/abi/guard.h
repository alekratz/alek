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

#ifndef ALEK_CXX_GUARD_H
#define ALEK_CXX_GUARD_H
namespace __cxxabiv1 {
extern "C" {

/* guard variables go here */

__extension__ typedef int __guard __attribute__((mode(__DI__)));

/* Local static variable guard functions */
int __cxa_guard_acquire (__guard *);
void __cxa_guard_release (__guard *);
void __cxa_guard_abort (__guard *);

} /* extern "C" */
} /* __cxxabiv1 */
#endif /* ALEK_CXX_GUARD_H */