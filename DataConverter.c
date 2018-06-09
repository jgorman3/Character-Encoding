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
  //if (fileData <= 0x7F) {
    codepoint = fileData;
    printf("%08X\n",codepoint);
    return 0;
}

int twoFrames(uint8_t byte1,uint8_t byte2)
{
  char char1[4];
  sprintf(char1,"%d%d",byte1,byte2);
  int intframe1 = (int)strtol(char1,NULL,16);
  uint8_t codepoint1 = ((intframe1 & 0x1F) << 6) | ((intframe1) & 0x3F);
  printf("%08X\n",codepoint1);
  return 0;
}

int threeFrames(uint8_t byte1,uint8_t byte2,uint8_t byte3)
{
  char char2[6];
  sprintf(char2,"%d%d%d",byte1,byte2,byte3);
  int intframe2 = (int)strtol(char2,NULL,16);
  uint8_t codepoint2 = (((intframe2 & 0x0F) << 12) | (((intframe2) & 0x3F) << 6) |
  ((intframe2) & 0x3F));
  printf("%08X\n",codepoint2);
  return 0;
}

int fourFrames(uint8_t byte1,uint8_t byte2,uint8_t byte3, uint8_t byte4)
{
  char char3[8];
  sprintf(char3,"%d%d%d%d",byte1,byte2,byte3,byte4);
  int intframe3 = (int)strtol(char3,NULL,16);
  uint8_t codepoint3 = (((intframe3 & 0x07) << 18) | ((intframe3 & 0x3F) << 12) |
  ((intframe3 & 0x3F) <<  6) | ((intframe3 & 0x3F)));
  printf("%08X\n",codepoint3);
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
      //printf("%X\n",buffer[i]);
    }
  }
  return 0;
}
