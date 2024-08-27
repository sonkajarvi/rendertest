#ifndef VECTOR_H
#define VECTOR_H

/*
 * vector_is_empty
 * vector_length
 * vector_capacity
 * vector_front_ref
 * vector_back_ref
 *
 * vector_push
 * vector_pop
 * vector_insert
 * vector_remove
 * vector_push_range
 * vector_reserve
 * vector_resize (todo)
 * vector_shrink (todo)
 * vector_clear
 * vector_free
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VECTOR_DEFAULT_CAPACITY 2

/**
 * @brief check if a vector is empty
 *
 * @param v vector
 *
 * @note returns 1, if v is null
 */
#define vector_is_empty(v)  ((v) ? vector_length((v)) == 0 : 1)

/**
 * @brief get length of a vector
 *
 * @param v vector
 *
 * @note returns 0, if v is null
 */
#define vector_length(v)    ((v) ? (size_t)__vector_header((v))->length : (size_t)0)

/**
 * @brief get capacity of a vector
 *
 * @param v vector
 *
 * @note returns 0, if v is null
 */
#define vector_capacity(v)  ((v) ? __vector_header((v))->capacity : 0)

/**
 * @brief get a reference to first element of a vector
 *
 * @param v vector
 *
 * @note returns null, if v is null (this probably isn't needed)
 */
#define vector_front_ref(v)  (v)

/**
 * @brief get a reference to last element of a vector
 *
 * @param v vector
 *
 * @note returns null, if v is null
 */
#define vector_back_ref(v)   ((v) ? (v) + vector_length((v)) - 1 : NULL)


/**
 * @brief push a value to a vector
 *
 * @param v vector
 * @param value value
 */
#define vector_push(v, value) \
    (__vector_grow((v), 1), (v)[__vector_header((v))->length++] = (value))

/**
 * @brief pop last value from a vector
 *
 * @param v vector
 *
 * @note does nothing, if vector is empty/null
 */
#define vector_pop(v) \
    (vector_length((v)) > 0 ? __vector_header((v))->length-- : 0)

/**
 * @brief insert a value at index in a vector
 *
 * @param v vector
 * @param index index
 * @param value value
 *
 * @note does a push, if index is the back
 */
#define vector_insert(v, index, value) \
    ((index) == vector_length((v)) \
        ? vector_push((v), (value)) \
        : (index) < vector_length((v)) \
            ? (__vector_grow((v), 1), \
                memmove((v) + (index) + 1, (v) + (index), \
                    (__vector_header((v))->length++ - (index)) * sizeof(*(v))), \
                (v)[(index)] = (value)) \
            : 0)

/**
 * @brief remove a value at index from a vector
 *
 * @param v vector
 * @param index index
 *
 * @note does a pop, if index is the back
 */
#define vector_remove(v, index) \
    ((index) == vector_length((v)) - 1 \
        ? vector_pop((v)) \
        : (index) < vector_length((v)) - 1 \
            ? (memmove((v) + (index), (v) + (index) + 1, \
                (__vector_header((v))->length-- - (index)) * sizeof(*(v))), 0) \
            : 0)

/**
 * @brief push a range of values to a vector
 *
 * @param v vector
 * @param ptr array
 * @param len array length
 *
 * @note does nothing, if ptr is null or len is less than 1
 */
#define vector_push_range(v, ptr, len) \
    ((ptr) && (len) > 0 \
        ? __vector_grow((v), (len)), \
            memmove((v) + vector_length((v)), (ptr), (len) * sizeof(*(ptr))), \
            __vector_header((v))->length += (len) \
        : 0)

/**
 * @brief push a value to a vector using memmove
 *
 * @param v vector
 * @param value value
 */
#define vector_push_copy(v, value) \
    (__vector_grow((v), 1), \
        memmove((v) + vector_length((v)), &(value), sizeof((value))), \
        __vector_header((v))->length++)

/**
 * @brief reserve capacity for a vector
 *
 * @param v vector
 * @param amount amount to reserve
 *
 * @note does nothing, if amount is less than vector capacity
 */
#define vector_reserve(v, amount) \
    ((amount) > vector_capacity((v)) \
        ? (v) = __vector_realloc((v), (amount), sizeof(*(v))) \
        : 0)

/**
 * @brief clear a vector
 *
 * @param v
 *
 * @note does nothing, if v is null
 */
#define vector_clear(v) \
    ((v) ? __vector_header((v))->length = 0 : 0)

/**
 * @brief free a vector
 *
 * @param v vector
 *
 * @note does nothing, if v is null
 */
#define vector_free(v) \
    ((v) ? (free(__vector_header((v))), (v) = NULL) : 0)


#define __vector_header(v) ((StVectorHeader *)(v) - 1)

#define __vector_dbg(v) \
    printf("(%lld %lld)\n", vector_length((v)), vector_capacity((v)))

#define __vector_dbg2(v, fmt) \
    do { \
        for (size_t i = 0; i < vector_length((v)); i++) \
            printf(fmt" ", v[i]); \
        printf("\n"); \
    } while (0)

#define __vector_f(x) ((x) + ((x) >> 1) + ((x) >> 3))
// #define __vector_f(x) (x * 2)

#define __vector_grow(v, add_len) \
    (!(v) || vector_capacity((v)) < vector_length((v)) + (add_len) \
        ? (v) = __vector_realloc((v), __vector_calc_cap((v), (add_len)), sizeof(*(v))) \
        : 0)

typedef struct StVectorHeader
{
    size_t length;
    size_t capacity;
} StVectorHeader;

size_t __vector_calc_cap(void *, const size_t);
void *__vector_realloc(void *, const size_t, const size_t);

#endif // VECTOR_H
