add_library(dynarmic
    ../include/dynarmic/A32/a32.h
    ../include/dynarmic/A32/config.h
    ../include/dynarmic/A32/coprocessor.h
    ../include/dynarmic/A32/coprocessor_util.h
    ../include/dynarmic/A32/disassembler.h
    common/address_range.h
    common/aes.cpp
    common/aes.h
    common/assert.h
    common/bit_util.h
    common/cast_util.h
    common/common_types.h
    common/crc32.cpp
    common/crc32.h
    common/fp_util.h
    common/intrusive_list.h
    common/iterator_util.h
    common/llvm_disassemble.cpp
    common/llvm_disassemble.h
    common/macro_util.h
    common/math_util.h
    common/memory_pool.cpp
    common/memory_pool.h
    common/mp.h
    common/scope_exit.h
    common/sm4.cpp
    common/sm4.h
    common/string_util.h
    common/variant_util.h
    frontend/A32/decoder/arm.h
    frontend/A32/decoder/thumb16.h
    frontend/A32/decoder/thumb32.h
    frontend/A32/decoder/vfp2.h
    frontend/A32/disassembler/disassembler.h
    frontend/A32/disassembler/disassembler_arm.cpp
    frontend/A32/disassembler/disassembler_thumb.cpp
    frontend/A32/FPSCR.h
    frontend/A32/ir_emitter.cpp
    frontend/A32/ir_emitter.h
    frontend/A32/location_descriptor.cpp
    frontend/A32/location_descriptor.h
    frontend/A32/PSR.h
    frontend/A32/translate/translate.cpp
    frontend/A32/translate/translate.h
    frontend/A32/translate/translate_arm.cpp
    frontend/A32/translate/translate_arm/branch.cpp
    frontend/A32/translate/translate_arm/coprocessor.cpp
    frontend/A32/translate/translate_arm/data_processing.cpp
    frontend/A32/translate/translate_arm/exception_generating.cpp
    frontend/A32/translate/translate_arm/extension.cpp
    frontend/A32/translate/translate_arm/load_store.cpp
    frontend/A32/translate/translate_arm/misc.cpp
    frontend/A32/translate/translate_arm/multiply.cpp
    frontend/A32/translate/translate_arm/packing.cpp
    frontend/A32/translate/translate_arm/parallel.cpp
    frontend/A32/translate/translate_arm/reversal.cpp
    frontend/A32/translate/translate_arm/saturated.cpp
    frontend/A32/translate/translate_arm/status_register_access.cpp
    frontend/A32/translate/translate_arm/synchronization.cpp
    frontend/A32/translate/translate_arm/translate_arm.h
    frontend/A32/translate/translate_arm/vfp2.cpp
    frontend/A32/translate/translate_thumb.cpp
    frontend/A32/types.cpp
    frontend/A32/types.h
    frontend/A64/decoder/a64.h
    frontend/A64/decoder/a64.inc
    frontend/A64/FPCR.h
    frontend/A64/imm.h
    frontend/A64/ir_emitter.cpp
    frontend/A64/ir_emitter.h
    frontend/A64/location_descriptor.cpp
    frontend/A64/location_descriptor.h
    frontend/A64/translate/impl/branch.cpp
    frontend/A64/translate/impl/data_processing_addsub.cpp
    frontend/A64/translate/impl/data_processing_bitfield.cpp
    frontend/A64/translate/impl/data_processing_conditional_compare.cpp
    frontend/A64/translate/impl/data_processing_conditional_select.cpp
    frontend/A64/translate/impl/data_processing_crc32.cpp
    frontend/A64/translate/impl/data_processing_logical.cpp
    frontend/A64/translate/impl/data_processing_multiply.cpp
    frontend/A64/translate/impl/data_processing_pcrel.cpp
    frontend/A64/translate/impl/data_processing_register.cpp
    frontend/A64/translate/impl/data_processing_shift.cpp
    frontend/A64/translate/impl/exception_generating.cpp
    frontend/A64/translate/impl/floating_point_compare.cpp
    frontend/A64/translate/impl/floating_point_conversion_fixed_point.cpp
    frontend/A64/translate/impl/floating_point_conversion_integer.cpp
    frontend/A64/translate/impl/floating_point_conditional_compare.cpp
    frontend/A64/translate/impl/floating_point_conditional_select.cpp
    frontend/A64/translate/impl/floating_point_data_processing_one_register.cpp
    frontend/A64/translate/impl/floating_point_data_processing_three_register.cpp
    frontend/A64/translate/impl/floating_point_data_processing_two_register.cpp
    frontend/A64/translate/impl/impl.cpp
    frontend/A64/translate/impl/impl.h
    frontend/A64/translate/impl/load_store_exclusive.cpp
    frontend/A64/translate/impl/load_store_load_literal.cpp
    frontend/A64/translate/impl/load_store_multiple_structures.cpp
    frontend/A64/translate/impl/load_store_register_immediate.cpp
    frontend/A64/translate/impl/load_store_register_pair.cpp
    frontend/A64/translate/impl/load_store_register_register_offset.cpp
    frontend/A64/translate/impl/load_store_register_unprivileged.cpp
    frontend/A64/translate/impl/move_wide.cpp
    frontend/A64/translate/impl/simd_aes.cpp
    frontend/A64/translate/impl/simd_copy.cpp
    frontend/A64/translate/impl/simd_crypto_four_register.cpp
    frontend/A64/translate/impl/simd_crypto_three_register.cpp
    frontend/A64/translate/impl/simd_extract.cpp
    frontend/A64/translate/impl/simd_modified_immediate.cpp
    frontend/A64/translate/impl/simd_permute.cpp
    frontend/A64/translate/impl/simd_scalar_pairwise.cpp
    frontend/A64/translate/impl/simd_scalar_shift_by_immediate.cpp
    frontend/A64/translate/impl/simd_scalar_three_same.cpp
    frontend/A64/translate/impl/simd_scalar_two_register_misc.cpp
    frontend/A64/translate/impl/simd_sha.cpp
    frontend/A64/translate/impl/simd_sha512.cpp
    frontend/A64/translate/impl/simd_shift_by_immediate.cpp
    frontend/A64/translate/impl/simd_three_different.cpp
    frontend/A64/translate/impl/simd_three_same.cpp
    frontend/A64/translate/impl/simd_two_register_misc.cpp
    frontend/A64/translate/impl/simd_vector_x_indexed_element.cpp
    frontend/A64/translate/impl/sys_dc.cpp
    frontend/A64/translate/impl/system.cpp
    frontend/A64/translate/translate.cpp
    frontend/A64/translate/translate.h
    frontend/A64/types.cpp
    frontend/A64/types.h
    frontend/decoder/decoder_detail.h
    frontend/decoder/matcher.h
    frontend/ir/basic_block.cpp
    frontend/ir/basic_block.h
    frontend/ir/ir_emitter.cpp
    frontend/ir/ir_emitter.h
    frontend/ir/location_descriptor.cpp
    frontend/ir/location_descriptor.h
    frontend/ir/microinstruction.cpp
    frontend/ir/microinstruction.h
    frontend/ir/opcodes.cpp
    frontend/ir/opcodes.h
    frontend/ir/opcodes.inc
    frontend/ir/terminal.h
    frontend/ir/type.cpp
    frontend/ir/type.h
    frontend/ir/value.cpp
    frontend/ir/value.h
    ir_opt/a32_constant_memory_reads_pass.cpp
    ir_opt/a32_get_set_elimination_pass.cpp
    ir_opt/a64_callback_config_pass.cpp
    ir_opt/a64_get_set_elimination_pass.cpp
    ir_opt/a64_merge_interpret_blocks.cpp
    ir_opt/constant_propagation_pass.cpp
    ir_opt/dead_code_elimination_pass.cpp
    ir_opt/passes.h
    ir_opt/verification_pass.cpp
)

