#include "Image_Class.h" // Include the Image class header
#include <iostream>
#include <string>
#include <cctype>

using namespace std;

int main()
{
    while (true)
    {
        // Variables to store input and image data
        string inputImageName, invertedImageName, imageExtension, invertedImageExtension;
        char userChoice;

        // Prompt user to enter input image details
        cout << "Enter the name of the input image: ";
        cin >> inputImageName;
        cout << "Enter the image extension (png, bmp, tga, jpg): ";
        cin >> imageExtension;

        // Load the input image
        Image inputImage(inputImageName + "." + imageExtension);

        // Check if the image exists
        if (inputImage.width == 0 || inputImage.height == 0 )
        {
            cout << "Image not found!" << endl;
            break;
        }

        // Invert the colors of the input image
        for (int j = 0; j < inputImage.height; j++)
        {
            for (int i = 0; i < inputImage.width; i++)
            {
                // Get pixel colors
                unsigned char & red = inputImage(i, j, 0); 
                unsigned char & green = inputImage(i, j, 1); 
                unsigned char & blue = inputImage(i, j, 2); 

                // Invert pixel colors
                red = 255 - red;
                green = 255 - green;
                blue = 255 - blue; 
            }
        }

        // Ask user if they want to save the inverted image
        cout << "Do you want to save the inverted image? (Y/N): ";
        cin >> userChoice;

        if (tolower(userChoice) == 'y')
        {
            // Prompt user to enter details for saving inverted image
            cout << "Enter name of inverted image: ";
            cin >> invertedImageName;
            cout << "Choose inverted image extension (PNG, JPEG, JPG, BMP): ";
            cin >> invertedImageExtension;

            // Save the inverted image
            if (!inputImage.saveImage(invertedImageName + "." + invertedImageExtension))
            {
                cout << "Image could not be saved" << endl;
                return -1;
            }

            cout << "The image has been inverted and saved successfully" << endl;
        }
        else if(tolower(userChoice) == 'n')
        {
            cout << "The image has been inverted successfully" << endl;
        }
        else
        {
            cout << "Please select 'Y' or 'N'" << endl;
        }
    }
    return 0;
}
