#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "includes.h"
#include "os.h"
#include "base64.h"

#define CODED_FILE_NAME "encoded.txt"
#define DECODED_FILE_NAME "decoded.txt"

// Declaration of methods
unsigned long long fSize(FILE *fp);
int code(const char *archivito);
int decode(const char *archivito);
int writeFile(const char* nameFile, unsigned char* buff, size_t size);
unsigned char * base64_encode(const unsigned char *src, size_t len, size_t *out_len);
unsigned char * base64_decode(const unsigned char *src, size_t len,size_t *out_len);

static const unsigned char base64_table[65] =
	"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

int main(int argc, char ** argv){
    if(argc != 3)
        return -1;

    if(strcmp(argv[1],"--encode") == 0)
        return code(argv[2]);

    if(strcmp(argv[1],"--decode") ==0 )
        return decode(argv[2]);

    printf("Error in arguments [ %s %s ]\n", argv[1],argv[2]);
    return -2;
}

int code(const char *archivito){
	
	unsigned char *texto;
	size_t sArch;

	FILE *arch = fopen(archivito, "r");
	if (arch == NULL){
    	printf("Error opening file! %s\n",archivito);
    	exit(1);
	}
	fseek(arch, 0L, SEEK_END); 
  
    // calculating the size of the file 
    sArch = (size_t)ftell(arch);
    fclose(arch);
	
	texto = base64_encode(archivito,sArch,NULL);

	if(texto == NULL)
		return -10;
	
	//Asignar al texto
	return 0;
}

int decode(const char *archivito){
	
	unsigned char *texto;
	size_t sArch;

	FILE *arch = fopen(archivito, "r");
	if (arch == NULL){
    	printf("Error opening file! %s\n",archivito);
    	exit(1);
	}
    fseek(arch, 0L, SEEK_END); 
  
    // calculating the size of the file 
    sArch = (size_t)ftell(arch);

    fclose(arch);

	texto = base64_decode(archivito,sArch,NULL);
	if(texto == NULL)
		return -10;
	
	//Asignar al texto
	return 0;
}

unsigned long long fSize(FILE *fp){
    struct stat size;
    fstat(fileno(fp), &size);
    return size.st_size;
}

/*
 * Base64 encoding/decoding (RFC1341)
 * Copyright (c) 2005-2011, Jouni Malinen <j@w1.fi>
 *
 * This software may be distributed under the terms of the BSD license.
 * See README for more details.
 * 
 * base64_encode - Base64 encode
 * @src: Data to be encoded
 * @len: Length of the data to be encoded
 * @out_len: Pointer to output length variable, or %NULL if not used
 * Returns: Allocated buffer of out_len bytes of encoded data,
 * or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer. Returned buffer is
 * nul terminated to make it easier to use as a C string. The nul terminator is
 * not included in out_len.
 */
unsigned char * base64_encode(const unsigned char *src, size_t len, size_t *out_len)
{
	unsigned char *out, *pos;
	const unsigned char *end, *in;
	size_t olen;
	int line_len;

	olen = len * 4 / 3 + 4; /* 3-byte blocks to 4-byte */
	olen += olen / 72; /* line feeds */
	olen++; /* nul termination */
	if (olen < len)
		return NULL; /* integer overflow */
	out = os_malloc(olen);
	if (out == NULL)
		return NULL;

	end = src + len;
	in = src;
	pos = out;
	line_len = 0;
	while (end - in >= 3) {
		*pos++ = base64_table[in[0] >> 2];
		*pos++ = base64_table[((in[0] & 0x03) << 4) | (in[1] >> 4)];
		*pos++ = base64_table[((in[1] & 0x0f) << 2) | (in[2] >> 6)];
		*pos++ = base64_table[in[2] & 0x3f];
		in += 3;
		line_len += 4;
		if (line_len >= 72) {
			*pos++ = '\n';
			line_len = 0;
		}
	}

	if (end - in) {
		*pos++ = base64_table[in[0] >> 2];
		if (end - in == 1) {
			*pos++ = base64_table[(in[0] & 0x03) << 4];
			*pos++ = '=';
		} else {
			*pos++ = base64_table[((in[0] & 0x03) << 4) |
					      (in[1] >> 4)];
			*pos++ = base64_table[(in[1] & 0x0f) << 2];
		}
		*pos++ = '=';
		line_len += 4;
	}

	if (line_len)
		*pos++ = '\n';

	*pos = '\0';
	if (out_len)
		*out_len = pos - out;
	return out;
}


/**
 * base64_decode - Base64 decode
 * @src: Data to be decoded
 * @len: Length of the data to be decoded
 * @out_len: Pointer to output length variable
 * Returns: Allocated buffer of out_len bytes of decoded data,
 * or %NULL on failure
 *
 * Caller is responsible for freeing the returned buffer.
 */
unsigned char * base64_decode(const unsigned char *src, size_t len,size_t *out_len)
{
	unsigned char dtable[256], *out, *pos, block[4], tmp;
	size_t i, count, olen;
	int pad = 0;

	os_memset(dtable, 0x80, 256);
	for (i = 0; i < sizeof(base64_table) - 1; i++)
		dtable[base64_table[i]] = (unsigned char) i;
	dtable['='] = 0;

	count = 0;
	for (i = 0; i < len; i++) {
		if (dtable[src[i]] != 0x80)
			count++;
	}

	if (count == 0 || count % 4)
		return NULL;

	olen = count / 4 * 3;
	pos = out = os_malloc(olen);
	if (out == NULL)
		return NULL;

	count = 0;
	for (i = 0; i < len; i++) {
		tmp = dtable[src[i]];
		if (tmp == 0x80)
			continue;

		if (src[i] == '=')
			pad++;
		block[count] = tmp;
		count++;
		if (count == 4) {
			*pos++ = (block[0] << 2) | (block[1] >> 4);
			*pos++ = (block[1] << 4) | (block[2] >> 2);
			*pos++ = (block[2] << 6) | block[3];
			count = 0;
			if (pad) {
				if (pad == 1)
					pos--;
				else if (pad == 2)
					pos -= 2;
				else {
					/* Invalid padding */
					os_free(out);
					return NULL;
				}
				break;
			}
		}
	}

	*out_len = pos - out;
	return out;
}