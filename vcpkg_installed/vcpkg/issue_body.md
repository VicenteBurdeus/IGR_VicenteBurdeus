Package: glew:x64-windows@2.2.0#4

**Host Environment**

- Host: x64-windows
- Compiler: MSVC 19.43.34809.0
-    vcpkg-tool version: 2024-12-09-1005b78fa1bf1dde1a20c2734cba4ea61ca94d9a
    vcpkg-readonly: true
    vcpkg-scripts version: 0c4cf19224a049cf82f4521e29e39f7bd680440c

**To Reproduce**

`vcpkg install `

**Failure logs**

```
-- Using cached glew-2.2.0.tgz.
-- Cleaning sources at C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/src/glew-80f5997feb.clean. Use --editable to skip cleaning for the packages you specify.
-- Extracting source C:/Users/Vicente/AppData/Local/vcpkg/downloads/glew-2.2.0.tgz
-- Applying patch fix-LNK2019.patch
-- Applying patch base_address.patch
-- Using source at C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/src/glew-80f5997feb.clean
-- Found external ninja('1.12.1').
-- Configuring x64-windows-dbg
CMake Error at scripts/cmake/vcpkg_execute_required_process.cmake:127 (message):
    Command failed: "C:/Program Files/CMake/bin/cmake.exe" "C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/src/glew-80f5997feb.clean/build/cmake" -G Ninja -DCMAKE_BUILD_TYPE=Debug "-DCMAKE_INSTALL_PREFIX=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/pkgs/glew_x64-windows/debug" -DFETCHCONTENT_FULLY_DISCONNECTED=ON -DBUILD_UTILS=OFF "-DCMAKE_MAKE_PROGRAM=C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -DBUILD_SHARED_LIBS=ON "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/toolchains/windows.cmake" -DVCPKG_TARGET_TRIPLET=x64-windows -DVCPKG_SET_CHARSET_FLAG=ON -DVCPKG_PLATFORM_TOOLSET=v143 -DCMAKE_EXPORT_NO_PACKAGE_REGISTRY=ON -DCMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY=ON -DCMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY=ON -DCMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP=TRUE -DCMAKE_VERBOSE_MAKEFILE=ON -DVCPKG_APPLOCAL_DEPS=OFF "-DCMAKE_TOOLCHAIN_FILE=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake" -DCMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION=ON -DVCPKG_CXX_FLAGS= -DVCPKG_CXX_FLAGS_RELEASE= -DVCPKG_CXX_FLAGS_DEBUG= -DVCPKG_C_FLAGS= -DVCPKG_C_FLAGS_RELEASE= -DVCPKG_C_FLAGS_DEBUG= -DVCPKG_CRT_LINKAGE=dynamic -DVCPKG_LINKER_FLAGS= -DVCPKG_LINKER_FLAGS_RELEASE= -DVCPKG_LINKER_FLAGS_DEBUG= -DVCPKG_TARGET_ARCHITECTURE=x64 -DCMAKE_INSTALL_LIBDIR:STRING=lib -DCMAKE_INSTALL_BINDIR:STRING=bin "-D_VCPKG_ROOT_DIR=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg" "-D_VCPKG_INSTALLED_DIR=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed" -DVCPKG_MANIFEST_INSTALL=OFF
    Working Directory: C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg
    Error code: 1
    See logs for more information:
      C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-CMakeCache.txt.log
      C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-CMakeConfigureLog.yaml.log
      C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-out.log
      C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-err.log

Call Stack (most recent call first):
  C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/x64-windows/share/vcpkg-cmake/vcpkg_cmake_configure.cmake:287 (vcpkg_execute_required_process)
  C:/Users/Vicente/AppData/Local/vcpkg/registries/git-trees/bf42d73479dcd0f239b71dbed4d0d3af22efb294/portfile.cmake:22 (vcpkg_cmake_configure)
  scripts/ports.cmake:196 (include)



```

<details><summary>C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-out.log</summary>

```
-- The C compiler identification is MSVC 19.43.34809.0
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/cl.exe - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Configuring incomplete, errors occurred!
```
</details>

