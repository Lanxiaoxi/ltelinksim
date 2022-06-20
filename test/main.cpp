#include "public.h"

#include "ConfigurationFile.h"
#include "SimCommand.h"
#include "SimEntity.h"
int main() {

    //读取配置文件
    std::shared_ptr<ConfigurationFile> configuration_file = std::make_shared<ConfigurationFile>();
    configuration_file->ReadConfigurationFile(R"(C:\code\lte_link_sim\configuration\lte_cfg.xml)");

    //创建仿真命令
    std::shared_ptr<SimCommand> sim_command = std::make_shared<SimCommand>(configuration_file);
    sim_command->SimCommandInit();

    //创建仿真实体执行仿真
    std::shared_ptr<SimEntity> sim_entity = std::make_shared<SimEntity>(sim_command);
    sim_entity->InitSimEntity();
    sim_entity->Run();







    return 0;
}
