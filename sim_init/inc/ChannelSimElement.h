//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_CHANNELSIMELEMENT_H
#define LTE_LINK_SIM_CHANNELSIMELEMENT_H
#include "SimElementInterface.h"

class ChannelSimElement : public SimElementInterface{
public:
    void LoadConfiguration(std::shared_ptr<ConfigurationFile> configurationFile) override;

    bool CheckConfiguration() override;
};


#endif //LTE_LINK_SIM_CHANNELSIMELEMENT_H
