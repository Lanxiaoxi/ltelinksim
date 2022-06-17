//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_SIMELEMENTINTERFACE_H
#define LTE_LINK_SIM_SIMELEMENTINTERFACE_H

#include "ConfigurationFile.h"

class SimElementInterface {
public:
    //从配置文件对象中读取所需配置
    virtual void LoadConfiguration(std::shared_ptr<ConfigurationFile> configurationFile) = 0;
    //检查配置合法性
    virtual bool CheckConfiguration() = 0;

};


#endif //LTE_LINK_SIM_SIMELEMENTINTERFACE_H
