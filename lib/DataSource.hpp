//
// Created by XPS on 2022/6/20.
//

#ifndef LTE_LINK_SIM_DATASOURCE_HPP
#define LTE_LINK_SIM_DATASOURCE_HPP
#include "public.h"

namespace datasource {

    void LoadSeq(const DataSourceType type,const Int32 len,VecUint8 &buff){
        switch (type) {

            case ALL0:
                buff.assign(len,0);
                break;
            case ALL1:
                buff.assign(len,1);
                break;
//            case PN9:
//                break;
        }
    }

}

#endif //LTE_LINK_SIM_DATASOURCE_HPP
