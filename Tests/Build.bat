xcopy /s /y "Bin\Engine.dll" "Tests/Bin\Engine.dll"

g++ -g Tests/Source/*.cpp Tests/Source/Tests/*.cpp  -ITests/Source -IEngine/Source -LBin -LTests/Bin -lEngine -lglfw3 -o Tests/Bin/Tests.exe