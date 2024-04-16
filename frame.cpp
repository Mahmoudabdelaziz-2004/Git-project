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
void addGoldFrame(Image &image)
{
    int borderWidth = 100;
    int width = image.width;
    int height = image.height;

    unsigned char goldRed = 255;
    unsigned char goldGreen = 215;
    unsigned char goldBlue = 0;
    for (int x = 0; x < width; ++x)
    {
        for (int c = 0; c < image.channels; ++c)
        {
            for (int i = 0; i < borderWidth; ++i)
            {
                image.setPixel(x, i, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : goldBlue));
                image.setPixel(x, height - 1 - i, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : goldBlue));
            }
        }
    }
    for (int y = 0; y < height; ++y)
    {
        for (int c = 0; c < image.channels; ++c)
        {
            for (int i = 0; i < borderWidth; ++i)
            {
                image.setPixel(i, y, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : goldBlue));
                image.setPixel(width - 1 - i, y, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : goldBlue));
            }
        }
    }
}

void addFancyDoubleBorder(Image &image)
{
    int borderWidth = 100;
    int width = image.width;
    int height = image.height;

    unsigned char goldRed = 0;
    unsigned char goldGreen = 0;
    unsigned char blue = 255; // Darker blue color

    for (int x = 0; x < width; ++x)
    {
        for (int c = 0; c < image.channels; ++c)
        {
            for (int i = 0; i < borderWidth; ++i)
            {
                int y_offset = static_cast<int>(5 * sin(0.1 * x + 0.1 * i));
                int y_top = i + y_offset;
                int y_bottom = height - 1 - i - y_offset;

                if (y_top >= 0 && y_top < height)
                {
                    image.setPixel(x, y_top, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue)); // Darker blue color here
                }
                if (y_bottom >= 0 && y_bottom < height)
                {
                    image.setPixel(x, y_bottom, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue)); // Darker blue color here
                }
            }
        }
    }

    for (int y = 0; y < height; ++y)
    {
        for (int c = 0; c < image.channels; ++c)
        {
            for (int i = 0; i < borderWidth; ++i)
            {
                int x_offset = static_cast<int>(5 * cos(0.1 * y + 0.1 * i));
                int x_left = i + x_offset;
                int x_right = width - 1 - i - x_offset;

                if (x_left >= 0 && x_left < width)
                {
                    image.setPixel(x_left, y, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue)); // Darker blue color here
                }
                if (x_right >= 0 && x_right < width)
                {
                    image.setPixel(x_right, y, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue)); // Darker blue color here
                }
            }
        }
    }
    int innerBorderWidth = borderWidth / 2;
    for (int x = innerBorderWidth; x < width - innerBorderWidth; ++x)
    {
        for (int c = 0; c < image.channels; ++c)
        {
            for (int i = 0; i < innerBorderWidth; ++i)
            {
                image.setPixel(x, i, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue));              // Darker blue color here
                image.setPixel(x, height - 1 - i, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue)); // Darker blue color here
            }
        }
    }
    for (int y = innerBorderWidth; y < height - innerBorderWidth; ++y)
    {
        for (int c = 0; c < image.channels; ++c)
        {
            for (int i = 0; i < innerBorderWidth; ++i)
            {
                image.setPixel(i, y, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue));             // Darker blue color here
                image.setPixel(width - 1 - i, y, c, (c == 0) ? goldRed : ((c == 1) ? goldGreen : blue)); // Darker blue color here
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
    string frameTypeChoice;
    cout << "Choose frame type (1 for simple, 2 for fancy): ";
    while (true)
    {
        cin >> frameTypeChoice;
        if (frameTypeChoice == "1")
        {
            addGoldFrame(inputImage);
            SavedImg(inputImage);
            break;
        }
        else if (frameTypeChoice == "2")
        {
            addFancyDoubleBorder(inputImage);
            SavedImg(inputImage);
            break;
        }
        else
        {
            cout << "please select a valid choice: ";
        }
    }
    }
    return 0;
}
