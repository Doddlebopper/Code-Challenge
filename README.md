# Code-Challenge
This is a terminal based word guessing game written in C++ using:
-CPR for HTTP requests
-nlohmann/json for JSON parsing

Make sure your using a C++ compiler that is C++17 or newer or else it won't work.

This project uses [vcpkg](https://github.com/microsoft/vcpkg) to manage dependencies.

Installing vcpkg:
### Windows
  Powershell or Bash :
  git clone https://github.com/microsoft/vcpkg
  cd vcpkg
  .\bootstrap-vcpkg.bat
  .\vcpkg integrate install
  .\vcpkg install cpr nlohmann-json

### macOS / Linux
  git clone https://github.com/microsoft/vcpkg.git
  cd vcpkg
  ./bootstrap-vcpkg.sh
  ./vcpkg install cpr nlohmann-json

How to run:
(Note: It might take a while for vcpkg to download and I apologize for that but I didn't find another way to implement an API)
1. Clone the repo
2. Run `vcpkg integrate install`
3. Run `vcpkg install cpr nlohmann-json`
4. Open `Coding-Challenge.sln` in your ide of choice
5. Build <- (Very Important) and run

