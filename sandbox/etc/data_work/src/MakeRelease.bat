@echo off
echo Build DataWork

"C:\Program Files\Microsoft Visual Studio 9.0\Common7\IDE\devenv.exe" ^
	DataWork.sln /rebuild Release

echo Copy Release
rmdir /S /Q	_Release
mkdir _Release
copy Analisys\*.fig _Release > nul
copy Analisys\*.m _Release > nul
copy Processor\\bin\Release\Processor.exe _Release > nul
copy Processor\\bin\Release\Archive.mdb _Release > nul
copy Registrator\Release\Reg*.exe _Release > nul
copy Shell\\bin\Release\Shell.exe _Release > nul
copy .\Help.doc _Release > nul

echo Clear Temps
rmdir /S /Q Processor\bin
rmdir /S /Q Processor\obj
rmdir /S /Q Registrator\Release
rmdir /S /Q Shell\bin
rmdir /S /Q Shell\obj

echo Done!
pause
echo on