/* **************************** [v] INCLUDES [v] **************************** */
#include <stddef.h> /*
#typedef size_t;
#        */
#include <stdint.h> /*
#typedef uint16_t;
#        */
/* **************************** [^] INCLUDES [^] **************************** */

void
	vga_memset(volatile uint16_t *b, uint16_t c, size_t len)
{
	while (len--)
		b[len] = c;
}
