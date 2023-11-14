#include "lz77.h"
// #include "utilities.h"
// #include "cli.h"

#include <vector>

int main(int argc, char **argv){
    Lz77 compress {argc, argv};
    compress.compress();

    return 0;
}