#include "Image_Class.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

bool isValidExtension(const string &newname)
{
    // Convert the extension to lowercase for case-insensitive comparison
    string extension = newname.substr(newname.find_last_of(".") + 1);
    for (char &x : extension)
    {
        x = tolower(x);
    }
    // List of valid extensions
    vector<string> validExtensions = {"jpg", "jpeg", "bmp", "png", "tga"};

    // Check if the extension is in the list of valid extensions
    return find(validExtensions.begin(), validExtensions.end(), extension) != validExtensions.end();
}
void SavedImg(Image &save)
{
    cout << "\nDo you want to save the edited image?\n";
    cout << "1) Yes\n2) Discard Changes\n";
    string choice2;
    getline(cin, choice2);
    while (choice2 != "1" && choice2 != "2")
    {
        cout << "Please select a valid choice: ";
        getline(cin, choice2);
    }

    if (choice2 == "1")
    {
        string newname;
        cout << "Please enter the name of new image\nand specify extension .jpg, .jpeg, .bmp, .png, .tga: ";
        cin >> newname;
        while (!isValidExtension(newname))
        {
            cout << "Invalid file extension. Only Supported: .jpg, .jpeg, .bmp, .png, .tga: ";
            cin >> newname;
            continue;
        }
        save.saveImage(newname);
        cout << "Image saved successfully.\n\n";
    }
    else if (choice2 == "2")
    {
        cout << "Changes discarded successfully.\n\n";
    }
}
void applyTVEffect(Image& image) {
    // Loop through each pixel in the image
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < image.width; x++) {
            // Generate random noise
            int noise = rand() % 30 - 15;

            // Add noise to each channel (RGB) of the pixel value
            for (int c = 0; c < image.channels; c++) {
                int newValue = image(x, y, c) + noise;

                // Ensure pixel value is within [0, 255] range
                if (newValue < 0)
                    newValue = 0;
                else if (newValue > 255)
                    newValue = 255;

                // Update pixel value with noise
                image(x, y, c) = newValue;
            }
        }
    }
}
int main()
{
    while (true)
    {
        // Variables to store input and image data
        string inputImageName, blurredImageName, imageExtension, blurredImageExtension;
        char userChoice;
        string level;

        // Prompt user to enter input image details
        cout << "Enter the name of the input image: ";
        cin >> inputImageName;
        cout << "Enter the image extension (png, bmp, tga, jpg): ";
        cin >> imageExtension;

        // Load the input image
        Image inputImage(inputImageName + "." + imageExtension);

        // Check if the image exists
        if (inputImage.width == 0 || inputImage.height == 0)
        {
            cout << "Image not found!" << endl;
            break;
        }
        applyTVEffect(inputImage);
        SavedImg(inputImage);
    }
}