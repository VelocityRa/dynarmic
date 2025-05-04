/* This file is part of the dynarmic project.
 * Copyright (c) 2016 MerryMage
 * SPDX-License-Identifier: 0BSD
 */

#include <cstdlib>
#include <string>

#include <fmt/format.h>
#include <fmt/ostream.h>
#include <mcl/bit/bit_field.hpp>

#include "dynarmic/common/string_util.h"
#include "dynarmic/frontend/A32/a32_types.h"
#include "dynarmic/frontend/A32/decoder/thumb16.h"
#include "dynarmic/frontend/A32/decoder/thumb32.h"
#include "dynarmic/frontend/A32/disassembler/disassembler.h"
#include "dynarmic/frontend/imm.h"

namespace Dynarmic::A32 {

class DisassemblerThumb16Visitor {
public:
    using instruction_return_type = std::string;

    std::string thumb16_LSL_imm(Imm<5> imm5, Reg m, Reg d) {
        return fmt::format("lsls {}, {}, #{}", d, m, imm5.ZeroExtend());
    }

    std::string thumb16_LSR_imm(Imm<5> imm5, Reg m, Reg d) {
        const u32 shift = imm5 != 0 ? imm5.ZeroExtend() : 32U;
        return fmt::format("lsrs {}, {}, #{}", d, m, shift);
    }

    std::string thumb16_ASR_imm(Imm<5> imm5, Reg m, Reg d) {
        const u32 shift = imm5 != 0 ? imm5.ZeroExtend() : 32U;
        return fmt::format("asrs {}, {}, #{}", d, m, shift);
    }

    std::string thumb16_ADD_reg_t1(Reg m, Reg n, Reg d) {
        return fmt::format("adds {}, {}, {}", d, n, m);
    }

    std::string thumb16_SUB_reg(Reg m, Reg n, Reg d) {
        return fmt::format("subs {}, {}, {}", d, n, m);
    }

    std::string thumb16_ADD_imm_t1(Imm<3> imm3, Reg n, Reg d) {
        return fmt::format("adds {}, {}, #{}", d, n, imm3.ZeroExtend());
    }

    std::string thumb16_SUB_imm_t1(Imm<3> imm3, Reg n, Reg d) {
        return fmt::format("subs {}, {}, #{}", d, n, imm3.ZeroExtend());
    }

    std::string thumb16_MOV_imm(Reg d, Imm<8> imm8) {
        return fmt::format("movs {}, #{}", d, imm8.ZeroExtend());
    }

    std::string thumb16_CMP_imm(Reg n, Imm<8> imm8) {
        return fmt::format("cmp {}, #{}", n, imm8.ZeroExtend());
    }

    std::string thumb16_ADD_imm_t2(Reg d_n, Imm<8> imm8) {
        return fmt::format("adds {}, #{}", d_n, imm8.ZeroExtend());
    }

    std::string thumb16_SUB_imm_t2(Reg d_n, Imm<8> imm8) {
        return fmt::format("subs {}, #{}", d_n, imm8.ZeroExtend());
    }

    std::string thumb16_AND_reg(Reg m, Reg d_n) {
        return fmt::format("ands {}, {}", d_n, m);
    }

    std::string thumb16_EOR_reg(Reg m, Reg d_n) {
        return fmt::format("eors {}, {}", d_n, m);
    }

    std::string thumb16_LSL_reg(Reg m, Reg d_n) {
        return fmt::format("lsls {}, {}", d_n, m);
    }

    std::string thumb16_LSR_reg(Reg m, Reg d_n) {
        return fmt::format("lsrs {}, {}", d_n, m);
    }

    std::string thumb16_ASR_reg(Reg m, Reg d_n) {
        return fmt::format("asrs {}, {}", d_n, m);
    }

    std::string thumb16_ADC_reg(Reg m, Reg d_n) {
        return fmt::format("adcs {}, {}", d_n, m);
    }

    std::string thumb16_SBC_reg(Reg m, Reg d_n) {
        return fmt::format("sbcs {}, {}", d_n, m);
    }

    std::string thumb16_ROR_reg(Reg m, Reg d_n) {
        return fmt::format("rors {}, {}", d_n, m);
    }

    std::string thumb16_TST_reg(Reg m, Reg n) {
        return fmt::format("tst {}, {}", n, m);
    }

    std::string thumb16_RSB_imm(Reg n, Reg d) {
        // Pre-UAL syntax: NEGS <Rd>, <Rn>
        return fmt::format("rsbs {}, {}, #0", d, n);
    }

    std::string thumb16_CMP_reg_t1(Reg m, Reg n) {
        return fmt::format("cmp {}, {}", n, m);
    }

    std::string thumb16_CMN_reg(Reg m, Reg n) {
        return fmt::format("cmn {}, {}", n, m);
    }

    std::string thumb16_ORR_reg(Reg m, Reg d_n) {
        return fmt::format("orrs {}, {}", d_n, m);
    }

    std::string thumb16_MUL_reg(Reg n, Reg d_m) {
        return fmt::format("muls {}, {}, {}", d_m, n, d_m);
    }

    std::string thumb16_BIC_reg(Reg m, Reg d_n) {
        return fmt::format("bics {}, {}", d_n, m);
    }

    std::string thumb16_MVN_reg(Reg m, Reg d) {
        return fmt::format("mvns {}, {}", d, m);
    }

    std::string thumb16_ADD_reg_t2(bool d_n_hi, Reg m, Reg d_n_lo) {
        const Reg d_n = d_n_hi ? (d_n_lo + 8) : d_n_lo;
        return fmt::format("add {}, {}", d_n, m);
    }

    std::string thumb16_CMP_reg_t2(bool n_hi, Reg m, Reg n_lo) {
        const Reg n = n_hi ? (n_lo + 8) : n_lo;
        return fmt::format("cmp {}, {}", n, m);
    }

    std::string thumb16_MOV_reg(bool d_hi, Reg m, Reg d_lo) {
        const Reg d = d_hi ? (d_lo + 8) : d_lo;
        return fmt::format("mov {}, {}", d, m);
    }

