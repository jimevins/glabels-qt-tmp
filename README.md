![logo](glabels/images/glabels-logo.png)
![gLabels Label Designer](glabels/images/glabels-label-designer.png)

[![Build Status](https://travis-ci.org/jimevins/glabels-qt-tmp.svg?branch=master)](https://travis-ci.org/jimevins/glabels-qt-tmp)

*******************************************************************************

## What is gLabels-qt?

gLabels-qt is the development version of the next major version of gLabels (4.0).

![screenshot](docs/images/screenshot.png)


## What's new in gLabels-qt?

- Based on the Qt5 framework.
- Unlike previous versions, glabels-qt is a cross-platform application.
    * So far, it has been built and tested under both Linux and Windows 7 (using MSYS/MINGW toolchain).
- Updated UI based on typical workflows.


## Status

gLabels-qt has been under off-and-on development for several years..
It is still missing several features to bring it in parity with glabels-3.4.  These include

- Batch mode
- Compatability with older glabels files
- Custom product templates designer
- Online manual


## Download

### Latest Release

There are currently no official releases of gLabels-qt.

### Continuous Integration Snapshots

Continuous integration snapshots are not official releases.  These snapshots represent the latest
bleading-edge development (unstable) code.  Please, DO NOT use it in a production environment.  Do not
expect compatability or consistency of features between snapshots.

| Platform | Files |
|:---------|:------|
| Linux x86_64 [AppImage](http:appimage.org): *Download, make it executable, and run!* | [glabels-continuous-x86_64.AppImage](https://github.com/jimevins/glabels-qt-tmp/releases/download/continuous/glabels-continuous-x86_64.AppImage) |
| Source Code TAR.GZ | [continuous.tar.gz](https://github.com/jimevins/glabels-qt-tmp/archive/continuous.tar.gz) |
| Source Code ZIP    | [continuous.zip](https://github.com/jimevins/glabels-qt-tmp/archive/continuous.tar.gz) |


## Build Instructions

- [Linux Build Instructions](docs/BUILD-INSTRUCTIONS-LINUX.md)
- [Windows Build Instructions](docs/BUILD-INSTRUCTIONS-WINDOWS.md)
- Mac Build Instructions (TBD)


## Help Needed

* Help is needed to add support to build and package glabels for various platforms and packaging systems.
These include

    - Windows (VisualStudio)
   - Windows (MINGW)
   - Mac
   - Linux (flatpak)
   - Linux (snap)

* Help is needed writing online documentation.

* Help is needed writing translations.

* Suggestions.

* For code contributions, see [docs/HACKING.md](docs/HACKING.md).

