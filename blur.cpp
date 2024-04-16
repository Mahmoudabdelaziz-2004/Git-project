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
void blurImageLevel(Image &inputImage, int blurRadius)
{
    // Edge handling variables
    int leftLimit = 0, rightLimit = inputImage.width - 1;
    int topLimit = 0, bottomLimit = inputImage.height - 1;

    // Temporary storage for blurred values
    vector<vector<vector<int>>> prefixSum(inputImage.channels, vector<vector<int>>(inputImage.height + 1, vector<int>(inputImage.width + 1, 0)));

    // Calculate prefix sum for the entire image for each channel separately
    for (int c = 0; c < inputImage.channels; c++)
    {
        for (int y = 0; y < inputImage.height; y++)
        {
            for (int x = 0; x < inputImage.width; x++)
            {
                prefixSum[c][y + 1][x + 1] = inputImage.imageData[(y * inputImage.width + x) * inputImage.channels + c];
                prefixSum[c][y + 1][x + 1] += prefixSum[c][y][x + 1] + prefixSum[c][y + 1][x] - prefixSum[c][y][x];
            }
        }
    }

    // Iterate through each pixel
    for (int y = 0; y < inputImage.height; y++)
    {
        for (int x = 0; x < inputImage.width; x++)
        {
            // Calculate average considering edge cases for each channel separately
            for (int c = 0; c < inputImage.channels; c++)
            {
                int x1 = max(0, x - blurRadius);
                int x2 = min(inputImage.width - 1, x + blurRadius);
                int y1 = max(0, y - blurRadius);
                int y2 = min(inputImage.height - 1, y + blurRadius);
                int neighborCount = (x2 - x1 + 1) * (y2 - y1 + 1);

                // Calculate sum of pixels in the blur region using prefix sum for each channel separately
                int channelSum = prefixSum[c][y2 + 1][x2 + 1] - prefixSum[c][y1][x2 + 1] - prefixSum[c][y2 + 1][x1] + prefixSum[c][y1][x1];

                // Set the blurred value (average) for each channel separately
                inputImage.imageData[(y * inputImage.width + x) * inputImage.channels + c] = channelSum / neighborCount;
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
;
        // Prompt user to enter blur radius
        // Prompt user to enter blur radius
        cout << "Enter the blur level you want (1 , 2 , 3): ";
        while (true)
        {
            cin >> level;
            if (level == "1")
            {
                int blurRadius = 20;
                blurImageLevel(inputImage, blurRadius);
                SavedImg(inputImage);
                break;
            }
            else if (level == "2")
            {
                int blurRadius = 30;
                blurImageLevel(inputImage, blurRadius);
                SavedImg(inputImage);
                break;
            }
            else if (level == "3")
            {
                int blurRadius = 45;
                blurImageLevel(inputImage, blurRadius);
                SavedImg(inputImage);
                break;
            }
            else
            {
                cout << "please select a valid choice: ";
            }
        }
        break;
    }
}
