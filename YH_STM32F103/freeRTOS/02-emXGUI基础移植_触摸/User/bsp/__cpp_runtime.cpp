
#include <stddef.h>
#include "Kernel.h"

/*=========================================================================================*/

void* operator new(size_t size)
{
	return (void*)vmalloc(size);
}


void operator delete(void *p)
{
	vfree(p);
}

////

void* operator new[](size_t size)
{
	return (void*)vmalloc(size);
}

void operator delete[](void *p)
{
	vfree(p);
}

/*=========================================================================================*/
