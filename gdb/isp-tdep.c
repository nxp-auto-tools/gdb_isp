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
//#include "opcodes/isp-dis.h"
#include "target.h"
#include "objfiles.h"


/* Provide a prototype to silence -Wmissing-prototypes.  */
void _initialize_isp_tdep (void);

/* List of required functions
num_regs
register_name
*/

static char *register_names[] = {"pc"};


static const char *
isp_register_name (struct gdbarch *gdbarch, int regnum)
{
	if (regnum >= 0 && regnum < ARRAY_SIZE(register_names))
		return register_names[regnum];

    return NULL;
}

static struct type *
isp_register_type (struct gdbarch *arch,
		    int             regnum)
{
  //TODO:
  return builtin_type (arch)->builtin_uint32;
}


static struct gdbarch *
isp_gdbarch_init (struct gdbarch_info info, struct gdbarch_list *arches)
{
    //_initialize_isp_tdep();
    struct gdbarch       *gdbarch;
    int		mach;

    arches = gdbarch_list_lookup_by_info(arches, &info);
    if (arches != NULL)
        return arches->gdbarch;

    if (info.bfd_arch_info != NULL)
    	mach = info.bfd_arch_info->mach;
    else
    	mach = bfd_mach_isp_ipus;

    gdbarch = gdbarch_alloc (&info, NULL);

    //This function must be called depends on architecture
    if (mach == bfd_mach_isp_ipus)
    	set_gdbarch_print_insn(gdbarch, print_insn_isp_ipus);
    else
    	set_gdbarch_print_insn(gdbarch, print_insn_isp_ipuv);

    set_gdbarch_register_name(gdbarch, isp_register_name);
    set_gdbarch_register_type(gdbarch, isp_register_type);
    //set_gdbarch_bite_order(gdbarch, BFD_ENDIAN_LITTLE);
    //(*gdbarch)->byte_order = BFD_ENDIAN_LITTLE;
    set_gdbarch_num_regs(gdbarch, 1);
    
    return (gdbarch);
}

/*Call back from the initialize_all_files()*/
void
_initialize_isp_tdep (void)
{
    gdbarch_register (bfd_arch_isp, isp_gdbarch_init, NULL);
    initialize_tdesc_isp_ipus ();
    initialize_tdesc_isp_ipuv ();
}
