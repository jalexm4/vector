//
// C implementation of the C++ vector datastructure.
//

#include <stdlib.h>
#include <string.h>

#include <vector/vector.h>


// Creates a vector datastructure of (size) elements of (datatype_size) bytes. Resizes if capacity reached.
Vector *vector_create(size_t size, size_t datatype_size)
{
    // Allocate memory for the Vector struct.
    Vector *vector = malloc(sizeof(Vector));
    if (!vector)
    {
        return NULL;
    }

    // Vector currently contains 0 elements and can hold up to (size) before a resize operation.
    vector->size = 0;
    vector->capacity = size;
    vector->datatype_size = datatype_size;

    // Allocate memory for to store (size) of a datatype.
    vector->data = malloc(vector->datatype_size * vector->capacity);
    if (!vector->data)
    {
        free(vector);
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

    // Byte offset to write (data) bytes into.
    void *dest = (char *) vector->data + (vector->size * vector->datatype_size);

    // Write data into vector
    memcpy(dest, data, vector->datatype_size);

    vector->size++;

    return;
}

// Get a pointer to an element in the vector
void *vector_get(Vector *vector, size_t index)
{
    // Index is out of bounds
    if (index > vector->size)
    {
        return NULL;
    }

    // Pointer to byte offset of an element in the vector
    void *data = (char *) vector->data + (index * vector->datatype_size);

    return data;
}


void vector_remove(Vector *vector, size_t index)
{
    // Index is out of bounds
    if (index > vector->size)
    {
        return;
    }

    // Byte offset of element to be removed
    void *target = (char *) vector->data + (index * vector->datatype_size);

    // Byte offset of the next element after the one to be removed
    void *next = (char *) target + vector->datatype_size;

    // Bytes to be shifted
    size_t bytes = (vector->size - index - 1) * vector->datatype_size;

    // Shift elements
    memmove(target, next, bytes);

    vector->size--;

    return;
}

void vector_resize(Vector *vector)
{
    // Double space available
    vector->capacity *= 2;

    // Allocate concurrent memory for new capacity
    vector->data = realloc(vector->data, vector->datatype_size * vector->capacity);

    return;
}

void vector_free(Vector *vector)
{
    free(vector->data);
    free(vector);

    return;
}
