/*
 * Copyrights
 */


#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"

const bfd_arch_info_type bfd_isp_ipus_arch =
{
  32,				/* bits per word */
  32,				/* bits per address */
  8,				/* bits per byte */
  bfd_arch_isp,			/* architecture */
  bfd_mach_isp_ipus,		/* machine */
  "isp",			/* architecture name */
  "isp-ipus",			/* printable name */
  2,				/* section align power */
  TRUE,				/* the default ? */
  bfd_default_compatible,	/* architecture comparison fn */
  bfd_default_scan,		/* string to architecture convert fn */
  bfd_arch_default_fill,	/* default fill */
  NULL			/* next in list */
};

const bfd_arch_info_type bfd_isp_arch =
{
  32,				/* bits per word */
  32,				/* bits per address */
  8,				/* bits per byte */
  bfd_arch_isp,			/* architecture */
  bfd_mach_isp_ipuv,		/* machine */
  "isp",			/* architecture name */
  "isp-ipuv",			/* printable name */
  2,				/* section align power */
  FALSE,			/* the default ? */
  bfd_default_compatible,	/* architecture comparison fn */
  bfd_default_scan,		/* string to architecture convert fn */
  bfd_arch_default_fill,	/* default fill */
  &bfd_isp_ipus_arch		/* next in list */
};