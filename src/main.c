#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "texture.h"

int main() {
    mugg_texture* tex = mugg_create_texture_from_file("./test.png");

    if(tex == NULL) {
        printf("failed to load texture!\n");
        return EXIT_FAILURE;
    }
    
    printf("loaded texture, res:%dx%d, bpp:%d, size:%d\n", tex->width, tex->height, tex->bpp, tex->width*tex->height*(tex->bpp/8));

    mugg_destroy_texture(tex);

    return EXIT_SUCCESS;
}
