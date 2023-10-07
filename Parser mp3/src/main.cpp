#include "lib/frame.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <memory>

int main(int argc, char **argv) {

    char* file_name = argv[1];
    std::ifstream is(file_name, std::ios::binary);

    char* file_identifier = new char [InfoSize::kFILE_IDENTIFIER];
    is.read(file_identifier, InfoSize::kFILE_IDENTIFIER);
    std::cout << "File identifier: ";
    for (int i = 0; i < InfoSize::kFILE_IDENTIFIER; ++i) {
        std::cout << file_identifier[i];
    }
    delete[] file_identifier;
    std::cout << '\n';

    is.seekg(InfoSize::kFILE_IDENTIFIER, std::ifstream::cur);
    char* size_frames_hex = new char[InfoSize::kSIZE_FRAMES];
    is.read(size_frames_hex, InfoSize::kSIZE_FRAMES);

    int p = InfoSize::kSIZE_FRAMES - 1;
    uint32_t size_frames_bytes = 0;
    for (int i = 0; i < InfoSize::kSIZE_FRAMES; ++i) {
        size_frames_bytes += uint32_t(size_frames_hex[i]) * pow(InfoSize::kTWO_IN_THE_SEVENTH, p);
        --p;
    }
    std::cout << "Frame size in bytes: " << size_frames_bytes << '\n';
    delete[] size_frames_hex;

    std::vector<std::shared_ptr<Frame>> Frames;
    Frames = Parse(is, size_frames_bytes, Frames);

    for (int i = 2; i < argc; ++i) {
        for (auto & Frame : Frames) {
            if (argv[i] == Frame->frame_name_) {
                Frame->PrintInfo();
            }
        }
    }

    return 0;
}
