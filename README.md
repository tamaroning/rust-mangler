# rust-mangler

Leverage Rustc!

## Prerequisites

- CMake
- LLVM 17
    - `llvm.sh` is the easiest way to install it.
- `rustc` command
    - Nightly version.
    - I am using `rustc 1.74.0-nightly (20999de3a 2023-09-15)`


Build with LLVM 17 also requires zstd. You can install it by running:

```
sudo apt install -y libzstd-dev
```

## Build

```bash
git clone <this repo>
cd <this repo>
mkdir bulid
cd build
cmake ..
make
cd ..
```

## Run

```bash
./mangle.sh <rust file>
```

## Example

```
$ cat a.rs
pub fn main() {
    let f = |a: i32| a + 1;
    let _ = f(1);
}

pub mod mod_a {
    pub fn f() {}
}
$ ./mangle.sh a.rs
a::main → _RNvCs9Ow5YWZ7x0A_1a4main
a::main::{closure#0} → _RNCNvCs9Ow5YWZ7x0A_1a4main0B3_
a::mod_a::f → _RNvNtCs9Ow5YWZ7x0A_1a5mod_a1f
$ 
```
