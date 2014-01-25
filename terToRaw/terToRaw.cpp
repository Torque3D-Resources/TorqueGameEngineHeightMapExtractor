// terToRaw.cpp : Defines the entry point for the console application.
//

#include <string>

int main (int argc, char* argv[])
{
    // It's C++ so hush.
    std::string usage =
        " terToRaw <fileName>\n"
        " - This program will extract a heightmap from a Torque Game Engine .ter file\n"
        " - and save it as a raw 256 X 256 X 16 bit gray scale height map.\n";

    if(argc != 2)
    {
        printf(usage.c_str());
        return 0;
    }

    if(strlen(argv[1]) > 128)
    {
        // Because I'm too lazy for proper error detection in silly tools.
        fprintf(stderr, "Please provide a filename shorter than 128 chars.\n");
        exit(1);
    }

    std::string fileName_ext = argv[1];
    std::string outFileName;

    // Get the extension and filename
    size_t delim = fileName_ext.find_last_of(".");
    std::string fileName = fileName_ext.substr(0 , delim);
    std::string extension = fileName_ext.substr(delim + 1);

    // Convert the extension to lower case.
    for(size_t position = 0; position < extension.size(); ++position)
    {
        extension[position] = tolower(extension[position]);
    }

    if(extension == "ter")
    {
        outFileName = fileName + ".raw";
    }
    else
    {
        printf(usage.c_str());
        return 0;
    }

    /* Convert the file */
    FILE* fin = fopen(fileName_ext.c_str(), "rb");

    if(!fin)
    {
        fprintf(stderr, "Can't open input file \"%s\"\n", fileName_ext.c_str());
        exit(1);
    }

    FILE* fout = fopen(outFileName.c_str(), "wb");

    if(!fout)
    {
        fprintf(stderr, "Can't open output file \"%s\"\n", outFileName.c_str());
        exit(1);
    }

    // Discard the first char holding the file version.
    fgetc(fin);

    // The buffer
    unsigned short destinationBuffer[256*256];

    // Read and Write
    fread(destinationBuffer, sizeof(unsigned short), 256*256, fin);
    fwrite(destinationBuffer, sizeof(unsigned short), 256*256, fout);

    fclose(fout);
    fclose(fin);

    fprintf(stderr, "All Done.\n");

    return 0;
}

