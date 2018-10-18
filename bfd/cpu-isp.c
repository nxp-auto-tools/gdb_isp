/*
* Copyright (c) 2018, NXP.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without modification,
* are permitted provided that the following conditions are met:
*
* o Redistributions of source code must retain the above copyright notice, this list
*   of conditions and the following disclaimer.
*
* o Redistributions in binary form must reproduce the above copyright notice, this
*   list of conditions and the following disclaimer in the documentation and/or
*   other materials provided with the distribution.
*
* o Neither the name of NXP, Inc. nor the names of its
*   contributors may be used to endorse or promote products derived from this
*   software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
* ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
* DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
* ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
* ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
* SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/



#include "sysdep.h"
#include "bfd.h"
#include "libbfd.h"
const bfd_arch_info_type bfd_isp64_ipuv_arch =
{
  64,				/* bits per word */
  64,				/* bits per address */
  8,				/* bits per byte */
  bfd_arch_isp,			/* architecture */
  bfd_mach_isp_ipuv,		/* machine */
  "isp-le",			/* architecture name */
  "isp-ipuv-le",			/* printable name */
  2,				/* section align power */
  FALSE,			/* the default ? */
  bfd_default_compatible,	/* architecture comparison fn */
  bfd_default_scan,		/* string to architecture convert fn */
  bfd_arch_default_fill,	/* default fill */
  NULL		/* next in list */
};

const bfd_arch_info_type bfd_isp64_arch =
{
  64,				/* bits per word */
  64,				/* bits per address */
  8,				/* bits per byte */
  bfd_arch_isp,			/* architecture */
  bfd_mach_isp_ipus,		/* machine */
  "isp-le",			/* architecture name */
  "isp-ipus-le",			/* printable name */
  2,				/* section align power */
  TRUE,				/* the default ? */
  bfd_default_compatible,	/* architecture comparison fn */
  bfd_default_scan,		/* string to architecture convert fn */
  bfd_arch_default_fill,	/* default fill */
  &bfd_isp64_ipuv_arch			/* next in list */
};

const bfd_arch_info_type bfd_isp_ipuv_arch =
{
  32,				/* bits per word */
  32,				/* bits per address */
  8,				/* bits per byte */
  bfd_arch_isp,			/* architecture */
  bfd_mach_isp_ipuv,		/* machine */
  "isp-le",			/* architecture name */
  "isp-ipuv-le",			/* printable name */
  2,				/* section align power */
  FALSE,			/* the default ? */
  bfd_default_compatible,	/* architecture comparison fn */
  bfd_default_scan,		/* string to architecture convert fn */
  bfd_arch_default_fill,	/* default fill */
  &bfd_isp64_arch		/* next in list */
};

const bfd_arch_info_type bfd_isp_arch =
{
  32,				/* bits per word */
  32,				/* bits per address */
  8,				/* bits per byte */
  bfd_arch_isp,			/* architecture */
  bfd_mach_isp_ipus,		/* machine */
  "isp-le",			/* architecture name */
  "isp-ipus-le",			/* printable name */
  2,				/* section align power */
  TRUE,				/* the default ? */
  bfd_default_compatible,	/* architecture comparison fn */
  bfd_default_scan,		/* string to architecture convert fn */
  bfd_arch_default_fill,	/* default fill */
  &bfd_isp_ipuv_arch			/* next in list */
};
