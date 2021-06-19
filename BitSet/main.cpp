#include <stdio.h>
#include <memory.h>
#define byte1(x, y) (((1<<(8-(x)))-(1<<(7-(y)))))
typedef unsigned char byte;
typedef unsigned int uint;
void BitSet(byte* dst, uint index, byte* src, uint length) {
	uint i8 = index >> 3;
	uint j8 = index & 7;
	uint l8 = (j8 + length) >> 3;
	uint m8 = (j8 + length) & 7;
	if (l8 == 0) {
		dst[i8] = (src[0] >> j8 & byte1(j8, m8 - 1)) | (dst[i8] & byte1(0, j8 - 1)) | (dst[i8] & byte1(m8, 7));
		return;
	}
	dst[i8] = (src[0] >> j8 & byte1(j8, 7)) | (dst[i8] & byte1(0, j8 - 1));
	if (l8 == 1) {
		if (m8 > j8) {
			dst[i8 + 1] = ((src[0] << (8 - j8)) & 0xff) | ((src[1] >> j8) & byte1(j8, m8 - 1)) | (dst[i8 + 1] & byte1(m8, 7));
			return;
		}
		dst[i8 + 1] = ((src[0] << (8 - j8)) & byte1(0, m8 - 1)) | (dst[i8 + 1] & byte1(m8, 7));
		return;
	}

	for (uint i = 1; i < l8; i++) {
		dst[i8 + i] = ((src[i - 1] << (8 - j8)) & 0xff) | (src[i] >> j8);
	}
	if (m8 > j8) {
		dst[i8 + l8] = ((src[l8 - 1] << (8 - j8)) & 0xff) | ((src[l8] >> j8) & byte1(j8, m8 - 1)) | (dst[i8 + l8] & byte1(m8, 7));
		return;
	}
	dst[i8 + l8] = ((src[l8 - 1] << (8 - j8)) & byte1(0, m8 - 1)) | (dst[i8 + l8] & byte1(m8, 7));
	return;
	
}
int main() {
	for (int i = 0; i < 8; i++)
		for (int j = i; j < 8; j++) {
			printf("%d:%d:", i, j);
			for (int k = 0; k < 8; k++)
				printf("%d", byte1(i, j) >> (7 - k) & 1);
			puts("");
		}
	byte str1[50] = { 0 };
	byte str2[50] = { 0 };
	memset(str2, 0xff, 50);
	BitSet(str1, 17, str2, 131);
	for (int i = 0; i < 50; i++)
		printf("%x", str1[i]);
	return 0;
}