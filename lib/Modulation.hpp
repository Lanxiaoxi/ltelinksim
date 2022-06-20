//
// Created by XPS on 2022/6/20.
//

#ifndef LTE_LINK_SIM_MODULATION_HPP
#define LTE_LINK_SIM_MODULATION_HPP

#include "public.h"

namespace modulation {

    static uint32_t b2decimal(VecUint8& bit_seq){
        uint32_t dec = 0;
        for (int i = 0; i < bit_seq.size(); ++i) {
            dec = dec | bit_seq[i];
            if (i == bit_seq.size()-1) break;
            dec = dec << 1;
        }
        return dec;
    }


    static void ModBPSK(VecUint8& bit,VecCompl& sym){

        const Compl sym_s[2] = {{0.70710678, 0.70710678}, //0
                                 {-0.70710678, -0.70710678}  // 1
        };
        for (auto it:bit) {
            sym.push_back(it == 0 ? sym_s[0] : sym_s[1]);
        }
    }
    static void ModQPSK(VecUint8& bit, VecCompl& sym){

        const float sym_s = 0.70710678;
        Compl temp = {0,0};

        for (int i = 0; i < bit.size()/2; ++i) {
            for (int j = 0; j < 2; ++j) {
                if (j == 0)
                    temp.real(bit[i*2+j] == 0 ? sym_s : -sym_s);
                else
                    temp.imag(bit[i*2+j] == 0 ? sym_s : -sym_s);
                if (bit[i*2+j] == NIL_ELEM){
                    temp = {0,0};
                    break;
                }

            }
            sym.push_back(temp);
        }

    }
    static void Mod16(VecUint8& bit,VecCompl& sym){

        const Compl sym_s[4] = {
                {0.3162277,0.3162277},
                {0.3162277,0.9486833},
                {0.9486833,0.3162277},
                {0.9486833,0.9486833}
        };

        VecUint8 temp;
        Compl temp_d;
        uint32_t ind;

        for (int i = 0; i < bit.size(); i += 4) {
            //读入6 bit 信息
            for (int j = 0; j < 4; ++j) {
                temp.push_back(bit[i+j]);
            }
            //转换为10进制
            ind = b2decimal(temp);
            temp.clear();
            temp_d = sym_s[ind%4];
            //确定符号
            if (ind >= 4 && ind < 8)
            {
                temp_d.imag(temp_d.imag()*(-1));
            } else if (ind >= 8 && ind < 12)
            {
                temp_d.real(temp_d.real()*(-1));
            } else if (ind >= 12){
                temp_d.real(temp_d.real()*(-1));
                temp_d.imag(temp_d.imag()*(-1));
            }
            sym.push_back(temp_d);
        }


    }
    static void Mod64(VecUint8& bit,VecCompl& sym){
        const Compl sym_s[16] = {
                {0.46291005,0.46291005},
                {0.46291005, 0.15430335},
                { 0.15430335, 0.46291005 },
                { 0.15430335, 0.15430335 },
                { 0.46291005, 0.77151675 },
                { 0.46291005, 1.08012345 },
                { 0.15430335, 0.77151675 },
                { 0.15430335, 1.08012345 },
                { 0.77151675, 0.46291005 },
                { 0.77151675, 0.15430335 },
                { 1.08012345, 0.46291005 },
                { 1.08012345, 0.15430335 },
                { 0.77151675, 0.77151675 },
                { 0.77151675, 1.08012345 },
                { 1.08012345, 0.77151675 },
                { 1.08012345, 1.08012345 }
        };

        VecUint8 temp;
        Compl temp_d;
        uint32_t ind;

        for (int i = 0; i < bit.size(); i += 6) {
            //读入6 bit 信息
            for (int j = 0; j < 6; ++j) {
                temp.push_back(bit[i+j]);
            }
            //转换为10进制
            ind = b2decimal(temp);
            temp.clear();
            temp_d = sym_s[ind%16];
            //确定符号
            if (ind >= 16 && ind < 32)
            {
                temp_d.imag(temp_d.imag()*(-1));
            } else if (ind >= 32 && ind < 48)
            {
                temp_d.real(temp_d.real()*(-1));
            } else if (ind >= 48){
                temp_d.real(temp_d.real()*(-1));
                temp_d.imag(temp_d.imag()*(-1));
            }
            sym.push_back(temp_d);
        }


    }
    static void Mod256(VecUint8& bit,VecCompl& sym){
        const Compl sym_s[64] = {
                {0.38348,0.38348},
                {0.38348,0.53688},
                {0.53688,0.38348},
                {0.53688,0.53688},
                {0.38348,0.23009},
                {0.38348,0.076696},
                {0.53688,0.23009},
                {0.53688,0.076696},
                {0.23009,0.38348},
                {0.23009,0.53688},
                {0.076696,0.38348},
                {0.076696,0.53688},
                {0.23009,0.23009},
                {0.23009,0.076696},
                {0.076696,0.23009},
                {0.076696,0.076696},
                {0.38348,0.84366},
                {0.38348,0.69027},
                {0.53688,0.84366},
                {0.53688,0.69027},
                {0.38348,0.99705},
                {0.38348,1.1504},
                {0.53688,0.99705},
                {0.53688,1.1504},
                {0.23009,0.84366},
                {0.23009,0.69027},
                {0.076696,0.84366},
                {0.076696,0.69027},
                {0.23009,0.99705},
                {0.23009,1.1504},
                {0.076696,0.99705},
                {0.076696,1.1504},
                {0.84366,0.38348},
                {0.84366,0.53688},
                {0.69027,0.38348},
                {0.69027,0.53688},
                {0.84366,0.23009},
                {0.84366,0.076696},
                {0.69027,0.23009},
                {0.69027,0.076696},
                {0.99705,0.38348},
                {0.99705,0.53688},
                {1.1504,0.38348},
                {1.1504,0.53688},
                {0.99705,0.23009},
                {0.99705,0.076696},
                {1.1504,0.23009},
                {1.1504,0.076696},
                {0.84366,0.84366},
                {0.84366,0.69027},
                {0.69027,0.84366},
                {0.69027,0.69027},
                {0.84366,0.99705},
                {0.84366,1.1504},
                {0.69027,0.99705},
                {0.69027,1.1504},
                {0.99705,0.84366},
                {0.99705,0.69027},
                {1.1504,0.84366},
                {1.1504,0.69027},
                {0.99705,0.99705},
                {0.99705,1.1504},
                {1.1504,0.99705},
                {1.1504,1.1504},
        };

        VecUint8 temp;
        Compl temp_d;
        uint32_t ind;

        for (int i = 0; i < bit.size(); i += 8) {
            //读入8 bit 信息
            for (int j = 0; j < 8; ++j) {
                temp.push_back(bit[i+j]);
            }
            //转换为10进制
            ind = b2decimal(temp);
            temp.clear();
            temp_d = sym_s[ind%64];
            //确定符号
            if (ind >= 64 && ind < 128)
            {
                temp_d.imag(temp_d.imag()*(-1));
            } else if (ind >= 128 && ind < 192)
            {
                temp_d.real(temp_d.real()*(-1));
            } else if (ind >= 192){
                temp_d.real(temp_d.real()*(-1));
                temp_d.imag(temp_d.imag()*(-1));
            }
            sym.push_back(temp_d);
        }


    }
    static void Mod1024(VecUint8& bit,VecCompl& sym){
        VecUint8 temp;
        Compl temp_d;
        int32_t real_temp;
        int32_t imag_temp;
        const float delta = 0.03829197;

        for (int i = 0; i < bit.size(); i += 8) {
            //读入8 bit 信息
            for (int j = 0; j < 10; ++j) {
                temp.push_back(bit[i+j]);
            }
            real_temp = 2-(1-2*temp[8]);
            real_temp = 4-(1-2*temp[6])*real_temp;
            real_temp = 8-(1-2*temp[4])*real_temp;
            real_temp = 16-(1-2*temp[2])*real_temp;
            real_temp = (1-2*temp[0])*real_temp;

            imag_temp = 2-(1-2*temp[9]);
            imag_temp = 4-(1-2*temp[7])*imag_temp;
            imag_temp = 8-(1-2*temp[5])*imag_temp;
            imag_temp = 16-(1-2*temp[3])*imag_temp;
            imag_temp = (1-2*temp[1])*imag_temp;

            temp_d.real(real_temp*delta);
            temp_d.imag(imag_temp*delta);

            sym.push_back(temp_d);

            temp.clear();
        }
    }





