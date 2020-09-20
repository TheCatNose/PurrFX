#include "CByteOrder.h"

PurrFX::EByteOrder PurrFX::CByteOrder::get()
{
    union 
    {
        uint32_t a = 1;
        uint8_t  b[4];
    } oMemory;
    
    if (oMemory.b[0] == 1)
        return EByteOrder::LittleEndian;
    else
        return EByteOrder::BigEndian;
}
