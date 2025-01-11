#include "cfmt.h"
#include <stdlib.h>

int main()
{
	const char *test1 = "test1";
	char *test2 = "test2";

	format_fprint(stdout, "test char* {} {}\n", 2, FORMAT_ARG(test1, FORMAT_STR), FORMAT_ARG(test2, FORMAT_STR));

	format_fprint(stderr, "Formatted message: {2:#x} {1:d} {0},with {3} {4:.3f}\n", 5, FORMAT_ARG("Hello from fmt!", FORMAT_STR),
		      FORMAT_ARG(3, FORMAT_INT),
		      FORMAT_ARG_INT(20),
		      FORMAT_ARG_STR("fadsaf"),
		      FORMAT_ARG(5.40, FORMAT_DOUBLE));

	format_print("test stdout {}\n", 1, FORMAT_ARG_STR(test1));

	/* format_system_error(43,"error etst {}"); */
	format_system_error_fprint(stderr, 2, "error test {}", 1, FORMAT_ARG_STR("no"));
	char *res = format_string_dup("test {} {}", 2, FORMAT_ARG_INT(5), FORMAT_ARG_INT(6));
	printf("%s\n", res);
	free(res);

	return 0;
}
