//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_ENODEB_H
#define LTE_LINK_SIM_ENODEB_H
#include "PDSCH.h"
#include "ConfigurationFile.h"

class ENodeB {

public:
    PDSCH pdsch_;

    Int32 total_subframes;

private:
    Int32 dl_rb;

    Int32 nof_crs_port;

    Int32 cell_id;

    Int32 frame_number;

    Int32 subframe_number;

    Int32 nof_ctrl_region_sym;

    CpType cp_type;

    PhichResource phich_resource;

    CpType phich_duration;

    TransmissionMode transmission_mode;
public:
    void LoadConfiguration(std::shared_ptr<ConfigurationFile> configurationFile);

    void Init();

    void GenerateSubframe();




public:
    const PDSCH getPdsch() const;

    void setPdsch(const PDSCH &pdsch);

    Int32 getDlRb() const;

    void setDlRb(Int32 dlRb);

    Int32 getNofCrsPort() const;

    void setNofCrsPort(Int32 nofCrsPort);

    Int32 getCellId() const;

    void setCellId(Int32 cellId);

    Int32 getFrameNumber() const;

    void setFrameNumber(Int32 frameNumber);

    Int32 getSubframeNumber() const;

    void setSubframeNumber(Int32 subframeNumber);

    Int32 getNofCtrlRegionSym() const;

    void setNofCtrlRegionSym(Int32 nofCtrlRegionSym);

    CpType getCpType() const;

    void setCpType(CpType cpType);

    PhichResource getPhichResource() const;

    void setPhichResource(PhichResource phichResource);

    CpType getPhichDuration() const;

    void setPhichDuration(CpType phichDuration);

    TransmissionMode getTransmissionMode() const;

    void setTransmissionMode(TransmissionMode transmissionMode);
};


#endif //LTE_LINK_SIM_ENODEB_H
