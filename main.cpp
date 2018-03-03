//
// Created by zzhfeng on 2018/3/1.
//

#include <iostream>
#include "GolombDecoder.h"
#include "GolombEncoder.h"
#include "ReadAndWriteFile.h"

int main()
{
    uint8_t buffer[1024];
    int m = 8;
    string encode_file = "D://encode.txt";

    //Encode
    GolombEncoder encoder(m);

    encoder.setBuffer(buffer,1024);

    std::cout << "encode 8 !" << std::endl;
    encoder.encode(8);
    std::cout << "encode 24 !" << std::endl;
    encoder.encode(24);
    std::cout << "encode 18 !" << std::endl;
    encoder.encode(18);
    std::cout << "encode 36 !" << std::endl;
    encoder.encode(36);
    std::cout << "encode 91 !" << std::endl;
    encoder.encode(91);

    encoder.end_encode();

    uint64_t len = encoder.get_total_length();
    WriteToFile writeHandler(encode_file);
    writeHandler.write(buffer,len);

    //Decoder
    uint8_t decodeBuffer[1024];
    ReadFromFile readFromFile(encode_file);
    readFromFile.read(decodeBuffer,1024);
    GolombDecoder decoder(m);
    decoder.setBuffer(decodeBuffer,1024);

    uint64_t num;
    decoder.decode(num);
    std::cout << "decode ! output : " << num << std::endl;
    decoder.decode(num);
    std::cout << "decode ! output : " << num << std::endl;
    decoder.decode(num);
    std::cout << "decode ! output : " << num << std::endl;
    decoder.decode(num);
    std::cout << "decode ! output : " << num << std::endl;
    decoder.decode(num);
    std::cout << "decode ! output : " << num << std::endl;

    return 0;
}