    std::string thumb16_LDR_literal(Reg t, Imm<8> imm8) {
        const u32 imm32 = imm8.ZeroExtend() << 2;
        return fmt::format("ldr {}, [pc, #{}]", t, imm32);
    }

    std::string thumb16_STR_reg(Reg m, Reg n, Reg t) {
        return fmt::format("str {}, [{}, {}]", t, n, m);
    }

    std::string thumb16_STRH_reg(Reg m, Reg n, Reg t) {
        return fmt::format("strh {}, [{}, {}]", t, n, m);
    }

    std::string thumb16_STRB_reg(Reg m, Reg n, Reg t) {
        return fmt::format("strb {}, [{}, {}]", t, n, m);
    }

    std::string thumb16_LDRSB_reg(Reg m, Reg n, Reg t) {
        return fmt::format("ldrsb {}, [{}, {}]", t, n, m);
    }

    std::string thumb16_LDR_reg(Reg m, Reg n, Reg t) {
        return fmt::format("ldr {}, [{}, {}]", t, n, m);
    }

    std::string thumb16_LDRH_reg(Reg m, Reg n, Reg t) {
        return fmt::format("ldrh {}, [%s, %s]", t, n, m);
    }

    std::string thumb16_LDRB_reg(Reg m, Reg n, Reg t) {
        return fmt::format("ldrb {}, [{}, {}]", t, n, m);
    }

    std::string thumb16_LDRSH_reg(Reg m, Reg n, Reg t) {
        return fmt::format("ldrsh {}, [{}, {}]", t, n, m);
    }

    std::string thumb16_STR_imm_t1(Imm<5> imm5, Reg n, Reg t) {
        const u32 imm32 = imm5.ZeroExtend() << 2;
        return fmt::format("str {}, [{}, #{}]", t, n, imm32);
    }

    std::string thumb16_LDR_imm_t1(Imm<5> imm5, Reg n, Reg t) {
        const u32 imm32 = imm5.ZeroExtend() << 2;
        return fmt::format("ldr {}, [{}, #{}]", t, n, imm32);
    }

    std::string thumb16_STRB_imm(Imm<5> imm5, Reg n, Reg t) {
        const u32 imm32 = imm5.ZeroExtend();
        return fmt::format("strb {}, [{}, #{}]", t, n, imm32);
    }

    std::string thumb16_LDRB_imm(Imm<5> imm5, Reg n, Reg t) {
        const u32 imm32 = imm5.ZeroExtend();
        return fmt::format("ldrb {}, [{}, #{}]", t, n, imm32);
    }

    std::string thumb16_STRH_imm(Imm<5> imm5, Reg n, Reg t) {
        const u32 imm32 = imm5.ZeroExtend() << 1;
        return fmt::format("strh {}, [{}, #{}]", t, n, imm32);
    }

    std::string thumb16_LDRH_imm(Imm<5> imm5, Reg n, Reg t) {
        const u32 imm32 = imm5.ZeroExtend() << 1;
        return fmt::format("ldrh {}, [{}, #{}]", t, n, imm32);
    }

    std::string thumb16_STR_imm_t2(Reg t, Imm<8> imm8) {
        const u32 imm32 = imm8.ZeroExtend() << 2;
        return fmt::format("str {}, [sp, #{}]", t, imm32);
    }

    std::string thumb16_LDR_imm_t2(Reg t, Imm<8> imm8) {
        const u32 imm32 = imm8.ZeroExtend() << 2;
        return fmt::format("ldr {}, [sp, #{}]", t, imm32);
    }

    std::string thumb16_ADR(Reg d, Imm<8> imm8) {
        const u32 imm32 = imm8.ZeroExtend() << 2;
        return fmt::format("adr {}, +#{}", d, imm32);
    }

    std::string thumb16_ADD_sp_t1(Reg d, Imm<8> imm8) {
        const u32 imm32 = imm8.ZeroExtend() << 2;
        return fmt::format("add {}, sp, #{}", d, imm32);
    }

    std::string thumb16_ADD_sp_t2(Imm<7> imm7) {
        const u32 imm32 = imm7.ZeroExtend() << 2;
        return fmt::format("add sp, sp, #{}", imm32);
    }

    std::string thumb16_SUB_sp(Imm<7> imm7) {
        const u32 imm32 = imm7.ZeroExtend() << 2;
        return fmt::format("sub sp, sp, #{}", imm32);
    }

    std::string thumb16_NOP() {
        return "nop";
    }

    std::string thumb16_SEV() {
        return "sev";
    }

    std::string thumb16_SEVL() {
        return "sevl";
    }

    std::string thumb16_WFE() {
        return "wfe";
    }

    std::string thumb16_WFI() {
        return "wfi";
    }

    std::string thumb16_YIELD() {
        return "yield";
    }

    std::string thumb16_IT(Imm<8> imm8) {
        const Cond firstcond = imm8.Bits<4, 7, Cond>();
        const bool firstcond0 = imm8.Bit<4>();
        const auto [x, y, z] = [&] {
            if (imm8.Bits<0, 3>() == 0b1000) {
                return std::make_tuple("", "", "");
            }
            if (imm8.Bits<0, 2>() == 0b100) {
                return std::make_tuple(imm8.Bit<3>() == firstcond0 ? "t" : "e", "", "");
            }
            if (imm8.Bits<0, 1>() == 0b10) {
                return std::make_tuple(imm8.Bit<3>() == firstcond0 ? "t" : "e", imm8.Bit<2>() == firstcond0 ? "t" : "e", "");
            }
            // Sanity note: Here imm8.Bit<0>() is guaranteed to be == 1. (imm8 can never be 0bxxxx0000)
            return std::make_tuple(imm8.Bit<3>() == firstcond0 ? "t" : "e", imm8.Bit<2>() == firstcond0 ? "t" : "e", imm8.Bit<1>() == firstcond0 ? "t" : "e");
        }();
        return fmt::format("it{}{}{} {}", x, y, z, CondToString(firstcond));
    }

