/*
 *  zzuf - general purpose fuzzer
 *
 *  Copyright © 2002—2015 Sam Hocevar <sam@hocevar.net>
 *              2012 Kévin Szkudłapski <kszkudlapski@quarkslab.com>
 *
 *  This program is free software. It comes without any warranty, to
 *  the extent permitted by applicable law. You can redistribute it
 *  and/or modify it under the terms of the Do What the Fuck You Want
 *  to Public License, Version 2, as published by the WTFPL Task Force.
 *  See http://www.wtfpl.net/ for more details.
 */

/*
 *  libzzuf.c: preloaded wrapper library
 */

#define _GNU_SOURCE

#if defined HAVE_STDINT_H
#   include <stdint.h>
#elif defined HAVE_INTTYPES_H
#   include <inttypes.h>
#endif
#include <stdlib.h>
#if defined HAVE_REGEX_H
#   if _WIN32
#       include "util/regex.h"
#   else
#       include <regex.h>
#   endif
#endif
#if _WIN32
#   include <windows.h>
#endif
#include <string.h>
#include <math.h>

#include "common.h"
#include "fd.h"
#include "fuzz.h"
#include "ranges.h"
#if defined LIBZZUF
#   include "debug.h"
#endif

static int32_t seed = DEFAULT_SEED;
static double  minratio = DEFAULT_RATIO;
static double  maxratio = DEFAULT_RATIO;
static int     autoinc = 0;

void zzuf_set_seed(int32_t s)
{
    seed = s;
}

void zzuf_set_ratio(double r0, double r1)
{
    if (r0 == 0.0 && r1 == 0.0)
    {
        maxratio = minratio = 0.0;
        return;
    }

    minratio = r0 < MIN_RATIO ? MIN_RATIO : r0 > MAX_RATIO ? MAX_RATIO : r0;
    maxratio = r1 < MIN_RATIO ? MIN_RATIO : r1 > MAX_RATIO ? MAX_RATIO : r1;
    if (maxratio < minratio)
        maxratio = minratio;
}

double zzuf_get_ratio(void)
{
    uint8_t const shuffle[16] =
    { 0, 12, 2, 10,
      14, 8, 15, 7,
      9, 13, 3, 6,
      4, 1, 11, 5 };
    uint16_t rate;
    double min, max, cur;

    if (minratio == maxratio)
        return minratio; /* this also takes care of 0.0 */

    rate = shuffle[seed & 0xf] << 12;
    rate |= (seed & 0xf0) << 4;
    rate |= (seed & 0xf00) >> 4;
    rate |= (seed & 0xf000) >> 12;

    min = log(minratio);
    max = log(maxratio);

    cur = min + (max - min) * rate / 0xffff;

    return exp(cur);
}

void zzuf_set_auto_increment(void)
{
    autoinc = 1;
}

void _zz_register(fuzz_context_t* fuzz)
{
    fuzz->pos = 0;
    fuzz->seed = seed;
    fuzz->ratio = zzuf_get_ratio();
    fuzz->cur = -1;
#if defined HAVE_FGETLN
    fuzz->tmp = NULL;
#endif
    fuzz->uflag = 0;

    if (autoinc)
        seed++;
}

int64_t _zz_getpos(fuzz_context_t* fuzz)
{
    if(!fuzz)
    {
	return -1;
    }

    return fuzz->pos;
}

void _zz_setpos(fuzz_context_t* fuzz, int64_t pos)
{
    if(fuzz)
    {
    	fuzz->pos = pos;
    }
}

void _zz_addpos(fuzz_context_t* fuzz, int64_t off)
{
    if(fuzz)
    {
    	fuzz->pos += off;
    }
}