<details><summary>C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-err.log</summary>

```
CMake Warning (dev) at CMakeLists.txt:5 (project):
  cmake_minimum_required() should be called prior to this top-level project()
  call.  Please see the cmake-commands(7) manual for usage documentation of
  both commands.
This warning is for project developers.  Use -Wno-dev to suppress it.

CMake Error at CMakeLists.txt:7 (cmake_minimum_required):
  Compatibility with CMake < 3.5 has been removed from CMake.

  Update the VERSION argument <min> value.  Or, use the <min>...<max> syntax
  to tell CMake that the project requires at least <min> but has been updated
  to work with policies introduced by <max> or earlier.

  Or, add -DCMAKE_POLICY_VERSION_MINIMUM=3.5 to try configuring anyway.
```
</details>

<details><summary>C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-CMakeConfigureLog.yaml.log</summary>

```

---
events:
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineSystem.cmake:205 (message)"
      - "CMakeLists.txt:5 (project)"
    message: |
      The system is: Windows - 10.0.26100 - AMD64
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCompilerId.cmake:17 (message)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCompilerId.cmake:64 (__determine_compiler_id_test)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCCompiler.cmake:123 (CMAKE_DETERMINE_COMPILER_ID)"
      - "CMakeLists.txt:5 (project)"
    message: |
      Compiling the C compiler identification source file "CMakeCCompilerId.c" succeeded.
      Compiler: C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/cl.exe 
      Build flags: /nologo;/DWIN32;/D_WINDOWS;/utf-8;/MP
      Id flags:  
      
      The output was:
      0
      CMakeCCompilerId.c
      
      
      Compilation of the C compiler identification source "CMakeCCompilerId.c" produced "CMakeCCompilerId.exe"
      
      Compilation of the C compiler identification source "CMakeCCompilerId.c" produced "CMakeCCompilerId.obj"
      
      The C compiler identification is MSVC, found in:
        C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg/CMakeFiles/4.0.2/CompilerIdC/CMakeCCompilerId.exe
      
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCompilerId.cmake:1322 (message)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCompilerId.cmake:250 (CMAKE_DETERMINE_MSVC_SHOWINCLUDES_PREFIX)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCCompiler.cmake:123 (CMAKE_DETERMINE_COMPILER_ID)"
      - "CMakeLists.txt:5 (project)"
    message: |
      Detecting C compiler /showIncludes prefix:
        main.c
        Nota: inclusión del archivo: C:\\Users\\Vicente\\Desktop\\IGR\\Practicas_GL\\Trabajo 2\\vcpkg_installed\\vcpkg\\blds\\glew\\x64-windows-dbg\\CMakeFiles\\ShowIncludes\\foo.h
        
      Found prefix "Nota: inclusión del archivo: "
  -
    kind: "try_compile-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCompilerABI.cmake:83 (try_compile)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:5 (project)"
    checks:
      - "Detecting C compiler ABI info"
    directories:
      source: "C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-ju7snh"
      binary: "C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-ju7snh"
    cmakeVariables:
      CMAKE_C_FLAGS: " /nologo /DWIN32 /D_WINDOWS /utf-8 /MP "
      CMAKE_EXE_LINKER_FLAGS: "/machine:x64"
      CMAKE_MSVC_DEBUG_INFORMATION_FORMAT: ""
      CMAKE_MSVC_RUNTIME_LIBRARY: "MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>"
      VCPKG_CHAINLOAD_TOOLCHAIN_FILE: "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/toolchains/windows.cmake"
      VCPKG_CRT_LINKAGE: "dynamic"
      VCPKG_CXX_FLAGS: ""
      VCPKG_CXX_FLAGS_DEBUG: ""
      VCPKG_CXX_FLAGS_RELEASE: ""
      VCPKG_C_FLAGS: ""
      VCPKG_C_FLAGS_DEBUG: ""
      VCPKG_C_FLAGS_RELEASE: ""
      VCPKG_INSTALLED_DIR: "C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed"
      VCPKG_LINKER_FLAGS: ""
      VCPKG_LINKER_FLAGS_DEBUG: ""
      VCPKG_LINKER_FLAGS_RELEASE: ""
      VCPKG_PLATFORM_TOOLSET: "v143"
      VCPKG_PREFER_SYSTEM_LIBS: "OFF"
      VCPKG_SET_CHARSET_FLAG: "ON"
      VCPKG_TARGET_ARCHITECTURE: "x64"
      VCPKG_TARGET_TRIPLET: "x64-windows"
      Z_VCPKG_ROOT_DIR: "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg"
    buildResult:
      variable: "CMAKE_C_ABI_COMPILED"
      cached: true
      stdout: |
        Change Dir: 'C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg/CMakeFiles/CMakeScratch/TryCompile-ju7snh'
        
        Run Build Command(s): "C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe" -v cmTC_94296
        [1/2] C:\\PROGRA~1\\MICROS~1\\2022\\COMMUN~1\\VC\\Tools\\MSVC\\1443~1.348\\bin\\Hostx64\\x64\\cl.exe  /nologo   /nologo /DWIN32 /D_WINDOWS /utf-8 /MP   /D_DEBUG /MDd /Z7 /Ob0 /Od /RTC1 /showIncludes /FoCMakeFiles\\cmTC_94296.dir\\CMakeCCompilerABI.c.obj /FdCMakeFiles\\cmTC_94296.dir\\ /FS -c "C:\\Program Files\\CMake\\share\\cmake-4.0\\Modules\\CMakeCCompilerABI.c"
        [2/2] C:\\WINDOWS\\system32\\cmd.exe /C "cd . && "C:\\Program Files\\CMake\\bin\\cmake.exe" -E vs_link_exe --msvc-ver=1943 --intdir=CMakeFiles\\cmTC_94296.dir --rc=C:\\PROGRA~2\\WINDOW~4\\10\\bin\\100226~1.0\\x64\\rc.exe --mt=C:\\PROGRA~2\\WINDOW~4\\10\\bin\\100226~1.0\\x64\\mt.exe --manifests  -- C:\\PROGRA~1\\MICROS~1\\2022\\COMMUN~1\\VC\\Tools\\MSVC\\1443~1.348\\bin\\Hostx64\\x64\\link.exe /nologo CMakeFiles\\cmTC_94296.dir\\CMakeCCompilerABI.c.obj  /out:cmTC_94296.exe /implib:cmTC_94296.lib /pdb:cmTC_94296.pdb /version:0.0 /machine:x64 /nologo /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib && cd ."
        
      exitCode: 0
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCompilerABI.cmake:227 (message)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:5 (project)"
    message: |
      Parsed C implicit link information:
        link line regex: [^( *|.*[/\\])(ld[0-9]*(|\\.[a-rt-z][a-z]*|\\.s[a-np-z][a-z]*|\\.so[a-z]+)|link\\.exe|lld-link(\\.exe)?|CMAKE_LINK_STARTFILE-NOTFOUND|([^/\\]+-)?ld|collect2)[^/\\]*( |$)]
        linker tool regex: [^[ 	]*(->|")?[ 	]*(([^"]*[/\\])?(ld[0-9]*(|\\.[a-rt-z][a-z]*|\\.s[a-np-z][a-z]*|\\.so[a-z]+)|link\\.exe|lld-link(\\.exe)?))("|,| |$)]
        linker tool for 'C': C:/PROGRA~1/MICROS~1/2022/COMMUN~1/VC/Tools/MSVC/1443~1.348/bin/Hostx64/x64/link.exe
        implicit libs: []
        implicit objs: []
        implicit dirs: []
        implicit fwks: []
      
      
  -
    kind: "message-v1"
    backtrace:
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/Internal/CMakeDetermineLinkerId.cmake:36 (message)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeDetermineCompilerABI.cmake:270 (cmake_determine_linker_id)"
      - "C:/Program Files/CMake/share/cmake-4.0/Modules/CMakeTestCCompiler.cmake:26 (CMAKE_DETERMINE_COMPILER_ABI)"
      - "CMakeLists.txt:5 (project)"
    message: |
      Running the C compiler's linker: "C:/PROGRA~1/MICROS~1/2022/COMMUN~1/VC/Tools/MSVC/1443~1.348/bin/Hostx64/x64/link.exe" "-v"
      Microsoft (R) Incremental Linker Version 14.43.34809.0
      Copyright (C) Microsoft Corporation.  All rights reserved.
...
```
</details>

