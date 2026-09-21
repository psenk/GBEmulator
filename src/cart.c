#include "cart.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <minwindef.h>
#include <windows.h>

char runtime_path_buffer[MAX_PATH]; // string holding working directory file path
uint8_t cartridge_data[MAX_CART_SIZE];
bool cartridge_loaded = false;
cart_header_struct *cartridge_header = (cart_header_struct *)(cartridge_data + 0x100);

bool get_runtime_path() // write working directory into buffer
{
    if (GetCurrentDirectory(MAX_PATH, runtime_path_buffer) == 0)
    {
        return false;
    }
    return true;
}

bool cart_open_file()
{
    if (!get_runtime_path())
    {
        return false;
    }

    char filename[MAX_PATH];

    OPENFILENAMEA ofn;                       // struct containing information to initialize open file dialog box
    ZeroMemory(&filename, sizeof(filename)); // zeroize filename memory space
    ZeroMemory(&ofn, sizeof(ofn));           // zeroize ofn memory space

    // populating ofn struct data
    ofn.lStructSize = sizeof(ofn);                            // size of the struct
    ofn.hwndOwner = NULL;                                     // window that owns this dialog box
    ofn.lpstrFilter = "GB ROM Files\0*.gb\0AnyFile\0*.*\0\0"; // file filters
    ofn.lpstrFile = filename;                                 // initializes file name edit control
    ofn.nMaxFile = MAX_PATH;                                  // size of lpstrFile buffer
    ofn.lpstrInitialDir = runtime_path_buffer;                // initial directory
    ofn.lpstrTitle = "Select a ROM file";                     // title bar of dialog window
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;      // prevent adding to recent files directory, file has to exist to be opened

    if (GetOpenFileNameA(&ofn))
    {
        cart_load(filename);
        return true;
    }
    return false;
}

void cart_print_info() // print header data
{
    printf("Entry point: %.2X%.2X%.2X%.2X\n", cartridge_header->entry_point[0], cartridge_header->entry_point[1], cartridge_header->entry_point[2], cartridge_header->entry_point[3]);
    printf("Title: %s\n", cartridge_header->title);
    printf("CGB Flag: %.2X\n", cartridge_header->cgb_flag);
    printf("New Licensee Code: %.2X%.2X\n", cartridge_header->new_licensee_code[0], cartridge_header->new_licensee_code[1]);
    printf("SGB Flag: %.2X\n", cartridge_header->sgb_flag);
    printf("Cartridge Type: %.2X\n", cartridge_header->cartridge_type);
    printf("ROM Size: %.2X\n", cartridge_header->rom_size);
    printf("RAM Size: %.2X\n", cartridge_header->ram_size);
    printf("Destination Code: %.2X\n", cartridge_header->destination_code);
    printf("Old Licensee Code: %.2X\n", cartridge_header->old_licensee_code);
    printf("Mask ROM Version Number: %.2X\n", cartridge_header->mask_rom_version_number);
    printf("Header Checksum: %.2X\n", cartridge_header->header_checksum);
    printf("Global Checksum: %.2X%.2X\n", cartridge_header->global_checksum_hi, cartridge_header->global_checksum_lo);
}

bool cart_load(const char *filename)
{
    FILE *file = fopen(filename, "rb"); // open file in read binary mode
    if (file)
    {
        fseek(file, 0, SEEK_END); // moves read position to end of file to get size
        long size = ftell(file);  // get current position (size thanks to above)
        fseek(file, 0, SEEK_SET); // back to start of file

        fread(cartridge_data, 1, MAX_CART_SIZE, file); // reads 1 byte each from file into cartridge data
        fclose(file);
        printf("ROM %s loaded, size: %ld bytes\n", filename, size);
        return true;
    }

    printf("Failed to load file %s\n", filename);
    return false;
}