//
// Created by zzhfeng on 2018/3/2.
//

#ifndef GOLOMB_RICE_READANDWRITEFILE_H
#define GOLOMB_RICE_READANDWRITEFILE_H

#include <fstream>
#include <string>

using namespace std;

/**
 * 从文件中读取编码后的压缩数据到缓冲区buffer中
 */
class ReadFromFile {
public:
    //构造函数
    ReadFromFile(string file_name);

    //读取函数
    bool read(uint8_t *buffer, uint64_t len);

private:
    //私有读取函数
    void Read(uint8_t *buffer, uint64_t len);

    //文件名字
    string file_name;
};

/**
 * 将缓冲区buffer中的编码数据写到文件当中
 */
class WriteToFile {
public:
    //构造函数
    WriteToFile(string file_name);

    //写函数
    bool write(uint8_t *buffer, uint64_t len);

private:
    //写函数
    void Write(uint8_t *buffer, uint64_t len);

    //文件名
    string file_name;
};

//读取类构造函数
ReadFromFile::ReadFromFile(string filename) {
    file_name = filename;
}

//读函数
bool ReadFromFile::read(uint8_t *buffer, uint64_t len) {
    Read(buffer, len);
    return true;
}

//读取函数
void ReadFromFile::Read(uint8_t *buffer, uint64_t len) {
    ifstream in;
    in.open(file_name);
    for (int i = 0; i < len; i++) {
        in >> buffer[i];
        if(!in)
            break;
    }
    in.close();
}

//写类构造函数
WriteToFile::WriteToFile(string filename) {
    file_name = filename;
}

//写函数
bool WriteToFile::write(uint8_t *buffer, uint64_t len) {
    Write(buffer, len);
    return true;
}

//写函数
void WriteToFile::Write(uint8_t *buffer, uint64_t len) {
    ofstream out;
    out.open(file_name);
    for (int i = 0; i < len; i++){
        out << buffer[i];
    }
    out.flush();
    out.close();
}

#endif //GOLOMB_RICE_READANDWRITEFILE_H
