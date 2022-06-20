//
// Created by XPS on 2022/6/20.
//

#ifndef LTE_LINK_SIM_CODEBLOCKPROCEDURE_HPP
#define LTE_LINK_SIM_CODEBLOCKPROCEDURE_HPP

#include "public.h"

#include <cmath>

#include "TurboCodeParams.hpp"
namespace codeblock {

    static MtxUint8 CodeblockSegmentation(VecUint8 &transblock_data) {

        //5.1.2	Code block segmentation and code block CRC attachment
//        bit_cube.resize(nof_transblock); // [传输块][码块段][bit]
        MtxUint8 tb_data_after_seg;
        const uint32_t Z = 6144;


            uint32_t B = transblock_data.size();
            uint32_t B_prime = 0; //码块分割并添加CRC之后的总长度
            uint32_t C = 0;       //码块分割后的码块数
            uint32_t C_plus = 0;  //码块长度为K_plus的码块数
            uint32_t C_mius = 0;  //码块长度为K_mius的码块数
            uint32_t K_r = 0;     //码块r的长度
            uint32_t K_plus = 0;  //第一个码块的长度
            uint32_t K_mius = 0;
            uint32_t delta_K = 0;
            uint32_t F = 0; //填充比特的长度
            uint32_t L = 0;

            uint32_t j = 0;

            //计算--码块分割并添加CRC之后的总长度
            //计算--码块分割后的码块数
            if(transblock_data.size() >= Z)
            {
                L = 24;
                C = ceil(B/(Z-24.0));
                B_prime = B + C*24;
            } else{
                C = 1;
                B_prime = B;
                L = 0;
            }

            //计算各个码块的长度
            do {
                K_plus = turboparams::getInternalInterleaverParams(j,0);
                ++j;
            } while (K_plus * C < B_prime);


            //计算不同长度的码块数目
            if(C == 1)
            {
                C_plus = 1;
                K_mius = 0;
                C_mius = 0;
            } else if (C > 1){
                j = 0;
                while (K_mius < K_plus){
                    K_mius = turboparams::getInternalInterleaverParams(j,0);
                    ++j;
                }
                K_mius = turboparams::getInternalInterleaverParams(j-2,0);
                delta_K = K_plus - K_mius;
                C_mius = (C*K_plus-B_prime)/delta_K;
                C_plus = C - C_mius;
            }

            //计算填充bit
            F = C_plus*K_plus + C_mius*K_mius - B_prime;
            tb_data_after_seg.resize(C);
            tb_data_after_seg[0].assign(F,0); //crc = 0 之后>>> 255 -- null

            //执行分割
            uint32_t k = F;
            uint32_t s = 0;
            for (int c = 0; c < C; ++c) {
                //依次处理每个码块
                K_r = c < C_mius ? K_mius : K_plus;
                while (k < K_r - L)
                {
                    tb_data_after_seg[c].push_back(transblock_data[s]);
                    k++;
                    s++;
                }

                //依次为各个码块添加CRC
                if (C > 1){
                    crc::Encode(tb_data_after_seg[c],CRC24B);
                }
                //恢复null元素  --
                for (int f = 0; f < F; ++f) {
                    tb_data_after_seg[0][f] = NULL_ELEM;
                }

                k = 0;

            }
            return tb_data_after_seg;
        }

        //链接
        void CodeblockConcatenation(const MtxUint8 &codeword_before_con,VecUint8 &codeword_data) {
            //依次处理每个码块
            for (const auto & c : codeword_before_con) {
                codeword_data.insert(codeword_data.end(),c.begin(),c.end());
            }

        }


}

#endif //LTE_LINK_SIM_CODEBLOCKPROCEDURE_HPP
