//
// Created by XPS on 2022/6/17.
//

#include "SimCommand.h"

#include <utility>

SimCommand::SimCommand(std::shared_ptr<ConfigurationFile> configurationFile){
    configuration_file_ = std::move(configurationFile);

}

bool SimCommand::SimCommandInit() {

    //加载配置
    transmiter_.LoadConfiguration(configuration_file_);
    channel_.LoadConfiguration(configuration_file_);
    reciver_.LoadConfiguration(configuration_file_);
    common_.LoadConfiguration(configuration_file_);
    // 检验配置
    if (transmiter_.CheckConfiguration()&&
            channel_.CheckConfiguration()&&
            reciver_.CheckConfiguration()&&
            common_.CheckConfiguration()){
        return true;
    }
    return false;
}
