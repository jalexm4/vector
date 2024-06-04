//
// C implementation of the C++ vector datastructure.
// Currently uses an array of void pointers.
//

#include <stdio.h>
#include <stdlib.h>

#include <vector/vector.h>


// Creates a vector that can hold (size) elements. Will resize itself if needed.
Vector *vector_create(size_t size)
{
    // Allocate memory for the Vector struct.
    Vector *vector = malloc(sizeof(Vector));
    if (!vector)
    {
        printf("[*] Unable to allocate %lu bytes\n", sizeof(Vector));
        return NULL;
    }

    // Vector currently contains 0 elements and can hold up to (size) before a resize operation.
    vector->size = 0;
    vector->capacity = size;

    // Allocate memory for (size) pointers.
    vector->data = malloc(sizeof(void *) * vector->capacity);
    if (!vector->data)
    {
        printf("[*] Unable to allocate %lu bytes\n", sizeof(void *) * vector->capacity);
        return NULL;
    }

    return vector;
}

// Push a void pointer onto the vector
void vector_push_back(Vector *vector, void *data)
{
    // Resize vector if more space is needed.
    if (vector->size == vector->capacity)
    {
        vector_resize(vector);
    }

    // Storing pointer
    vector->data[vector->size] = data;
    vector->size++;

    return;
}

// Get a pointer to an element in the vector
void *vector_get(Vector *vector, size_t index)
{
    // Index is out of bounds
    if (index >= vector->size)
    {
        return NULL;
    }

    return vector->data[index];
}


void vector_remove(Vector *vector, size_t index)
{
    // Index is out of bounds
    if (index >= vector->size)
    {
        return;
    }

    // Deallocate whatever the pointer is storing
    free(vector->data[index]);

    // Shift the vector to align properly
    for (size_t i = index, n = vector->size - 1; i < n; i++)
    {
        vector->data[i] = vector->data[i + 1];
    }

    vector->size--;

    return;
}

void vector_resize(Vector *vector)
{
    // Double space available
    vector->capacity *= 2;

    // Allocate memory for new capacity
    vector->data = realloc(vector->data, sizeof(void *) * vector->capacity);
    if (vector->data == NULL)
    {
        printf("[*] Unable to allocate %lu bytes\n", sizeof(void *) * vector->capacity);
    }

    return;
}

void vector_free(Vector *vector)
{
    // Deallocate all elements
    for (size_t i = 0, n = vector->size; i < n; i++)
    {
        free(vector->data[i]);
    }

    // Dellocate pointer to pointer array and Vector struct
    free(vector->data);
    free(vector);

    return;
}
