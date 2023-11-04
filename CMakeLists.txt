# https://stackoverflow.com/questions/30867712/add-llvm-to-project-using-cmake
cmake_minimum_required(VERSION 3.19)
project(RustMangler)

find_package(LLVM 17 REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(mangle src/main.cc)

llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
target_link_libraries(mangle ${llvm_libs})
