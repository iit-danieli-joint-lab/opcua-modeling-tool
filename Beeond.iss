[ISSI]
#define ISSI_BackgroundImage "Beeond.bmp"
#define ISSI_BackgroundImage_BGColor "clWhite"

; Include ISSI
#define ISSI_IncludePath "C:\ISSI"
#include ISSI_IncludePath+"\_issi.isi"

#define AppName "UA Model eXcelerator"
#define AppVersion ReadIni(SourcePath + "\version.ini", "UMX", "Version", "0.0")
#define AppVersionBuild ReadIni(SourcePath + "\version.ini", "UMX", "Build", "0")
[Setup]
AppName=UA Model eXcelerator (UMX) {#AppVersion}.{#AppVersionBuild}
AppVerName={#AppName} {#AppVersion}.{#AppVersionBuild}
AppVersion={#AppVersion}.{#AppVersionBuild}
AppPublisher=Beeond, Inc.
AppPublisherURL=https://beeond.net/
AppSupportURL=https://beeond.net/
AppUpdatesURL=https://beeond.net/
AppCopyright=Beeond, Inc. Copyright (c) 2017
CreateAppDir=yes
DefaultDirName={pf}\Beeond\UMX
DefaultGroupName=Beeond\UMX
DisableDirPage=no
OutputDir=.\build_output_installer\
OutputBaseFileName=Beeond_UMX_Setup

;I'm not sure why we need to explicitly specify the Start Menu folder for Beeond on uninstall deletion.
;Without this, Beoond folder would still show up in the Start Menu after uninstall.
[UninstallDelete]
Type: filesandordirs; Name: "{commonprograms}\{group}"

;No need to specify the files and directories. It will be deleted automatically.
;[UninstallDelete]
;Type: files; Name: "{app}\*.dll"
;Type: files; Name: "{app}\*.exe"
;Type: files; Name: "{app}\*.xsd"
;Type: files; Name: "{app}\new_model_template.xml"
;Type: files; Name: "{app}\icons\*.*"
;Type: files; Name: "{app}\icons"


[Files]
Source: "build_output\*"; DestDir: "{app}"; Flags: recursesubdirs

[Icons]
Name: "{commonprograms}\{#AppName}"; Filename: "{app}\eXcelerator.exe"
Name: "{commondesktop}\{#AppName}"; Filename: "{app}\eXcelerator.exe"
Name: "{group}\{#AppName}"; Filename: "{app}\eXcelerator.exe"
Name: "{group}\Uninstall"; Filename: "{uninstallexe}"