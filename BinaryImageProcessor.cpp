#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include "uandf.h"

class BinaryImageProcessor {
private:
    std::vector<std::vector<char>> image; //2D vector for the original image
    std::vector<std::vector<char>> labeledImage; //2D vector for the labeled image
    std::string filename;
    std::map<char, int> componentSizes; //Map for the sizes of each component
	uandf ds = uandf(72* 75); //Disjoint set (# of pixels in the image)


public:
	BinaryImageProcessor(const std::string& filename){
		//Initialize the image from the file
		this->filename = filename;
		image = readImage();
	}

    std::vector<std::vector<char>> readImage() {
        std::vector<std::vector<char>> img;
        std::ifstream infile(filename);
        std::string line;

        //Loops through each line in the file and adds each pixel to the 2D vector image
        while (getline(infile, line)) {
            std::vector<char> row;
            for (char pixel : line) {
                row.push_back(pixel);
            }
            img.push_back(row);
        }
        return img;
    }

    void printOriginalImage() const {
    	//Iterates through each element in the 2D vector image
        for (const auto& row : image) {
            for (char pixel : row) {
                std::cout << pixel;
            }
            std::cout << std::endl;
        }
    }

    void processImage() {
    	//Calls on the functions to find and label the components
        findConnectedComponents();
        labelComponents();
    }

    void findConnectedComponents() {
		int rows = 72;
		int cols = 75;

		//Finds all the connected components, uses 2 nested for loops to check for 8-way associativity
		for (int i = 0; i < rows; ++i) {
			for (int j = 0; j < cols; ++j) {
				if (image[i][j] == '+') {
					int current = i * cols + j;
					for (int di = -1; di <= 1; ++di) {
						for (int dj = -1; dj <= 1; ++dj) {
							int ni = i + di, nj = j + dj;
							if (ni >= 0 && ni < rows && nj >= 0 && nj < cols && !(di == 0 && dj == 0) && image[ni][nj] == '+') {
								ds.union_sets(current, ni * cols + nj);
							}
						}
					}
				}
			}
		}
	}

    void labelComponents() {
        std::map<int, char> labels;
        char currentLabel = 'a'; //First label for the first component
        labeledImage = std::vector<std::vector<char>>(image.size(), std::vector<char>(image[0].size(), ' '));

        // Labels the connected components
        for (int i = 0; i < image.size(); ++i) {
            for (int j = 0; j < image[i].size(); ++j) {
                if (image[i][j] == '+') {
                    int root = ds.find_set(i * image[0].size() + j);
                    if (labels.find(root) == labels.end()) {
                        labels[root] = currentLabel++; //Increments the current label to the next letter in the alphabet
                    }
                    labeledImage[i][j] = labels[root];
                }
            }
        }
    }

    void printLabeledImage() const {
    	//Iterates through each element in the 2D vector labeledImage
        for (const auto& row : labeledImage) {
            for (char pixel : row) {
                std::cout << pixel;
            }
            std::cout << std::endl;
        }
    }

	void printComponentSizes() {
		// Counts the size of each component
		for (const auto& row : labeledImage) {
			for (char label : row) {
				if (label != ' ') {
					componentSizes[label]++;
				}
			}
		}

		// Create a vector of pairs (label, size) for sorting in ascending order
		std::vector<std::pair<char, int>> sortedComponentSizes(componentSizes.begin(), componentSizes.end());

		// Sort the vector based on the size, from smallest to largest
		std::sort(sortedComponentSizes.begin(), sortedComponentSizes.end(),
				  [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
					  return a.second < b.second;
				  });

		// Prints the sorted list of component sizes
		for (const auto& pair : sortedComponentSizes) {
			std::cout << "Component " << pair.first << " size: " << pair.second << std::endl;
		}
	}

    void printFilteredComponents(int minSize) const {
    	// Iterates through the 2D labeled imaged
        for (const auto& row : labeledImage) {
            for (char label : row) {
                if (label == ' ' || componentSizes.at(label) < minSize) { // Checks if component size is less than the minimum size
                    std::cout << ' ';
                } else {
                    std::cout << label;
                }
            }
            std::cout << std::endl;
        }
    }


};

int main() {
    std::string filename = "infile";
    BinaryImageProcessor processor(filename);

    std::cout << "1. Original Image" << std::endl;
    processor.printOriginalImage();

    processor.processImage();

    std::cout << std::endl;
    std::cout << "2. Labeled Image" << std::endl;
    processor.printLabeledImage();

    std::cout << std::endl;
    std::cout << "3. List of Component Sizes" << std::endl;
    processor.printComponentSizes();

    std::cout << std::endl;
    std::cout << "4. Labeled Image of Component Sizes >= 2" << std::endl;
    processor.printFilteredComponents(2);

    std::cout << std::endl;
    std::cout << "5. Labeled Image of Component Sizes >= 11" << std::endl;
    processor.printFilteredComponents(11);

    return 0;
}
