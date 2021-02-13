/* https://gist.github.com/JUNNETWORKS/1cde1e301caf379a13b78b3cf82a6e2f#file-write_utf-8-c */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

void print_bin_from_char(char *c, int bytes){
	char *bin = calloc(sizeof(char), 8 * bytes);
	int i, j;
	unsigned int num;
	int bin_digit = 0;
	unsigned char *unsigned_c = (unsigned char *)c;
	for (i = bytes - 1; i >= 0; i--)
	{
		num = (unsigned int)unsigned_c[i];
		for (j = 7; j >= 0; j--)
		{
			bin[8 * i + j] = '0' + num % 2;
			num = num / 2;
			bin_digit++;
		}
	}
	i--;
	j--;
	write(1, "0b", 2);
	for (i = 8 * bytes; i > bin_digit; i--) // 0埋め
		write(1, &"0", 1);
	for (i = 0; i < bin_digit; i++)
		write(1, bin + i, 1);
	write(1, "\n", 1);
	free(bin);
}

int get_byte(char *c){
	if (!(*c & (1 << 7))) // 1ビット目が0の時は1バイト(ASCIIと同じ)
		return (1);
	int bytes = 0;
	for (int i = 7; i >= 4; i--)
	{
		if (*c & (1 << i))
			bytes++;
		else
			return (bytes);
	}
	return (bytes);
}

int main(int argc, char **argv){
	/*
	https://ja.wikipedia.org/wiki/UTF-8
	
	1バイト目の先頭の連続するビット "1"（その後にビット "0" が1つ付く）の個数で、
	その文字のバイト数がわかるようになっている。
	バイト目以降はビットパターン "10" で始まり,文字境界を判定出来る.
	
	先頭ビットが "0" なら1バイト文字、"10" なら2バイト以上の文字の2番目以降のバイト、
	"110" なら2バイト文字の先頭バイト、"1110" なら3バイト文字の先頭バイト、
	"11110" なら4バイト文字の先頭バイトであると判定できる。
	ASCIIは 0x00 ~ 0x7F までなので,utf-8でもそのまま使える
	*/
	// print_bin_from_char()のテスト用
	char tmp;
	tmp = 0x0f;
	print_bin_from_char(&tmp, 1);
	
	char *c = "あ"; // 11100011:10000001:10000010
	printf("\n%s bytes: %d\n", c, get_byte(c));
	print_bin_from_char(c, get_byte(c));
	char c_aa[3] = {0b11100011, 0b10000001, 0b10000010};  // テスト用
	write(1, c_aa, 3);
	
	char *c1 = "a";
	printf("\n%s bytes: %d\n", c1, get_byte(c1));
	print_bin_from_char(c1, get_byte(c1));
	char c_a = 0b01100001;
	write(1, &c_a, 1);
	
	char *c2 = "À";
	printf("\n%s bytes: %d\n", c2, get_byte(c2));
	print_bin_from_char(c2, get_byte(c2));
	
	char *c3 = "🤔";
	printf("\n%s bytes: %d\n", c3, get_byte(c3));
	print_bin_from_char(c3, get_byte(c3));
	char thinking[4] = {0b11110000, 0b10011111, 0b10100100, 0b10010100};  // テスト用
	write(1, thinking, 4);
	write(1, "\n", 1);

	// コマンドライン引数で渡されたやつを出力
	for (int i = 1 ; i < argc ; i++){
		printf("\n%s bytes: %d\n", argv[i], get_byte(argv[i]));
		print_bin_from_char(argv[i], get_byte(argv[i]));
		write(1, argv[i], get_byte(argv[i]));
		write(1, "\n", 1);
	}
	return (0);
}