    static void Modulate(VecUint8& bit_seq,VecCompl& sym_seq,ModType ModType){
        switch (ModType) {
            case BPSK:
                ModBPSK(bit_seq, sym_seq);
                break;
            case QPSK:
                ModQPSK(bit_seq, sym_seq);
                break;
            case QAM_16:
                Mod16(bit_seq, sym_seq);
                break;
            case QAM_64:
                Mod64(bit_seq, sym_seq);
                break;
            case QAM_256:
                Mod256(bit_seq, sym_seq);
                break;
            case QAM_1024:
                Mod1024(bit_seq, sym_seq);
                break;
            default:
                return;
        }

    }

    //根据调制方式计算调制阶数
    static uint32_t getModQm(ModType ModType){
        uint32_t Q_m = 0;
        switch (ModType) {
            case BPSK:
                Q_m = 1;
                break;
            case QPSK:
                Q_m = 2;
                break;
            case QAM_16:
                Q_m = 4;
                break;
            case QAM_64:
                Q_m = 6;
                break;
            case QAM_256:
                Q_m = 8;
                break;
            case QAM_1024:
                Q_m = 10;
                break;
            default:
                std::cout << "get_mod_Qm : unsupport mod type \n";
                break;
        }
        return Q_m;
    }

    //根据MCS计算调制方式
    static ModType getModTypeByMCS(Uint32 mcs){
        ModType ModType = BPSK;
        if (mcs <= 9 || mcs == 29)
        {
            ModType = QPSK;
        } else if (mcs <= 16 || mcs == 30){
            ModType = QAM_16;
        } else if (mcs <= 28 || mcs == 31){
            ModType = QAM_64;
        }

        //处理特殊情况
//        if (rnti_type == RA_RNTI || rnti_type == P_RNTI || rnti_type == SI_RNTI)
//        {
//            ModType = QPSK;
//        }
        return ModType;
    }
    
}

#endif //LTE_LINK_SIM_MODULATION_HPP
