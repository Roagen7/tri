#include "files.h"

#include <sstream>
#include <fstream>

using namespace std;

// source: https://github.com/mortennobel/SimpleRenderEngine/blob/fb00a04cb38e2227adf4bdb17e1b38ec160632c2/utils/files_to_cpp.cpp#L30-L49
string tri::util::readShader(const string& filename) {
    stringstream ss;
    fstream fstream;
    auto type = ios_base::in;

    fstream.open(filename, type);

    string line;
    bool start = true;
    while( getline( fstream, line ) ) {
        if (!start){
            ss<<endl;
        }
        ss << line;
        start = false;
    }

    fstream.close();
    return ss.str();
}
