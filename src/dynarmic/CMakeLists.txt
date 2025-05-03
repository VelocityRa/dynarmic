add_library(dynarmic
    common/always_false.h
    common/cast_util.h
    common/crypto/aes.cpp
    common/crypto/aes.h
    common/crypto/crc32.cpp
    common/crypto/crc32.h
    common/crypto/sm4.cpp
    common/crypto/sm4.h
    common/fp/fpcr.h
    common/fp/fpsr.h
    common/fp/fused.cpp
    common/fp/fused.h
    common/fp/info.h
    common/fp/mantissa_util.h
    common/fp/op.h
    common/fp/op/FPCompare.cpp
    common/fp/op/FPCompare.h
    common/fp/op/FPConvert.cpp
    common/fp/op/FPConvert.h
    common/fp/op/FPMulAdd.cpp
    common/fp/op/FPMulAdd.h
    common/fp/op/FPNeg.h
    common/fp/op/FPRecipEstimate.cpp
    common/fp/op/FPRecipEstimate.h
    common/fp/op/FPRecipExponent.cpp
    common/fp/op/FPRecipExponent.h
    common/fp/op/FPRecipStepFused.cpp
    common/fp/op/FPRecipStepFused.h
    common/fp/op/FPRoundInt.cpp
    common/fp/op/FPRoundInt.h
    common/fp/op/FPRSqrtEstimate.cpp
    common/fp/op/FPRSqrtEstimate.h
    common/fp/op/FPRSqrtStepFused.cpp
    common/fp/op/FPRSqrtStepFused.h
    common/fp/op/FPToFixed.cpp
    common/fp/op/FPToFixed.h
    common/fp/process_exception.cpp
    common/fp/process_exception.h
    common/fp/process_nan.cpp
    common/fp/process_nan.h
    common/fp/rounding_mode.h
    common/fp/unpacked.cpp
    common/fp/unpacked.h
    common/fp/util.h
    common/llvm_disassemble.cpp
    common/llvm_disassemble.h
    common/lut_from_list.h
    common/math_util.cpp
    common/math_util.h
    common/memory_pool.cpp
    common/memory_pool.h
    common/safe_ops.h
    common/string_util.h
    common/u128.cpp
    common/u128.h
    common/variant_util.h
    frontend/A32/a32_types.cpp
    frontend/A32/a32_types.h
    frontend/decoder/decoder_detail.h
    frontend/decoder/matcher.h
    frontend/imm.cpp
    frontend/imm.h
    interface/optimization_flags.h
)

if ("A32" IN_LIST DYNARMIC_FRONTENDS)
    target_sources(dynarmic PRIVATE
        frontend/A32/decoder/arm.h
        frontend/A32/decoder/arm.inc
        frontend/A32/decoder/asimd.h
        frontend/A32/decoder/asimd.inc
        frontend/A32/decoder/thumb16.h
        frontend/A32/decoder/thumb16.inc
        frontend/A32/decoder/thumb32.h
        frontend/A32/decoder/thumb32.inc
        frontend/A32/decoder/vfp.h
        frontend/A32/decoder/vfp.inc
        frontend/A32/disassembler/disassembler.h
        frontend/A32/disassembler/disassembler_arm.cpp
        frontend/A32/disassembler/disassembler_thumb.cpp
        frontend/A32/FPSCR.h
        frontend/A32/ITState.h
        frontend/A32/PSR.h
        interface/A32/arch_version.h
        interface/A32/coprocessor_util.h
        interface/A32/disassembler.h
    )
endif()

include(CreateDirectoryGroups)
create_target_directory_groups(dynarmic)

target_include_directories(dynarmic PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
set_target_properties(dynarmic PROPERTIES
    VERSION ${dynarmic_VERSION}
    SOVERSION ${dynarmic_VERSION_MAJOR}.${dynarmic_VERSION_MINOR}
)
target_compile_options(dynarmic PRIVATE ${DYNARMIC_CXX_FLAGS})
target_link_libraries(dynarmic
    PRIVATE
        fmt::fmt
        merry::mcl
        tsl::robin_map
)
if (DYNARMIC_IGNORE_ASSERTS)
    target_compile_definitions(dynarmic PRIVATE MCL_IGNORE_ASSERTS=1)
endif()
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(dynarmic PRIVATE FMT_USE_WINDOWS_H=0)
endif()
target_compile_definitions(dynarmic PRIVATE FMT_USE_USER_DEFINED_LITERALS=1)
