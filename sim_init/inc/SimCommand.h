//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_SIMCOMMAND_H
#define LTE_LINK_SIM_SIMCOMMAND_H

#include "TransmiterSimElement.h"
#include "ChannelSimElement.h"
#include "ReciverSimElement.h"
#include "CommonSimElement.h"


class SimCommand {
public:
    std::shared_ptr<ConfigurationFile> configuration_file_;

    TransmiterSimElement transmiter_;
    ChannelSimElement channel_;
    ReciverSimElement reciver_;
    CommonSimElement common_;

public:
    SimCommand(std::shared_ptr<ConfigurationFile> configurationFile);
    bool SimCommandInit();
};


#endif //LTE_LINK_SIM_SIMCOMMAND_H