<details><summary>C:\Users\Vicente\Desktop\IGR\Practicas_GL\Trabajo 2\vcpkg_installed\vcpkg\blds\glew\config-x64-windows-dbg-CMakeCache.txt.log</summary>

```
# This is the CMakeCache file.
# For build in directory: c:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg
# It was generated by CMake: C:/Program Files/CMake/bin/cmake.exe
# You can edit this file to change values found and used by cmake.
# If you do not want to change any of the values, simply exit the editor.
# If you do want to change a value, simply edit, save, and exit the editor.
# The syntax for the file is as follows:
# KEY:TYPE=VALUE
# KEY is the name of a variable in the cache.
# TYPE is a hint to GUIs for the type of VALUE, DO NOT EDIT TYPE!.
# VALUE is the current value for the KEY.

########################
# EXTERNAL cache entries
########################

//No help, variable specified on the command line.
BUILD_SHARED_LIBS:UNINITIALIZED=ON

//No help, variable specified on the command line.
BUILD_UTILS:UNINITIALIZED=OFF

//Path to a program.
CMAKE_AR:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/lib.exe

//Choose the type of build, options are: None Debug Release RelWithDebInfo
// MinSizeRel ...
CMAKE_BUILD_TYPE:STRING=Debug

CMAKE_CROSSCOMPILING:STRING=OFF

CMAKE_CXX_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /GR /EHsc /MP '

CMAKE_CXX_FLAGS_DEBUG:STRING='/D_DEBUG /MDd /Z7 /Ob0 /Od /RTC1 '

CMAKE_CXX_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//C compiler
CMAKE_C_COMPILER:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/cl.exe

CMAKE_C_FLAGS:STRING=' /nologo /DWIN32 /D_WINDOWS /utf-8 /MP '

CMAKE_C_FLAGS_DEBUG:STRING='/D_DEBUG /MDd /Z7 /Ob0 /Od /RTC1 '

//Flags used by the C compiler during MINSIZEREL builds.
CMAKE_C_FLAGS_MINSIZEREL:STRING=/MD /O1 /Ob1 /DNDEBUG

CMAKE_C_FLAGS_RELEASE:STRING='/MD /O2 /Oi /Gy /DNDEBUG /Z7 '

//Flags used by the C compiler during RELWITHDEBINFO builds.
CMAKE_C_FLAGS_RELWITHDEBINFO:STRING=/MD /Zi /O2 /Ob1 /DNDEBUG

//Libraries linked by default with all C applications.
CMAKE_C_STANDARD_LIBRARIES:STRING=kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib

//No help, variable specified on the command line.
CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION:UNINITIALIZED=ON

//Flags used by the linker during all build types.
CMAKE_EXE_LINKER_FLAGS:STRING=/machine:x64

//Flags used by the linker during DEBUG builds.
CMAKE_EXE_LINKER_FLAGS_DEBUG:STRING=/nologo    /debug /INCREMENTAL

//Flags used by the linker during MINSIZEREL builds.
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL:STRING=/INCREMENTAL:NO

CMAKE_EXE_LINKER_FLAGS_RELEASE:STRING='/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF  '

//Flags used by the linker during RELWITHDEBINFO builds.
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO:STRING=/debug /INCREMENTAL

//Enable/Disable output of build database during the build.
CMAKE_EXPORT_BUILD_DATABASE:BOOL=

//Enable/Disable output of compile commands during generation.
CMAKE_EXPORT_COMPILE_COMMANDS:BOOL=

//No help, variable specified on the command line.
CMAKE_EXPORT_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_PACKAGE_REGISTRY:UNINITIALIZED=ON

//No help, variable specified on the command line.
CMAKE_FIND_PACKAGE_NO_SYSTEM_PACKAGE_REGISTRY:UNINITIALIZED=ON

//Value Computed by CMake.
CMAKE_FIND_PACKAGE_REDIRECTS_DIR:STATIC=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg/CMakeFiles/pkgRedirects

//No help, variable specified on the command line.
CMAKE_INSTALL_BINDIR:STRING=bin

//No help, variable specified on the command line.
CMAKE_INSTALL_LIBDIR:STRING=lib

//Install path prefix, prepended onto install directories.
CMAKE_INSTALL_PREFIX:PATH=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/pkgs/glew_x64-windows/debug

//No help, variable specified on the command line.
CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP:UNINITIALIZED=TRUE

//Path to a program.
CMAKE_LINKER:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.43.34808/bin/Hostx64/x64/link.exe

//make program
CMAKE_MAKE_PROGRAM:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/Common7/IDE/CommonExtensions/Microsoft/CMake/Ninja/ninja.exe

//Flags used by the linker during the creation of modules during
// all build types.
CMAKE_MODULE_LINKER_FLAGS:STRING=/machine:x64

//Flags used by the linker during the creation of modules during
// DEBUG builds.
CMAKE_MODULE_LINKER_FLAGS_DEBUG:STRING=/nologo    /debug /INCREMENTAL

//Flags used by the linker during the creation of modules during
// MINSIZEREL builds.
CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL:STRING=/INCREMENTAL:NO

CMAKE_MODULE_LINKER_FLAGS_RELEASE:STRING='/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF  '

//Flags used by the linker during the creation of modules during
// RELWITHDEBINFO builds.
CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO:STRING=/debug /INCREMENTAL

CMAKE_MSVC_RUNTIME_LIBRARY:STRING=MultiThreaded$<$<CONFIG:Debug>:Debug>$<$<STREQUAL:dynamic,dynamic>:DLL>

//Path to a program.
CMAKE_MT:FILEPATH=C:/Program Files (x86)/Windows Kits/10/bin/10.0.22621.0/x64/mt.exe

//Value Computed by CMake
CMAKE_PROJECT_DESCRIPTION:STATIC=

//Value Computed by CMake
CMAKE_PROJECT_HOMEPAGE_URL:STATIC=

//Value Computed by CMake
CMAKE_PROJECT_NAME:STATIC=glew

//RC compiler
CMAKE_RC_COMPILER:FILEPATH=C:/Program Files (x86)/Windows Kits/10/bin/10.0.22621.0/x64/rc.exe

CMAKE_RC_FLAGS:STRING=-c65001 /DWIN32

//Flags for Windows Resource Compiler during DEBUG builds.
CMAKE_RC_FLAGS_DEBUG:STRING=-D_DEBUG

//Flags for Windows Resource Compiler during MINSIZEREL builds.
CMAKE_RC_FLAGS_MINSIZEREL:STRING=

//Flags for Windows Resource Compiler during RELEASE builds.
CMAKE_RC_FLAGS_RELEASE:STRING=

//Flags for Windows Resource Compiler during RELWITHDEBINFO builds.
CMAKE_RC_FLAGS_RELWITHDEBINFO:STRING=

//Flags used by the linker during the creation of shared libraries
// during all build types.
CMAKE_SHARED_LINKER_FLAGS:STRING=/machine:x64

//Flags used by the linker during the creation of shared libraries
// during DEBUG builds.
CMAKE_SHARED_LINKER_FLAGS_DEBUG:STRING=/nologo    /debug /INCREMENTAL

//Flags used by the linker during the creation of shared libraries
// during MINSIZEREL builds.
CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL:STRING=/INCREMENTAL:NO

CMAKE_SHARED_LINKER_FLAGS_RELEASE:STRING='/nologo /DEBUG /INCREMENTAL:NO /OPT:REF /OPT:ICF  '

//Flags used by the linker during the creation of shared libraries
// during RELWITHDEBINFO builds.
CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO:STRING=/debug /INCREMENTAL

//If set, runtime paths are not added when installing shared libraries,
// but are added when building.
CMAKE_SKIP_INSTALL_RPATH:BOOL=NO

//If set, runtime paths are not added when using shared libraries.
CMAKE_SKIP_RPATH:BOOL=NO

//Flags used by the linker during the creation of static libraries
// during all build types.
CMAKE_STATIC_LINKER_FLAGS:STRING=/machine:x64

//Flags used by the linker during the creation of static libraries
// during DEBUG builds.
CMAKE_STATIC_LINKER_FLAGS_DEBUG:STRING=/nologo

//Flags used by the linker during the creation of static libraries
// during MINSIZEREL builds.
CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL:STRING=

//Flags used by the linker during the creation of static libraries
// during RELEASE builds.
CMAKE_STATIC_LINKER_FLAGS_RELEASE:STRING=/nologo

//Flags used by the linker during the creation of static libraries
// during RELWITHDEBINFO builds.
CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO:STRING=

CMAKE_SYSTEM_NAME:STRING=Windows

CMAKE_SYSTEM_PROCESSOR:STRING=AMD64

CMAKE_SYSTEM_VERSION:STRING=10.0.26100

//The CMake toolchain file
CMAKE_TOOLCHAIN_FILE:FILEPATH=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/buildsystems/vcpkg.cmake

//If this value is on, makefiles will be generated without the
// .SILENT directive, and all commands will be echoed to the console
// during the make.  This is useful for debugging only. With Visual
// Studio IDE projects all commands are done without /nologo.
CMAKE_VERBOSE_MAKEFILE:BOOL=ON

//No help, variable specified on the command line.
FETCHCONTENT_FULLY_DISCONNECTED:UNINITIALIZED=ON

//Automatically copy dependencies into the output directory for
// executables.
VCPKG_APPLOCAL_DEPS:BOOL=OFF

//No help, variable specified on the command line.
VCPKG_CHAINLOAD_TOOLCHAIN_FILE:UNINITIALIZED=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg/scripts/toolchains/windows.cmake

//No help, variable specified on the command line.
VCPKG_CRT_LINKAGE:UNINITIALIZED=dynamic

//No help, variable specified on the command line.
VCPKG_CXX_FLAGS:UNINITIALIZED=

//No help, variable specified on the command line.
VCPKG_CXX_FLAGS_DEBUG:UNINITIALIZED=

//No help, variable specified on the command line.
VCPKG_CXX_FLAGS_RELEASE:UNINITIALIZED=

//No help, variable specified on the command line.
VCPKG_C_FLAGS:UNINITIALIZED=

//No help, variable specified on the command line.
VCPKG_C_FLAGS_DEBUG:UNINITIALIZED=

//No help, variable specified on the command line.
VCPKG_C_FLAGS_RELEASE:UNINITIALIZED=

//The directory which contains the installed libraries for each
// triplet
VCPKG_INSTALLED_DIR:PATH=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed

//No help, variable specified on the command line.
VCPKG_LINKER_FLAGS:UNINITIALIZED=

//No help, variable specified on the command line.
VCPKG_LINKER_FLAGS_DEBUG:UNINITIALIZED=

//No help, variable specified on the command line.
VCPKG_LINKER_FLAGS_RELEASE:UNINITIALIZED=

//The path to the vcpkg manifest directory.
VCPKG_MANIFEST_DIR:PATH=

//Use manifest mode, as opposed to classic mode.
VCPKG_MANIFEST_MODE:BOOL=OFF

//No help, variable specified on the command line.
VCPKG_PLATFORM_TOOLSET:UNINITIALIZED=v143

//Appends the vcpkg paths to CMAKE_PREFIX_PATH, CMAKE_LIBRARY_PATH
// and CMAKE_FIND_ROOT_PATH so that vcpkg libraries/packages are
// found after toolchain/system libraries/packages.
VCPKG_PREFER_SYSTEM_LIBS:BOOL=OFF

//Enable the setup of CMAKE_PROGRAM_PATH to vcpkg paths
VCPKG_SETUP_CMAKE_PROGRAM_PATH:BOOL=ON

//No help, variable specified on the command line.
VCPKG_SET_CHARSET_FLAG:UNINITIALIZED=ON

//No help, variable specified on the command line.
VCPKG_TARGET_ARCHITECTURE:UNINITIALIZED=x64

//Vcpkg target triplet (ex. x86-windows)
VCPKG_TARGET_TRIPLET:STRING=x64-windows

//Trace calls to find_package()
VCPKG_TRACE_FIND_PACKAGE:BOOL=OFF

//Enables messages from the VCPKG toolchain for debugging purposes.
VCPKG_VERBOSE:BOOL=OFF

//(experimental) Automatically copy dependencies into the install
// target directory for executables. Requires CMake 3.14.
X_VCPKG_APPLOCAL_DEPS_INSTALL:BOOL=OFF

//(experimental) Add USES_TERMINAL to VCPKG_APPLOCAL_DEPS to force
// serialization.
X_VCPKG_APPLOCAL_DEPS_SERIALIZED:BOOL=OFF

//The directory which contains the installed libraries for each
// triplet
_VCPKG_INSTALLED_DIR:PATH=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed

//No help, variable specified on the command line.
_VCPKG_ROOT_DIR:UNINITIALIZED=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg

//Value Computed by CMake
glew_BINARY_DIR:STATIC=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg

//Value Computed by CMake
glew_IS_TOP_LEVEL:STATIC=ON

//Value Computed by CMake
glew_SOURCE_DIR:STATIC=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/src/glew-80f5997feb.clean/build/cmake


########################
# INTERNAL cache entries
########################

//ADVANCED property for variable: CMAKE_AR
CMAKE_AR-ADVANCED:INTERNAL=1
//This is the directory where this CMakeCache.txt was created
CMAKE_CACHEFILE_DIR:INTERNAL=c:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/x64-windows-dbg
//Major version of cmake used to create the current loaded cache
CMAKE_CACHE_MAJOR_VERSION:INTERNAL=4
//Minor version of cmake used to create the current loaded cache
CMAKE_CACHE_MINOR_VERSION:INTERNAL=0
//Patch version of cmake used to create the current loaded cache
CMAKE_CACHE_PATCH_VERSION:INTERNAL=2
//Path to CMake executable.
CMAKE_COMMAND:INTERNAL=C:/Program Files/CMake/bin/cmake.exe
//Path to cpack program executable.
CMAKE_CPACK_COMMAND:INTERNAL=C:/Program Files/CMake/bin/cpack.exe
//Path to ctest program executable.
CMAKE_CTEST_COMMAND:INTERNAL=C:/Program Files/CMake/bin/ctest.exe
//ADVANCED property for variable: CMAKE_C_COMPILER
CMAKE_C_COMPILER-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS
CMAKE_C_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_DEBUG
CMAKE_C_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_MINSIZEREL
CMAKE_C_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELEASE
CMAKE_C_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_FLAGS_RELWITHDEBINFO
CMAKE_C_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_C_STANDARD_LIBRARIES
CMAKE_C_STANDARD_LIBRARIES-ADVANCED:INTERNAL=1
//Path to cache edit program executable.
CMAKE_EDIT_COMMAND:INTERNAL=C:/Program Files/CMake/bin/cmake-gui.exe
//Executable file format
CMAKE_EXECUTABLE_FORMAT:INTERNAL=Unknown
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS
CMAKE_EXE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_DEBUG
CMAKE_EXE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_MINSIZEREL
CMAKE_EXE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELEASE
CMAKE_EXE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_BUILD_DATABASE
CMAKE_EXPORT_BUILD_DATABASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_EXPORT_COMPILE_COMMANDS
CMAKE_EXPORT_COMPILE_COMMANDS-ADVANCED:INTERNAL=1
//Name of external makefile project generator.
CMAKE_EXTRA_GENERATOR:INTERNAL=
//Name of generator.
CMAKE_GENERATOR:INTERNAL=Ninja
//Generator instance identifier.
CMAKE_GENERATOR_INSTANCE:INTERNAL=
//Name of generator platform.
CMAKE_GENERATOR_PLATFORM:INTERNAL=
//Name of generator toolset.
CMAKE_GENERATOR_TOOLSET:INTERNAL=
//Source directory with the top level CMakeLists.txt file for this
// project
CMAKE_HOME_DIRECTORY:INTERNAL=C:/Users/Vicente/Desktop/IGR/Practicas_GL/Trabajo 2/vcpkg_installed/vcpkg/blds/glew/src/glew-80f5997feb.clean/build/cmake
//ADVANCED property for variable: CMAKE_LINKER
CMAKE_LINKER-ADVANCED:INTERNAL=1
//Name of CMakeLists files to read
CMAKE_LIST_FILE_NAME:INTERNAL=CMakeLists.txt
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS
CMAKE_MODULE_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_DEBUG
CMAKE_MODULE_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL
CMAKE_MODULE_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELEASE
CMAKE_MODULE_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_MODULE_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_MT
CMAKE_MT-ADVANCED:INTERNAL=1
//number of local generators
CMAKE_NUMBER_OF_MAKEFILES:INTERNAL=1
//Platform information initialized
CMAKE_PLATFORM_INFO_INITIALIZED:INTERNAL=1
//noop for ranlib
CMAKE_RANLIB:INTERNAL=:
//ADVANCED property for variable: CMAKE_RC_COMPILER
CMAKE_RC_COMPILER-ADVANCED:INTERNAL=1
CMAKE_RC_COMPILER_WORKS:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS
CMAKE_RC_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_DEBUG
CMAKE_RC_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_MINSIZEREL
CMAKE_RC_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELEASE
CMAKE_RC_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_RC_FLAGS_RELWITHDEBINFO
CMAKE_RC_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//Path to CMake installation.
CMAKE_ROOT:INTERNAL=C:/Program Files/CMake/share/cmake-4.0
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS
CMAKE_SHARED_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_DEBUG
CMAKE_SHARED_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL
CMAKE_SHARED_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELEASE
CMAKE_SHARED_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_SHARED_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_INSTALL_RPATH
CMAKE_SKIP_INSTALL_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_SKIP_RPATH
CMAKE_SKIP_RPATH-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS
CMAKE_STATIC_LINKER_FLAGS-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_DEBUG
CMAKE_STATIC_LINKER_FLAGS_DEBUG-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL
CMAKE_STATIC_LINKER_FLAGS_MINSIZEREL-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELEASE
CMAKE_STATIC_LINKER_FLAGS_RELEASE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO
CMAKE_STATIC_LINKER_FLAGS_RELWITHDEBINFO-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_TOOLCHAIN_FILE
CMAKE_TOOLCHAIN_FILE-ADVANCED:INTERNAL=1
//ADVANCED property for variable: CMAKE_VERBOSE_MAKEFILE
CMAKE_VERBOSE_MAKEFILE-ADVANCED:INTERNAL=1
//Install the dependencies listed in your manifest:
//\n    If this is off, you will have to manually install your dependencies.
//\n    See https://github.com/microsoft/vcpkg/tree/master/docs/specifications/manifests.md
// for more info.
//\n
VCPKG_MANIFEST_INSTALL:INTERNAL=OFF
//ADVANCED property for variable: VCPKG_VERBOSE
VCPKG_VERBOSE-ADVANCED:INTERNAL=1
//Making sure VCPKG_MANIFEST_MODE doesn't change
Z_VCPKG_CHECK_MANIFEST_MODE:INTERNAL=OFF
//Vcpkg root directory
Z_VCPKG_ROOT_DIR:INTERNAL=C:/Program Files/Microsoft Visual Studio/2022/Community/VC/vcpkg

```
</details>

**Additional context**

<details><summary>vcpkg.json</summary>

```
{
  "name": "tu-proyecto",
  "version": "1.0.0",
  "dependencies": [
    "glew",
    "sdl2",
    "sdl2-mixer"
  ]
}

```
</details>
