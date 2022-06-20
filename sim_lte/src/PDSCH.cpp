//
// Created by XPS on 2022/6/17.
//

#include "PDSCH.h"

#include "DataSource.hpp"
#include "TBSizeTable.hpp"
#include "CRC.hpp"
#include "CodeBlockProcedure.hpp"
#include "TurboCode.hpp"
#include "TurboCodeRateMatch.hpp"
#include "Modulation.hpp"
void PDSCH::GenerateData() {

    //加载数据源
    datasource::LoadSeq(data_source_type,transblock_size[0],transblock_data[0]);
    //  crc
    crc::Encode(transblock_data[0],CRC24A);
    //------------------------seg--------------------------------
    MtxUint8 data_after_seg = codeblock::CodeblockSegmentation(transblock_data[0]);
    //---------------turbo---------------------------------------------------
    MtxUint8 data_after_turbo;
    PDSCHTurboEncode(data_after_seg,data_after_turbo);
    //------------------------RM--------------------------------------
    Int32 G = 1000; // 可用于当前传输块传输的最大bit数 TODO 计算码字大小
    MtxUint8 data_after_rm;
    PDSCHRateMatch(data_after_turbo,data_after_rm,G);
    //connection
    codeword_data.resize(nof_transblock);
    codeblock::CodeblockConcatenation(data_after_rm,codeword_data[0]);

    
    
    

    
    
    //    caculate_paras();
//    caculate_ind();
//    calculate_pdsch_info();
//    //加载用户数据
//    load_user_data();
//    // DL-SCH
//    crc_attach();
//    codeblockSegmentation();
//    channel_coding();
//    rate_match();
//    codeblockConcatenation();
//
//    //PDSCH
//    scrambling();
//    modulation();
//    layermapping();
//    precoding();

}

void PDSCH::GenerateInd() {

}

void PDSCH::Init() {

    //初始化传输策略，默认传输模式的主测略
    transmission_scheme = InitTransScheme(tm_);

    //初始化传输块个数
    nof_transblock = InitNofTB(transmission_scheme);

    //计算码块大小
    transblock_size.push_back(
            TBsizetable::getTBSize(mcs[0],PRB_set_.size(),nof_layer)
            );

    //计算调制类型
    modulation_type.push_back(
            modulation::getModTypeByMCS(mcs[0])
            );

    //初始化buff
    transblock_data.resize(nof_transblock);

}

DataSourceType PDSCH::getDataSourceType() const {
    return data_source_type;
}

void PDSCH::setDataSourceType(DataSourceType dataSourceType) {
    data_source_type = dataSourceType;
}

const VecInt32 &PDSCH::getMcs() const {
    return mcs;
}

void PDSCH::setMcs(const VecInt32 &mcs) {
    PDSCH::mcs = mcs;
}

const VecInt32 &PDSCH::getPrbSet() const {
    return PRB_set_;
}

void PDSCH::setPrbSet(const std::pair<Int32,Int32> &PRB_set) {
    for (int i = PRB_set.first; i <= PRB_set.second; ++i) {
        PRB_set_.push_back(i);
    }
}

Int32 PDSCH::getNofLayer() const {
    return nof_layer;
}

void PDSCH::setNofLayer(Int32 nofLayer) {
    nof_layer = nofLayer;
}

TransmissionScheme PDSCH::InitTransScheme(const TransmissionMode tm) {
    TransmissionScheme ts;
    switch (tm) {
        case TM_1:
            ts = SINGLE_PORT;
            break;
        case TM_2:
            ts = TRANSMIT_DIVERSITY;
            break;
//        case TM_3:
//            break;
//        case TM_4:
//            break;
//        case TM_5:
//            break;
//        case TM_6:
//            break;
//        case TM_7:
//            break;
//        case TM_8:
//            break;
//        case TM_9:
//            break;
    }
    return ts;
}

TransmissionMode PDSCH::getTm() const {
    return tm_;
}

void PDSCH::setTm(TransmissionMode tm) {
    tm_ = tm;
}

Int32 PDSCH::InitNofTB(const TransmissionScheme ts) {

    switch (ts) {

        case TRANSMIT_DIVERSITY:
        case SINGLE_PORT:
            return 1;
        case SPATIAL_MULTIPLEX_CDD:
        case SPATIAL_MULTIPLEX:
        case SPATIAL_MULTIPLEX_DMRS:
            return 2;
    }
    return 0;
}

void PDSCH::PDSCHTurboEncode(MtxUint8 &data_after_seg, MtxUint8 &data_after_turbo) {
    data_after_turbo.resize(data_after_seg.size());
    //处理NULL元素
    uint32_t F = 0;
    uint32_t temp = data_after_seg[0].size() + 4;
    for (unsigned char & j : data_after_seg[0]) {
        if(j == NULL_ELEM){
            F++;
            j = 0;
        }
    }
    //对每一个码块进行编码
    for (int i = 0; i < data_after_seg.size(); ++i) {
        data_after_turbo[i] = turbocode::Encode(data_after_seg[i]);
    }
    //恢复NULL元素
    for (int j = 0; j < F; ++j) {
        data_after_turbo[0][j] = NULL_ELEM;
        data_after_turbo[0][j+temp] = NULL_ELEM;
    }
}

void PDSCH::PDSCHRateMatch(MtxUint8 &data_after_turbo,MtxUint8 &data_after_rm,const Int32 G) {
    uint32_t E;
    uint32_t Q_m = 0;
    uint32_t G_prime = 0;
    uint32_t N_L = 0; // 当前tb对应映射的层数
    uint32_t gama = 0;
    uint32_t C = 0; //一个tb的码块数
    Int32 RV = 0; //冗余版本


    //计算该传输块进行速率匹配的相关参数
//        G = pdsch_info.codeword_size[i];


    C = data_after_turbo.size();
    Q_m = modulation::getModQm(modulation_type[0]);

    if (transmission_scheme == TRANSMIT_DIVERSITY){
        N_L = 2;
    } else{
        //N_L = TB_nof_map_layer[i]; TODO 计算映射层数
        N_L = 1; //先默认单个端口
    }
    G_prime = G/(N_L*Q_m);
    gama = G_prime % C;

    //对每一个码块进行速率匹配
    data_after_rm.resize(data_after_turbo.size());
    for (int j = 0; j < data_after_turbo.size(); ++j)
    {
        //计算E
        if (j <= C - gama - 1)
        {
            E = N_L*Q_m*(G_prime/C);
        } else{
            E = N_L*Q_m*ceil((G_prime*1.0)/C);
        }
        turboRM::RateMatch(data_after_turbo[j],data_after_rm[j],E,RV);
    }
}
