#include <stdio.h>
#include <stdint.h>

// Define a BYTE as an unsigned 8-bit integer
typedef uint8_t BYTE;

// Define the block size (typical for a FAT file system)
#define BLOCK_SIZE 512

int main(int argc, char *argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Open the input file
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE]; // Buffer to store 512-byte blocks
    FILE *output = NULL;     // File pointer for the output JPEG
    char filename[8];        // To store filenames like "###.jpg"
    int file_count = 0;      // Counter for the number of JPEG files found

    // Read the input file block by block
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        // Check if the block is the start of a new JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it
            if (output != NULL)
            {
                fclose(output);
            }

            // Create a new file for the JPEG
            sprintf(filename, "%03i.jpg", file_count);
            output = fopen(filename, "w");
            if (output == NULL)
            {
                printf("Could not create file.\n");
                fclose(input);
                return 1;
            }

            file_count++; // Increment JPEG counter
        }

        // If a JPEG file is open, write the current block to it
        if (output != NULL)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, output);
        }
    }

    // Close any remaining open files
    if (output != NULL)
    {
        fclose(output);
    }
    fclose(input);

    return 0;
}
