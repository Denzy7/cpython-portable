# cpython-portable
Build cpython with just a few steps for any platform. This builds up on top of [cpython-lite](https://github.com/Denzy7/cpython-lite). Be sure to check it out!

# preamble
Python is a fast evolving langugage which changes overnight. So building it becomes very difficult especially in a portable way. This project aims to use CMake to build a very usable Python package which can run on any platform like WIndows, Linux or Android. This is especially useful for platforms that do not provide it as a default

# building
- Check the version the `CMakeLists.txt` recommends. You want to obtain Python sources with that `<major>.<minor>` version. Otherwise compatibility is not guranteed. This is `PYVER`

- Next note the sources location. A standard `CPython` distribution has directories like `Lib`, `Modules`, `Objects`, `PC`. This is `PYSRC`. 

- Now set these variables in your `CMakeLists.txt` and `add_subdirectory` then `target_link_libraries(<YOUR-TARGET> cpython-portable)` and done! Remember to set include directories to `<PYSRC>/Python`
	
	