# Installation

## Step 1: Windows

- Install [MSYS2](https://www.msys2.org/) to get GCC and other C++ tools. Once installed enter following command in the UCRT64 terminal that pops up after installation.
    
    (If you already have msys2 installed, or if you closed the popup, open UCRT64 terminal from `C:\msys64\ucrt64.exe`)

    `pacman -S --needed base-devel mingw-w64-ucrt-x86_64-toolchain  mingw-w64-x86_64-cmake`

    Press enter twice to confirm and install required packages

    You should now have `cmake` file in `C:\msys64\mingw64\bin\` directory

- Install [Git](https://git-scm.com/download/win)

## Step 1:  Linux (UNTESTED)

- Install dependencies

    `sudo apt install git build-essential cmake pkg-config mesa-utils libglu1-mesa-dev mesa-common-dev`

## Step 1: Mac (UNTESTED)

- Install [Homebrew](https://brew.sh/)
- `brew install gcc cmake git`

## Step 2: Setup VSCode

- Open this project in VSCode

    `git clone https://github.com/sparshg/opengl`

    `code opengl`

- Install these extensions:
    - C/C++
    - C/C++ Extension Pack
    - CMake
    - Cmake Tools

- **LINUX/MAC USERS**: Remove `"cmake.cmakePath"` from `.vscode/settings.json` in this project.

- Click Run on bottom bar (left side), and select `[Scan for kits]`
- Click Run again, select `[GCC ... mingw32 (ucrt64)] `

A window should popup on screen.
