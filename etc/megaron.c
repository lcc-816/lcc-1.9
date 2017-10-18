/* VAXes running UNIX 4.3BSD at University of Arizona */

#include <string.h>

char *cpp[] = { "/usr/local/lib/gcc-cpp", "-undef", "-Dvax",
	"$1", "$2", "$3", 0 };
char *include[] = { "-I/usr/drh/include/ansi", 0 };
char *com[] = { "/usr/drh/lib/rcc", "$1", "$2", "$3", 0 };
char *as[] = { "/bin/as", "-J", "-o", "$3", "$1", "$2", 0 };
char *ld[] = { "/bin/ld", "-o", "$3", "/lib/crt0.o", "-X",
	"$1", "$2", "", "-lm", "", "-lc", 0 };

int option(arg) char *arg; {
	if (strcmp(arg, "-g") == 0)
		ld[9]  = "-lg";
	else if (strcmp(arg, "-p") == 0) {
		ld[3]  = "/lib/mcrt0.o";
		ld[10] = "-lc_p";
	} else if (strcmp(arg, "-pg") == 0) {
		ld[3]  = "/usr/lib/gcrt0.o";
		ld[10] = "-lc_p";
	} else if (strcmp(arg, "-b") == 0
	&& access("/usr/drh/lib/bbexit.o", 4) == 0)
		ld[7]  = "/usr/drh/lib/bbexit.o";
	else
		return 0;
	return 1;
}
