//
// Created by zzhfeng on 2018/3/2.
//

#ifndef GOLOMB_RICE_GOLOMBENCODER_H
#define GOLOMB_RICE_GOLOMBENCODER_H

#pragma once
#include "BitStream.h"

/**
 * 编码器
 */
class GolombEncoder{
public:
    //构造函数
    GolombEncoder(uint64_t parameter);

    //编码num，并判断此时byte缓冲区是否填满
    bool encode(uint64_t num);

    //结束编码，将所有数据全部写去到byteBuffer中
    bool end_encode();

    //处理玩buffer中的数据后重置buffer（写文件等）
    void resetBuffer();

    //设置buffer
    void setBuffer(uint8_t *buffer, int len);

    //返回buffer中已存的字节数
    uint64_t get_total_length(){
        return bitStream.get_total_length();
    }

private:
    //编码器函数
    uint64_t Encoder(uint64_t num);

    //BitOutputStream类
    BitOutputStream bitStream;

    //编码参数，同解码参数相同
    uint64_t parameter;

    //编码参数的阶数 数值上等于log(parameter)/log(2)
    uint64_t k;
};
/**
 * 构造函数
 * @param para 编码参数
 */
GolombEncoder::GolombEncoder(uint64_t para){
    parameter = para;
    k = log(parameter) / log(2);
}

/**
 * 编码操作
 * @param num
 * @return 返回缓冲区是否已满
 */
bool GolombEncoder::encode(uint64_t num){
    uint64_t free_len = bitStream.free_length();
    uint64_t code_len = Encoder(num);
    return free_len >= code_len;
}

/**
 * 结束编码，将所有数据全部写入到byteBuffer中
 * @return
 */
bool GolombEncoder::end_encode(){
    bitStream.flush_bits_to_bytes();
    return true;
}

/**
 * 重置Buffer
 */
void GolombEncoder::resetBuffer(){
    bitStream.resetBuffer();
}

/**
 * 设置编码数据存储的缓冲区
 * @param buffer
 * @param len
 */
void GolombEncoder::setBuffer(uint8_t *buffer, int len){
    bitStream.setBuffer(buffer, len);
}

/**
 * 编码器函数
 * @param num 要编码的数值
 * @return 返回编码后的长度
 */
uint64_t GolombEncoder::Encoder(uint64_t num){
    uint64_t q = num >> k;
    uint64_t r = num & (parameter - 1);
    auto code_len = q + 1 + k;
    bitStream.putBit(1, q);
    bitStream.putBit(0);

    for(int i = 0; i < k; i++){
        bool bit = (bool)(r & 0x01);
        bitStream.putBit(bit);
        r >>= 1;
    }
    return code_len;
}

#endif //GOLOMB_RICE_GOLOMBENCODER_H
