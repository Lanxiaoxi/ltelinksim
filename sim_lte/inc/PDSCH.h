//
// Created by XPS on 2022/6/17.
//


#ifndef LTE_LINK_SIM_PDSCH_H
#define LTE_LINK_SIM_PDSCH_H
#include "public.h"

class PDSCH {
private:

    DataSourceType data_source_type;

    TransmissionMode tm_;

    TransmissionScheme transmission_scheme;

    Int32 nof_transblock;

    VecInt32 transblock_size;

    VecInt32 mcs;


    VecInt32 PRB_set_;

    Int32 nof_layer;
public:
    Int32 getNofLayer() const;

    void setNofLayer(Int32 nofLayer);

    TransmissionMode getTm() const;

    void setTm(TransmissionMode tm);

    const VecInt32 &getPrbSet() const;

    void setPrbSet(const std::pair<Int32,Int32> &PRB_set);

    const VecInt32 &getMcs() const;

    void setMcs(const VecInt32 &mcs);

private:

    std::vector<ModType> modulation_type;

    //-------------buff-----------
    MtxUint8 transblock_data;

    MtxUint8 codeword_data;



public:

    void Init();

    void GenerateData();

    void GenerateInd();

    TransmissionScheme InitTransScheme(const TransmissionMode tm);

    Int32 InitNofTB(const TransmissionScheme ts);

    DataSourceType getDataSourceType() const;

    void setDataSourceType(DataSourceType dataSourceType);

private:
    void PDSCHTurboEncode(MtxUint8& data_after_seg,MtxUint8 &data_after_turbo);

    void PDSCHRateMatch(MtxUint8 &data_after_turbo,MtxUint8 &data_after_rm,const Int32 G);
};


#endif //LTE_LINK_SIM_PDSCH_H
