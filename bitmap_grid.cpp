#include <iostream>
#include <cstdio>

using namespace std;


#pragma pack(push, 1)
typedef struct {
    unsigned short type;                 /* Magic identifier            */
    unsigned int size;                       /* File size in bytes          */
    unsigned int reserved;
    unsigned int offset;                     /* Offset to image data, bytes */
} HEADER;

typedef struct {
    unsigned int size;               /* Header size in bytes      */
    int width,height;                /* Width and height of image */
    unsigned short planes;       /* Number of colour planes   */
    unsigned short bits;         /* Bits per pixel            */
    unsigned int compression;        /* Compression type          */
    unsigned int imagesize;          /* Image size in bytes       */
    int xresolution,yresolution;     /* Pixels per meter          */
    unsigned int ncolours;           /* Number of colours         */
    unsigned int importantcolours;   /* Important colours         */
} INFOHEADER;
#pragma pack(pop)

typedef struct {
    unsigned char r,g,b,junk;
} COLOURINDEX;

int main(){
    HEADER header;
    INFOHEADER info;

    FILE *pFile = fopen("lena.bmp", "rb");
    FILE *p2 = fopen("grid.bmp", "wb");
    if(pFile == NULL){
        printf("open fill error!\n");
        return -1;
    }
    printf("%ld, %ld\n", sizeof(HEADER), sizeof(INFOHEADER));

    fread((char *)&header , sizeof(HEADER), 1, pFile);
    printf("filesize:%d, offset:%d\n", header.size, header.offset);
    if(header.type != 0x4D42){
        printf("bitmap file format error\n");
        return -1;
    }

    fread((char *)&info , sizeof(INFOHEADER), 1, pFile);
    printf("width:%d, height:%d, bits:%d, imagesize:%d\n", info.width, info.height, info.bits, info.imagesize);

    fseek(pFile, header.offset, SEEK_SET);
    unsigned char * buffer = (unsigned char *)calloc(info.imagesize, sizeof(unsigned char));
    fread(buffer, info.imagesize, 1, pFile);

    int count = info.bits / 8; // BGR
    int line = count * info.width;

    for(int j = 0; j < info.height; j++){
        for(int i = 0; i < info.width; i++){
            if( j%64 == 0 | i%64 == 0){
                *(buffer + j * line + i * count) = 255;
                *(buffer + j * line + i * count + 1) = 255;
                *(buffer + j * line + i * count + 2) = 255;
            }
        }
    }
    printf("%d\n", info.imagesize * 2);

    fwrite(&header, 1, sizeof(HEADER), p2);
    fwrite(&info, 1, sizeof(INFOHEADER), p2);
    fwrite(buffer, 1, info.imagesize, p2);

    free(buffer);
    fclose(pFile);
    fclose(p2);
}
