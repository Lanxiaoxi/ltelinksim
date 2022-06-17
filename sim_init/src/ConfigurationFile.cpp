//
// Created by XPS on 2022/6/17.
//

#include "ConfigurationFile.h"

#include <cstdlib>

#include "tinyxml.h"

bool ConfigurationFile::ReadConfigurationFile(const char *filename) {
    TiXmlDocument document;
    if(!document.LoadFile(filename)){
        std::cout << "file read fail" << std::endl;
        return false;
    }
    //读取下行配置
    TiXmlElement* downlink = document.FirstChildElement("main")->FirstChildElement("downlink");

     cell_id = atoi(downlink->FirstChildElement("cellid")->GetText());
     DL_RB = atoi(downlink->FirstChildElement("bandwidth")->GetText());
     crs_port = atoi(downlink->FirstChildElement("crsport")->GetText());
     frame = atoi(downlink->FirstChildElement("frame")->GetText());
     subframe = atoi(downlink->FirstChildElement("subframe")->GetText());
     ctrl_region_sym = atoi(downlink->FirstChildElement("ctrl_region_sym")->GetText());
     cptype_ = String2EnumCptype(downlink->FirstChildElement("cptype")->GetText());
     phichr_ = String2Enumphichr(downlink->FirstChildElement("phichr")->GetText());
     phichd_ = String2EnumCptype(downlink->FirstChildElement("phichd")->GetText());
     tm_ = String2Enumtm(downlink->FirstChildElement("tm")->GetText());



    return true;
}

CpType ConfigurationFile::String2EnumCptype(const char* cptype){
    if (strcmp(cptype,"normal") == 0){
        return NORMAL;
    } else if (strcmp(cptype,"extended") == 0){
        return EXTENDED;
    } else{
        std::cout << " default String2EnumCptype" << std::endl;
        return NORMAL;
    }
}
PhichResource ConfigurationFile::String2Enumphichr(const char* phichr){
    if (strcmp(phichr,"1/6") == 0){
        return OneSixth;
    } else if (strcmp(phichr,"1/2") == 0){
        return HALF;
    }else if (strcmp(phichr,"1") == 0){
        return ONE;
    }else if (strcmp(phichr,"2") == 0){
        return TWO;
    } else{
        std::cout<< " default String2Enumphichr" <<std::endl;
        return OneSixth;
    }
}

TransmissionMode ConfigurationFile::String2Enumtm(const char* tm){
    if (strcmp(tm,"1") == 0){
        return TM_1;
    } else if (strcmp(tm,"2") == 0){
        return TM_2;
    }else if (strcmp(tm,"3") == 0){
        return TM_3;
    }else if (strcmp(tm,"4") == 0){
        return TM_4;
    }else if (strcmp(tm,"5") == 0){
        return TM_5;
    }else if (strcmp(tm,"6") == 0){
        return TM_6;
    }else if (strcmp(tm,"7") == 0){
        return TM_7;
    }else if (strcmp(tm,"8") == 0){
        return TM_8;
    } else {
        std::cout<< " default String2Enumtm" <<std::endl;
        return TM_1;
    }
}