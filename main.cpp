#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include "pixel.h"

std::vector<Pixel> pixel_list;

void read_pixels(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        Pixel p;
        std::getline(iss, token, ',');
        p.x = std::stoi(token);
        std::getline(iss, token, ',');
        p.y = std::stoi(token);
        std::getline(iss, token, ',');
        p.r = std::stof(token);
        std::getline(iss, token, ',');
        p.g = std::stof(token);
        std::getline(iss, token);
        p.b = std::stof(token);
        pixel_list.push_back(p);
    }
    file.close();
}

void average_colors(const std::vector<Pixel>& pixel_list) {
    float avg_r = 0.0f, avg_g = 0.0f, avg_b = 0.0f;
    for (const auto& pixel : pixel_list) {
        avg_r += pixel.r;
        avg_g += pixel.g;
        avg_b += pixel.b;
    }
    int num_pixels = pixel_list.size();
    avg_r /= num_pixels;
    avg_g /= num_pixels;
    avg_b /= num_pixels;
    std::cout << "Average R: " << avg_r << std::endl;
    std::cout << "Average G: " << avg_g << std::endl;
    std::cout << "Average B: " << avg_b << std::endl;
}

void flip_vertically(std::vector<Pixel>& pixel_list) {
    int height = 256;
    int width = 512;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height / 2; ++j) {
            std::swap(pixel_list[j * width + i], pixel_list[(height - 1 - j) * width + i]);
        }
    }
}

void save_pixels(const std::string& filename, const std::vector<Pixel>& pixel_list) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    for (const auto& pixel : pixel_list) {
        file << pixel.x << "," << pixel.y << "," << pixel.r << "," << pixel.g << "," << pixel.b << std::endl;
    }
    file.close();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    read_pixels(filename);
    average_colors(pixel_list);
    flip_vertically(pixel_list);
    save_pixels("flipped.dat", pixel_list);

    return 0;
