#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "bmp.h"
#include <assert.h>



int main(int argc,char **argv){
    // Считываем все данные с командной строки.
    if (argc < 8){
        printf("Check usage: not enough parameters for proper work\n");
        return EXIT_FAILURE;
    }
    char * action = *(argv + 1);
    (void)action;
    char * in_path = *(argv + 2);
    char * out_path = *(argv + 3);
    unsigned int new_x = (unsigned int) atoi (* (argv + 4));
    unsigned int new_y = (unsigned int) atoi (* (argv + 5));
    unsigned int new_width = (unsigned int) atoi (* (argv + 6));
    unsigned int new_height = (unsigned int) atoi (* (argv + 7));
    
    assert (strcmp(action, "crop-rotate") == 0);
    assert (new_width > 0);
    assert (new_height > 0);

    // Считываем изображение.
    ImageStructure SourceImageStructure;
    SourceImageStructure = load_bmp(in_path);
    crop(&SourceImageStructure, new_x, new_y, new_width, new_height);
    rotate(&SourceImageStructure);
    save_bmp(&SourceImageStructure, out_path);
}
