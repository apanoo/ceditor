#pragma once
#include <iostream>
#include <string.h> // memset

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

class FileUtils {
public:
    // release raw data memory
    static void free_raw(unsigned char* data) {
        delete[] data;
    }
    // read raw data to memory
    static unsigned char* read_raw( const char* filename, unsigned int* size=nullptr) {
#ifdef __ANDROID__
    // android resources path: example.png
    return read_an(const_del_pre(filename, 7), size);
#else
    // other resources path: assets/example.png
    return read_noan(filename, size);
#endif
    }
    // must release image after read image
    static void free_image(unsigned char* data) {
        delete []data;
    }
    // read image for cross platform
    static unsigned char* read_image(const char* filename, int* width, int* height, int* channels) {
        unsigned int size;
        unsigned char* data = read_raw(filename, &size);

        return decode_common(data, size, width, height, channels);
    }
private:
    // common read file
    static unsigned char* read_noan(const char* filename, unsigned int* size=nullptr) {
        FILE* file = fopen( filename, "rb" );
        if (file == NULL) {
            std::cout << "Cannot open file: " << filename << std::endl;
            exit(-1);
        }
        
        fseek( file, 0, SEEK_END );
        unsigned int length = ftell( file );           // file length
        if (size != nullptr) *size = length;           // return size
        unsigned char* data   = new unsigned char[ length + 1 ];  // data + '\0'
        memset( data, 0, length + 1 );                  // clear memory
        fseek( file, 0, SEEK_SET );                     // back to begain of file
        fread( data, 1, length, file );
        fclose( file );
        return data;
    }

    // android read file 
    static unsigned char* read_an(const char* filename, unsigned int* size=nullptr) {
        SDL_RWops *rw = SDL_RWFromFile(filename, "rb");
        if (rw == NULL) return NULL;

        Sint64 res_size = SDL_RWsize(rw);
        if (size != nullptr) *size = res_size;   // return size
        unsigned char* res = new unsigned char[res_size + 1];

        Sint64 nb_read_total = 0, nb_read = 1;
        unsigned char* buf = res;
        while (nb_read_total < res_size && nb_read != 0) {
                nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
                nb_read_total += nb_read;
                buf += nb_read;
        }
        SDL_RWclose(rw);
        if (nb_read_total != res_size) {
                delete[] res;
                return NULL;
        }

        res[nb_read_total] = '\0';

        return res;
    }

    /**
     * return target[n-1, ..., sizeof(target)-1]
     **/
    static const char* const_del_pre(const char* target, int n) {
        std::string to(target);
        return to.substr(n).c_str();
    }

    // decode commom image file
    static unsigned char* decode_common(unsigned char* data, unsigned int size, int* width, int* height, int* channels) {
        // set image flip on axis y
        stbi_set_flip_vertically_on_load(true);
        // load image from memory
        return stbi_load_from_memory(data, size, width, height, channels, 0);
    }
};
