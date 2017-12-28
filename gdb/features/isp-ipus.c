/* THIS FILE IS GENERATED.  -*- buffer-read-only: t -*- vi:set ro:
  Original: vspa1.xml */

#include "defs.h"
#include "osabi.h"
#include "target-descriptions.h"

struct target_desc *tdesc_isp_ipus;
static void
initialize_tdesc_isp_ipus (void)
{
  struct target_desc *result = allocate_target_description ();
  struct tdesc_feature *feature;

  set_tdesc_architecture (result, bfd_scan_arch ("ipus"));

  feature = tdesc_create_feature (result, "org.gnu.gdb.ipus.apu.acp");
  tdesc_create_reg (feature, "pc", 0, 1, NULL, 16, "uint16");
  

  tdesc_isp_ipus = result;
}
