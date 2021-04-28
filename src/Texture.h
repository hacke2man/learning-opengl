#ifndef __TEXTURE_H__
#define __TEXTURE_H__
#ifdef __cplusplus
extern "C" {
#endif

  struct Texture {
    unsigned int id;
    char * filePath;
    unsigned char * localBuffer;
    int height, width, BPP;
  };

  struct Texture * CreateTexture(char * path);

  void BindTexture( struct Texture * texture, unsigned int slot);
  void UnBindTexture();

#ifdef __cplusplus
}
#endif
#endif
