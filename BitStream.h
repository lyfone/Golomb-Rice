//
// Created by zzhfeng on 2018/3/1.
//

#ifndef GOLOMB_RICE_BITSTREAM_H
#define GOLOMB_RICE_BITSTREAM_H

#pragma once
#include <bitset>
#include <cstdint>
#include <math.h>

#define BIT_LENGTH 64 //BitBuffer 的大小

//BitBuffer结构体
struct BitBuffer{
    std::bitset<BIT_LENGTH> data;   // bit缓存
    int pos;                        //当前bit位置
    int count;                      //bit个数

    //  构造函数
    BitBuffer();

    //获取一个bit
    bool getBit();
    //写入一个bit
    void putBit(bool bit);

    //获取一个byte
    uint8_t getByte();

    //写入一个Byte
    void putByte(uint8_t byte);
};

//ByteBuffer结构体
struct ByteBuffer{
    uint8_t *data;      //byte指针
    uint64_t pos;       //当前的byte位置
    uint64_t length;    //ByteBuffer的数据长度

    uint64_t total_length; //编码写入时ByteBuffer中已有的总字节数

    //构造函数
    ByteBuffer();

    //获取一个byte
    uint8_t getByte();

    //写入一个byte
    void putByte(uint8_t byte);

    //设置byte数组
    void setBufferData(uint8_t *buffer, int length);

    //重置byte数组
    void reset();
};

/*
 *   BitOutputStream类  bit输出流，用于存储编码好的数据，内部有两个缓冲区 bitBuffer，byteBuffer
 *   编码数据时，往bitBuffer中存，当满足一个byte时，从BitBuffer中取出放入ByteBuffer中
*/
class BitOutputStream
{
    ;
public:
    // 写入一个bit
    void putBit(bool bit);

    // 写入多个相同的bit
    void putBit(bool bit, uint64_t num);

    // 设置buffer
    void setBuffer(uint8_t *buffer, int len);
    //重置buffer
    void resetBuffer();

    //当前写入的字节数
    uint64_t get_total_length();

    //buffer空闲的空间
    uint64_t free_length();

    //将bit缓冲区内的数据全部刷新到byte字节缓冲区
    bool flush_bits_to_bytes();

private:
    BitBuffer bits;     //编码时的bit缓冲区
    ByteBuffer bytes;   //编码时的byte缓冲区
};

/*
 *   BitInputStream类 Bit输入流，用于读取缓冲区中的编码好的数据，进行解码。
 *   最开始的数据放在ByteBuffer中，读取时，取出一个Byte放入bitBuffer中，
 *   依次读取每个bit，读取完后，重复操作，直到解码完成。
*/
class BitInputStream
{
public:
    // 读取一个bit
    bool getBit();

    // 读取len长度的数据流写入解码的ByteBuffer中
    void setBuffer(uint8_t *buffer, int len);

private:
    BitBuffer bits;     //解码时的bit缓冲区
    ByteBuffer bytes;   //解码时的byte缓冲区
};

#endif //GOLOMB_RICE_BITSTREAM_H