    std::string thumb16_SXTH(Reg m, Reg d) {
        return fmt::format("sxth {}, {}", d, m);
    }

    std::string thumb16_SXTB(Reg m, Reg d) {
        return fmt::format("sxtb {}, {}", d, m);
    }

    std::string thumb16_UXTH(Reg m, Reg d) {
        return fmt::format("uxth {}, {}", d, m);
    }

    std::string thumb16_UXTB(Reg m, Reg d) {
        return fmt::format("uxtb {}, {}", d, m);
    }

    std::string thumb16_PUSH(bool M, RegList reg_list) {
        if (M)
            reg_list |= 1 << 14;
        return fmt::format("push {{{}}}", RegListToString(reg_list));
    }

    std::string thumb16_POP(bool P, RegList reg_list) {
        if (P)
            reg_list |= 1 << 15;
        return fmt::format("pop {{{}}}", RegListToString(reg_list));
    }

    std::string thumb16_SETEND(bool E) {
        return fmt::format("setend {}", E ? "BE" : "LE");
    }

    std::string thumb16_CPS(bool im, bool a, bool i, bool f) {
        return fmt::format("cps{} {}{}{}", im ? "id" : "ie", a ? "a" : "", i ? "i" : "", f ? "f" : "");
    }

    std::string thumb16_REV(Reg m, Reg d) {
        return fmt::format("rev {}, {}", d, m);
    }

    std::string thumb16_REV16(Reg m, Reg d) {
        return fmt::format("rev16 {}, {}", d, m);
    }

    std::string thumb16_REVSH(Reg m, Reg d) {
        return fmt::format("revsh {}, {}", d, m);
    }

    std::string thumb16_BKPT(Imm<8> imm8) {
        return fmt::format("bkpt #{}", imm8.ZeroExtend());
    }

    std::string thumb16_STMIA(Reg n, RegList reg_list) {
        return fmt::format("stm {}!, {{{}}}", n, RegListToString(reg_list));
    }

    std::string thumb16_LDMIA(Reg n, RegList reg_list) {
        const bool write_back = !mcl::bit::get_bit(static_cast<size_t>(n), reg_list);
        return fmt::format("ldm {}{}, {{{}}}", n, write_back ? "!" : "", RegListToString(reg_list));
    }

    std::string thumb16_BX(Reg m) {
        return fmt::format("bx {}", m);
    }

    std::string thumb16_BLX_reg(Reg m) {
        return fmt::format("blx {}", m);
    }

    std::string thumb16_CBZ_CBNZ(bool nonzero, Imm<1> i, Imm<5> imm5, Reg n) {
        const char* const name = nonzero ? "cbnz" : "cbz";
        const u32 imm = concatenate(i, imm5, Imm<1>{0}).ZeroExtend();

        return fmt::format("{} {}, #{}", name, n, imm);
    }

    std::string thumb16_UDF() {
        return fmt::format("udf");
    }

    std::string thumb16_SVC(Imm<8> imm8) {
        return fmt::format("svc #{}", imm8.ZeroExtend());
    }

    std::string thumb16_B_t1(Cond cond, Imm<8> imm8) {
        const s32 imm32 = static_cast<s32>((imm8.SignExtend<u32>() << 1) + 4);
        return fmt::format("b{} {}#{}",
                           CondToString(cond),
                           Common::SignToChar(imm32),
                           abs(imm32));
    }

    std::string thumb16_B_t2(Imm<11> imm11) {
        const s32 imm32 = static_cast<s32>((imm11.SignExtend<u32>() << 1) + 4);
        return fmt::format("b {}#{}",
                           Common::SignToChar(imm32),
                           abs(imm32));
    }
};

class DisassemblerThumb32Visitor {
public:
    using instruction_return_type = std::string;

