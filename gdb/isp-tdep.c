/* ISP */

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



#define ISP_PC_REGNUM 0

/* Provide a prototype to silence -Wmissing-prototypes.  */
void _initialize_isp_tdep (void);



static char *register_names[] = {"pc"};


static const char *
isp_register_name (struct gdbarch *gdbarch, int regnum)
{
	if (regnum >= 0 && regnum < ARRAY_SIZE(register_names))
		return register_names[regnum];

    return NULL;
}

static struct type *
isp_register_type (struct gdbarch *arch, int regnum)
{
  return builtin_type (arch)->builtin_uint32;
}

static CORE_ADDR
isp_unwind_pc (struct gdbarch *gdbarch, struct frame_info *this_frame)
{
  CORE_ADDR pc
    = frame_unwind_register_unsigned (this_frame, ISP_PC_REGNUM);

  return pc;
}

static CORE_ADDR
isp_read_pc (struct regcache *regcache)
{
  struct gdbarch_tdep *tdep = gdbarch_tdep (get_regcache_arch (regcache));
  ULONGEST pc;
  regcache_cooked_read_unsigned (regcache, ISP_PC_REGNUM, &pc);
  /* Mask off interrupt enable bit.  */
  return  pc;
}

static CORE_ADDR
isp_skip_prologue (struct gdbarch *gdbarch, CORE_ADDR start_pc)
{
  return 0;
}

static const gdb_byte *
isp_breakpoint_from_pc (struct gdbarch *gdbarch, CORE_ADDR *pc, int *len)
{
  static const gdb_byte break_insn[] = { 0x91 };

  *len = sizeof (break_insn);
  return break_insn;
}


struct isp_unwind_cache
{
  /* The frame's base, optionally used by the high-level debug info.  */
  CORE_ADDR base;
  /* The address of the first instruction in this function */
  CORE_ADDR pc;
  /* The offset of register saved on stack.  If register is not saved, the
     corresponding element is -1.  */
   CORE_ADDR prev_pc;
   CORE_ADDR cfa;
  //CORE_ADDR reg_saved[2];
};




static void
isp_setup_default (struct isp_unwind_cache *cache)
{
  cache->base =0;
}

static struct isp_unwind_cache *
isp_frame_unwind_cache (struct frame_info *this_frame, void **this_cache)
{
  struct gdbarch *gdbarch = get_frame_arch (this_frame);
  struct isp_unwind_cache *cache;
  CORE_ADDR current_pc;

  if (*this_cache != NULL)
    return (struct isp_unwind_cache *) *this_cache;

  cache = FRAME_OBSTACK_ZALLOC (struct isp_unwind_cache);
  (*this_cache) = cache;
  isp_setup_default (cache);

  cache->pc = get_frame_func (this_frame);
  current_pc = get_frame_pc (this_frame);

  return cache;
}


static void
isp_frame_this_id (struct frame_info *this_frame,
			  void **this_cache, struct frame_id *this_id)
{
  struct isp_unwind_cache *cache =
     isp_frame_unwind_cache (this_frame, this_cache);

  /* This marks the outermost frame.  */
  if (cache->base == 0)
    return;

  (*this_id) = frame_id_build (cache->cfa, cache->pc);
}


static struct value *
isp_frame_prev_register (struct frame_info *this_frame,
			  void **this_cache, int regnum)
{
  struct isp_unwind_cache *cache =
	isp_frame_unwind_cache (this_frame, this_cache);
  CORE_ADDR noFrame;
  int i;

  /* If we are asked to unwind the PC, then we need to unwind PC ? */
  if (regnum == ISP_PC_REGNUM)
	  return frame_unwind_got_register(this_frame,regnum, regnum);

  return frame_unwind_got_register (this_frame, regnum, regnum);
}


static const struct frame_unwind isp_frame_unwind =
{
  NORMAL_FRAME,
  default_frame_unwind_stop_reason,
  isp_frame_this_id,
  isp_frame_prev_register,
  NULL,
  default_frame_sniffer
};

