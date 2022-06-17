//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_CONFIGURATIONFILE_H
#define LTE_LINK_SIM_CONFIGURATIONFILE_H

#include "public.h"

//读取配置文件参数
class ConfigurationFile {

public:

    Int32 DL_RB;
    Int32 cell_id;
    Int32 crs_port;
    Int32 frame;
    Int32 subframe;
    Int32 ctrl_region_sym;
    CpType cptype_;
    PhichResource phichr_;
    CpType phichd_;
    TransmissionMode tm_;


public:

    bool ReadConfigurationFile(const char* filename);

private:
    CpType String2EnumCptype(const char* cptype);
    PhichResource String2Enumphichr(const char* phichr);
    TransmissionMode String2Enumtm(const char* tm);

};


#endif //LTE_LINK_SIM_CONFIGURATIONFILE_H
