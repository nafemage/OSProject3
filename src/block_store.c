#include <stdio.h>
#include <stdint.h>
#include "bitmap.h"
#include "block_store.h"
// include more if you need

// You might find this handy.  I put it around unused parameters, but you should
// remove it before you submit. Just allows things to compile initially.
#define UNUSED(x) (void)(x)

//struct for block_store
typedef struct block_store {
    bitmap_t* bitmap;  //Creates a bitmap to show which blocks are free and not free
    uint8_t* data_blocks;  //The pointer to the data_blocks
} block_store_t;

//Creates a block store
block_store_t* block_store_create() {
   
    block_store_t* bs = calloc(1, sizeof(block_store_t)); //Allocates memory for all the block data
    //Return null if unable to allocate blocks
    if (!bs) { 
        perror("Failed to allocate block_store");
        return NULL;
    }


    size_t total_data_size = BLOCK_STORE_NUM_BYTES; // Total bytes for all blocks



    bs->data_blocks = calloc(total_data_size, 1); //Allocates data_blocks in block_store 
    if (!bs->data_blocks) { //If allocation failed
        perror("Failed to allocate data blocks");
        free(bs); //Free the memory that was allocated
        return NULL;
    }

    // Calculates the starting index of the bitmap
    size_t bitmap_byte_index = BITMAP_START_BLOCK * BLOCK_SIZE_BYTES;
    

    // Create an overlay bitmap starting at BITMAP_START_BLOCK within the data blocks
    bs->bitmap = bitmap_overlay(BITMAP_SIZE_BITS, bs->data_blocks + bitmap_byte_index);
    if (!bs->bitmap) {
        perror("Failed to create bitmap overlay");
        free(bs->data_blocks);
        free(bs);
        return NULL;
    }

    // Mark the blocks used by the bitmap as allocated
    for (size_t i = 0; i < BITMAP_NUM_BLOCKS; ++i) {
        size_t block_id = BITMAP_START_BLOCK + i;
        if (!block_store_request(bs, block_id)) {
            perror("Failed to allocate block for bitmap");
            bitmap_destroy(bs->bitmap);
            free(bs->data_blocks);
            free(bs);
            return NULL;
        }
    }

    return bs;
}
void block_store_destroy(block_store_t* const bs) {
    if (bs) {
        // Free the data blocks
        if (bs->data_blocks) {
            free(bs->data_blocks);
            bs->data_blocks = NULL;  // Nullify the pointer after freeing
        }

        // Free the block store structure itself
        free(bs);
    }
}
size_t block_store_allocate(block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

bool block_store_request(block_store_t *const bs, const size_t block_id)
{
    UNUSED(bs);
    UNUSED(block_id);
    return false;
}

void block_store_release(block_store_t *const bs, const size_t block_id)
{
    UNUSED(bs);
    UNUSED(block_id);
}

size_t block_store_get_used_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_free_blocks(const block_store_t *const bs)
{
    UNUSED(bs);
    return 0;
}

size_t block_store_get_total_blocks()
{
    return 0;
}

size_t block_store_read(const block_store_t *const bs, const size_t block_id, void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

size_t block_store_write(block_store_t *const bs, const size_t block_id, const void *buffer)
{
    UNUSED(bs);
    UNUSED(block_id);
    UNUSED(buffer);
    return 0;
}

block_store_t *block_store_deserialize(const char *const filename)
{
    UNUSED(filename);
    return NULL;
}

size_t block_store_serialize(const block_store_t *const bs, const char *const filename)
{
    UNUSED(bs);
    UNUSED(filename);
    return 0;
}