if (ARCHITECTURE_x86_64)
    target_sources(dynarmic PRIVATE
         backend_x64/a32_emit_x64.cpp
         backend_x64/a32_emit_x64.h
         backend_x64/a32_interface.cpp
         backend_x64/a32_jitstate.cpp
         backend_x64/a32_jitstate.h
         backend_x64/a64_emit_x64.cpp
         backend_x64/a64_emit_x64.h
         backend_x64/a64_interface.cpp
         backend_x64/a64_jitstate.cpp
         backend_x64/a64_jitstate.h
         backend_x64/abi.cpp
         backend_x64/abi.h
         backend_x64/block_of_code.cpp
         backend_x64/block_of_code.h
         backend_x64/block_range_information.cpp
         backend_x64/block_range_information.h
         backend_x64/callback.cpp
         backend_x64/callback.h
         backend_x64/constant_pool.cpp
         backend_x64/constant_pool.h
         backend_x64/devirtualize.h
         backend_x64/emit_x64.cpp
         backend_x64/emit_x64.h
         backend_x64/emit_x64_aes.cpp
         backend_x64/emit_x64_crc32.cpp
         backend_x64/emit_x64_data_processing.cpp
         backend_x64/emit_x64_floating_point.cpp
         backend_x64/emit_x64_packed.cpp
         backend_x64/emit_x64_saturation.cpp
         backend_x64/emit_x64_sm4.cpp
         backend_x64/emit_x64_vector.cpp
         backend_x64/emit_x64_vector_floating_point.cpp
         backend_x64/hostloc.cpp
         backend_x64/hostloc.h
         backend_x64/jitstate_info.h
         backend_x64/oparg.h
         backend_x64/reg_alloc.cpp
         backend_x64/reg_alloc.h
    )

    if (WIN32)
        target_sources(dynarmic PRIVATE backend_x64/exception_handler_windows.cpp)
    else()
        target_sources(dynarmic PRIVATE backend_x64/exception_handler_generic.cpp)
    endif()
else()
    message(FATAL_ERROR "Unsupported architecture")
endif()

include(CreateDirectoryGroups)
create_target_directory_groups(dynarmic)

target_include_directories(dynarmic
                           PUBLIC ../include
                           PRIVATE .)
target_compile_options(dynarmic PRIVATE ${DYNARMIC_CXX_FLAGS})
target_link_libraries(dynarmic
    PUBLIC
        boost
    PRIVATE
        fmt::fmt
        xbyak
        $<$<BOOL:DYNARMIC_USE_LLVM>:${llvm_libs}>
)
if (DYNARMIC_ENABLE_CPU_FEATURE_DETECTION)
    target_compile_definitions(dynarmic PRIVATE DYNARMIC_ENABLE_CPU_FEATURE_DETECTION=1)
endif()
if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_compile_definitions(dynarmic PRIVATE FMT_USE_WINDOWS_H=0)
endif()
