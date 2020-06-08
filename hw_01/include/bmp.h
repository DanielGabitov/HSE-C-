#pragma once
#include <stdint.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct BmpFileHeader {
  uint16_t type;
  uint32_t size;
  int32_t __reserved;
  uint32_t image_offset;
}BmpFileHeader;

typedef struct DIBHeader{
  uint32_t size;
  uint32_t width;
  uint32_t height;
  uint16_t planes;
  uint16_t bits_per_pixel;
  uint32_t compression;
  uint32_t image_size;
  uint32_t x_pixels_per_meter;
  uint32_t y_pixels_per_meter;
  uint32_t colors;
  uint32_t important_colors;
}DIBHeader;

typedef struct ImageData{
  void * data_pointer;
}ImageData;

typedef struct ImageStructure{
  BmpFileHeader BmpFileHeader;
  DIBHeader DIBHeader;
  ImageData ImageData;
}ImageStructure;
#pragma pack(pop)


ImageStructure load_bmp(char *);
void FillPadding(void * dest, size_t padding );
void save_bmp(ImageStructure *,char *);
void rotate(ImageStructure *);
void crop(ImageStructure *, unsigned int x,unsigned int y, unsigned int, unsigned int);

