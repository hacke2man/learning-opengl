#include "Texture.h"
#include <GL/glew.h>
#include "deps/stb_image.h"
#include <stdio.h>

struct Texture * CreateTexture(char * path)
{
    struct Texture * texture = malloc(sizeof(struct Texture));
    stbi_set_flip_vertically_on_load(1);
    texture->localBuffer = stbi_load(path, &texture->width, &texture->height, &texture->BPP, 4);

    glGenTextures(1, &texture->id);
    glBindTexture(GL_TEXTURE_2D, texture->id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, texture->localBuffer);
    glBindTexture(GL_TEXTURE_2D, 0);

    /* printf("%s\n", stbi_failure_reason()); */

    if(texture->localBuffer)
        stbi_image_free(texture->localBuffer);

    return texture;
}

void BindTexture(struct Texture * texture, unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, texture->id);
}
