//
// Created by XPS on 2022/6/17.
//

#include "TransmiterSimElement.h"

void TransmiterSimElement::LoadConfiguration(std::shared_ptr<ConfigurationFile> configurationFile) {
    //读取ENB
    eNodeB_.LoadConfiguration(configurationFile);

}

bool TransmiterSimElement::CheckConfiguration() {
    return true;
}

