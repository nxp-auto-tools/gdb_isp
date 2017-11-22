/* THIS FILE IS GENERATED.  -*- buffer-read-only: t -*- vi:set ro:
  Original: apex.xml */

#include "defs.h"
#include "osabi.h"
#include "target-descriptions.h"

struct target_desc *tdesc_apex;
static void
initialize_tdesc_apex_apu (void)
{
  struct target_desc *result = allocate_target_description ();
  struct tdesc_feature *feature;
  struct tdesc_type *union_field_type,*vector_cell_type;
  struct tdesc_type *type;

  set_tdesc_architecture (result, bfd_scan_arch ("apex"));

  feature = tdesc_create_feature (result, "org.gnu.gdb.apex.apu.acp");
  tdesc_create_reg (feature, "r0",  0, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r1",  1, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r2",  2, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r3",  3, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r4",  4, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r5",  5, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r6",  6, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r7",  7, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r8",  8, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r9",  9, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r10", 10, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r11", 11, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r12", 12, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r13", 13, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r14", 14, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r15", 15, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r16", 16, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r17", 17, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r18", 18, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r19", 19, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r20", 20, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r21", 21, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r22", 22, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r23", 23, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r24", 24, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r25", 25, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r26", 26, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r27", 27, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r28", 28, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r29", 29, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r30", 30, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "r31", 31, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "ov",  32, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "pc",  33, 1, NULL, 32, "uint32");

  feature = tdesc_create_feature (result, "org.gnu.gdb.apex.apu.vec");

  vector_cell_type = tdesc_named_type (feature, "uint16");

  tdesc_create_vector (feature, "vector", vector_cell_type, 32);
  type = tdesc_create_union (feature, "vector_type");
  union_field_type = tdesc_named_type (feature, "vector");
  tdesc_add_field (type, "v32_uint16", union_field_type);

  tdesc_create_reg (feature, "v0",   34, 1, NULL, 512, "vector_type");
  tdesc_create_reg (feature, "v1",   35, 1, NULL, 512, "vector_type");
  tdesc_create_reg (feature, "v2",   36, 1, NULL, 512, "vector_type");
  tdesc_create_reg (feature, "v3",   37, 1, NULL, 512, "vector_type");
  tdesc_create_reg (feature, "v4",   38, 1, NULL, 512, "vector_type");
  tdesc_create_reg (feature, "v5",   39, 1, NULL, 512, "vector_type");
  tdesc_create_reg (feature, "v6",   40, 1, NULL, 512, "vector_type");
  tdesc_create_reg (feature, "v7",   41, 1, NULL, 512, "vector_type");

  tdesc_create_reg (feature, "ovv",  42, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vc0",  43, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vc1",  44, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vc2",  45, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vc3",  46, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcsptr",47,1, NULL,  8, "uint8");
  tdesc_create_reg (feature, "vcs0", 48, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcs1", 49, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcs2", 50, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcs3", 51, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcs4", 52, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcs5", 53, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcs6", 54, 1, NULL, 32, "uint32");
  tdesc_create_reg (feature, "vcs7", 55, 1, NULL, 32, "uint32");

  feature = tdesc_create_feature (result, "org.gnu.gdb.apex.apu.acp.dbg");
  tdesc_create_reg (feature, "cmem_if_apu_pm_start", 56, 1, "system", 32, "uint32");
  tdesc_create_reg (feature, "cmem_if_apu_dm_start", 57, 1, "system", 32, "uint32");

  tdesc_apex = result;
}
