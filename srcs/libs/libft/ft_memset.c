/* **************************** [v] INCLUDES [v] **************************** */
#include <stddef.h> /*
#typedef size_t;
#        */
/* **************************** [^] INCLUDES [^] **************************** */

void
	*ft_memset(void *b, register int c, register size_t len)
{
	while (len--)
		((unsigned char *)b)[len] = (unsigned char)c;
	return (b);
}
