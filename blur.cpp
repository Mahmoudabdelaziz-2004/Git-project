#include "Image_Class.h" // Include the Image class header (assuming it has basic functionalities)
#include <iostream>
#include <string>
#include <cctype>
#include <vector> // Include vector for temporary storage

using namespace std;


void blurImage(Image& inputImage) {
  // Edge handling variables
  int blurRadius = 25; // Fixed blur radius (adjust as needed)  
  int leftLimit = 0, rightLimit = inputImage.width - 1;
  int topLimit = 0, bottomLimit = inputImage.height - 1;

  // Temporary storage for blurred values
  vector<unsigned char> blurredRow(inputImage.width * inputImage.channels, 0);
  vector<vector<unsigned char>> blurredImage(inputImage.height, blurredRow);

  // Iterate through each pixel
  for (int y = 0; y < inputImage.height; y++) {
    for (int x = 0; x < inputImage.width; x++) {
      // Calculate average considering edge cases
      int redSum = 0, greenSum = 0, blueSum = 0;
      int neighborCount = 0;
      for (int dy = -blurRadius; dy <= blurRadius; dy++) {
        for (int dx = -blurRadius; dx <= blurRadius; dx++) {
          int newX = x + dx;
          int newY = y + dy;

          // Check if within image boundaries
          if (newX >= leftLimit && newX <= rightLimit && newY >= topLimit && newY <= bottomLimit) {
            redSum += inputImage.imageData[(newY * inputImage.width + newX) * inputImage.channels];
            greenSum += inputImage.imageData[(newY * inputImage.width + newX) * inputImage.channels + 1];
            blueSum += inputImage.imageData[(newY * inputImage.width + newX) * inputImage.channels + 2];
            neighborCount++;
          }
        }
      }

      // Set the blurred value (average)
      blurredImage[y][x * inputImage.channels] = redSum / neighborCount;
      blurredImage[y][x * inputImage.channels + 1] = greenSum / neighborCount;
      blurredImage[y][x * inputImage.channels + 2] = blueSum / neighborCount;
    }
  }

  // Copy blurred values back to original image data
  for (int y = 0; y < inputImage.height; y++) {
    for (int x = 0; x < inputImage.width; x++) {
      for (int c = 0; c < inputImage.channels; c++) {
        inputImage.imageData[(y * inputImage.width + x) * inputImage.channels + c] = blurredImage[y][x * inputImage.channels + c];
      }
    }
  }
}

int main() {
    while (true) {
        // Variables to store input and image data
        string inputImageName, blurredImageName, imageExtension, blurredImageExtension;
        char userChoice;

        // Prompt user to enter input image details
        cout << "Enter the name of the input image: ";
        cin >> inputImageName;
        cout << "Enter the image extension (png, bmp, tga, jpg): ";
        cin >> imageExtension;

        // Load the input image
        Image inputImage(inputImageName + "." + imageExtension);

        // Check if the image exists
        if (inputImage.width == 0 || inputImage.height == 0) {
            cout << "Image not found!" << endl;
            break;
        }

        // Apply blur
        blurImage(inputImage);

        // Ask user if they want to save the blurred image
        cout << "Do you want to save the blurred image? (Y/N): ";
        cin >> userChoice;

        if (tolower(userChoice) == 'y') {
            // Prompt user
         cout << "Enter name of blurred image: ";
        cin >> blurredImageName;
        cout << "Choose blurred image extension (PNG, JPEG, JPG, BMP): ";
        cin >> blurredImageExtension;

        // Save the blurred image
        if (!inputImage.saveImage(blurredImageName + "." + blurredImageExtension)) {
            cerr << "Error saving blurred image!" << endl;
        } else {
            cout << "Blurred image saved successfully!" << endl;
        }
    }

    return 0;
}
}