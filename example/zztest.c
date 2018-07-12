#include <string.h>
#include <stdio.h>

#include <common.h>
#include <fuzz.h>
#include <fd.h>

int main(int argc, char** argv)
{
	char s[1000];
	
	strncpy(s, "The quick brown fox jumps over the lazy dog", 1000);

	fuzz_context_t zz;

	zzuf_set_ratio(0.04, 0.04);
	_zz_register(&zz);
	_zz_fuzz(&zz, s, strlen(s));

	printf("%s\n", s);

	return 0;
}
