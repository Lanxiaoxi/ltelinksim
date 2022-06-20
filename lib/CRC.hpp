//
// Created by XPS on 2022/6/20.
//

#ifndef LTE_LINK_SIM_CRC_HPP
#define LTE_LINK_SIM_CRC_HPP

#include "public.h"
#include <deque>

namespace crc {
    static void Encode(VecUint8& bit_seq, CRCType crc_len){

        const VecUint8 g_seq_8 = {1,1,0,0,1,1,0,1,1};
        const VecUint8 g_seq_16 = {1,0,0,0,1,0,0,0,0,0,0,1,0,0,0,0,1};
        const VecUint8 g_seq_24a = {1,1,0,0,0,0,1,1,0,0,1,0,0,1,1,0,0,1,1,1,1,1,0,1,1};
        const VecUint8 g_seq_24b = {1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,1,1};

        std::deque<Uint8> g_seq;
        std::deque<Uint8> buff;
        uint32_t length;
        buff.assign(bit_seq.begin(),bit_seq.end());
        //选择生成多项式
        switch (crc_len) {
            case CRC8:
                length = 8;
                g_seq.assign(g_seq_8.begin(),g_seq_8.end());
                for (int i = 0; i < 8; ++i) buff.push_back(0);
                break;
            case CRC16:
                length = 16;
                g_seq.assign(g_seq_16.begin(),g_seq_16.end());
                for (int i = 0; i < 16; ++i) buff.push_back(0);
                break;
            case CRC24A:
                length = 24;
                g_seq.assign(g_seq_24a.begin(),g_seq_24a.end());
                for (int i = 0; i < 24; ++i) buff.push_back(0);
                break;
            case CRC24B:
                length = 24;
                g_seq.assign(g_seq_24b.begin(),g_seq_24b.end());
                for (int i = 0; i < 24; ++i) buff.push_back(0);
                break;
            default:
                return;
        }

        while (buff.size() > length)
        {
            //异或
            for (int i = 0; i < g_seq.size(); ++i) {
                buff[i] = g_seq[i] ^ buff[i];
            }
            //更新buff
            while (!buff.front())
            {
                buff.pop_front();
            }
        }

        while (buff.size() < length)
        {
            buff.push_front(0);
        }

        //将CRC附着
        for (int i = 0; i < g_seq.size()-1; ++i) {
            bit_seq.push_back(buff[i]);
        }


    }

}

#endif //LTE_LINK_SIM_CRC_HPP
