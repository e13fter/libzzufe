/*
 *  zzuf - general purpose fuzzer
 *
 *  Copyright © 2002—2015 Sam Hocevar <sam@hocevar.net>
 *
 *  This program is free software. It comes without any warranty, to
 *  the extent permitted by applicable law. You can redistribute it
 *  and/or modify it under the terms of the Do What the Fuck You Want
 *  to Public License, Version 2, as published by the WTFPL Task Force.
 *  See http://www.wtfpl.net/ for more details.
 */

/*
 *  fuzz.h: fuzz functions
 */

#include "common.h"

void _zz_fuzzing(char const *);
void _zz_bytes(char const *);
void zzuf_protect_range(char const *);
void zzuf_refuse_range(char const *);

void _zz_fuzz(fuzz_context_t*, volatile uint8_t *, int64_t);

