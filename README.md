# NaiveCGL

A young and simple (sometimes naive) computational geometry library.

## Build
- Clone the repository
  ``` sh
  git clone https://github.com/AnthonyK213/NaiveCGL
  ```
- Install dependencies
  - Windows
    - Install the latest release of [vcpkg](https://github.com/microsoft/vcpkg)
      ``` ps1
      git clone https://github.com/microsoft/vcpkg
      .\vcpkg\bootstrap-vcpkg.bat
      ```
    - Set environment variable
      - `VCPKG_ROOT`
  - Unix
    - Debian
      ``` sh
      sudo apt-get install ...
      ```
    - RedHat
      ``` bash
      sudo dnf install ...
      ```
- Build with cmake
  ``` sh
  cd NaiveCGL
  mkdir build
  cd build
  cmake ..
  ```
