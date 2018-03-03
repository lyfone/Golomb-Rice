//
// Created by zzhfeng on 2018/3/1.
//

#include "BitStream.h"


/*
*   BitBuffer
*/

//初始化构韩函数
BitBuffer::BitBuffer() {
    data.reset();
    pos = 0;
    count = 0;
}

//读取一个bit
bool BitBuffer::getBit() {
    bool bit = data[0];
    count--;
    pos--;
    data >>= 1;
    return bit;
}

//写入一个bit
void BitBuffer::putBit(bool bit) {
    data.set(pos, bit);
    pos++;
    count++;
}

//读一个byte
uint8_t BitBuffer::getByte() {
    uint8_t byte = (uint8_t) (data.to_ulong());
    count -= 8;
    pos -= 8;
    data >>= 8;
    return byte;
}

//写入一个byte
void BitBuffer::putByte(uint8_t byte) {
    uint32_t temp = ((uint32_t) byte) << count;
    data |= temp;
    count += 8;
    pos += 8;
}

/*
*   ByteBuffer
*/
//初始化构造函数
ByteBuffer::ByteBuffer() {
    data = nullptr;
    pos = 0;
    length = 0;
    total_length = 0;
}

//读一个byte
uint8_t ByteBuffer::getByte() {
    auto byte = data[pos];
    pos++;
    return byte;
}

//写一个byte
void ByteBuffer::putByte(uint8_t byte) {
    data[pos] = byte;
    pos++;
    total_length++;
}

//设置bytebuffer
void ByteBuffer::setBufferData(uint8_t *buffer, int leng) {
    data = buffer;
    length = leng;
}

//重置byteBuffer
void ByteBuffer::reset() {
    pos = 0;
    total_length = 0;
}

/*
 *   BitOutputStream bit输出流，用于存储编码好的数据，内部有两个缓冲区 bitBuffer，byteBuffer
 *   编码数据时，往bitBuffer中存，当满足一个byte时，从BitBuffer中取出放入ByteBuffer中
*/

//向bit流中写入一个bit
void BitOutputStream::putBit(bool bit) {
    if (bits.count >= 8 && bytes.pos < bytes.length) {
        auto byte = bits.getByte();
        bytes.putByte(byte);
    }
    bits.putBit(bit);
}

//向bit流中写入多个相同的bit
void BitOutputStream::putBit(bool bit, uint64_t num) {
    for (int i = 0; i < num; i++) {
        putBit(bit);
    }
}

//设置bit流的buffer
void BitOutputStream::setBuffer(uint8_t *buffer, int len) {
    bytes.setBufferData(buffer, len);
}

//重置bit流的buffer
void BitOutputStream::resetBuffer() {
    bytes.reset();
}

//获取buffer中数据的字节数
uint64_t BitOutputStream::get_total_length() {
    return bytes.total_length;
}

//获取buffer中剩余空间大小
uint64_t BitOutputStream::free_length() {
    return (bytes.length - bytes.pos) * 8 - bits.count;
}

//将bit缓冲区中的数据写书byteBuffer
bool BitOutputStream::flush_bits_to_bytes() {
    while (bits.count > 0) {
        auto byte = bits.getByte();
        bytes.putByte(byte);
    }
    auto int_nums = bytes.total_length % 8;
    if (int_nums != 0) {
        for (int i = int_nums; i < 8; i++) {
            bytes.putByte(0x00);
        }
    }
    return true;
}

/*
 *   BitInputStream Bit输入流，用于读取缓冲区中的编码好的数据，进行解码。
 *   最开始的数据放在ByteBuffer中，读取时，取出一个Byte放入bitBuffer中，
 *   依次读取每个bit，读取完后，重复操作，直到解码完成。
*/

//读取一个bit
bool BitInputStream::getBit() {
    bool bit;
    if (bits.count <= 0) {
        auto byte = bytes.getByte();
        bits.putByte(byte);
    }
    bit = bits.getBit();
    return bit;
}

//设置buffer
void BitInputStream::setBuffer(uint8_t *buffer, int length) {
    bytes.setBufferData(buffer, length);
}

