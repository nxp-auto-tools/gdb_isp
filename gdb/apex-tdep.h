/*
 * Copyrights
 */

#ifndef APEX_TDEP__H
#define APEX_TDEP__H

#ifndef TARGET_APEX
#define TARGET_APEX
#endif

/*! APEX specific per-architecture information.*/
enum apex_base_addr{
	apex_0 = 0x74000000,
	apex_1 = 0x78000000
}apex_base_addr;

struct gdbarch_tdep
{
  unsigned int  num_matchpoints;	/* Total h/w breakpoints available. */
  unsigned int  scalar_gp_regs_num;		/* Number of general registers.  */
  unsigned int	num_cu_regs;		/* TODO: Number of computational units. Does it needed */
  int           bytes_per_scalar_word; /* self-commented */
  int			bytes_per_vector_word; /* self-commented */
  int           bytes_per_dmem_address; /* ACP memory */
  int			bytes_per_cmem_address;	/* VU memory */
  struct type* apex_vector_512_type;
};

enum {
  /* ACP registers */
  APEX_R0_REGNUM = 0,
  APEX_LR_REGNUM = APEX_R0_REGNUM + 29,
  APEX_VSP_REGNUM,
  APEX_SP_REGNUM,
  APEX_OV_REGNUM,
  APEX_PC_REGNUM,
  APEX_ACP_REGS_END,
	/* VCU vectors */
  v0_REGNUM = APEX_ACP_REGS_END,
  v1_REGNUM,
  v2_REGNUM,
  v3_REGNUM,
  v4_REGNUM,
  v5_REGNUM,
  v6_REGNUM,
  v7_REGNUM,
  VECTORS_END,
	/* VCU ctl regs */
  ovv_REGNUM = VECTORS_END,
  vc0_REGNUM,
  vc1_REGNUM,
  vc2_REGNUM,
  vc3_REGNUM,
  vcsptr_REGNUM,
  vcs0_REGNUM,
  vcs1_REGNUM,
  vcs2_REGNUM,
  vcs3_REGNUM,
  vcs4_REGNUM,
  vcs5_REGNUM,
  vcs6_REGNUM,
  vcs7_REGNUM,
  VCU_REGS_END,
  cmem_if_apu_pm_start_regnum = VCU_REGS_END,
  cmem_if_apu_dm_start_regnum,
  APEX_REGS_TOTAL_NUM

};


/***** TRUE OFFSETS ******/

#define APEX_ACP_REG_GP 	0
#define APEX_ACP_REG_CTL 	32
#define APEX_VCU_REG_GP		44
#define APEX_VCU_REG_CTL	52

#endif
