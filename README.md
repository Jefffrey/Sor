###Synopsis

This header only library contains a main tensor class and related functions and data structures including matrices and vectors.

###Dependencies

The library depends on:

 - C++17

Additional testing dependencies are:

 - Python 2+
 - [Ninja](https://ninja-build.org/)

###Installation

This is an header-only library, so the installation is as simple as pasting the content of the `include/` folder into some accessible path.

By invoking:

```
python bootstrap.py
ninja install
```

all files and folders inside `include/` will be copied in the installation path specified by `--install-path` (it defaults to `/usr/local/`). I recommend inspecting the actual command being run before running it, as the syntax is different between operating systems.

###Testing

To run the tests an executable has to built and run using:

```
python bootstrap.py
ninja
./tests
```