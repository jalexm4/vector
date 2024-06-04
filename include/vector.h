#ifndef VECTOR_H
#define VECTOR_H

#include <stdio.h>


typedef struct
{
    void **data;
    size_t size;
    size_t capacity;
} Vector;


Vector *vector_create(size_t size);
void vector_push_back(Vector *vector, void *data);
void *vector_get(Vector *vector, size_t index);
void vector_remove(Vector *vector, size_t index);
void vector_resize(Vector *vector);
void vector_free(Vector *vector);

#endif // VECTOR_H
