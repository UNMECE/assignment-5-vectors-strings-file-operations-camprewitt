#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "pixel.h" // Include the pixel.h header

// Declare your functions and global variables here
std::vector<Pixel> pixel_list;

void read_pixels_from_file(const std::string &filename, std::vector<Pixel> &pixel_list) {
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        Pixel pixel;
        char delimiter;

        // Extract values from the string and store in pixel object
        ss >> pixel.x >> delimiter >> pixel.y >> delimiter >> pixel.r >> delimiter >> pixel.g >> delimiter >> pixel.b;
        // Add pixel to the list
        pixel_list.push_back(pixel);
    }
}

void average_colors(const std::vector<Pixel> &pixel_list) {
    float total_r = 0, total_g = 0, total_b = 0;
    size_t pixel_count = pixel_list.size();

    for (const auto &pixel : pixel_list) {
        total_r += pixel.r;
        total_g += pixel.g;
        total_b += pixel.b;
    }

    std::cout << "Average R: " << total_r / pixel_count << std::endl;
    std::cout << "Average G: " << total_g / pixel_count << std::endl;
    std::cout << "Average B: " << total_b / pixel_count << std::endl;
}

void flip_vertically(std::vector<Pixel> &pixel_list, int y_length) {
    for (auto &pixel : pixel_list) {
        pixel.y = y_length - 1 - pixel.y;
    }
}

void save_flipped_pixels_to_file(const std::string &filename, const std::vector<Pixel> &pixel_list) {
    std::ofstream file(filename);

    for (const auto &pixel : pixel_list) {
        file << pixel.x << ',' << pixel.y << ',' << pixel.r << ',' << pixel.g << ',' << pixel.b << '\n';
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    read_pixels_from_file(filename, pixel_list);

    average_colors(pixel_list);

    int y_length = 256;  // Given in the assignment
    flip_vertically(pixel_list, y_length);

    save_flipped_pixels_to_file("flipped.dat", pixel_list);

    return 0;
}