// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Allocating memory to store the header
    uint8_t header[HEADER_SIZE];

    // Reading the header from the input file
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);

    // Writing the header to the output file
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Reading samples from the input file, modifying them, and writing to the output file
    int16_t sample;
    while (fread(&sample, sizeof(int16_t), 1, input))
    {
        // Adjusting the volume of the sample by the factor
        sample *= factor;

        // Writing the modified sample to the output file
        fwrite(&sample, sizeof(int16_t), 1, output);
    }

    fclose(input);
    fclose(output);
}
