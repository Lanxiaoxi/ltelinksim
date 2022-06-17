//
// Created by XPS on 2022/6/17.
// 本文件主要包含 枚举定义 全局宏定义 类型定义等通用全局定义
//


#ifndef LTE_LINK_SIM_PUBLIC_H
#define LTE_LINK_SIM_PUBLIC_H

#include <iostream>
#include <memory>

typedef int Int32;
typedef unsigned int Uint32;
typedef char Int8;
typedef unsigned char Uint8;



//各种枚举类
//循环前缀类型
typedef enum { NORMAL = 1,EXTENDED = 0}CpType;
//PHICH_RESOURCE
typedef enum {OneSixth = 0,HALF = 1,ONE = 2,TWO = 3}PhichResource;;
//调制方式
typedef enum {BPSK = 0,QPSK = 1,QAM_16 = 2,QAM_64 = 3,QAM_256 = 4,QAM_1024 = 5}ModType;
//资源分配类型
typedef enum {RA_TYPE0 = 0,RA_TYPE1,RA_TYPE2}ResourceAllocType;
//传输模式
typedef enum {TM_1 = 0,TM_2 = 1,TM_3 = 2,TM_4 = 3,TM_5 = 4,TM_6 = 5,TM_7 = 6,TM_8 = 7,TM_9 = 8}TransmissionMode;
//传输策略
typedef enum {TRANSMIT_DIVERSITY = 0,SPATIAL_MULTIPLEX_CDD,SPATIAL_MULTIPLEX,SPATIAL_MULTIPLEX_DMRS,SINGLE_PORT}TransmissionScheme;
//CRC type
typedef enum {CRC8,CRC16,CRC24A,CRC24B}CRCType;


#endif //LTE_LINK_SIM_PUBLIC_H
