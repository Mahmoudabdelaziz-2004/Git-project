/*
* Explain: This program allows the user to edit photos using 12 filter and check validation
           of precence of images and validation of inputs within the program.

 * Author:      Marwan Hussein Mohamed Mohamed          20230382        marawanlabana649@gmail.com
 *              Mahmoud Abdelaziz Mahmoud               20230603        20230603@stud.fci-cu.edu.eg
 *              Mohamed Refaat                          20230337        mrefaat8853@gmail.com
 *
 * Lab Number:  S19, S20
 * TA:          Eng. Yomna Fathy
 * 
 * link of repo : https://github.com/Momo17029/project 
 *
 * ID1:         20230337: Filters: 1, 4, 7, 10, 13 (Grayscale Conversion & Merge & Darken and Lighten & Detect edges & Good natural sunlight)
 *
 * ID2:         20230382: Filters: 2, 5, 8, 11, 16(Black and White & Flip & Crop & Reasize & Purple)
 *
 * ID3:         20230603: Filters: 3, 6, 9, 12, 15 (invert images & Rotate & Add Frame & Blur & TV)
*/
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

void gray_scale(Image &image)
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int avg = 0;
            for (int c = 0; c < 3; c++)
            {
                avg += image(i, j, c);
            }
            avg /= 3;
            for (int a = 0; a < 3; a++) // Set all RGB channels to the average value to convert to grayscale
            {
                image(i, j, a) = avg;
            }
        }
    }
}

void filter2(Image &image) // black and white
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            unsigned int avg = 0;
            for (int c = 0; c < 3; c++)
            {
                avg += image(i, j, c);
            }
            avg /= 3;
            for (int a = 0; a < 3; a++)
            {
                if (avg > 255 / 2) // Gray is greater than the middle
                    image(i, j, a) = 255;
                else
                    image(i, j, a) = 0;
            }
        }
    }
}
void cropMerge(Image &image, Image &img2)
{
    // Determine the common dimensions between the two images
    int common_width = min(image.width, img2.width);
    int common_height = min(image.height, img2.height);
    Image merged(common_width, common_height);

    for (int i = 0; i < common_width; ++i)
    {
        for (int j = 0; j < common_height; ++j)
        {
            for (int k = 0; k < 3; ++k)
            {
                // Calculate the average pixel value between the two images
                int average = (image(i, j, k) + img2(i, j, k)) / 2;
                merged(i, j, k) = average;
            }
        }
    }
    SavedImg(merged);
}

void resizeMerge(Image &image, Image &img2)
{
    cout << "Dimensions like:\n1) first image \n2) second image" << endl;
    cout << "Please enter 1 or 2: ";

    string choice;

    double w, h;
    while (true)
    {
        cin >> choice;
        if (choice == "1") // in case resize to image1
        {
            w = image.width;
            h = image.height;
            break;
        }
        else if (choice == "2") // in case resize to image2
        {
            w = img2.width;
            h = img2.height;
            break;
        }
        else
        {
            cout << "Invalid choice , please enter a valid choice: ";
        }
    }

    float coffw1 = w / image.width;  // coefficient between new width and old width for image1
    float coffh1 = h / image.height; // coefficient between new height and old height for image2
    float coffw2 = w / img2.width;   // coefficient between new width and old width for image2
    float coffh2 = h / img2.height;  // coefficient between new height and old height for image2

    Image resized1(w, h);
    Image resized2(w, h);

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                // Resize image to match dimensions of img2
                resized1(i, j, k) = image(i / coffw1, j / coffh1, k);
                // Resize img2 to match dimensions of image
                resized2(i, j, k) = img2(i / coffw2, j / coffh2, k);
            }
        }
    }

    // Perform operations with resized images or save them as desired
    Image new_image(resized1.width, resized1.height);

    for (int i = 0; i < resized1.width; ++i)
    {
        for (int j = 0; j < resized1.height; ++j)
        {

            for (int c = 0; c < 3; ++c)
            {
                int marge = (resized1(i, j, c) + resized2(i, j, c)) / 2;

                if (marge >= 255)
                {
                    marge = 255;
                }
                if (marge <= 0)
                {
                    marge = 0;
                }

                new_image(i, j, c) = marge;
            }
        }
    }
    SavedImg(new_image);
}

