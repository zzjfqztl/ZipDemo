@echo off
rem
rem CMake wrapper for current project, to ease the process of generating
rem project files or Makefiles
rem
rem Usage: run_cmake.bat <build_dir> <debug_runtime_output_dir> <runtime_output_dir> <source_dir> <cmake_generator>
rem
setlocal

set PWD=%cd%.

set CMAKE_BUILD_DIR=%~1
if "%CMAKE_BUILD_DIR%"=="" set CMAKE_BUILD_DIR=%PWD%\build

set CMAKE_DEBUG_OUTPUT=%~2
if "%CMAKE_DEBUG_OUTPUT%"=="" set CMAKE_DEBUG_OUTPUT=%PWD%\build\Debug

set CMAKE_RUNTIME_OUTPUT=%~3
if "%CMAKE_RUNTIME_OUTPUT%"=="" set CMAKE_RUNTIME_OUTPUT=%PWD%\build\Release

set SOURCE_DIR=%~4
if "%SOURCE_DIR%"=="" set SOURCE_DIR=%PWD%

set CMAKE_GENERATOR=%~5
if "%CMAKE_GENERATOR%"=="" set CMAKE_GENERATOR=Visual Studio 16 2019

set CMAKE_BUILD_TYPE=Release

if not exist "%CMAKE_BUILD_DIR%" mkdir "%CMAKE_BUILD_DIR%"
pushd "%CMAKE_BUILD_DIR%" && ^
cmake -G "%CMAKE_GENERATOR%" ^
    -Wno-dev ^
    -DCMAKE_BUILD_TYPE="%CMAKE_BUILD_TYPE%" ^
    -DNAMA_BUILD_SHARED_LIB=ON ^
    -DNAMA_ENABLE_PHYSICS=ON ^
    -DNAMA_ENABLE_PROFILE=ON ^
    -DGENERATE_UNITY_PLUGIN=OFF ^
    -DGENERATE_TEST=ON ^
	-A x64 ^
    "%SOURCE_DIR%" && ^
popd

endlocal

pause