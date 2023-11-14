#include "lz77.h"

#include <vector>

int main(int argc, char **argv){
    Lz77 fileToCompress {argc, argv};
    fileToCompress.compress();

    return 0;
}