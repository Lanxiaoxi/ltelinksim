//
// Created by XPS on 2022/6/17.
//

#include "ENodeB.h"

const PDSCH &ENodeB::getPdsch() const {
    return pdsch_;
}

void ENodeB::setPdsch(const PDSCH &pdsch) {
    pdsch_ = pdsch;
}

Int32 ENodeB::getDlRb() const {
    return dl_rb;
}

void ENodeB::setDlRb(Int32 dlRb) {
    dl_rb = dlRb;
}

Int32 ENodeB::getNofCrsPort() const {
    return nof_crs_port;
}

void ENodeB::setNofCrsPort(Int32 nofCrsPort) {
    nof_crs_port = nofCrsPort;
}

Int32 ENodeB::getCellId() const {
    return cell_id;
}

void ENodeB::setCellId(Int32 cellId) {
    cell_id = cellId;
}

Int32 ENodeB::getFrameNumber() const {
    return frame_number;
}

void ENodeB::setFrameNumber(Int32 frameNumber) {
    frame_number = frameNumber;
}

Int32 ENodeB::getSubframeNumber() const {
    return subframe_number;
}

void ENodeB::setSubframeNumber(Int32 subframeNumber) {
    subframe_number = subframeNumber;
}

Int32 ENodeB::getNofCtrlRegionSym() const {
    return nof_ctrl_region_sym;
}

void ENodeB::setNofCtrlRegionSym(Int32 nofCtrlRegionSym) {
    nof_ctrl_region_sym = nofCtrlRegionSym;
}

CpType ENodeB::getCpType() const {
    return cp_type;
}

void ENodeB::setCpType(CpType cpType) {
    cp_type = cpType;
}

PhichResource ENodeB::getPhichResource() const {
    return phich_resource;
}

void ENodeB::setPhichResource(PhichResource phichResource) {
    phich_resource = phichResource;
}

CpType ENodeB::getPhichDuration() const {
    return phich_duration;
}

void ENodeB::setPhichDuration(CpType phichDuration) {
    phich_duration = phichDuration;
}

TransmissionMode ENodeB::getTransmissionMode() const {
    return transmission_mode;
}

void ENodeB::setTransmissionMode(TransmissionMode transmissionMode) {
    transmission_mode = transmissionMode;
}
