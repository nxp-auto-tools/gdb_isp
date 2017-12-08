/* Single instruction disassembler for the ISP.

   Copyright (C) 2015-2017 Free Software Foundation, Inc.

   This file is part of the GNU opcodes library.

   This library is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   It is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
   or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public
   License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor, Boston,
   MA 02110-1301, USA.  */

#include "sysdep.h"
#include "dis-asm.h"
#include "isp-dis.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <setjmp.h>


/* Print the ISP instruction at address addr in debugged memory,
   on info->stream. Return length of the instruction, in bytes.  */
int
print_insn_isp (bfd_vma addr, disassemble_info *info)
{
   return 0;
}

