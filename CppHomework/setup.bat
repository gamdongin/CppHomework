@echo off
cd /d "%~dp0"

if not exist "vcpkg" (
    echo Downloading vcpkg...

    powershell -Command ^
    "Invoke-WebRequest https://github.com/microsoft/vcpkg/archive/refs/heads/master.zip -OutFile vcpkg.zip"

    powershell -Command ^
    "Expand-Archive vcpkg.zip -DestinationPath . -Force"

    ren vcpkg-master vcpkg
    del vcpkg.zip
)

cd vcpkg

call bootstrap-vcpkg.bat

.\vcpkg.exe install tesseract:x64-windows --classic
.\vcpkg.exe install curl:x64-windows --classic
.\vcpkg.exe install nlohmann-json:x64-windows --classic

.\vcpkg.exe integrate install

pause