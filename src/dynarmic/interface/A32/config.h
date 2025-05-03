/* This file is part of the dynarmic project.
 * Copyright (c) 2016 MerryMage
 * SPDX-License-Identifier: 0BSD
 */

#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>

#include "dynarmic/frontend/A32/translate/translate_callbacks.h"
#include "dynarmic/interface/A32/arch_version.h"
#include "dynarmic/interface/optimization_flags.h"

namespace Dynarmic {
namespace A32 {

using VAddr = std::uint32_t;

enum class Exception {
    /// An UndefinedFault occured due to executing instruction with an unallocated encoding
    UndefinedInstruction,
    /// An unpredictable instruction is to be executed. Implementation-defined behaviour should now happen.
    /// This behaviour is up to the user of this library to define.
    UnpredictableInstruction,
    /// A decode error occurred when decoding this instruction. This should never happen.
    DecodeError,
    /// A SEV instruction was executed. The event register of all PEs should be set. (Hint instruction.)
    SendEvent,
    /// A SEVL instruction was executed. The event register of the current PE should be set. (Hint instruction.)
    SendEventLocal,
    /// A WFI instruction was executed. You may now enter a low-power state. (Hint instruction.)
    WaitForInterrupt,
    /// A WFE instruction was executed. You may now enter a low-power state if the event register is clear. (Hint instruction.)
    WaitForEvent,
    /// A YIELD instruction was executed. (Hint instruction.)
    Yield,
    /// A BKPT instruction was executed.
    Breakpoint,
    /// A PLD instruction was executed. (Hint instruction.)
    PreloadData,
    /// A PLDW instruction was executed. (Hint instruction.)
    PreloadDataWithIntentToWrite,
    /// A PLI instruction was executed. (Hint instruction.)
    PreloadInstruction,
    /// Attempted to execute a code block at an address for which MemoryReadCode returned std::nullopt.
    /// (Intended to be used to emulate memory protection faults.)
    NoExecuteFault,
};

}  // namespace A32
}  // namespace Dynarmic
