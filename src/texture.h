#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <FreeImage.h>

typedef struct {
    int width, height, bpp;
    void* data;
} mugg_texture;

FREE_IMAGE_FORMAT mugg_texture_get_format_from_path(const char* path) {
    FREE_IMAGE_FORMAT format = FreeImage_GetFileType(path, 0);
    
    if(format == FIF_UNKNOWN) {
        format = FreeImage_GetFIFFromFilename(path);
    }

    return format;
}

mugg_texture* mugg_create_texture_from_file(const char* path) {
    mugg_texture* tex;

    FIBITMAP* bitmap;
    FREE_IMAGE_FORMAT format = mugg_texture_get_format_from_path(path);
    
    if(FreeImage_FIFSupportsReading(format)) {
        bitmap = FreeImage_Load(format, path, 0);
    } else {
        return NULL;
    }
    
    if(!bitmap) {
        return NULL;
    }
   
    tex = (mugg_texture*)malloc(sizeof(mugg_texture));
    memset(tex, 0, sizeof(mugg_texture));

    tex->width = FreeImage_GetWidth(bitmap);
    tex->height = FreeImage_GetHeight(bitmap);
    tex->bpp = FreeImage_GetBPP(bitmap);
    
    int size = tex->width*tex->height*(tex->bpp/8);

    if(size == 0) {
        FreeImage_Unload(bitmap);
        free(tex);
        return NULL;
    }

    tex->data = (unsigned char*)malloc(size);

    FreeImage_ConvertToRawBits((BYTE*)tex->data, bitmap, tex->width*(tex->bpp/8), tex->bpp, FI_RGBA_RED_MASK, FI_RGBA_GREEN_MASK, FI_RGBA_BLUE_MASK, FALSE);

    FreeImage_Unload(bitmap);

    return tex;
}

void mugg_destroy_texture(mugg_texture* tex) {
    if(!tex) {
        return;
    }

    if(tex->data) {
        free(tex->data);
    }

    free(tex);
}
