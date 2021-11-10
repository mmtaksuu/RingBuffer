/**
 * @file    : ring_buffer project file
 * @author  : MEHMET AKSU
 * @note    : mmtaksu.25@gmail.com
 * @date    : 09 / Kasım / 2021
 * @code    : ring_buffer.c file
 * @details : 
 */


#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "ring_buffer.h"

void RingBuffer_Init(RingBuffer_t* instance)
{
    instance->oku_idx = 0;
    instance->yaz_idx = 0;
    instance->n_total_bytes = BUFFER_SIZE;
    instance->n_available_bytes = 0;
    memset(instance->buff, 0, sizeof(*instance->buff)*BUFFER_SIZE);
}

RingBuffer_t* RingBuffer_Create(uint32_t capacity)
{
    RingBuffer_t* instance = (RingBuffer_t*) malloc(sizeof(*instance->buff)*capacity);
    assert(instance);

    instance->oku_idx = 0;
    instance->yaz_idx = 0;
    instance->n_total_bytes = capacity;
    instance->n_available_bytes = 0;
    memset(instance->buff, 0, sizeof(*instance->buff)*capacity);

    return instance;
}

void RingBuffer_Destroy(RingBuffer_t* instance)
{
    if (instance)
        free((void*)instance);
}

void RingBuffer_MakeEmpty(RingBuffer_t* instance)
{
    RingBuffer_Init(instance);
}

int  RingBuffer_IsEmpty(const RingBuffer_t* instance)
{
    if (instance->n_available_bytes > 0)
        return 0;
    else
        return 1;
}

int  RingBuffer_IsFull(const RingBuffer_t* instance)
{
    if (instance->n_available_bytes >= instance->n_total_bytes)
        return 1;
    else
        return 0;
}

uint32_t RingBuffer_Size(const RingBuffer_t* instance)
{
    return instance->n_available_bytes;
}

uint32_t RingBuffer_Capacity(const RingBuffer_t* instance)
{
    return instance->n_total_bytes;
}

void RingBuffer_WriteByte(RingBuffer_t* instance, uint8_t data)
{
    instance->buff[instance->yaz_idx++] = data;

    if (instance->yaz_idx >= instance->n_total_bytes)
        instance->yaz_idx = 0;

    if (!RingBuffer_IsFull(instance))
    {
        instance->n_available_bytes++;
    }
    else
    {
        instance->oku_idx++;

        if (instance->oku_idx >= instance->n_total_bytes)
            instance->oku_idx = 0;
    }
}

int  RingBuffer_ReadByte(RingBuffer_t* instance, uint8_t* p_data)
{
    int result = 0;

    if (!RingBuffer_IsEmpty(instance))
    {
        *p_data = instance->buff[instance->oku_idx];
        instance->oku_idx++;
        instance->n_available_bytes--;

        if (instance->oku_idx >= instance->n_total_bytes)
            instance->oku_idx = 0;

        result = 1;
    }

    return result;
}

void RingBuffer_WriteSomeBytes(RingBuffer_t* instance, const uint8_t* p_data, uint16_t size)
{
    while (size)
    {
        RingBuffer_WriteByte(instance, *p_data);
        p_data++;
        size--;
    }
}

int  RingBuffer_ReadSomeBytes(RingBuffer_t* instance, uint8_t* p_data)
{
    int n_bytes = 0;

    while (instance->n_available_bytes > 0)
    {
        n_bytes += RingBuffer_ReadByte(instance, p_data);
        p_data++;
    }

    return n_bytes;
}



