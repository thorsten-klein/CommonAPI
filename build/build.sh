mkdir -p build
rm -rf build
mkdir -p build

cd build
cmake ../../sourcecode -G"Eclipse CDT4 - Unix Makefiles" -DCMAKE_ECLIPSE_VERSION=4.7
make # VERBOSE=1
