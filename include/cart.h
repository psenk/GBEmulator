#pragma once

#include <stdint.h>
#include <stdbool.h>

const int MAX_CART_SIZE = 1024 * 1024;        // largest possible ROM
extern uint8_t cartridge_data[MAX_CART_SIZE]; // game ROM
extern bool cartridge_loaded;

typedef struct cart_header_struct
{
    uint8_t entry_point[4];       // boot ROM jumps here
    uint8_t nintendo_logo[48];    // bitmap image displayed when powered on
    uint8_t title[15];            // title of game
    uint8_t cgb_flag;             // color game boy mode
    uint8_t new_licensee_code[2]; // game publisher
    uint8_t sgb_flag;             // super game boy mode
    uint8_t cartridge_type;       // hardware present
    uint8_t rom_size;
    uint8_t ram_size;
    uint8_t destination_code;        // where game intended to be sold
    uint8_t old_licensee_code;       // game publisher, older carts
    uint8_t mask_rom_version_number; // version of game
    uint8_t header_checksum;
    uint8_t global_checksum_hi; // big endian
    uint8_t global_checksum_lo;
} cart_header_struct;

extern cart_header_struct *cartridge_header;

bool cart_open_file();
void cart_print_info();
bool cart_load(const char *filename);