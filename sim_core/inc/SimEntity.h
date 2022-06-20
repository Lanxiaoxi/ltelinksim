//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_SIMENTITY_H
#define LTE_LINK_SIM_SIMENTITY_H
#include "SimCommand.h"
#include "WaveformGenerator.h"
#include "WaveformReciver.h"
#include "FadingChannelGenerator.h"
#include "AWGNChannelGenerator.h"
#include "SimLogger.h"

class SimEntity {

private:
    std::shared_ptr<SimCommand> sim_command_;

    std::shared_ptr<WaveformGenerator> waveform_generator_;
    std::shared_ptr<FadingChannelGenerator> fading_channel_generator_;
    std::shared_ptr<AWGNChannelGenerator> awgn_channel_generator_;
    std::shared_ptr<WaveformReciver> waveform_reciver_;
    std::shared_ptr<SimLogger> sim_logger_;
public:
    SimEntity(const std::shared_ptr<SimCommand> &simCommand);

    void InitSimEntity();

    void Run();

    void RunLTE();

};


#endif //LTE_LINK_SIM_SIMENTITY_H
