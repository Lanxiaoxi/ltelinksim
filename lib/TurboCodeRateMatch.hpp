//
// Created by XPS on 2022/6/20.
//

#ifndef LTE_LINK_SIM_TURBOCODERATEMATCH_HPP
#define LTE_LINK_SIM_TURBOCODERATEMATCH_HPP
#include "public.h"

#include <cmath>

#include "RateMatchPublic.hpp"

namespace turboRM {
    //对应于Turbo编码的速率匹配
    //D - bit_seq长度的1/3
    static void RateMatch(VecUint8& bit_seq,VecUint8 &out_seq,const Uint32 E,const Uint32 rv){

        Uint32 D = bit_seq.size()/3;
        //切割为三条数据流
        VecUint8 in_1,in_2,in_3;
        in_1.assign(bit_seq.begin(),bit_seq.begin()+D);
        in_2.assign(bit_seq.begin()+D,bit_seq.begin()+2*D);
        in_3.assign(bit_seq.begin()+2*D,bit_seq.end());

        //子块交织
        ratematchpub::SubblockInterlever(in_1,1);
        ratematchpub::SubblockInterlever(in_2,1);
        ratematchpub::SubblockInterlever(in_3,2);

        //合并
//        bit_seq.clear();
        out_seq.insert(out_seq.end(),in_1.begin(),in_1.end());
        //极性位交替放置
        for (int i = 0; i < in_2.size(); ++i) {
            out_seq.push_back(in_2[i]);
            out_seq.push_back(in_3[i]);
        }

        //N_cb 计算 k0;
        //对仿真来说，不存在收端处理不了的情况，所以令 N_cb = K_w
        Uint32 N_cb = out_seq.size();
        Uint32 row = ceil(N_cb/3/32.0);
        Uint32 k_0 = row*(2*rv* ceil(N_cb/(8.0*row))+2);

        //bit select
        ratematchpub::BitSelect(out_seq,E,k_0,N_cb);

    }
}
#endif //LTE_LINK_SIM_TURBOCODERATEMATCH_HPP
