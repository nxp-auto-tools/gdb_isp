/* THIS FILE IS GENERATED.  -*- buffer-read-only: t -*- vi:set ro:
  Original: vspa1.xml */

#include "defs.h"
#include "osabi.h"
#include "target-descriptions.h"

struct target_desc *tdesc_isp_ipuv;
static void
initialize_tdesc_isp_ipuv (void)
{
  struct target_desc *result = allocate_target_description ();
  struct tdesc_feature *feature;

  set_tdesc_architecture (result, bfd_scan_arch ("isp-ipuv"));

  feature = tdesc_create_feature (result, "org.gnu.gdb.ipuv.apu.acp");
  tdesc_create_reg (feature, "pc", 0, 1, NULL, 32, "code_ptr");
  

  tdesc_isp_ipuv = result;
}