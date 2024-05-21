#include "str.h"

void test_str()
{
	struct str* s = new_str();
	str_append(s, 'a');
	str_append(s, 'b');
	str_append(s, 'b');
	str_append(s, 'b');
	print_str(s);
	free_str(s);
}

int main(void)
{
	test_str();
}
