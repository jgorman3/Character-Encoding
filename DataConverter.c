///input data is text file containing UTF-8 encoding, data is converted
//into multiple differing encodings UTF-16BE LE, UTF32BE LE, Windows 1252,
//ISO Western Languages, and Mac OS Roman
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_LENGTH 1024
//in code, endianness is considered
#define replaceChar16 0xFFFD
#define replaceChar32 0x0000FFFD
int utf8octets = 0;
uint8_t codepoint = 0x00;
int j = 0;

//checks legality of UTF data being passed from txt file
int isUTF8Legal (uint8_t fileData)
{
  /*return fileData <= 0x0000007F
        && (fileData >= 0x0000C080 && fileData <= 0x0000DFBF)
        && (fileData >= 0x00E08080 && fileData <= 0x00EFBFBF)
        && (fileData >= 0xF0808080 && fileData <= 0xF7BFBFBF);*/
  return 0;
}

uint8_t UTF8toCodeP (uint8_t fileData[])
{
  if (fileData[j] <= 0x7F) {
    codepoint = fileData[j];
    return codepoint;
    printf("%c",'\n');

  //two bytes
} else if ((fileData[j] >= 0xC0) && (fileData[j] <= 0xDF)) {
    codepoint = ((fileData[j] & 0x1F) << 6) | ((fileData[j + 1]) & 0x3F);
    return codepoint;

  //three bytes
} else if ((fileData[j] >= 0xE0) && (fileData[j] <= 0xEF)) {
    codepoint = (((fileData[j] & 0x0F) << 12) | (((fileData[j + 1]) & 0x3F) << 6) |
    ((fileData[j + 2]) & 0x3F));
    return codepoint;
  //four bytes
} else //((fileData >= 0xF0) && (fileData <= 0xF7)) {
  {
    codepoint = (((fileData[j] & 0x07) << 18) | ((fileData[j+1] & 0x3F) << 12) |
    ((fileData[j+2] & 0x3F) <<  6) | ((fileData[j+3] & 0x3F)));
    return codepoint;
  }
}

int UTF16BE (uint8_t fileData)
{
  //uint32_t be16DataArray[utf8octets];
  if (!isUTF8Legal(fileData)) {
    putchar(0xFF);
    putchar(0xFD);
  }
  return 0;
}

int UTF16LE (uint8_t fileData)
{
  //uint32_t le16DataArray[utf8octets];
  if (!isUTF8Legal(fileData)) {
    putchar(0xFD);
    putchar(0xFF);
  }
  return 0;
}

int UTF32BE (uint8_t fileData)
{
  //uint32_t be32DataArray[utf8octets];
  if (!isUTF8Legal(fileData)) {
    putchar(0x00);
    putchar(0x00);
    putchar(0xFF);
    putchar(0xFD);
  }
  return 0;
}

int UTF32LE (uint8_t fileData)
{
  //uint32_t le32DataArray[utf8octets];
  if (!isUTF8Legal(fileData)) {
    putchar(0x00);
    putchar(0x00);
    putchar(0xFD);
    putchar(0xFF);
  }
  return 0;
}

int main ( void )
{
  uint8_t buffer[BUFFER_LENGTH];

  while (true)
  {
    int utf8octets = fread(buffer, 1, BUFFER_LENGTH, stdin);
    //printf("%d\n",utf8octets);  //determines length of file in bytes
    if (utf8octets == 0) {
      break;
    }
    for (int i = 0; i < utf8octets; i++) {
      printf("%X\n",UTF8toCodeP(&buffer[i]));
    }
  }
  return 0;
}
