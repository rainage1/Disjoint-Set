#ifndef BINARYIMAGEPROCESSOR_H
#define BINARYIMAGEPROCESSOR_H

#include <vector>
#include <string>
#include <map>
#include "uandf.h"

class BinaryImageProcessor {
private:
    std::vector<std::vector<char>> image;
    std::vector<std::vector<char>> labeledImage;
    std::string filename;
    std::map<char, int> componentSizes;
    uandf ds; // Declaration without initialization

public:
    BinaryImageProcessor(const std::string& filename); // Constructor

    void processImage();
    void printOriginalImage() const;
    void printLabeledImage() const;
    void printComponentSizes() const;
    void printFilteredComponents(int minSize) const;

private:
    std::vector<std::vector<char>> readImage();
    void findConnectedComponents();
    void labelComponents();
    char getNewLabel();
};

#endif // BINARYIMAGEPROCESSOR_H