void filter5(Image &image) // flip
{
    cout << "1) Horizontal Flip\n";
    cout << "2) Vertical Flip\n";
    string choice;
    cout << "Select a choice: ";
    cin >> choice;
    while (choice != "1" && choice != "2")
    {
        cout << "\nPlease select a valid choice: ";
        cin >> choice;
    }
    int width = image.width;
    int height = image.height;
    unsigned char temp[3]; // Temporary storage for pixel values during swapping

    if (choice == "1") // Horizontal flip
    {
        for (int i = 0; i < width / 2; i++)
        {
            for (int j = 0; j < height; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    temp[k] = image(i, j, k);                    // swap main pixel to temp.
                    image(i, j, k) = image(width - 1 - i, j, k); // swap the opposite pixel to the main pixel.
                    image(width - 1 - i, j, k) = temp[k];        // swap the main pixel to the opposite pixel.
                }
            }
        }
    }
    else if (choice == "2") // Vertical flip
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height / 2; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    temp[k] = image(i, j, k);                     // swap main pixel to temp.
                    image(i, j, k) = image(i, height - 1 - j, k); // swap the opposite pixel to the main pixel.
                    image(i, height - 1 - j, k) = temp[k];        // swap the main pixel to the opposite pixel.
                }
            }
        }
    }
}
Image rotateImage90(Image &image)
{
    Image rotatedImage(image.height, image.width);

    // Rotate the image
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {
            for (int k = 0; k < image.channels; ++k)
            {
                rotatedImage(image.height - j - 1, i, k) = image(i, j, k);
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
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
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

void filter7(Image &image) // darken lighten
{
    string operation;
    cout << "What do you want to make ?\n";
    cout << "1) Make the image darker.\n";
    cout << "2) Make the image lighter.\n";
    cout << "Please enter  1 or 2: ";
    while (true)
    {
        getline(cin, operation);
        if (operation == "1" || operation == "2")
        {
            break;
        }
        else
        {
            cout << "Please enter a valid choice: ";
        }
    }

    if (operation == "1")
    {

        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int c = 0; c < 3; ++c)
                {

                    int pixelValue = image(i, j, c);

                    // Darken the pixel value by dividing it by 2
                    pixelValue /= 2;

                    // Ensure the pixel value remains within the range [0, 255]
                    if (pixelValue < 0)
                    {
                        pixelValue = 0;
                    }

                    image(i, j, c) = pixelValue;
                }
            }
        }
    }
    else
    {

        for (int i = 0; i < image.width; ++i)
        {
            for (int j = 0; j < image.height; ++j)
            {
                for (int c = 0; c < 3; ++c)
                {

                    double pixelValue = image(i, j, c);

                    // Lighten the pixel value by multiplying it by 1.5
                    pixelValue *= 1.5;

                    // Ensure the pixel value remains within the range [0, 255]
                    if (pixelValue > 255)
                    {
                        pixelValue = 255;
                    }

                    image(i, j, c) = pixelValue;
                }
            }
        }
    }
}
void filter8(Image &image) // crop
{

    cout << "Image's width = " << image.width;
    cout << "\nImage's height = " << image.height;
    cout << "\nPlease enter start point Dimensions (must be a space between them): ";
    int x, y; // start points
    cin >> x >> y;
    while (x > image.width - 1 || y > image.height - 1 || x < 0 || y < 0)
    {
        cout << "\nplease enter a valid start point: ";
        cin >> x >> y;
    }

    cout << "please enter the Dimensions of area to cut (must be a space between them): ";
    int w, h; // area to crop
    cin >> w >> h;
    while (x + w > image.width || y + h > image.height || w < 1 || h < 1)
    {
        cout << "\nplease enter a valid area to cut: ";
        cin >> w >> h;
    }
    Image cropped(w, h); // to move croped pixels to a new image.
    int countX = 0, countY = 0;
    for (int i = x; i < x + w; i++)
    {
        for (int j = y; j < y + h; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                cropped(countX, countY, k) = image(i, j, k);
            }
            countY++;
        }
        countX++;
        countY = 0;
    }
    // saving cropped image
    SavedImg(cropped);
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

