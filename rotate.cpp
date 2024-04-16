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

Image rotateImage90(Image &image)
{
    Image rotatedImage(image.height , image.width);

    // Rotate the image
    for (int i = 0; i <  image.width; ++i)
    {
        for (int j = 0; j <  image.height; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                rotatedImage( image.height - j - 1,  i, k) = image(i, j, k);
            }
        }
    }

    return rotatedImage;
}

Image rotateImage270(Image &image)
{
    // Create a new image with swapped dimensions
    Image rotatedImage(image.height, image.width);

    // Rotate the image
    for (int i = 0; i <  image.width; ++i)
    {
        for (int j = 0; j <image.height  ; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                rotatedImage(j, image.width - i - 1, k) = image(i, j, k);
            }
        }
    }

    return rotatedImage;
}

Image rotateImage180(Image &image)
{
    Image rotatedImage(image.width, image.height);

    // Rotate the image
    for (int i = 0; i < image.height; ++i)
    {
        for (int j = 0; j < image.width; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                rotatedImage(image.width - j - 1, image.height - i - 1, k) = image(j, i, k);
            }
        }
    }

    return rotatedImage;
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
    string option;
    cout << "1. Rotate Image 90 Degrees\n";
    cout << "2. Rotate Image 180 Degrees\n";
    cout << "3. Rotate Image 270 Degrees\n";
    while (true)
    {
        cin >> option;
        if (option == "1")
        {
            Image rotatedImage90 = rotateImage90(inputImage);
            SavedImg(rotatedImage90);
            break;
        }
        else if (option == "2")
        {
            Image rotatedImage180 = rotateImage180(inputImage);
            SavedImg(rotatedImage180);
            break;
        }
        else if (option == "3")
        {
            Image rotatedImage270 = rotateImage270(inputImage);
            SavedImg(rotatedImage270);
            break;
        }
        else
            cout << "please select a valid choice: ";
    }
    }
}