#include <stdlib.h>
#include <tiffio.h>

#define IN_TIF      "input.tif"
#define OUT_TIF     "output.tif"

int32 PIXELS;
int32 COLS;
int32 ROWS;
int32 arr[600*600];
void read_tiff(){

   char filename[100];
   uint32 *raster;
   TIFF *tif;                          
   int i;
   uint32 r,g,b,a;
   uint32 tmp1,tmp2,tmp3,tmp4;

   strcpy(filename, IN_TIF);
   tif = TIFFOpen(filename,"r");
   if (tif == NULL)
      exit(-1);
   TIFFGetField(tif,TIFFTAG_IMAGEWIDTH,&COLS);
   TIFFGetField(tif,TIFFTAG_IMAGELENGTH,&ROWS);
   PIXELS = COLS * ROWS;
   raster = (uint32*) _TIFFmalloc(PIXELS *sizeof(uint32));   
   if (raster != NULL){
      if (TIFFReadRGBAImage(tif,COLS,ROWS,raster,0))
          for (i = 0; i < PIXELS; i++){
             r = (uint32) ((raster[i]) & 0xFF);
             g = (uint32) ((raster[i] >> 8) & 0xFF);
             b = (uint32) ((raster[i] >> 16) & 0xFF);
             a = (uint32) ((raster[i] >> 24) & 0xFF);

             tmp1 = ((a << 24) & 0xFF000000);
             tmp2 = ((b << 16) & 0x00FF0000);
             tmp3 = ((g << 8) & 0x0000FF00);   
             tmp4 = ((r << 0) & 0x000000FF);
             arr[i] = tmp1+tmp2+tmp3+tmp4;
          } 
   } 

   TIFFClose(tif);    
   _TIFFfree(raster); 

} 


void write_tiff(){
                  

   TIFF *tif;
   char filename[100];
   int i;
   uint32 data[PIXELS];
   uint32* data_ptr;
   int32 tmp1,tmp2;

   tmp1 = PIXELS/3;
   for (i=0; i < tmp1; i++)
      data[i] = arr[i];    
   tmp2 = (PIXELS/3)*2;
   for (i=tmp1; i < tmp2; i++)
      data[i] = 0xFFFFFFFF;
   for (i=tmp2; i < PIXELS; i++)
      data[i] = arr[i]; 
   strcpy(filename,OUT_TIF);
   tif = TIFFOpen(filename,"w");

   TIFFSetField(tif,TIFFTAG_IMAGEWIDTH,COLS);
   TIFFSetField(tif,TIFFTAG_IMAGELENGTH,ROWS);
   TIFFSetField(tif,TIFFTAG_BITSPERSAMPLE,8);
   TIFFSetField(tif,TIFFTAG_COMPRESSION,COMPRESSION_LZW);
   TIFFSetField(tif,TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_RGB);
   TIFFSetField(tif,TIFFTAG_SAMPLESPERPIXEL,4);  //4: rgba   
   TIFFSetField(tif,TIFFTAG_PLANARCONFIG, PLANARCONFIG_CONTIG);
   TIFFSetField(tif,TIFFTAG_ROWSPERSTRIP,1);

   data_ptr = data;
   for(i = ROWS-1; i >=0; i--){
      if (TIFFWriteScanline(tif,data_ptr,i,0) < 0) 
         printf("Error\n");
      data_ptr += COLS; 
   }
   TIFFClose(tif);
}


int main(void) {             
   
     read_tiff();                      
     write_tiff();
} 





