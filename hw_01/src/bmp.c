#include "bmp.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>



void FillPadding (void * dest, size_t padding){
    for (size_t i = 0; i < padding; i++){
        *(unsigned int *) (dest + i) = 0; 
    }
}

const unsigned int PROPER_BITES_PER_PIXEL = 24;
const int pixel_size = 3;

ImageStructure load_bmp(char * in_path){
    //Открываем файл, считваем данные, проверяем по assert`у.
    FILE * source_file = fopen(in_path, "rb");
    assert(source_file);
    ImageStructure LoadedImageStructure;
    assert(fread (&LoadedImageStructure.BmpFileHeader, 
        sizeof(LoadedImageStructure.BmpFileHeader), 1, source_file) == 1);
    

    assert(fread (&LoadedImageStructure.DIBHeader, 
        sizeof(LoadedImageStructure.DIBHeader), 1, source_file) == 1);
    // Выписываем данные из header`ов. Считываем изображение без паддинга.
    unsigned int width = LoadedImageStructure.DIBHeader.width;
    unsigned int height = LoadedImageStructure.DIBHeader.height;
    unsigned int padding = (width * 3 % 4) ? (4 - (width * 3 % 4) ) : 0;

    void * data = malloc(width * height * pixel_size);
    assert(data);

    for (unsigned int i = 0; i < height; i++){
        assert (fread(data + i * width * pixel_size, pixel_size, width, source_file) == width);
        if (padding)
            fseek(source_file, padding, SEEK_CUR);
    }

    LoadedImageStructure.ImageData.data_pointer = data;
    LoadedImageStructure.DIBHeader.image_size = width * height * pixel_size;

    // Проверяем данные картинки с введеными юзером данными.
    assert((unsigned int)LoadedImageStructure.DIBHeader.bits_per_pixel == PROPER_BITES_PER_PIXEL);
    fclose(source_file);

    return LoadedImageStructure;  

}

void save_bmp(ImageStructure * Image,char * path_out){
    FILE * dest_file = fopen(path_out, "wb");
    
    unsigned int image_size = Image->DIBHeader.image_size;
    unsigned int height = Image->DIBHeader.height;
    unsigned int width = Image->DIBHeader.width;
    unsigned int padding = (width * 3 % 4) ? (4 - (width * 3 % 4) ) : 0;
    void * old_data = Image->ImageData.data_pointer;


    if (!padding){
        assert (fwrite(&Image->BmpFileHeader, sizeof(Image->BmpFileHeader), 1, dest_file) == 1);
        assert (fwrite(&Image->DIBHeader, sizeof(Image->DIBHeader), 1, dest_file) == 1);
        assert (fwrite(old_data, image_size, 1, dest_file) == 1);
        free(old_data);
        fclose(dest_file);
        return;  
    }
    // Изменяем размер.
    int new_image_size = height *(width * pixel_size +  padding);
    void * new_data = malloc (new_image_size);
    Image->DIBHeader.image_size = new_image_size;

    // Считываем данные.
    size_t new_data_off = 0;
    for (unsigned int i = 0; i < image_size; i += pixel_size){
        //Заполняем паддинг
        if (i % (width * pixel_size) == 0 && i > 0){
            FillPadding(new_data + new_data_off, padding);
            new_data_off += padding;
        }
        memcpy(new_data + new_data_off, old_data + i, pixel_size);
        new_data_off += pixel_size;
    }

    // Освобождаем память, закрываем файл, записываем готовое изображение. 
    free(old_data);
    Image->ImageData.data_pointer = new_data;
    assert (fwrite(&Image->BmpFileHeader, sizeof(Image->BmpFileHeader), 1, dest_file) == 1);
    assert (fwrite(&Image->DIBHeader, sizeof(Image->DIBHeader), 1, dest_file) == 1);
    assert (fwrite(new_data, new_image_size, 1, dest_file) == 1);

    free(new_data);
    fclose(dest_file);
}

void rotate(ImageStructure * Source_image){
    // Считываем данные.
    unsigned int width = Source_image->DIBHeader.width;
    unsigned int height = Source_image->DIBHeader.height;
    unsigned int image_size = Source_image->DIBHeader.image_size;
    void * data = Source_image->ImageData.data_pointer;
    // Выделяем память для повернутого изображения.

    void * new_data = malloc(image_size);

    // Переворот. Достаточно элегантно?.
    size_t new_data_off = 0;
    for (unsigned int i = 0; i < width * pixel_size ; i += pixel_size){

        for (unsigned int j = 0; j < height; j++){

            memcpy((new_data + new_data_off), (data + (width * pixel_size) * (j)
                + width * pixel_size - pixel_size - i) , pixel_size);
            new_data_off += pixel_size;

        }
    }

    // Меняем значения в структуре.
    Source_image->DIBHeader.height = width;
    Source_image->DIBHeader.width = height;
    Source_image->ImageData.data_pointer= new_data;
    // Освобождаем память
    free(data);
}

void crop(ImageStructure * Source_image, unsigned int start_x, unsigned int start_y,
        unsigned int given_width, unsigned int given_height){

    unsigned int width = Source_image->DIBHeader.width;
    unsigned int height = Source_image->DIBHeader.height;
    void * data = Source_image->ImageData.data_pointer;

    assert(start_x + given_width <= width);
    assert(start_y + given_height <= height);

    unsigned int end_x = (start_x + given_width) * pixel_size;
    unsigned int end_y = height - (start_y + given_height) ;
    start_x = start_x * pixel_size;
    start_y = height - start_y;
    


    void * new_data = malloc(given_height * given_width * pixel_size);
    size_t pixel_off = 0;

    for (unsigned int i = end_y; i < start_y; i ++){

        for (unsigned int j = start_x; j < end_x; j += pixel_size){

            memcpy(new_data + pixel_off, data + width * pixel_size * (i) + j, pixel_size);
            pixel_off += pixel_size;

        }

    }

    Source_image->DIBHeader.width = given_width;
    Source_image->DIBHeader.height = given_height; 
    Source_image->DIBHeader.image_size =  given_height * given_width * pixel_size;   
    Source_image->ImageData.data_pointer = new_data;
    free(data);

}
