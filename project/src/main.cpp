#include "lz77.h"
#include "tMathUtilities.h"
#include "tStringUtilities.h"

#include <vector>

int main(int argc, char **argv){
    // Lz77 fileToCompress {argc, argv};
    // if(fileToCompress.argument("-t") == "c"){
    //     fileToCompress.compress();
    // }
    // else if(fileToCompress.argument("-t") == "d"){
    //     fileToCompress.decompress();
    // }

    long x = 63643;
    long y = 12355;
    Lz77Prepend test1 {x, y};
    for(int i=0; i<test1.size(); i++){
        std::cout << TStringUtilities::byteToBitString(test1.at(i)) << std::endl;
    }

    return 0;
}