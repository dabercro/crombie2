# crombie2

This is a software package for plotting and other repetitive analysis tasks.
It uses some of the methods developed in
[CrombieTools](https://github.com/dabercro/CrombieTools),
hence the uncreative name.

## Installation

Installation from this source repository requires the
`gtkmm-2.4` libraries, `automake-1.16`, ROOT 6, and
a compiler that supports the C++17 standard.
From inside the root directory of this project, so the following.

```
autoreconf
# You may need to check out the 'Makefile.in' and 'configure' again
checkout Makefile.in
checkout configure
mkdir build
cd build
../configure <options>
```

For compilation on the MIT tier-3,
I actually have to use the following configure command because
the operating system has a very old `libc++.so` or something:

```
CPPFLAGS=-D_GLIBCXX_USE_CXX11_ABI=0 ../configure
```

Then build

```
make -j3 && make install-strip   # Debugging symbols will be in your build directory
```

By default, this will install the executables `crombie2` and `crombie2catch`
into the `bin` directory relative to the project's root.
You can run this executable from other tier-3 nodes that only have the
libraries for `gtkmm-2.4` installed (which is most of them).
