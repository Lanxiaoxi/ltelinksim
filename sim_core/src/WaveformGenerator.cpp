//
// Created by XPS on 2022/6/17.
//

#include "WaveformGenerator.h"

void WaveformGenerator::InitWaveformGenerator(ENodeB &eNodeB) {
    eNodeB.Init();


}

void WaveformGenerator::Generate(ENodeB eNodeB) {

    eNodeB.GenerateSubframe();



}
