#include <lz77.h>
#include <utilities.h>

#include <vector>

int main(int argc, char **argv){
    std::vector<char> chars {'0', '1', '1', '0', '1', '1', '0'};
    std::vector<bool> bools = convertCharBinaryVectorToBoolVector(chars);

    return 0;
}