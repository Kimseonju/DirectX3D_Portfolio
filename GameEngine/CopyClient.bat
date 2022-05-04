cd..
cd..

REM Client3D 클래스정보 옮겨오기
xcopy .\Client3D\Include\*.h .\Client\Include\ /s /d /y
xcopy .\Client3D\Include\*.inl .\Client\Include\ /s /d /y
xcopy .\Client3D\Include\*.hpp .\Client\Include\ /s /d /y
xcopy .\Client3D\Bin\Client3D_Debug.lib .\GameEditor\Bin\ /s /d /y

xcopy .\Client3D\Bin\Mesh\*.bne .\GameEditor\Bin\Mesh\ /s /d /y
xcopy .\Client3D\Bin\Mesh\*.msh .\GameEditor\Bin\Mesh\ /s /d /y
xcopy .\Client3D\Bin\Mesh\*.sqc .\GameEditor\Bin\Mesh\ /s /d /y
xcopy .\Client3D\Bin\Mesh\*.tga .\GameEditor\Bin\Mesh\ /s /d /y
xcopy .\Client3D\Bin\Mesh\*.png .\GameEditor\Bin\Mesh\ /s /d /y
xcopy .\Client3D\Bin\Mesh\*.jpeg .\GameEditor\Bin\Mesh\ /s /d /y
xcopy .\Client3D\Bin\Mesh\*.bmp .\GameEditor\Bin\Mesh\ /s /d /y

xcopy .\Client3D\Bin\Texture\*.tga .\GameEditor\Bin\Texture\ /s /d /y
xcopy .\Client3D\Bin\Texture\*.png .\GameEditor\Bin\Texture\ /s /d /y
xcopy .\Client3D\Bin\Texture\*.jpeg .\GameEditor\Bin\Texture\ /s /d /y
xcopy .\Client3D\Bin\Texture\*.bmp .\GameEditor\Bin\Texture\ /s /d /y


