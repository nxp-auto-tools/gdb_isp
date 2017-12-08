/* Target-dependent code for the ISP.

   Copyright (C) 2015-2016 Free Software Foundation, Inc.

   This file is part of GDB.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

#include "defs.h"
#include "arch-utils.h"
#include "dis-asm.h"
#include "floatformat.h"
#include "frame.h"
#include "frame-base.h"
#include "frame-unwind.h"
#include "gdbcore.h"
#include "gdbtypes.h"
#include "osabi.h"
#include "regcache.h"
#include "regset.h"
#include "trad-frame.h"
#include "dwarf2-frame.h"
#include "value.h"
#include "isp-tdep.h"
#include "features/isp-ipus.c"
#include "features/isp-ipuv.c"
#include "target.h"
#include "objfiles.h"


/* Provide a prototype to silence -Wmissing-prototypes.  */
void _initialize_isp_tdep (void);

static struct gdbarch *
isp_gdbarch_init (struct gdbarch_info info, struct gdbarch_list *arches)
{
  //_initialize_isp_tdep();
	struct gdbarch       *gdbarch;

	gdbarch = gdbarch_alloc (&info, NULL);

	set_gdbarch_print_insn (gdbarch, print_insn_isp);
  return (gdbarch);
}


void
_initialize_isp_tdep (void)
{
  gdbarch_register (bfd_arch_isp, isp_gdbarch_init, NULL);
  initialize_tdesc_isp_ipus ();
  initialize_tdesc_isp_ipuv ();
}