void filter10(Image &image)
{
    for (int i = 0; i < image.width - 1; ++i)
    {
        for (int j = 0; j < image.height - 1; ++j)
        {
            unsigned int diff = 0;

            // Compute intensity difference between adjacent pixels
            for (int c = 0; c < 3; ++c)
            {
                diff += abs(image(i, j, c) - image(i + 1, j + 1, c));
            }
            diff /= 3; // Average the difference across channels

            // Apply thresholding to detect edges
            if (diff > 30)
            { // Adjust threshold as needed
                // Set pixel to white (edge)
                for (int a = 0; a < 3; a++)
                {
                    image(i, j, a) = 0;
                }
            }
            else
            {
                // Set pixel to black (non-edge)
                for (int a = 0; a < 3; a++)
                {
                    image(i, j, a) = 255;
                }
            }
        }
    }
}
void filter11(Image &image) // resize
{
    cout << "Image's width = " << image.width;
    cout << "\nImage's height = " << image.height;
    cout << "\nPlease enter new dimensions\n";
    string w_str, h_str;
    double w, h;

    // Keep looping until valid input is provided for width
    while (true) {
        cout << "Enter width: ";
        cin >> w_str;

        // Check if the input contains only digits or a decimal point
        bool isValidWidth = true;
        for (char c : w_str) {
            if (!isdigit(c) && c != '.') {
                isValidWidth = false;
                break;
            }
        }

        // If the input is valid, convert it to double and check if it's greater than 0
        if (isValidWidth) {
            w = stod(w_str);
            if (w > 0) {
                break;  // Exit the loop if the width is valid
            }
        }

        cout << "Please enter a valid number greater than 0." << endl;
        cin.clear();        // Clear error flags
        cin.ignore(100, '\n');  // Discard invalid input
    }

    // Keep looping until valid input is provided for height
    while (true) {
        cout << "Enter height: ";
        cin >> h_str;

        // Check if the input contains only digits or a decimal point
        bool isValidHeight = true;
        for (char c : h_str) {
            if (!isdigit(c) && c != '.') {
                isValidHeight = false;
                break;
            }
        }

        // If the input is valid, convert it to double and check if it's greater than 0
        if (isValidHeight) {
            h = stod(h_str);
            if (h > 0) {
                break;  // Exit the loop if the height is valid
            }
        }

        cout << "Please enter a valid number greater than 0." << endl;
        cin.clear();        // Clear error flags
        cin.ignore(100, '\n');  // Discard invalid input
    }

    float coffw = w / image.width;  // cofficient between new width and old width
    float coffh = h / image.height; // cofficient between new height and old height

    Image resized(w, h);
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                resized(i, j, k) = image(i / coffw, j / coffh, k);
            }
        }
    }
    // Saving the resized image
    SavedImg(resized);
}

