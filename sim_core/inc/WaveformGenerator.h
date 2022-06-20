//
// Created by XPS on 2022/6/17.
//

#ifndef LTE_LINK_SIM_WAVEFORMGENERATOR_H
#define LTE_LINK_SIM_WAVEFORMGENERATOR_H

#include "ENodeB.h"


class WaveformGenerator {
public:
    void InitWaveformGenerator(ENodeB &eNodeB);

    void Generate(ENodeB eNodeB);

};


#endif //LTE_LINK_SIM_WAVEFORMGENERATOR_H