static tdesc_arch_data * validate_reg_ipus(const struct target_desc *tdesc){
    struct tdesc_arch_data *tdesc_data = NULL;
    const struct tdesc_feature *feature;
    int valid_p, i;


    feature = tdesc_find_feature (tdesc, "org.gnu.gdb.isp.ipus");
    if (feature == NULL)
        return NULL;

    tdesc_data = tdesc_data_alloc ();
    valid_p = 1;
    for (i = 0; i < 1; i++)	/* PC */
        valid_p &= tdesc_numbered_register (feature, tdesc_data, i, register_names[i]);

    if (!valid_p){
        tdesc_data_cleanup (tdesc_data);
        return NULL;
    }
    
    return tdesc_data;
}


static tdesc_arch_data * validate_reg_ipuv(const struct target_desc *tdesc){
    struct tdesc_arch_data *tdesc_data = NULL;
    const struct tdesc_feature *feature;
    int valid_p, i;


    feature = tdesc_find_feature (tdesc, "org.gnu.gdb.isp.ipuv");
    if (feature == NULL)
        return NULL;

    tdesc_data = tdesc_data_alloc ();
    valid_p = 1;
    for (i = 0; i < 1; i++)	/* PC */
        valid_p &= tdesc_numbered_register (feature, tdesc_data, i, register_names[i]);

    if (!valid_p){
        tdesc_data_cleanup (tdesc_data);
        return NULL;
    }
    
    return tdesc_data;
}


static struct gdbarch *
isp_gdbarch_init (struct gdbarch_info info, struct gdbarch_list *arches)
{
    //_initialize_isp_tdep();
    struct gdbarch_tdep  *tdep;
    struct gdbarch       *gdbarch;
    int		mach;
    struct tdesc_arch_data *tdesc_data = NULL;
    const struct target_desc *tdesc = info.target_desc;
    
    if (info.bfd_arch_info != NULL)
    	mach = info.bfd_arch_info->mach;
    else
    	mach = bfd_mach_isp_ipus;
    
    //check tdesc
    if (tdesc_has_registers (tdesc))
    {
        if (mach == bfd_mach_isp_ipus){
            tdesc_data = validate_reg_ipus(tdesc);
        }else if (mach == bfd_mach_isp_ipuv){
            tdesc_data = validate_reg_ipuv(tdesc);
        }
    }
        

    arches = gdbarch_list_lookup_by_info(arches, &info);
    if (arches != NULL)
        return arches->gdbarch;
    
    gdbarch = gdbarch_alloc (&info, NULL);

    //This function must be called depends on architecture
    if (mach == bfd_mach_isp_ipus)
    	set_gdbarch_print_insn(gdbarch, print_insn_isp_ipus);
    else
    	set_gdbarch_print_insn(gdbarch, print_insn_isp_ipuv);

    set_gdbarch_register_name(gdbarch, isp_register_name);
    set_gdbarch_register_type(gdbarch, isp_register_type);

    set_gdbarch_num_regs(gdbarch, 1);
    info.byte_order_for_code = BFD_ENDIAN_LITTLE;
    
    /*Frame handling*/
    set_gdbarch_unwind_pc (gdbarch, isp_unwind_pc);
    set_gdbarch_read_pc(gdbarch, isp_read_pc);
    set_gdbarch_pc_regnum (gdbarch, ISP_PC_REGNUM);
    frame_unwind_append_unwinder (gdbarch, &isp_frame_unwind);
	
	//Set of dummy functions to avoid internal checks
	set_gdbarch_skip_prologue(gdbarch, isp_skip_prologue);
  	set_gdbarch_inner_than(gdbarch, core_addr_lessthan);
  	set_gdbarch_breakpoint_from_pc(gdbarch, isp_breakpoint_from_pc);
    
    /*Associates registers description with arch*/
    if (tdesc_data)
        tdesc_use_registers (gdbarch, tdesc, tdesc_data);

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
