

#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"
#include "elf-bfd.h"

/* This does not include any relocations, but should be good enough
   for GDB.  */

#define TARGET_LITTLE_SYM		isp_elf32_le_vec
#define TARGET_LITTLE_NAME		"elf32-le-isp"
#define ELF_ARCH		        bfd_arch_isp
#define ELF_MACHINE_CODE	    EM_ISP
#define ELF_MAXPAGESIZE  	    1 /* FIXME: This number is wrong,  It should be the page size in bytes.  */
#define bfd_elf32_bfd_reloc_type_lookup bfd_default_reloc_type_lookup
#define bfd_elf32_bfd_reloc_name_lookup _bfd_norelocs_bfd_reloc_name_lookup
#define elf_info_to_howto		_bfd_elf_no_info_to_howto

#include "elf32-target.h"
