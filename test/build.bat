call D:\library\boost_1_33_1\tools\build\jam_src\bin.ntx86\bjam.exe  "-sBOOST_BUILD_PATH=D:\library\boost_1_33_1\tools\build\v2" "-sMINGW_ROOT_DIRECTORY=D:\migw" "-sTOOLS=mingw"  > log_ming.txt
call "C:\Program Files\Microsoft Visual Studio 8\VC\vcvarsall.bat" 
call D:\library\boost_1_33_1\tools\build\jam_src\bin.ntx86\bjam.exe  "-sBOOST_BUILD_PATH=D:\library\boost_1_33_1\tools\build\v2" "-sTOOLS=msvc" > log_msvc.txt
				`	