    std::string thumb32_BL_imm(Imm<1> S, Imm<10> hi, Imm<1> j1, Imm<1> j2, Imm<11> lo) { return "BL_imm (unimplemented)"; }
    std::string thumb32_BLX_imm(Imm<1> S, Imm<10> hi, Imm<1> j1, Imm<1> j2, Imm<11> lo) { return "BLX_imm (unimplemented)"; }
    std::string thumb32_B(Imm<1> S, Imm<10> hi, Imm<1> j1, Imm<1> j2, Imm<11> lo) { return "B (unimplemented)"; }
    std::string thumb32_B_cond(Imm<1> S, Cond cond, Imm<6> hi, Imm<1> i1, Imm<1> i2, Imm<11> lo) { return "B_cond (unimplemented)"; }
    std::string thumb32_BXJ(Reg m) { return "BXJ (unimplemented)"; }
    std::string thumb32_CLREX() { return "CLREX (unimplemented)"; }
    std::string thumb32_DMB(Imm<4> /*option*/) { return "DMB (unimplemented)"; }
    std::string thumb32_DSB(Imm<4> /*option*/) { return "DSB (unimplemented)"; }
    std::string thumb32_ISB(Imm<4> /*option*/) { return "ISB (unimplemented)"; }
    std::string thumb32_NOP() { return "NOP (unimplemented)"; }
    std::string thumb32_SEV() { return "SEV (unimplemented)"; }
    std::string thumb32_SEVL() { return "SEVL (unimplemented)"; }
    std::string thumb32_UDF() { return "UDF (unimplemented)"; }
    std::string thumb32_WFE() { return "WFE (unimplemented)"; }
    std::string thumb32_WFI() { return "WFI (unimplemented)"; }
    std::string thumb32_YIELD() { return "YIELD (unimplemented)"; }
    std::string thumb32_MSR_reg(bool write_spsr, Reg n, Imm<4> mask) { return "MSR_reg (unimplemented)"; }
    std::string thumb32_MRS_reg(bool read_spsr, Reg d) { return "MRS_reg (unimplemented)"; }
    std::string thumb32_MCRR(bool two, Reg t2, Reg t, size_t coproc_no, size_t opc, CoprocReg CRm) { return "MCRR (unimplemented)"; }
    std::string thumb32_MRRC(bool two, Reg t2, Reg t, size_t coproc_no, size_t opc, CoprocReg CRm) { return "MRRC (unimplemented)"; }
    std::string thumb32_STC(bool two, bool p, bool u, bool d, bool w, Reg n, CoprocReg CRd, size_t coproc_no, Imm<8> imm8) { return "STC (unimplemented)"; }
    std::string thumb32_LDC(bool two, bool p, bool u, bool d, bool w, Reg n, CoprocReg CRd, size_t coproc_no, Imm<8> imm8) { return "LDC (unimplemented)"; }
    std::string thumb32_CDP(bool two, size_t opc1, CoprocReg CRn, CoprocReg CRd, size_t coproc_no, size_t opc2, CoprocReg CRm) { return "CDP (unimplemented)"; }
    std::string thumb32_MCR(bool two, size_t opc1, CoprocReg CRn, Reg t, size_t coproc_no, size_t opc2, CoprocReg CRm) { return "MCR (unimplemented)"; }
    std::string thumb32_MRC(bool two, size_t opc1, CoprocReg CRn, Reg t, size_t coproc_no, size_t opc2, CoprocReg CRm) { return "MRC (unimplemented)"; }
    std::string thumb32_TST_imm(Imm<1> i, Reg n, Imm<3> imm3, Imm<8> imm8) { return "TST_imm (unimplemented)"; }
    std::string thumb32_AND_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "AND_imm (unimplemented)"; }
    std::string thumb32_BIC_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "BIC_imm (unimplemented)"; }
    std::string thumb32_MOV_imm(Imm<1> i, bool S, Imm<3> imm3, Reg d, Imm<8> imm8) { return "MOV_imm (unimplemented)"; }
    std::string thumb32_ORR_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "ORR_imm (unimplemented)"; }
    std::string thumb32_MVN_imm(Imm<1> i, bool S, Imm<3> imm3, Reg d, Imm<8> imm8) { return "MVN_imm (unimplemented)"; }
    std::string thumb32_ORN_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "ORN_imm (unimplemented)"; }
    std::string thumb32_TEQ_imm(Imm<1> i, Reg n, Imm<3> imm3, Imm<8> imm8) { return "TEQ_imm (unimplemented)"; }
    std::string thumb32_EOR_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "EOR_imm (unimplemented)"; }
    std::string thumb32_CMN_imm(Imm<1> i, Reg n, Imm<3> imm3, Imm<8> imm8) { return "CMN_imm (unimplemented)"; }
    std::string thumb32_ADD_imm_1(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "ADD_imm_1 (unimplemented)"; }
    std::string thumb32_ADC_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "ADC_imm (unimplemented)"; }
    std::string thumb32_SBC_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "SBC_imm (unimplemented)"; }
    std::string thumb32_CMP_imm(Imm<1> i, Reg n, Imm<3> imm3, Imm<8> imm8) { return "CMP_imm (unimplemented)"; }
    std::string thumb32_SUB_imm_1(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "SUB_imm_1 (unimplemented)"; }
    std::string thumb32_RSB_imm(Imm<1> i, bool S, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "RSB_imm (unimplemented)"; }
    std::string thumb32_ADR_t2(Imm<1> imm1, Imm<3> imm3, Reg d, Imm<8> imm8) { return "ADR_t2 (unimplemented)"; }
    std::string thumb32_ADR_t3(Imm<1> imm1, Imm<3> imm3, Reg d, Imm<8> imm8) { return "ADR_t3 (unimplemented)"; }
    std::string thumb32_ADD_imm_2(Imm<1> imm1, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "ADD_imm_2 (unimplemented)"; }
    std::string thumb32_BFC(Imm<3> imm3, Reg d, Imm<2> imm2, Imm<5> msb) { return "BFC (unimplemented)"; }
    std::string thumb32_BFI(Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, Imm<5> msb) { return "BFI (unimplemented)"; }
    std::string thumb32_MOVT(Imm<1> imm1, Imm<4> imm4, Imm<3> imm3, Reg d, Imm<8> imm8) { return "MOVT (unimplemented)"; }
    std::string thumb32_MOVW_imm(Imm<1> imm1, Imm<4> imm4, Imm<3> imm3, Reg d, Imm<8> imm8) { return "MOVW_imm (unimplemented)"; }
    std::string thumb32_SBFX(Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, Imm<5> widthm1) { return "SBFX (unimplemented)"; }
    std::string thumb32_SSAT(bool sh, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, Imm<5> sat_imm) { return "SSAT (unimplemented)"; }
    std::string thumb32_SSAT16(Reg n, Reg d, Imm<4> sat_imm) { return "SSAT16 (unimplemented)"; }
    std::string thumb32_SUB_imm_2(Imm<1> imm1, Reg n, Imm<3> imm3, Reg d, Imm<8> imm8) { return "SUB_imm_2 (unimplemented)"; }
    std::string thumb32_UBFX(Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, Imm<5> widthm1) { return "UBFX (unimplemented)"; }
    std::string thumb32_USAT(bool sh, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, Imm<5> sat_imm) { return "USAT (unimplemented)"; }
    std::string thumb32_USAT16(Reg n, Reg d, Imm<4> sat_imm) { return "USAT16 (unimplemented)"; }
    std::string thumb32_ASR_reg(bool S, Reg m, Reg d, Reg s) { return "ASR_reg (unimplemented)"; }
    std::string thumb32_LSL_reg(bool S, Reg m, Reg d, Reg s) { return "LSL_reg (unimplemented)"; }
    std::string thumb32_LSR_reg(bool S, Reg m, Reg d, Reg s) { return "LSR_reg (unimplemented)"; }
    std::string thumb32_ROR_reg(bool S, Reg m, Reg d, Reg s) { return "ROR_reg (unimplemented)"; }
    std::string thumb32_SXTB(Reg d, SignExtendRotation rotate, Reg m) { return "SXTB (unimplemented)"; }
    std::string thumb32_SXTB16(Reg d, SignExtendRotation rotate, Reg m) { return "SXTB16 (unimplemented)"; }
    std::string thumb32_SXTAB(Reg n, Reg d, SignExtendRotation rotate, Reg m) { return "SXTAB (unimplemented)"; }
    std::string thumb32_SXTAB16(Reg n, Reg d, SignExtendRotation rotate, Reg m) { return "SXTAB16 (unimplemented)"; }
    std::string thumb32_SXTH(Reg d, SignExtendRotation rotate, Reg m) { return "SXTH (unimplemented)"; }
    std::string thumb32_SXTAH(Reg n, Reg d, SignExtendRotation rotate, Reg m) { return "SXTAH (unimplemented)"; }
    std::string thumb32_UXTB(Reg d, SignExtendRotation rotate, Reg m) { return "UXTB (unimplemented)"; }
    std::string thumb32_UXTB16(Reg d, SignExtendRotation rotate, Reg m) { return "UXTB16 (unimplemented)"; }
    std::string thumb32_UXTAB(Reg n, Reg d, SignExtendRotation rotate, Reg m) { return "UXTAB (unimplemented)"; }
    std::string thumb32_UXTAB16(Reg n, Reg d, SignExtendRotation rotate, Reg m) { return "UXTAB16 (unimplemented)"; }
    std::string thumb32_UXTH(Reg d, SignExtendRotation rotate, Reg m) { return "UXTH (unimplemented)"; }
    std::string thumb32_UXTAH(Reg n, Reg d, SignExtendRotation rotate, Reg m) { return "UXTAH (unimplemented)"; }
    std::string thumb32_TST_reg(Reg n, Imm<3> imm3, Imm<2> imm2, ShiftType type, Reg m) { return "TST_reg (unimplemented)"; }
    std::string thumb32_AND_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "AND_reg (unimplemented)"; }
    std::string thumb32_BIC_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "BIC_reg (unimplemented)"; }
    std::string thumb32_MOV_reg(bool S, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "MOV_reg (unimplemented)"; }
    std::string thumb32_ORR_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "ORR_reg (unimplemented)"; }
    std::string thumb32_MVN_reg(bool S, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "MVN_reg (unimplemented)"; }
    std::string thumb32_ORN_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "ORN_reg (unimplemented)"; }
    std::string thumb32_TEQ_reg(Reg n, Imm<3> imm3, Imm<2> imm2, ShiftType type, Reg m) { return "TEQ_reg (unimplemented)"; }
    std::string thumb32_EOR_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "EOR_reg (unimplemented)"; }
    std::string thumb32_PKH(Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, Imm<1> tb, Reg m) { return "PKH (unimplemented)"; }
    std::string thumb32_CMN_reg(Reg n, Imm<3> imm3, Imm<2> imm2, ShiftType type, Reg m) { return "CMN_reg (unimplemented)"; }
    std::string thumb32_ADD_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "ADD_reg (unimplemented)"; }
    std::string thumb32_ADC_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "ADC_reg (unimplemented)"; }
    std::string thumb32_SBC_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "SBC_reg (unimplemented)"; }
    std::string thumb32_CMP_reg(Reg n, Imm<3> imm3, Imm<2> imm2, ShiftType type, Reg m) { return "CMP_reg (unimplemented)"; }
    std::string thumb32_SUB_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "SUB_reg (unimplemented)"; }
    std::string thumb32_RSB_reg(bool S, Reg n, Imm<3> imm3, Reg d, Imm<2> imm2, ShiftType type, Reg m) { return "RSB_reg (unimplemented)"; }
    std::string thumb32_PLD_lit(bool /*U*/, Imm<12> /*imm12*/) { return "PLD_lit (unimplemented)"; }
    std::string thumb32_PLD_imm8(bool W, Reg /*n*/, Imm<8> /*imm8*/) { return "PLD_imm8 (unimplemented)"; }
    std::string thumb32_PLD_imm12(bool W, Reg /*n*/, Imm<12> /*imm12*/) { return "PLD_imm12 (unimplemented)"; }
    std::string thumb32_PLD_reg(bool W, Reg /*n*/, Imm<2> /*imm2*/, Reg m) { return "PLD_reg (unimplemented)"; }
    std::string thumb32_PLI_lit(bool /*U*/, Imm<12> /*imm12*/) { return "PLI_lit (unimplemented)"; }
    std::string thumb32_PLI_imm8(Reg /*n*/, Imm<8> /*imm8*/) { return "PLI_imm8 (unimplemented)"; }
    std::string thumb32_PLI_imm12(Reg /*n*/, Imm<12> /*imm12*/) { return "PLI_imm12 (unimplemented)"; }
    std::string thumb32_PLI_reg(Reg /*n*/, Imm<2> /*imm2*/, Reg m) { return "PLI_reg (unimplemented)"; }
    std::string thumb32_LDRB_lit(bool U, Reg t, Imm<12> imm12) { return "LDRB_lit (unimplemented)"; }
    std::string thumb32_LDRB_imm8(Reg n, Reg t, bool P, bool U, bool W, Imm<8> imm8) { return "LDRB_imm8 (unimplemented)"; }
    std::string thumb32_LDRB_imm12(Reg n, Reg t, Imm<12> imm12) { return "LDRB_imm12 (unimplemented)"; }
    std::string thumb32_LDRB_reg(Reg n, Reg t, Imm<2> imm2, Reg m) { return "LDRB_reg (unimplemented)"; }
    std::string thumb32_LDRBT(Reg n, Reg t, Imm<8> imm8) { return "LDRBT (unimplemented)"; }
    std::string thumb32_LDRSB_lit(bool U, Reg t, Imm<12> imm12) { return "LDRSB_lit (unimplemented)"; }
    std::string thumb32_LDRSB_imm8(Reg n, Reg t, bool P, bool U, bool W, Imm<8> imm8) { return "LDRSB_imm8 (unimplemented)"; }
    std::string thumb32_LDRSB_imm12(Reg n, Reg t, Imm<12> imm12) { return "LDRSB_imm12 (unimplemented)"; }
    std::string thumb32_LDRSB_reg(Reg n, Reg t, Imm<2> imm2, Reg m) { return "LDRSB_reg (unimplemented)"; }
    std::string thumb32_LDRSBT(Reg n, Reg t, Imm<8> imm8) { return "LDRSBT (unimplemented)"; }
    std::string thumb32_LDRH_lit(bool U, Reg t, Imm<12> imm12) { return "LDRH_lit (unimplemented)"; }
    std::string thumb32_LDRH_reg(Reg n, Reg t, Imm<2> imm2, Reg m) { return "LDRH_reg (unimplemented)"; }
    std::string thumb32_LDRH_imm8(Reg n, Reg t, bool P, bool U, bool W, Imm<8> imm8) { return "LDRH_imm8 (unimplemented)"; }
    std::string thumb32_LDRH_imm12(Reg n, Reg t, Imm<12> imm12) { return "LDRH_imm12 (unimplemented)"; }
    std::string thumb32_LDRHT(Reg n, Reg t, Imm<8> imm8) { return "LDRHT (unimplemented)"; }
    std::string thumb32_LDRSH_lit(bool U, Reg t, Imm<12> imm12) { return "LDRSH_lit (unimplemented)"; }
    std::string thumb32_LDRSH_reg(Reg n, Reg t, Imm<2> imm2, Reg m) { return "LDRSH_reg (unimplemented)"; }
    std::string thumb32_LDRSH_imm8(Reg n, Reg t, bool P, bool U, bool W, Imm<8> imm8) { return "LDRSH_imm8 (unimplemented)"; }
    std::string thumb32_LDRSH_imm12(Reg n, Reg t, Imm<12> imm12) { return "LDRSH_imm12 (unimplemented)"; }
    std::string thumb32_LDRSHT(Reg n, Reg t, Imm<8> imm8) { return "LDRSHT (unimplemented)"; }
    std::string thumb32_LDA(Reg n, Reg t) { return "LDA (unimplemented)"; }
    std::string thumb32_LDRD_imm_1(bool U, Reg n, Reg t, Reg t2, Imm<8> imm8) { return "LDRD_imm_1 (unimplemented)"; }
    std::string thumb32_LDRD_imm_2(bool U, bool W, Reg n, Reg t, Reg t2, Imm<8> imm8) { return "LDRD_imm_2 (unimplemented)"; }
    std::string thumb32_LDRD_lit_1(bool U, Reg t, Reg t2, Imm<8> imm8) { return "LDRD_lit_1 (unimplemented)"; }
    std::string thumb32_LDRD_lit_2(bool U, bool W, Reg t, Reg t2, Imm<8> imm8) { return "LDRD_lit_2 (unimplemented)"; }
    std::string thumb32_STRD_imm_1(bool U, Reg n, Reg t, Reg t2, Imm<8> imm8) { return "STRD_imm_1 (unimplemented)"; }
    std::string thumb32_STRD_imm_2(bool U, bool W, Reg n, Reg t, Reg t2, Imm<8> imm8) { return "STRD_imm_2 (unimplemented)"; }
    std::string thumb32_LDREX(Reg n, Reg t, Imm<8> imm8) { return "LDREX (unimplemented)"; }
    std::string thumb32_LDREXB(Reg n, Reg t) { return "LDREXB (unimplemented)"; }
    std::string thumb32_LDREXD(Reg n, Reg t, Reg t2) { return "LDREXD (unimplemented)"; }
    std::string thumb32_LDREXH(Reg n, Reg t) { return "LDREXH (unimplemented)"; }
    std::string thumb32_STL(Reg n, Reg t) { return "STL (unimplemented)"; }
    std::string thumb32_STREX(Reg n, Reg t, Reg d, Imm<8> imm8) { return "STREX (unimplemented)"; }
    std::string thumb32_STREXB(Reg n, Reg t, Reg d) { return "STREXB (unimplemented)"; }
    std::string thumb32_STREXD(Reg n, Reg t, Reg t2, Reg d) { return "STREXD (unimplemented)"; }
    std::string thumb32_STREXH(Reg n, Reg t, Reg d) { return "STREXH (unimplemented)"; }
    std::string thumb32_TBB(Reg n, Reg m) { return "TBB (unimplemented)"; }
    std::string thumb32_TBH(Reg n, Reg m) { return "TBH (unimplemented)"; }
    std::string thumb32_LDMDB(bool W, Reg n, Imm<16> reg_list) { return "LDMDB (unimplemented)"; }
    std::string thumb32_LDMIA(bool W, Reg n, Imm<16> reg_list) { return "LDMIA (unimplemented)"; }
    std::string thumb32_POP(Imm<16> reg_list) { return "POP (unimplemented)"; }
    std::string thumb32_PUSH(Imm<15> reg_list) { return "PUSH (unimplemented)"; }
    std::string thumb32_STMIA(bool W, Reg n, Imm<15> reg_list) { return "STMIA (unimplemented)"; }
    std::string thumb32_STMDB(bool W, Reg n, Imm<15> reg_list) { return "STMDB (unimplemented)"; }
    std::string thumb32_LDR_lit(bool U, Reg t, Imm<12> imm12) { return "LDR_lit (unimplemented)"; }
    std::string thumb32_LDR_imm8(Reg n, Reg t, bool P, bool U, bool W, Imm<8> imm8) { return "LDR_imm8 (unimplemented)"; }
    std::string thumb32_LDR_imm12(Reg n, Reg t, Imm<12> imm12) { return "LDR_imm12 (unimplemented)"; }
    std::string thumb32_LDR_reg(Reg n, Reg t, Imm<2> imm2, Reg m) { return "LDR_reg (unimplemented)"; }
    std::string thumb32_LDRT(Reg n, Reg t, Imm<8> imm8) { return "LDRT (unimplemented)"; }
    std::string thumb32_SDIV(Reg n, Reg d, Reg m) { return "SDIV (unimplemented)"; }
    std::string thumb32_SMLAL(Reg n, Reg dLo, Reg dHi, Reg m) { return "SMLAL (unimplemented)"; }
    std::string thumb32_SMLALD(Reg n, Reg dLo, Reg dHi, bool M, Reg m) { return "SMLALD (unimplemented)"; }
    std::string thumb32_SMLALXY(Reg n, Reg dLo, Reg dHi, bool N, bool M, Reg m) { return "SMLALXY (unimplemented)"; }
    std::string thumb32_SMLSLD(Reg n, Reg dLo, Reg dHi, bool M, Reg m) { return "SMLSLD (unimplemented)"; }
    std::string thumb32_SMULL(Reg n, Reg dLo, Reg dHi, Reg m) { return "SMULL (unimplemented)"; }
    std::string thumb32_UDIV(Reg n, Reg d, Reg m) { return "UDIV (unimplemented)"; }
    std::string thumb32_UMLAL(Reg n, Reg dLo, Reg dHi, Reg m) { return "UMLAL (unimplemented)"; }
    std::string thumb32_UMULL(Reg n, Reg dLo, Reg dHi, Reg m) { return "UMULL (unimplemented)"; }
    std::string thumb32_UMAAL(Reg n, Reg dLo, Reg dHi, Reg m) { return "UMAAL (unimplemented)"; }
    std::string thumb32_CLZ(Reg n, Reg d, Reg m) { return "CLZ (unimplemented)"; }
    std::string thumb32_QADD(Reg n, Reg d, Reg m) { return "QADD (unimplemented)"; }
    std::string thumb32_QDADD(Reg n, Reg d, Reg m) { return "QDADD (unimplemented)"; }
    std::string thumb32_QDSUB(Reg n, Reg d, Reg m) { return "QDSUB (unimplemented)"; }
    std::string thumb32_QSUB(Reg n, Reg d, Reg m) { return "QSUB (unimplemented)"; }
    std::string thumb32_RBIT(Reg n, Reg d, Reg m) { return "RBIT (unimplemented)"; }
    std::string thumb32_REV(Reg n, Reg d, Reg m) { return "REV (unimplemented)"; }
    std::string thumb32_REV16(Reg n, Reg d, Reg m) { return "REV16 (unimplemented)"; }
    std::string thumb32_REVSH(Reg n, Reg d, Reg m) { return "REVSH (unimplemented)"; }
    std::string thumb32_SEL(Reg n, Reg d, Reg m) { return "SEL (unimplemented)"; }
    std::string thumb32_MLA(Reg n, Reg a, Reg d, Reg m) { return "MLA (unimplemented)"; }
    std::string thumb32_MLS(Reg n, Reg a, Reg d, Reg m) { return "MLS (unimplemented)"; }
    std::string thumb32_MUL(Reg n, Reg d, Reg m) { return "MUL (unimplemented)"; }
    std::string thumb32_SMLAD(Reg n, Reg a, Reg d, bool X, Reg m) { return "SMLAD (unimplemented)"; }
    std::string thumb32_SMLSD(Reg n, Reg a, Reg d, bool X, Reg m) { return "SMLSD (unimplemented)"; }
    std::string thumb32_SMLAXY(Reg n, Reg a, Reg d, bool N, bool M, Reg m) { return "SMLAXY (unimplemented)"; }
    std::string thumb32_SMMLA(Reg n, Reg a, Reg d, bool R, Reg m) { return "SMMLA (unimplemented)"; }
    std::string thumb32_SMMLS(Reg n, Reg a, Reg d, bool R, Reg m) { return "SMMLS (unimplemented)"; }
    std::string thumb32_SMMUL(Reg n, Reg d, bool R, Reg m) { return "SMMUL (unimplemented)"; }
    std::string thumb32_SMUAD(Reg n, Reg d, bool M, Reg m) { return "SMUAD (unimplemented)"; }
    std::string thumb32_SMUSD(Reg n, Reg d, bool M, Reg m) { return "SMUSD (unimplemented)"; }
    std::string thumb32_SMULXY(Reg n, Reg d, bool N, bool M, Reg m) { return "SMULXY (unimplemented)"; }
    std::string thumb32_SMLAWY(Reg n, Reg a, Reg d, bool M, Reg m) { return "SMLAWY (unimplemented)"; }
    std::string thumb32_SMULWY(Reg n, Reg d, bool M, Reg m) { return "SMULWY (unimplemented)"; }
    std::string thumb32_USAD8(Reg n, Reg d, Reg m) { return "USAD8 (unimplemented)"; }
    std::string thumb32_USADA8(Reg n, Reg a, Reg d, Reg m) { return "USADA8 (unimplemented)"; }
    std::string thumb32_SADD8(Reg n, Reg d, Reg m) { return "SADD8 (unimplemented)"; }
    std::string thumb32_SADD16(Reg n, Reg d, Reg m) { return "SADD16 (unimplemented)"; }
    std::string thumb32_SASX(Reg n, Reg d, Reg m) { return "SASX (unimplemented)"; }
    std::string thumb32_SSAX(Reg n, Reg d, Reg m) { return "SSAX (unimplemented)"; }
    std::string thumb32_SSUB8(Reg n, Reg d, Reg m) { return "SSUB8 (unimplemented)"; }
    std::string thumb32_SSUB16(Reg n, Reg d, Reg m) { return "SSUB16 (unimplemented)"; }
    std::string thumb32_UADD8(Reg n, Reg d, Reg m) { return "UADD8 (unimplemented)"; }
    std::string thumb32_UADD16(Reg n, Reg d, Reg m) { return "UADD16 (unimplemented)"; }
    std::string thumb32_UASX(Reg n, Reg d, Reg m) { return "UASX (unimplemented)"; }
    std::string thumb32_USAX(Reg n, Reg d, Reg m) { return "USAX (unimplemented)"; }
    std::string thumb32_USUB8(Reg n, Reg d, Reg m) { return "USUB8 (unimplemented)"; }
    std::string thumb32_USUB16(Reg n, Reg d, Reg m) { return "USUB16 (unimplemented)"; }
    std::string thumb32_QADD8(Reg n, Reg d, Reg m) { return "QADD8 (unimplemented)"; }
    std::string thumb32_QADD16(Reg n, Reg d, Reg m) { return "QADD16 (unimplemented)"; }
    std::string thumb32_QASX(Reg n, Reg d, Reg m) { return "QASX (unimplemented)"; }
    std::string thumb32_QSAX(Reg n, Reg d, Reg m) { return "QSAX (unimplemented)"; }
    std::string thumb32_QSUB8(Reg n, Reg d, Reg m) { return "QSUB8 (unimplemented)"; }
    std::string thumb32_QSUB16(Reg n, Reg d, Reg m) { return "QSUB16 (unimplemented)"; }
    std::string thumb32_UQADD8(Reg n, Reg d, Reg m) { return "UQADD8 (unimplemented)"; }
    std::string thumb32_UQADD16(Reg n, Reg d, Reg m) { return "UQADD16 (unimplemented)"; }
    std::string thumb32_UQASX(Reg n, Reg d, Reg m) { return "UQASX (unimplemented)"; }
    std::string thumb32_UQSAX(Reg n, Reg d, Reg m) { return "UQSAX (unimplemented)"; }
    std::string thumb32_UQSUB8(Reg n, Reg d, Reg m) { return "UQSUB8 (unimplemented)"; }
    std::string thumb32_UQSUB16(Reg n, Reg d, Reg m) { return "UQSUB16 (unimplemented)"; }
    std::string thumb32_SHADD8(Reg n, Reg d, Reg m) { return "SHADD8 (unimplemented)"; }
    std::string thumb32_SHADD16(Reg n, Reg d, Reg m) { return "SHADD16 (unimplemented)"; }
    std::string thumb32_SHASX(Reg n, Reg d, Reg m) { return "SHASX (unimplemented)"; }
    std::string thumb32_SHSAX(Reg n, Reg d, Reg m) { return "SHSAX (unimplemented)"; }
    std::string thumb32_SHSUB8(Reg n, Reg d, Reg m) { return "SHSUB8 (unimplemented)"; }
    std::string thumb32_SHSUB16(Reg n, Reg d, Reg m) { return "SHSUB16 (unimplemented)"; }
    std::string thumb32_UHADD8(Reg n, Reg d, Reg m) { return "UHADD8 (unimplemented)"; }
    std::string thumb32_UHADD16(Reg n, Reg d, Reg m) { return "UHADD16 (unimplemented)"; }
    std::string thumb32_UHASX(Reg n, Reg d, Reg m) { return "UHASX (unimplemented)"; }
    std::string thumb32_UHSAX(Reg n, Reg d, Reg m) { return "UHSAX (unimplemented)"; }
    std::string thumb32_UHSUB8(Reg n, Reg d, Reg m) { return "UHSUB8 (unimplemented)"; }
    std::string thumb32_UHSUB16(Reg n, Reg d, Reg m) { return "UHSUB16 (unimplemented)"; }
    std::string thumb32_STRB_imm_1(Reg n, Reg t, bool P, bool U, Imm<8> imm8) { return "STRB_imm_1 (unimplemented)"; }
    std::string thumb32_STRB_imm_2(Reg n, Reg t, Imm<8> imm8) { return "STRB_imm_2 (unimplemented)"; }
    std::string thumb32_STRB_imm_3(Reg n, Reg t, Imm<12> imm12) { return "STRB_imm_3 (unimplemented)"; }
    std::string thumb32_STRBT(Reg n, Reg t, Imm<8> imm8) { return "STRBT (unimplemented)"; }
    std::string thumb32_STRB(Reg n, Reg t, Imm<2> imm2, Reg m) { return "STRB (unimplemented)"; }
    std::string thumb32_STRH_imm_1(Reg n, Reg t, bool P, bool U, Imm<8> imm8) { return "STRH_imm_1 (unimplemented)"; }
    std::string thumb32_STRH_imm_2(Reg n, Reg t, Imm<8> imm8) { return "STRH_imm_2 (unimplemented)"; }
    std::string thumb32_STRH_imm_3(Reg n, Reg t, Imm<12> imm12) { return "STRH_imm_3 (unimplemented)"; }
    std::string thumb32_STRHT(Reg n, Reg t, Imm<8> imm8) { return "STRHT (unimplemented)"; }
    std::string thumb32_STRH(Reg n, Reg t, Imm<2> imm2, Reg m) { return "STRH (unimplemented)"; }
    std::string thumb32_STR_imm_1(Reg n, Reg t, bool P, bool U, Imm<8> imm8) { return "STR_imm_1 (unimplemented)"; }
    std::string thumb32_STR_imm_2(Reg n, Reg t, Imm<8> imm8) { return "STR_imm_2 (unimplemented)"; }
    std::string thumb32_STR_imm_3(Reg n, Reg t, Imm<12> imm12) { return "STR_imm_3 (unimplemented)"; }
    std::string thumb32_STRT(Reg n, Reg t, Imm<8> imm8) { return "STRT (unimplemented)"; }
    std::string thumb32_STR_reg(Reg n, Reg t, Imm<2> imm2, Reg m) { return "STR_reg (unimplemented)"; }
};

std::string DisassembleThumb16(u16 instruction) {
    DisassemblerThumb16Visitor visitor;
    auto decoder = DecodeThumb16<DisassemblerThumb16Visitor>(instruction);
    return !decoder ? fmt::format("UNKNOWN: {:x}", instruction) : decoder->get().call(visitor, instruction);
}

std::string DisassembleThumb32(u32 instruction) {
    DisassemblerThumb32Visitor visitor;
    auto decoder = DecodeThumb32<DisassemblerThumb32Visitor>(instruction);
    return !decoder ? fmt::format("UNKNOWN: {:x}", instruction) : decoder->get().call(visitor, instruction);
}

}  // namespace Dynarmic::A32
