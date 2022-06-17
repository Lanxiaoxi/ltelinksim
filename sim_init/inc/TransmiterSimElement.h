//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_TRANSMITERSIMELEMENT_H
#define LTE_LINK_SIM_TRANSMITERSIMELEMENT_H

#include "SimElementInterface.h"

#include "ENodeB.h"


class TransmiterSimElement : public SimElementInterface{
private:
    ENodeB eNodeB_; //当前发射机元素只支持ENB相关配置

public:

    void LoadConfiguration(std::shared_ptr<ConfigurationFile> configurationFile) override;

    bool CheckConfiguration() override;


};


#endif //LTE_LINK_SIM_TRANSMITERSIMELEMENT_H
