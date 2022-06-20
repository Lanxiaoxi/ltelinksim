//
// Created by XPS on 2022/6/17.
//

#include "SimEntity.h"

SimEntity::SimEntity(const std::shared_ptr<SimCommand> &simCommand){
    sim_command_ = simCommand;
}

void SimEntity::InitSimEntity() {
    //生成各仿真实体
    waveform_generator_ = std::make_shared<WaveformGenerator>();
    fading_channel_generator_ = std::make_shared<FadingChannelGenerator>();
    awgn_channel_generator_ = std::make_shared<AWGNChannelGenerator>();
    waveform_reciver_ = std::make_shared<WaveformReciver>();
    sim_logger_ = std::make_shared<SimLogger>();

}

void SimEntity::Run() {

    switch (sim_command_->configuration_file_->sim_system) {
        case LTE:
            RunLTE();
            break;
        case WIFI:
            break;
    }

}

void SimEntity::RunLTE() {
    //初始化
    waveform_generator_->InitWaveformGenerator(
            sim_command_->transmiter_.eNodeB_
            );
//    waveform_reciver_->InitWaveformReciver();
//    awgn_channel_generator_->InitAWGNChannel();
//    fading_channel_generator_->InitFadingChannel();
//    sim_logger_->InitSimLogger();

    //生成波形
    waveform_generator_->Generate(
            sim_command_->transmiter_.eNodeB_
            );
    //过信道

    //接收解码并记录
}
