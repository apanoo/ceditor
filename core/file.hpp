#pragma once
#include <iostream>
#include <string.h> // memset

class FileUtils {
public:
    static std::string read( const char* filename ) {
#ifdef __ANDROID__
    // android resources path: example.png
    return read_an(const_del_pre(filename, 7));
#else
    // other resources path: assets/example.png
    return read_noan(filename);
#endif
    }
private:
    static std::string read_noan(const char* filename) {
        FILE* file = fopen( filename, "rt" );
        if (file == NULL) {
            std::cout << "cannot open file: " << filename << std::endl;
            exit(-1);
        }
        
        fseek( file, 0, SEEK_END );
        unsigned long length = ftell( file );           // file length
        char*         data   = new char[ length + 1 ];  // data + '\0'
        memset( data, 0, length + 1 );                  // clear memory
        fseek( file, 0, SEEK_SET );                     // back to begain of file
        fread( data, 1, length, file );
        fclose( file );
        std::string result( data );
        delete[] data;
        return result;
    }

    static std::string read_an(const char* filename) {
        SDL_RWops *rw = SDL_RWFromFile(filename, "rt");
        if (rw == NULL) return NULL;

        Sint64 res_size = SDL_RWsize(rw);
        char* res = (char*)malloc(res_size + 1);

        Sint64 nb_read_total = 0, nb_read = 1;
        char* buf = res;
        while (nb_read_total < res_size && nb_read != 0) {
                nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
                nb_read_total += nb_read;
                buf += nb_read;
        }
        SDL_RWclose(rw);
        if (nb_read_total != res_size) {
                free(res);
                return NULL;
        }

        res[nb_read_total] = '\0';
        std::string result(res);

        return result;
    }

    /**
     * return target[n-1, ..., sizeof(target)-1]
     **/
    static const char* const_del_pre(const char* target, int n) {
        std::string to(target);
        return to.substr(n).c_str();
    }
};
