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

void cart_print_info()
{
}

bool cart_load(const char *filename)
{
}