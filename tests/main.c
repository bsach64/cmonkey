#include <stdio.h>
#include "str.h"

void test_str()
{
	struct str* s = new_str();
	printf("%zu\n", s->length);
}

int main(void)
{
	test_str();
}
