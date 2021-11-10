/**
 * @file    : ring_buffer project file
 * @author  : MEHMET AKSU
 * @note    : mmtaksu.25@gmail.com
 * @date    : 09 / Kasım / 2021
 * @code    : ring_buffer.h file
 * @details : 
 */


#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#define     BUFFER_SIZE     2048

typedef struct {
    uint32_t yaz_idx;
    uint32_t oku_idx;
    uint32_t n_available_bytes;
    uint32_t n_total_bytes;
    uint8_t  buff[BUFFER_SIZE];
    uint8_t* d_buff;
}RingBuffer_t;

void RingBuffer_Init(RingBuffer_t* instance);
RingBuffer_t* RingBuffer_Create(uint32_t capacity);
void RingBuffer_Destroy(RingBuffer_t* instance);
void RingBuffer_MakeEmpty(RingBuffer_t* instance);
int  RingBuffer_IsEmpty(const RingBuffer_t* instance);
int  RingBuffer_IsFull(const RingBuffer_t* instance);
uint32_t RingBuffer_Size(const RingBuffer_t* instance);
uint32_t RingBuffer_Capacity(const RingBuffer_t* instance);
void RingBuffer_WriteByte(RingBuffer_t* instance, uint8_t data);
int  RingBuffer_ReadByte(RingBuffer_t* instance, uint8_t* p_data);
void RingBuffer_WriteSomeBytes(RingBuffer_t* instance, const uint8_t* p_data, uint16_t size);
int  RingBuffer_ReadSomeBytes(RingBuffer_t* instance, uint8_t* p_data);


#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /* RING_BUFFER_H */