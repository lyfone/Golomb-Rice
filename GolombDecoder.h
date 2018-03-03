//
// Created by zzhfeng on 2018/3/2.
//

#ifndef GOLOMB_RICE_GOLOMBDECODER_H
#define GOLOMB_RICE_GOLOMBDECODER_H

#pragma once
#include "BitStream.h"

/**
 * 解码器
 */
class GolombDecoder{
public:
    //构造函数
    GolombDecoder(uint64_t parameter);

    //设置解码数据所在的缓冲区
    void setBuffer(uint8_t *buffer, int num);

    //解码操作
    void decode(uint64_t &num);
private:
    //解码器函数
    uint64_t Decoder();

    //BitInputStream类
    BitInputStream bitStream;

    //解码参数，同编码参数相同
    uint64_t parameter;

    //解码参数的阶数 数值上等于log(parameter)/log(2)
    uint64_t k;
};

/**
 * 构造函数
 * @param para  解码参数
 */
GolombDecoder::GolombDecoder(uint64_t para){
    parameter = para;
    k = (uint64_t)(log(parameter) / log(2));
}

/**
 * 设置解码数据缓冲区
 * @param buffer
 * @param num
 */
void GolombDecoder::setBuffer(uint8_t *buffer, int num){
    bitStream.setBuffer(buffer,num);
}

/**
 * 解码操作
 * @param num 解码得到的数值
 */
void GolombDecoder::decode(uint64_t &num){
    num = Decoder();
}

/**
 * 解码器函数
 * @return 返回解码得到的数值
 */
uint64_t GolombDecoder::Decoder(){
    bool bit;
    uint64_t q = 0;
    bit = bitStream.getBit();
    while(bit){
        q++;
        bit = bitStream.getBit();
    }

    std::bitset<64> bits;
    bits.reset();
    for(int i=0; i < k; i++){
        bit = bitStream.getBit();
        bits.set(i,bit);
    }
    uint64_t num = q * parameter + bits.to_ulong();
    return num;
}

#endif //GOLOMB_RICE_GOLOMBDECODER_H
