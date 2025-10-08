/* **************************** [v] INCLUDES [v] **************************** */
#include <stddef.h> /*
#typedef size_t;
#        */
#include <stdint.h> /*
#typedef uint8_t;
#        */
/* **************************** [^] INCLUDES [^] **************************** */

void
	*ft_memcpy(void *dst, register const void *src, register size_t n)
{
	if ((!dst && !src) || !n)
		return (NULL);

	if (dst < src)
	{
		while (n--)
			*(uint8_t *)dst++ = *(const uint8_t *)src++;
	}
	else
	{
		while (n--)
			((uint8_t *)dst)[n] = ((const uint8_t *)src)[n];
	}
	return (dst);
}
