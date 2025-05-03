# Always build externals as static libraries, even when dynarmic is built as shared
if (BUILD_SHARED_LIBS)
    set(BUILD_SHARED_LIBS OFF)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
    set_property(DIRECTORY PROPERTY EXCLUDE_FROM_ALL ON)
endif()

# Allow options shadowing with normal variables when subproject use old cmake policy
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

# Disable tests in all externals supporting the standard option name
set(BUILD_TESTING OFF)

# For libraries that already come with a CMakeLists file,
# simply add the directory to that file as a subdirectory
# to have CMake automatically recognize them.

# fmt

if (NOT TARGET fmt::fmt)
    # fmtlib formatting library
    set(FMT_INSTALL ON)
    add_subdirectory(fmt)
endif()

# mcl

if (NOT TARGET merry::mcl)
    set(MCL_INSTALL ON)
    add_subdirectory(mcl)
endif()

# robin-map

if (NOT TARGET tsl::robin_map)
    add_subdirectory(robin-map)
endif()
