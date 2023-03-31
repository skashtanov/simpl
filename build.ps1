Remove-Item "build\msvc" -Recurse
cmake -S . -B "build\msvc" -G Ninja -DCMAKE_BUILD_TYPE="Release" -DCMAKE_MAKE_PROGRAM="D:\dev\tools\CLion 2022.2.4\bin\ninja\win\x64\ninja.exe"
cmake --build ".\build\msvc" --target stack_pimpl --config "Release" -j 12