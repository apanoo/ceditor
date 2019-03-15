#pragma once
#include <iostream>
#include <string.h> // memset

class FileUtils {
public:
    static std::string read( const char* filename ) {
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
};
