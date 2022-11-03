set BUILD_DIR=%cd%\build
rem  vs,nasm,perl需要配置本地路径
set VCVSRS32=E:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build
set MSBUILD=E:\Program Files\Microsoft Visual Studio\2022\Community\MSBuild\Current\Bin
set NMAKE=E:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.33.31629\bin\Hostx64\x64
set Path=C:\NASM;C:\Perl64\bin;%Path%

for /R "%NMAKE%" %%f in (nmake.exe) do (
   if exist "%%f" (
      set NMAKE=%%f
	  goto:end
	  )
)
:end
rmdir /s /q "%BUILD_DIR%"
mkdir %BUILD_DIR%
set BUILD_DIR=%BUILD_DIR:\=/%
echo %BUILD_DIR%
echo %VCVSRS32%
echo %MSBUILD%
echo %NMAKE%
tar xf %TAR_DIR% -C %BUILD_DIR%
set BUILD_DIR=%BUILD_DIR:/=\%
cd %BUILD_DIR%

cmake -DSERVER_DEMO=YES -G "Visual Studio 17 2022" -A x64 .. 

@REM if not exist %LIBSSL% (
@REM cd %OPEN_SSL%
@REM perl Configure VC-WIN64A --prefix=%cd%\openssl-dev
@REM call "%VCVSRS32%\vcvars64.bat"
@REM "%NMAKE%"
@REM "%NMAKE%" install
@REM mkdir -p ..\..\lib\openssl\include\openssl
@REM copy ..\openssl-dev\lib\* ..\..\lib\openssl\lib\win
@REM cd ..
@REM )

"%MSBUILD%\MSBuild.exe" CMakeInstallExample.sln /p:Configuration=Debug /p:Platform="x64"
copy ..\demo\* ..\bin\Debug\