void blurImageLevel(Image &inputImage , int blurRadius)
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
void filter13(Image &image) // good sunlight
{
    for (int i = 0; i < image.width; ++i)
    {
        for (int j = 0; j < image.height; ++j)
        {

            for (int c = 0; c < 3; ++c)
            {
                int pixelValue = image(i, j, c);

                // Apply a decrease in brightness by multiplying by 0.9
                pixelValue *= 0.9;

                // Apply a contrast adjustment using the formula: 0.9 * (pixelValue - 128) + 128
                pixelValue = 0.9 * (pixelValue - 128) + 128;

                // Increase the intensity of red and green channels
                if (c == 0 || c == 1)
                {

                    pixelValue += 90;
                }

                // Clamp the pixel value to ensure it remains within the range [0, 255]
                if (pixelValue >= 255)
                {
                    pixelValue = 255;
                }

                image(i, j, c) = pixelValue;
                // unsigned char &blue = image(i, j, 2);
                // blue *= 0.8;
            }
        }
    }
}
void applyTVEffect(Image &image)
{
    // Loop through each pixel in the image
    for (int y = 0; y < image.height; y++)
    {
        for (int x = 0; x < image.width; x++)
        {
            // Generate random noise
            int noise = rand() % 30 - 15;

            // Add noise to each channel (RGB) of the pixel value
            for (int c = 0; c < image.channels; c++)
            {
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

void filter16(Image &image) // purble
{
    for (int i = 0; i < image.width; i++)
    {
        for (int j = 0; j < image.height; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                unsigned char &green = image(i, j, 1);
                green *= 0.85; // decrease green = increase red and blue then increase purple.
                image(i, j, k);
            }
        }
    }
}
int main()
{
    while (true)
    {
        cout << "1) Load an Image\n";
        cout << "2) Exit\n";
        string choice0;
        cin >> choice0;
        if (choice0 == "1")
        {
            cout << "Please enter the name of your image: ";
            string image_name;
            cin >> image_name;
            Image image;
            while (true)
            {
                try
                {
                    image.loadNewImage(image_name);
                    break;
                }
                catch (invalid_argument)
                {
                    cout << "\nPlease enter a valid photo: ";
                    cin >> image_name;
                }
            }
            cout << "\n1) Grayscale Conversion\n"
                 << "2) Black and White\n"
                 << "3) Invert Image\n"
                 << "4) Merge Images\n"
                 << "5) Flip Image\n"
                 << "6) Rotate Image\n"
                 << "7) Darken and Lighten Image\n"
                 << "8) Crop Image\n"
                 << "9) Frame Image\n"
                 << "10) Detect Edges\n"
                 << "11) Resizing Image \n"
                 << "12) Blur Imae\n"
                 << "13) Good natural sunlight\n"
                 << "14) Wano villagers (televisions)\n"
                 << "15) Purple Image\n"
                 << "Please select a filter: ";
            cin.ignore();
            while (true)
            {
                string choice1;
                getline(cin, choice1);

                if (choice1 == "1") // gray scale
                {
                    gray_scale(image);
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "2") // B & W
                {
                    filter2(image);
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "3") // convert colors
                {
                    for (int j = 0; j < image.height; j++)
                    {
                        for (int i = 0; i < image.width; i++)
                        {
                            unsigned char &red = image(i, j, 0);
                            unsigned char &green = image(i, j, 1);
                            unsigned char &blue = image(i, j, 2);
                            red = 255 - red;     // the opposite to red degree.
                            green = 255 - green; // the opposite to green degree.
                            blue = 255 - blue;   // the opposite to blue degree.
                        }
                    }
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "4") // mrege by crop or resize
                {
                    cout << "\nPlease enter name of second image: ";
                    string im2;
                    cin >> im2;
                    Image img2;
                    while (true)
                    {
                        try
                        {
                            img2.loadNewImage(im2);
                            break;
                        }
                        catch (invalid_argument)
                        {
                            cout << "\nPlease enter a valid photo: ";
                            cin >> im2;
                        }
                    }
                    cout << "What marge you want?\n";
                    cout << "1) merge by resize\n";
                    cout << "2) merge by crop the common area\n";
                    cout << "Enter your choice: ";
                    string option;
                    while (true)
                    {
                        cin >> option;
                        if (option == "1")
                        {
                            resizeMerge(image, img2);
                            break;
                        }
                        else if (option == "2")
                        {
                            cropMerge(image, img2);
                            break;
                        }
                        else
                        {
                            cout << "Invalid choice , please enter a valid choice: ";
                        }
                    }
                    break;
                }
                else if (choice1 == "5") // flip
                {
                    filter5(image);
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "6") // rotate
                {
                    string option;
                    cout << "1. Rotate Image 90 Degrees\n";
                    cout << "2. Rotate Image 180 Degrees\n";
                    cout << "3. Rotate Image 270 Degrees\n";
                    while (true)
                    {
                        cin >> option;
                        if (option == "1")
                        {
                            Image rotatedImage90 = rotateImage90(image);
                            SavedImg(rotatedImage90);
                            break;
                        }
                        else if (option == "2")
                        {
                            Image rotatedImage180 = rotateImage180(image);
                            SavedImg(rotatedImage180);
                            break;
                        }
                        else if (option == "3")
                        {
                            Image rotatedImage270 = rotateImage270(image);
                            SavedImg(rotatedImage270);
                            break;
                        }
                        else
                            cout << "please select a valid choice: ";
                    }
                    break;
                }
                else if (choice1 == "7") // darken and lighten
                {
                    filter7(image);
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "8") // crop
                {
                    filter8(image);
                    break;
                }
                else if (choice1 == "9")
                {
                    string frameTypeChoice;
                    cout << "Choose frame type (1 for simple, 2 for fancy): ";
                    while (true)
                    {
                        cin >> frameTypeChoice;
                        if (frameTypeChoice == "1")
                        {
                            addGoldFrame(image);
                            SavedImg(image);
                            break;
                        }
                        else if (frameTypeChoice == "2")
                        {
                            addFancyDoubleBorder(image);
                            SavedImg(image);
                            break;
                        }
                        else
                        {
                            cout << "please select a valid choice: ";
                        }
                    }
                    break;
                }
                else if (choice1 == "10") // detect
                {
                    filter10(image);
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "11") // resize
                {
                    filter11(image);
                    break;
                }
                else if (choice1 == "12") // blur
                {
                    string level;
                    cout << "Enter the blur level you want (1 , 2 , 3): ";
                    while (true)
                    {
                        cin >> level;
                        if (level == "1")
                        {
                            int blurRadius = 20;
                            blurImageLevel(image, blurRadius);
                            SavedImg(image);
                            break;
                        }
                        else if (level == "2")
                        {
                            int blurRadius = 30;
                            blurImageLevel(image, blurRadius);
                            SavedImg(image);
                            break;
                        }
                        else if (level == "3")
                        {
                            int blurRadius = 45;
                            blurImageLevel(image , blurRadius);
                            SavedImg(image);
                            break;
                        }
                        else
                        {
                            cout << "please select a valid choice: ";
                        }
                    }
                    break;
                }
                else if (choice1 == "13") // sunlight
                {
                    filter13(image);
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "14") // television
                {
                    applyTVEffect(image);
                    SavedImg(image);
                    break;
                }
                else if (choice1 == "15") // purble
                {
                    filter16(image);
                    SavedImg(image);
                    break;
                }
                else
                {
                    cout << "Please select a valid filter: ";
                }
            }
        }
        else if (choice0 == "2")
            break;
        else
        {
            cout << "\nplease select a valid choice.\n";
            continue;
        }
        continue;
        return 0;
    }
}