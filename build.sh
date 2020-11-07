if [ $# -gt 0 ]; then BuildType=$1; else BuildType="Release"; fi
cmake -S src -B build -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=$BuildType
make -C build
