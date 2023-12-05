#include "lz77.h"

#include <vector>

int main(int argc, char **argv){
    Lz77 fileToCompress {argc, argv};
    if(fileToCompress.argument("-t") == "c"){
        fileToCompress.compress();
    }
    else if(fileToCompress.argument("-t") == "d"){
        fileToCompress.decompress();
    }

    return 0;
}