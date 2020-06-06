#pragma once

#define array_size(x) (sizeof(x)/sizeof(x[0]))

extern int strcmp(char const*, char const*);

inline bool strEqual(char const* a, char const* b) {
	return strcmp(a,b)==0;
}

inline bool charEqualIgnoreCaseAssumeAscii(char a, char b) {
	char const aa = a & 0xdf;
	char const bb = b & 0xdf;
	return (a==b) || ((aa == bb) && (aa >= 'A') && (aa <= 'Z'));
}

inline bool strEqualIgnoreCaseAssumeAscii(char const* a, char const* b) {
	while (*a && *b) {
		if (!charEqualIgnoreCaseAssumeAscii(*a, *b)) {
			return false;
		}
		++a;
		++b;
	}
	return *a == *b;
}

inline int alignToMultiple(int a, int divisor)
{
	if (divisor <= 1)
		return a;

	if ((a % divisor) == 0)
		return a;

	return a + divisor - (a % divisor);
}