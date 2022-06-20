//
// Created by XPS on 2022/6/20.
//

#ifndef LTE_LINK_SIM_TURBOCODE_HPP
#define LTE_LINK_SIM_TURBOCODE_HPP

#include "public.h"

#include <deque>

#include "TurboCodeParams.hpp"

namespace turbocode {
    //turbo交织
    static void TurboEncodeInterlever(VecUint8& bit_seq){
        uint32_t n = bit_seq.size();
        uint32_t ind = turboparams::getInternalInterleaverParams(n);
        const uint32_t f1 = turboparams::getInternalInterleaverParams(ind-1,1);
        const uint32_t f2 = turboparams::getInternalInterleaverParams(ind-1,2);

        //计算交织坐标
        VecUint32 index_des;
        for (int i = 0; i < n; ++i) {
            index_des.push_back((f1*i+f2*i*i) % n);
        }

        //执行交织
        VecUint8 buff;
        buff.resize(n);
        for (int i = 0; i < n; ++i) {
            buff[i] = bit_seq[index_des[i]];
        }

        //输出序列
        bit_seq.clear();
        bit_seq.assign(buff.begin(),buff.end());

    }
    // Turbo 编码
    static VecUint8 Encode(const VecUint8& bit_seq){

        //初始化两个移位寄存器
        uint8_t reg_1_next_bit;
        uint8_t reg_2_next_bit;
        std::deque<Uint8> reg_1(3,0);
        std::deque<Uint8> reg_2(3,0);

        //buff --
        uint8_t out_1_bit;
        uint8_t out_2_bit;
        uint8_t out_3_bit;
        uint8_t out_4_bit; //xk_prime
        VecUint8 out_1; //xk
        VecUint8 out_2; //zk
        VecUint8 out_3; //zk_prime
        MtxUint8 tail_bit; //[xk/zk/zk_prime/xk_prime][4]

        //交织
        VecUint8 bit_seq_inl;
        bit_seq_inl.assign(bit_seq.begin(),bit_seq.end());
        TurboEncodeInterlever(bit_seq_inl);


        //执行编码
        for (int i = 0; i < bit_seq.size(); ++i) {

            //计算第一个编码器输出
            //xk
            out_1_bit = bit_seq[i];
            out_1.push_back(out_1_bit);

            //zk
            reg_1_next_bit = (reg_1[1]+reg_1[2]+out_1_bit)%2;
            out_2_bit = (reg_1_next_bit + reg_1[0] + reg_1[2])%2;
            out_2.push_back(out_2_bit);

            //更新寄存器
            reg_1.pop_back();
            reg_1.push_front(reg_1_next_bit);

            //计算第二个编码器输出
            //zk_prime
            reg_2_next_bit = (reg_2[1]+reg_2[2]+bit_seq_inl[i])%2;
            out_3_bit = (reg_2_next_bit + reg_2[0] + reg_2[2])%2;
            out_3.push_back(out_3_bit);

            //更新寄存器
            reg_2.pop_back();
            reg_2.push_front(reg_2_next_bit);
        }

        //计算尾bit
        tail_bit.resize(4);
        for (int i = 0; i < 3; ++i) {
            //计算第一个编码器输出
            //xk
            out_1_bit = (reg_1[1]+reg_1[2])%2;
            tail_bit[0].push_back(out_1_bit);

            //zk
            reg_1_next_bit = (reg_1[1]+reg_1[2]+out_1_bit)%2;
            out_2_bit = (reg_1_next_bit + reg_1[0] + reg_1[2])%2;
            tail_bit[1].push_back(out_2_bit);

            //更新寄存器
            reg_1.pop_back();
            reg_1.push_front(reg_1_next_bit);

            //计算第二个编码器输出
            //zk_prime
            reg_2_next_bit = (reg_2[1]+reg_2[2]+reg_2[1]+reg_2[2])%2;
            out_3_bit = (reg_2_next_bit + reg_2[0] + reg_2[2])%2;
            tail_bit[2].push_back(out_3_bit);

            //xk_prime
            out_4_bit = (reg_2[1]+reg_2[2])%2;
            tail_bit[3].push_back(out_4_bit);

            //更新寄存器
            reg_2.pop_back();
            reg_2.push_front(reg_2_next_bit);
        }

        //将尾bit添加至out序列中 36.212 5.1.3.2.2
        out_1.push_back(tail_bit[0][0]);
        out_1.push_back(tail_bit[1][1]);
        out_1.push_back(tail_bit[3][0]);
        out_1.push_back(tail_bit[2][1]);

        out_2.push_back(tail_bit[1][0]);
        out_2.push_back(tail_bit[0][2]);
        out_2.push_back(tail_bit[2][0]);
        out_2.push_back(tail_bit[3][2]);

        out_3.push_back(tail_bit[0][1]);
        out_3.push_back(tail_bit[1][2]);
        out_3.push_back(tail_bit[3][1]);
        out_3.push_back(tail_bit[2][2]);

        //输出编码结果
        VecUint8 out_;
        out_.insert(out_.end(),out_1.begin(),out_1.end());
        out_.insert(out_.end(),out_2.begin(),out_2.end());
        out_.insert(out_.end(),out_3.begin(),out_3.end());
        return out_;

    }
}

#endif //LTE_LINK_SIM_TURBOCODE_HPP
