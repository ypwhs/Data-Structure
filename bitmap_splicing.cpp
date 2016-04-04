#include <iostream>
#include <cstdio>

using namespace std;

#pragma pack(push, 1)
typedef struct {
    unsigned short type;             /* Magic identifier            */
    unsigned int size;               /* File size in bytes          */
    unsigned int reserved;
    unsigned int offset;             /* Offset to image data, bytes */
} HEADER;

typedef struct {
    unsigned int size;               /* Header size in bytes      */
    int width,height;                /* Width and height of image */
    unsigned short planes;           /* Number of colour planes   */
    unsigned short bits;             /* Bits per pixel            */
    unsigned int compression;        /* Compression type          */
    unsigned int imagesize;          /* Image size in bytes       */
    int xresolution,yresolution;     /* Pixels per meter          */
    unsigned int ncolours;           /* Number of colours         */
    unsigned int importantcolours;   /* Important colours         */
} INFOHEADER;
#pragma pack(pop)

int main(){
    HEADER header_img1;
    HEADER header_img2;
    INFOHEADER info_img1;
    INFOHEADER info_img2;

    // Read img1 header
    FILE *img1 = fopen("lena.bmp", "rb");
    fread((char *)&header_img1, sizeof(HEADER), 1, img1);
    printf("filesize:%d, offset:%d\n", header_img1.size, header_img1.offset);
    if(header_img1.type != 0x4D42){  //BM
        printf("bitmap file format error\n");
        return -1;
    }

    fread((char *)&info_img1 , sizeof(INFOHEADER), 1, img1);
    printf("width:%d, height:%d, bits:%d, imagesize:%d\n", info_img1.width, info_img1.height, info_img1.bits, info_img1.imagesize);

    // Read img1 data
    fseek(img1, header_img1.offset, SEEK_SET);
    unsigned char * buffer_img1 = (unsigned char *)malloc(info_img1.imagesize * sizeof(unsigned char));
    fread(buffer_img1, info_img1.imagesize, 1, img1);

    // Read img2 header
    FILE *img2 = fopen("puzzle.bmp", "rb");
    fread((char *)&header_img2, sizeof(HEADER), 1, img2);
    fread((char *)&info_img2 , sizeof(INFOHEADER), 1, img2);
    // Read img2 data
    fseek(img2, header_img2.offset, SEEK_SET);
    unsigned char * buffer_img2 = (unsigned char *)malloc(info_img2.imagesize * sizeof(unsigned char));
    fread(buffer_img2, info_img2.imagesize, 1, img2);

    unsigned char * buffer = (unsigned char *)calloc(info_img1.imagesize * 2, sizeof(unsigned char));
    
    int count = info_img1.bits / 8; // BGR
    int line = count * info_img1.width; // One Line Bytes

    for(int j = 0; j < info_img1.height; j++){
        memcpy(buffer + j * line * 2 ,          buffer_img1 + j * line, line - count);  // Left
        memcpy(buffer + j * line * 2 + line,    buffer_img2 + j * line, line);          // Right
    }

    FILE * fp = fopen("test.bmp", "wb");
    info_img1.width *= 2;
    info_img1.imagesize *= 2;
    fwrite(&header_img1, 1, sizeof(HEADER), fp);
    fwrite(&info_img1, 1, sizeof(INFOHEADER), fp);
    fwrite(buffer, 1, info_img1.imagesize, fp);

    free(buffer_img1);
    free(buffer_img2);
    free(buffer);
    fclose(img1);
    fclose(img2);
    fclose(fp);
}
