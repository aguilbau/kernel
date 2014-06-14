#include "types.h"

void			*memcpy(void *dest, const void *src, uint32_t n)
{
	char		*dest_ptr;

	dest_ptr = (char *)dest;
	while (n--)
		*((char *)src++) = *dest_ptr++;
	return (dest);
}
