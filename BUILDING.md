# Building
Requires:
* CMake version 3.15 or newer
* Compilers:
  * MSVC 2019 or newer
  * Clang 12

When cloning the project remeber to clone the submodules as well

```git submodule update --init --recursive```

We use Vcpkg as a dependency manager which requires overriding the toolchain file

Set the following cmake variable ```CMAKE_TOOLCHAIN_FILE``` to ```[repo_dir]/Externals/vcpkg/buildsystems/vcpkg.cmake```

## Command Line Build
```bash
mkdir _build
cd _build
cmake -G[your generator] -DCMAKE_TOOLCHAIN_FILE=../Externals/vcpkg/buildsystems/vcpkg.cmake ..
cmake --build . --target [target]
```

## CLion
Inside File > Settings > Build, Execution, and Deployment > CMake find "CMake options:" then add the following:
```-DCMAKE_TOOLCHAIN_FILE="Externals/vcpkg/scripts/buildsystems/vcpkg.cmake"```

## Visual Studio
Oh god... why?
