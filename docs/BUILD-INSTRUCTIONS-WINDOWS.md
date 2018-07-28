gLabels Windows Build Instructions
==================================

gLabels for Windows can be built using one of the following toolchains:

- [MSYS/MINGW](#msysmingw)
- [Visual Studio](#visual-studio)


MSYS/MINGW
----------

### Prerequisites

- MSYS/MINGW, including the following packages
  + mingw32-gcc-g++
  + mingw32-libz
- CMake 3.2+
- Qt5 5.9+ for MINGW

Make sure that Qt tools and CMake are in your executable search path.  For example, add something like this to your .profile file:

```
export PATH=/c/Qt/5.9.3/mingw53_32/bin:${PATH}
export PATH="/c/Program Files/CMake/bin":${PATH}
```

The exact paths will depend on the version of Qt and CMake you have installed.


### Compile and Install

From an MSYS shell, type the following commands:

<pre>
$ cd <i>glabels_source_directory</i>
$ mkdir build
$ cd build
$ cmake -G "MSYS Makefiles" ..
$ make
</pre>

To install glabels, run an MSYS shell `as administrator`, and type the following commands:

<pre>
$ cd <i>glabels_source_directory</i>/build
$ make install
</pre>



Visual Studio
-------------

### Prerequisites

- Visual Studio (these instructions are for _Visual Studio 15 2017 Win64_)
- CMake 3.2+
- Qt5 5.9+ for your version of Visual Studio

Make sure that CMake and the Qt tools are in your executable search path.  For example, you may need to add something like the following to your PATH environment variable:

```
c:\Program Files\CMake\bin
c:\Qt\5.9.3\msvc2017_64\bin
```

The exact paths will depend on the version of Qt and CMake you have installed.

### Compile and Install

From a Windows Power Shell, use CMake to create and build a Visual Studio Solution:

<pre>
&gt; cd <i>glabels_source_directory</i>
&gt; mkdir build
&gt; cd build
&gt; cmake -G "Visual Studio 15 2017 Win64" -DCMAKE_PREFIX_PATH="c:\qt\5.9.3\msvc2017_64" ..
&gt; cmake --build . --config Release 
</pre>

To install, run a Windows Power Shell `as administrator`, and type the following commands:

<pre>
&gt; cd <i>glabels_source_directory</i>/build
&gt; cmake --build . --config Release --target INSTALL
</pre>

