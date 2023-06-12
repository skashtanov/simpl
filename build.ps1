cmake -S . -B build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release -- -j 12
cmake --install build --prefix build --config Release

cmake -S example -B example/build -G Ninja -DCMAKE_BUILD_TYPE=Release
cmake --build example/build --config Release
