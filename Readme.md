
```c++
#include <iostream>
#include "ring_buffer.h"
#include <random>


int main ()
{
    std::mt19937 eng{std::random_device{}()};
    std::uniform_int_distribution<uint8_t> dist{0, 255};

    RingBuffer_t ring_buffer{};
    RingBuffer_Init(&ring_buffer);

    for (int i = 0; i < BUFFER_SIZE * 2; ++i)
    {
        auto ch = dist(eng);
        std::cout << "Available Bytes : " << ring_buffer.n_available_bytes << std::endl;
        std::cout << "Eklenen Byte    : " << (int)ch << std::endl;
        std::cout << "Yazma Indeksi   : " << ring_buffer.yaz_idx << std::endl;
        RingBuffer_WriteByte(&ring_buffer, ch);

        std::cout << "Okuma Indeksi   : " << ring_buffer.oku_idx << std::endl;
        uint8_t data{};
        if (int res = RingBuffer_ReadByte(&ring_buffer, &data); res)
            std::cout << "Okunan Byte     : " << (int )(data) << std::endl;

    }

    return 0;
}
```


```c++
#include <iostream>
#include "ring_buffer.h"
#include <random>

using byte_pair = std::pair<uint16_t, uint8_t*>;

byte_pair generate_rand_buff ()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution<uint8_t> dist{0, 255};
    static std::uniform_int_distribution<uint8_t> size_dist{10, 50};

    auto size = size_dist(eng);
    auto buff = new uint8_t [size]{};

    for (int i = 0; i < size; ++i)
    {
        buff[i] = dist(eng);
    }

    return byte_pair{size, buff};
}


int main ()
{
    RingBuffer_t ring_buffer{};
    RingBuffer_Init(&ring_buffer);

    for (int i = 0; i < 10000; ++i)
    {
        auto bytes = generate_rand_buff();

        RingBuffer_WriteSomeBytes(&ring_buffer, bytes.second, bytes.first);

        delete bytes.second;
    }

    uint8_t data[BUFFER_SIZE]{};
    auto n_bytes = RingBuffer_ReadSomeBytes(&ring_buffer, data);

    return 0;
}

```

```c++
#include <iostream>
#include "ring_buffer.h"
#include <random>

using byte_pair = std::pair<uint16_t, uint8_t*>;

byte_pair generate_rand_buff ()
{
    static std::mt19937 eng{std::random_device{}()};
    static std::uniform_int_distribution<uint8_t> dist{0, 255};
    static std::uniform_int_distribution<uint16_t> size_dist{10, 2048};

    auto size = size_dist(eng);
    auto buff = new uint8_t [size]{};

    for (int i = 0; i < size; ++i)
    {
        buff[i] = dist(eng);
    }

    return byte_pair{size, buff};
}


int main ()
{
    RingBuffer_t* p_ring_buffer = RingBuffer_Create(1024*80);

    for (;;)
    {
        auto bytes = generate_rand_buff();

        RingBuffer_WriteSomeBytes(p_ring_buffer, bytes.second, bytes.first);

        delete bytes.second;

        uint8_t data[BUFFER_SIZE]{};
        auto n_bytes = RingBuffer_ReadSomeBytes(p_ring_buffer, data);
        std::cout << n_bytes << " Byte okundu." << std::endl;
        for (int j = 0; j < n_bytes; ++j)
            std::cout << data[j] << " ";
        std::cout << "\n------------------------------------------------\n" << std::endl;
    }

    return 0;
}

```