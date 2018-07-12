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
 *  fd.h: file descriptor functions
 */

#include "common.h"

#include <stdint.h>
#include <wchar.h>

void zzuf_set_seed(int32_t);
void zzuf_set_ratio(double, double);
double zzuf_get_ratio(void);
void zzuf_set_auto_increment(void);

int64_t _zz_getpos(fuzz_context_t*);
void _zz_setpos(fuzz_context_t*, int64_t);
void _zz_addpos(fuzz_context_t*, int64_t);

void _zz_register(fuzz_context_t* fuzz);
