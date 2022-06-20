//
// Created by XPS on 2022/6/20.
//

#ifndef LTE_LINK_SIM_RATEMATCHPUBLIC_HPP
#define LTE_LINK_SIM_RATEMATCHPUBLIC_HPP
#include "public.h"

#include <cmath>
namespace ratematchpub {
    //用于咬尾卷积编码和turbo的子块交织，通用部分
    //flag:  0 - conv   1 - turbo  2 - turbo 第三数据流
    static void SubblockInterlever(VecUint8& bit_seq, Uint32 flag){


        const Uint32 P_conv[32] = {1,17,9,25,5,21,13,29,
                                     3,19,11,27,7,23,15,31,
                                     0,16,8,24,4,20,12,28,
                                     2,18,10,26,6,22,14,30};

        const Uint32 P_turbo[32] = {0,16,8,24,4,20,12,28,
                                      2,18,10,26,6,22,14,30,
                                      1,17,9,25,5,21,13,29,
                                      3,19,11,27,7,23,15,31};

        VecUint32 pi_ind;
        MtxUint8 mtx_temp;
        
        Uint32 row = ceil(bit_seq.size()/32.0);
        int32_t nof_NULL = row*32 - bit_seq.size();

        //数据读入 255 = <NULL>
        mtx_temp.resize(row);
        for (int i = 0; i < row; ++i) {
            mtx_temp[i].resize(32);
            for (int j = 0; j < 32; ++j) {

                if (i*32+j >= nof_NULL)
                {
                    mtx_temp[i].at(j) = bit_seq[i*32+j-nof_NULL];
                } else{
                    mtx_temp[i].at(j) = NULL_ELEM;
                }
            }
        }

        bit_seq.clear();
        //turbo第三条流数据取出
        if (flag != 2){
            //数据取出
            for (int i = 0; i < 32; ++i) {
                for (int j = 0; j < row; ++j) {
                    if (flag == 0){
                        bit_seq.push_back(mtx_temp.at(j).at(P_conv[i]));
                    } else if (flag == 1){
                        bit_seq.push_back(mtx_temp.at(j).at(P_turbo[i]));
                    }
                }
            }
        } else{
            const Uint32 n = row*32;
            Uint32 ind = 0;
            Uint32 temp = 0;
            for (Uint32 k = 0; k < n; ++k) {
                ind = floor((k*1.0)/row);
                temp = P_turbo[ind] + 32*(k%row) + 1;
//                pi_ind[k] = temp%n;
                pi_ind.push_back(temp%n);
            }
            Uint32 ind_in_mtx;
            for (int i = 0; i < row; ++i) {
                for (int j = 0; j < 32; ++j) {
                    ind_in_mtx = i*32 + j;
                    bit_seq.push_back(mtx_temp.at(pi_ind[ind_in_mtx]/32).at(pi_ind[ind_in_mtx]%32));
                }
            }
        }

    }



    //咬尾卷积编码bit选择
    static void BitSelect(VecUint8& bit_seq,const Uint32 E){

        int32_t k = 0;
        int32_t j = 0;
        int32_t ind = 0;
        VecUint8 out_seq;
        out_seq.reserve(E);
        auto k_w = bit_seq.size();
        while (k < E)
        {
            ind = j % k_w;
            if (bit_seq[ind] != NULL_ELEM)
            {
                out_seq.push_back(bit_seq[ind]);
                k++;
            }
            j++;
        }
        bit_seq.clear();
        bit_seq.assign(out_seq.begin(),out_seq.end());

    }

    //turbo编码bit选择
    static void BitSelect(VecUint8& bit_seq,Uint32 E,Uint32 k_0,Uint32 N_cb){

        Uint32 k = 0;
        Uint32 j = 0;
        Uint32 ind = 0;
        VecUint8 out_seq;
        out_seq.reserve(E);


        while (k < E)
        {
            ind = (k_0+j) % N_cb;
            if (bit_seq[ind] != NULL_ELEM)
            {
                out_seq.push_back(bit_seq[ind]);
                k++;
            }
            j++;
        }
        bit_seq.clear();
        bit_seq.assign(out_seq.begin(),out_seq.end());

    }
}


#endif //LTE_LINK_SIM_RATEMATCHPUBLIC_HPP
