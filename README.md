
## Getting Started
Library - Debian : apt install git curl unzip tar cmake python3 build-essential libX11-dev libXect-dev
        - Arch : pacman -S git curl unzip tar cmake python3 base-devel libx11 libxect
Clone the repo with the `--recurse-submodules` flag
```bash
git clone --recurse-submodules https://github.com/silent1603/TinySDL.git
```  

Run `./vcpkg/bootstrap-vcpkg.sh` or `.\vcpkg\bootstrap-vcpkg.bat`

Fetch the dependencies (see [vcpkg.json](vcpkg.json)):  
(_This is optional, CMake should run `vcpkg install` anyway_)
```bash
./vcpkg/vcpkg --feature-flags=manifests install
```

Build the project using your IDE/build tool of choice or manually:

```bash
cmake -B build -S .
```
```bash
cmake --build build
```
## Troubleshooting
