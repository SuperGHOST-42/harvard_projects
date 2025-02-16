// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "wb");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);
    if (factor <= 0)
    {
        printf("Invalid factor: must be greater than 0\n");
        fclose(input);
        fclose(output);
        return 1;
    }

    // TODO: Copy header from input file to output file
    BYTE header[HEADER_SIZE];

    int byte_count = 0;
    fread(header, sizeof(BYTE), HEADER_SIZE, input);
    fwrite(header, sizeof(BYTE), HEADER_SIZE, output);

    // TODO: Read samples from input file and write updated data to output file
    int16_t buffer;
    while (fread(&buffer, sizeof(buffer), 1, input))
    {
        // Scale and clamp the sample in a single step
        buffer = (int16_t)(buffer * factor < INT16_MIN ? INT16_MIN : buffer * factor > INT16_MAX ? INT16_MAX : buffer * factor);

        fwrite(&buffer, sizeof(buffer), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
