#include "lz77.h"
#include "tMathUtilities.h"
#include "tStringUtilities.h"

#include <vector>
#include <string>

#include <vector>

int main(int argc, char** argv) {
    // Lz77CliArguments fileToCompress { argc, argv };

    Lz77 lz77Compress { "project_test1.raw.txt", "project_test1.txt.compressed", "c", 4096000, 4096000 };
    lz77Compress.run();
    Lz77 lz77Decompress { "project_test1.txt.compressed", "project_test1.decompressed.txt", "d", 4096000, 4096000 };
    lz77Decompress.run();

    return 0;
    }