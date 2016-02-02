#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "prime.h"

uint32_t mod10[200] = {
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
	, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , 0, 1, 2, 3, 4, 5, 6, 7, 8, 9
} ;

uint32_t div10[200] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0 , 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
	, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2 , 3, 3, 3, 3, 3, 3, 3, 3, 3, 3
	, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4 , 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
	, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6 , 7, 7, 7, 7, 7, 7, 7, 7, 7, 7
	, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 , 9, 9, 9, 9, 9, 9, 9, 9, 9, 9
	, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10 , 11, 11, 11, 11, 11, 11, 11, 11, 11, 11
	, 12, 12, 12, 12, 12, 12, 12, 12, 12, 12 , 13, 13, 13, 13, 13, 13, 13, 13, 13, 13
	, 14, 14, 14, 14, 14, 14, 14, 14, 14, 14 , 15, 15, 15, 15, 15, 15, 15, 15, 15, 15
	, 16, 16, 16, 16, 16, 16, 16, 16, 16, 16 , 17, 17, 17, 17, 17, 17, 17, 17, 17, 17
	, 18, 18, 18, 18, 18, 18, 18, 18, 18, 18 , 19, 19, 19, 19, 19, 19, 19, 19, 19, 19
} ;

uint64_t atoull(char *s) {
	unsigned int pos = 0;
	uint64_t result = 0;
	uint64_t c;

	while ((c = (uint64_t)(unsigned char)(s[pos] - '0')) < 10) {
		result = result * 10 + c;
		++pos;
	}

	return result;
}

void usage(const char *name) {
	printf("%s [-mn]\n\n", name);
	printf(" -m <min>\tStart at min value\n");
	printf(" -n <max>\tStop when max is reached\n");
	printf(" -h\t\tThis help\n");
}

int main(int argc, char *argv[]) {
	primegen pg;
	opterr = 0;
	uint32_t digits[64];
	uint64_t low = 2;
	uint64_t high = 1000000000;
	int c;

	while ((c = getopt(argc, argv, "m:n:")) != -1)
		switch (c) {
			case 'm':
				low = atoull(optarg);
				break;
			case 'n':
				high = atoull(optarg);
				break;
			case 'h':
			case '?':
			default:
				usage(argv[0]);
				return 1;
		}

	primegen_init(&pg);
	primegen_skipto(&pg, low);

	memset(digits, 0, 64);

	uint64_t p = primegen_peek(&pg);
	int len = 0;
	do {
		digits[len++] = p % 10;
		p /= 10;
	} while (p);

	p = primegen_peek(&pg);
	for (;;) {
		int i;

		uint32_t u = primegen_next(&pg) - p;
		p += u;

		if (p > high)
			break;

		for (i = 0; u; ++i) {
			u += digits[i];
			if (u >= 200) {
				digits[i] = u % 10;
				u = u / 10;
			} else {
				digits[i] = mod10[u];
				u = div10[u];
			}
		}

		if (i > len)
			len = i;

		for (i = len - 1; i >= 0; --i)
			putchar('0' + digits[i]);

		putchar('\n');
	}

	return 0;
}
