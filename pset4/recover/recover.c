#include <stdio.h>
#include <stdlib.h>
#include<stdint.h>
typedef uint8_t BYTE;


int main(int argc, char *argv[]){
    FILE *img_card = fopen(argv[1] , "r") ;
    if(!img_card) {
        perror( "Error Occured opening the file\n");
        return 1 ;
    }
    _Bool first_found = 0;
    int file_counter = 0;
    char *filename = NULL;
    FILE *img_found = NULL;
    for (BYTE *buffer = (BYTE *)malloc(sizeof(BYTE) * 512); (fread(buffer,sizeof(BYTE) ,512 , img_card ) == 512) ;) {
        if(buffer[0] == 0xff && buffer[1] ==0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0 ){
            if (!first_found) {
               first_found = 1;
               filename = (char*)malloc(sizeof(char) * 8);
               sprintf(filename , "%03i.jpg",file_counter);
               img_found = fopen(filename , "w");
               fwrite (buffer,sizeof(BYTE) ,512 , img_found);
            }else {
               fclose(img_found);
               img_found = NULL;
               free(filename);
               filename = NULL;
               file_counter += 1;
               filename = (char*)malloc(sizeof(char) * 8);
               sprintf(filename , "%03i.jpg",file_counter);
               img_found = fopen(filename , "w");
               fwrite (buffer,sizeof(BYTE) ,512 , img_found);
            }
       }else{
           if(!first_found) {
               free(buffer);
               continue;
           }
           fwrite (buffer,sizeof(BYTE) ,512 , img_found);
       }
    }
    fclose(img_card);
    img_card = NULL;
    return 0;
}
