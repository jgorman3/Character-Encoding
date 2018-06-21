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
/*int isUTF8Legal (uint8_t fileData[])
{
  return fileData <= 0x7F
        && (fileData >= 0xC080 && fileData <= 0xDFBF)
        && (fileData >= 0xE08080 && fileData <= 0xEFBFBF)
        && (fileData >= 0xF0808080 && fileData <= 0xF7BFBFBF);
}*/

int UTF8toCodeP (uint8_t fileData)
{
  codepoint = fileData;
  printf("%08X\n",codepoint);
  return 0;
}

int twoFrames(uint8_t byte1,uint8_t byte2)
{
  int codepoint1 = ((byte2 & 0x1F) << 6) | (byte1);
  if (codepoint1 >= 128)
  {
    printf("%08X\n",codepoint1);
  }
  return 0;
}

int threeFrames(uint8_t byte1,uint8_t byte2,uint8_t byte3)
{
  int codepoint2 = (((byte3 & 0x0F) << 12) | (((byte2) & 0x3F) << 6) |
  (byte1));
  if (codepoint2 >= 2048 && (codepoint2 < 55296 || codepoint2 > 57343))
  {
    printf("%08X\n",codepoint2);
  }
  return 0;
}

int fourFrames(uint8_t byte1,uint8_t byte2,uint8_t byte3, uint8_t byte4)
{
  int codepoint3 = (((byte4 & 0x07) << 18) | ((byte3 & 0x3F) << 12) |
  ((byte2 & 0x3F) <<  6) | (byte1));
  if (codepoint3 >= 65536 && codepoint3 <= 1114111)
  {
    printf("%08X\n",codepoint3);
  }
  return 0;
}

int UTF16BE (uint8_t fileData)
{
  //uint32_t be16DataArray[utf8octets];
  /*if (!isUTF8Legal(fileData)) {
    putchar(0xFF);
    putchar(0xFD);
  }*/
  return 0;
}

int UTF16LE (uint8_t fileData)
{
  //uint32_t le16DataArray[utf8octets];
  /*if (!isUTF8Legal(fileData)) {
    putchar(0xFD);
    putchar(0xFF);
  }*/
  return 0;
}

int UTF32BE (uint8_t fileData)
{
  //uint32_t be32DataArray[utf8octets];
  /*if (!isUTF8Legal(fileData)) {
    putchar(0x00);
    putchar(0x00);
    putchar(0xFF);
    putchar(0xFD);
  }*/
  return 0;
}

int UTF32LE (uint8_t fileData)
{
  //uint32_t le32DataArray[utf8octets];
  /*if (!isUTF8Legal(fileData)) {
    putchar(0x00);
    putchar(0x00);
    putchar(0xFD);
    putchar(0xFF);
  }*/
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
      if (buffer[i] < 0x7F)
      {
        UTF8toCodeP(buffer[i]);
      }
      else if ((buffer[i] >= 0xC0) && (buffer[i] <= 0xDF))
      {
        twoFrames(buffer[i],buffer[i+1]);
      }
      else if ((buffer[i] >= 0xE0) && (buffer[i] <= 0xEF))
      {
        threeFrames(buffer[i],buffer[i+1],buffer[i+2]);
      }
      else
      {
        fourFrames(buffer[i],buffer[i+1],buffer[i+2],buffer[i+3]);
      }
    }
  }
  return 0;
}
