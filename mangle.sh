cd `dirname 0`

if [ ! -f ./build/mangle ]; then
    mkdir build
    cd build
    cmake ..
    make
    cd ..    
fi

rustc -C symbol-mangling-version=v0 \
    -C opt-level=0 \
    -Z verbose \
    --emit llvm-ir \
    --crate-type=lib \
    -g \
    -o a.ll \
    $1

./build/mangle a.ll
