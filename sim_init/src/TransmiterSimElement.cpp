//
// Created by XPS on 2022/6/17.
//

#include "TransmiterSimElement.h"

void TransmiterSimElement::LoadConfiguration(std::shared_ptr<ConfigurationFile> configurationFile) {
    //读取ENB
    eNodeB_.setDlRb(configurationFile->DL_RB);
    eNodeB_.setNofCrsPort(configurationFile->crs_port);
    eNodeB_.setCellId(configurationFile->cell_id);
    eNodeB_.setFrameNumber(configurationFile->frame);
    eNodeB_.setSubframeNumber(configurationFile->subframe);
    eNodeB_.setNofCtrlRegionSym(configurationFile->ctrl_region_sym);
    eNodeB_.setCpType(configurationFile->cptype_);
    eNodeB_.setPhichResource(configurationFile->phichr_);
    eNodeB_.setPhichDuration(configurationFile->phichd_);
    eNodeB_.setTransmissionMode(configurationFile->tm_);

}

bool TransmiterSimElement::CheckConfiguration() {
    return true;
}
