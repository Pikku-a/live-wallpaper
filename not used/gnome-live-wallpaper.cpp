#include <iostream>
#include <string>
#include <vector>
#include <Magick++.h>

int main() {
    // Initialize ImageMagick library
    Magick::InitializeMagick(nullptr);

    // Prompt user for input file
    std::string inputFile;
    std::cout << "Enter the path to a GIF or WebP file: ";
    std::cin >> inputFile; //maybe
    std::getline(std::cin, inputFile);

    try {
        // Read input file
        Magick::Image inputImage(inputFile);

        // Extract frames from input image
        std::vector<Magick::Image> frames;
        //Magick::coalesceImages(&frames, inputFile);

        // Save each frame as a separate image file
        for (size_t i = 0; i < frames.size(); ++i) {
            std::string outputFilename = "frame_" + std::to_string(i) + ".png";
            frames[i].write(outputFilename);
        }

        std::cout << "Frames extracted successfully!" << std::endl;
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

//g++ -I/usr/include/x86_64-linux-gnu/ImageMagick-6 -I/usr/include/ImageMagick-6 -o gnome-live-wallpaper gnome-live-wallpaper.cpp -lMagick++
/*

#include "CImg.h"
#include <vector>
#include <string>
#include <iostream>

using namespace cimg_library;
using namespace std;

int main() {

    // Prompt user for input file
    string inputFile;
    cout << "Enter the path to a GIF or WebP file: ";
    //cin >> inputFile; //maybe
    getline(cin, inputFile);

   // Load the GIF or WebP image
   CImg<unsigned char> image("input.gif");

   // Get the number of frames in the image
   const unsigned int numFrames = image._spectrum;

   // Create a vector to store the individual frames
   vector<CImg<unsigned char>> frames;

   // Split the image into individual frames
   for (unsigned int i = 0; i < numFrames; i++) {
      // Get the i-th frame
      CImg<unsigned char> frame = image.get_frame(i);

      // Add the frame to the vector
      frames.push_back(frame);
   }

   // Save each frame as a separate image
   for (unsigned int i = 0; i < numFrames; i++) {
      // Generate a filename for the frame
      string filename = "frame_" + to_string(i) + ".jpg";

      // Save the frame as an image file
      frames[i].save(filename.c_str());
   }

   return 0;
}
