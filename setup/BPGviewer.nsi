;Created by Rupesh.s for BPG viewer

;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Compressor

  SetCompressor /SOLID lzma
  SetCompressorDictSize 32
;setup file
;--------------------------------
OutFile bpgviewer-1.0.0-win32.exe 
;--------------------------------
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Defines & includes
!define PRODUCT_NAME "BPGviewer"
!define PRODUCT_VERSION "1.0.0"
!define PRODUCT_PUBLISHER "Rupesh Sreeraman<BPGviewer.dev@gmail.com>"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"
!define PRODUCT_STARTMENU_GROUP "BPGviewer"
!define BPGviewer_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\BPGviewer"
Var ext
!include MUI2.nsh
!include "TextFunc.nsh"
!include FileAssociation.nsh
!include "LogicLib.nsh"

;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Configuration
;General
;Version tab on file properties
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
VIProductVersion "1.0.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" "BPGviewer Installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments""Better Portable Graphics image viewer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" "Rupesh Sreeraman"
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalTrademarks" ""
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "© Rupesh Sreeraman 2014"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "BPGviewer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" "1.0.0"

Name "BPGviewer"
BrandingText "BPGviewer 1.0 for Windows"
/* Sets default install dir to $PROGRAMFILES\BPGviewer.
  If InstallDirRegKey exists (from a previous installation,
  it will default to that directory instead. */
  InstallDir "$PROGRAMFILES\BPGviewer"
  InstallDirRegKey HKLM "Software\BPGviewer" "Path"
  
  ;Put on a show
  ShowInstDetails show
  ShowUnInstDetails show
  
  ;Vista+ XML manifest, does not affect older OSes
  RequestExecutionLevel admin
  
;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
;Interface Settings
XPStyle on

   !define  MUI_LANGDLL_ALWAYSSHOW

  !define MUI_ABORTWARNING
  !define MUI_COMPONENTSPAGE_SMALLDESC
  !define MUI_LICENSEPAGE_CHECKBOX
  !define MUI_FINISHPAGE_RUN $INSTDIR\BPGviewer.exe
  !define MUI_FINISHPAGE_RUN_NOTCHECKED
  !define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange.bmp"

  # Installer/Uninstaller icons
  !define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
  !define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"

  # Language Selection Dialog Settings
  !define MUI_LANGDLL_REGISTRY_ROOT "${PRODUCT_UNINST_ROOT_KEY}"
  !define MUI_LANGDLL_REGISTRY_KEY "${PRODUCT_UNINST_KEY}"
  !define MUI_LANGDLL_REGISTRY_VALUENAME "NSIS:Language"
;--------------------------------
;Pages
;MUI_PAGE_WELCOME should always be first and MUI_PAGE_FINISH should be last

  # Install Pages
  !insertmacro MUI_PAGE_WELCOME
  !insertmacro MUI_PAGE_LICENSE "c:\Copying.txt"
  !insertmacro MUI_PAGE_COMPONENTS
  !insertmacro MUI_PAGE_DIRECTORY
  !insertmacro MUI_PAGE_INSTFILES
  !insertmacro MUI_PAGE_FINISH

  # UnInstall Pages
  !insertmacro MUI_UNPAGE_INSTFILES
;--------------------------------
; Languages

  !insertmacro MUI_LANGUAGE "Basque"
  !insertmacro MUI_LANGUAGE "Catalan"
  !insertmacro MUI_LANGUAGE "Czech"
  !insertmacro MUI_LANGUAGE "Danish"
  !insertmacro MUI_LANGUAGE "Dutch"
  !insertmacro MUI_LANGUAGE "English"
  !insertmacro MUI_LANGUAGE "Finnish"
  !insertmacro MUI_LANGUAGE "French"
  !insertmacro MUI_LANGUAGE "German"
  !insertmacro MUI_LANGUAGE "Hebrew"
  !insertmacro MUI_LANGUAGE "Hungarian"
  !insertmacro MUI_LANGUAGE "Italian"
  !insertmacro MUI_LANGUAGE "Norwegian"
  !insertmacro MUI_LANGUAGE "NorwegianNynorsk"
  !insertmacro MUI_LANGUAGE "Polish"
  !insertmacro MUI_LANGUAGE "Portuguese"
  !insertmacro MUI_LANGUAGE "PortugueseBR"
  !insertmacro MUI_LANGUAGE "Russian"
  !insertmacro MUI_LANGUAGE "Slovak"
  !insertmacro MUI_LANGUAGE "Slovenian"
  !insertmacro MUI_LANGUAGE "Spanish"
  !insertmacro MUI_LANGUAGE "SpanishInternational"

;--------------------------------
;Reserve Files

  ;These files should be inserted before other files in the data block
  ;Keep these lines before any File command
  ;Only for solid compression (by default, solid compression is enabled for BZIP2 and LZMA)

  !insertmacro MUI_RESERVEFILE_LANGDLL
  
;--------------------------------

;+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


Section "BPGviewer(required)"
SectionIn RO
SetOutPath "$INSTDIR"
File "C:\BPGviewer_setup\bpgfile.ico"
File "C:\BPGviewer_setup\BPGviewer.exe.manifest"
File "C:\BPGviewer_setup\fmtsi.img"
File "C:\BPGviewer_setup\libgcc_s_dw2-1.dll"
File "C:\BPGviewer_setup\mingwm10.dll"
File "C:\BPGviewer_setup\QtCore4.dll"
File "C:\BPGviewer_setup\QtSvg4.dll"
File "C:\BPGviewer_setup\QtGui4.dll"
File "C:\BPGviewer_setup\QtNetwork4.dll"
File "C:\BPGviewer_setup\QtWebKit4.dll"
File "C:\BPGviewer_setup\QtXml4.dll"
File "C:\BPGviewer_setup\QtXmlPatterns4.dll"
File "C:\BPGviewer_setup\libpng12.dll"
File "C:\BPGviewer_setup\BPGviewer.exe"
File "C:\BPGviewer_setup\LICENSE.txt"

SetOutPath "$INSTDIR\imageformats"
File  "C:\BPGviewer_setup\imageformats\qgif4.dll"
File  "C:\BPGviewer_setup\imageformats\qico4.dll"
File  "C:\BPGviewer_setup\imageformats\qjpeg4.dll"
File  "C:\BPGviewer_setup\imageformats\qmng4.dll"
File  "C:\BPGviewer_setup\imageformats\qsvg4.dll"
File  "C:\BPGviewer_setup\imageformats\qtiff4.dll"



SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"
WriteRegStr HKLM "${BPGviewer_UNINST_KEY}" "DisplayName" "BPGviewer-BPG image viewer"
WriteRegStr HKLM "${BPGviewer_UNINST_KEY}" "UninstallString" "$\"$INSTDIR\uninstall.exe$\""
WriteRegStr HKLM "${BPGviewer_UNINST_KEY}" "DisplayIcon" "$INSTDIR\BPGviewer.exe"				 
ClearErrors

done:
;Update shell
!insertmacro  UPDATEFILEASSOC
ClearErrors

FileOpen $0 "$INSTDIR\fmtsi.img"  r
IfErrors vdone
;///////////////////////////////////
vloop:
FileRead $0 $1

${TrimNewLines} $1	$ext
DetailPrint $ext
StrCmp  $1 "eof" vdone vasso
vasso:
!insertmacro APP_ASSOCIATE  $ext \
                           "BPGviewer.ImageFile"\
						   "Image file"\
						   "$INSTDIR\bpgfile.ico" \
                           "Open with BPGviewer" \
	                       "$INSTDIR\BPGviewer.exe $\"%1$\"" 

StrCmp  $1 "" vdone vloop
;//////////////////////////////////////////////
FileClose $0

vdone:
;Update shell
!insertmacro  UPDATEFILEASSOC
;--------------------------------
; Desktop shortcut

  SetOutPath "$INSTDIR"
  # all = global; current = current user
  SetShellVarContext all
  CreateShortCut "$DESKTOP\BPGviewer.lnk" "$INSTDIR\BPGviewer.exe"

 
  SetOutPath "$INSTDIR"
  # Start menu shortcut creation
  SetShellVarContext all
  CreateDirectory "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}\${PRODUCT_NAME}.lnk" "$INSTDIR\BPGviewer.exe"
  CreateShortCut "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}\Uninstall ${PRODUCT_NAME}.lnk" "$INSTDIR\uninstall.exe"

SectionEnd


Section "un.Uninstaller Section"
ClearErrors
FileOpen $0 "$INSTDIR\fmtsi.img"  r
IfErrors uvdone
;///////////////////////////////////
uvloop:
FileRead $0 $1
${TrimNewLines} $1	$ext
DetailPrint $ext
StrCmp  $1 "eof" uvdone uvunasso
uvunasso:
!insertmacro APP_UNASSOCIATE $ext "BPGviewer.ImageFile"	
StrCmp  $1 "" uvdone uvloop
;////////////////////////////////////////////////
FileClose $0
uvdone:
;Update shell
!insertmacro  UPDATEFILEASSOC
Delete "$INSTDIR\bpgfile.ico"
Delete "$INSTDIR\BPGviewer.exe.manifest" 
Delete "$INSTDIR\libgcc_s_dw2-1.dll"
Delete "$INSTDIR\mingwm10.dll"
Delete "$INSTDIR\QtCore4.dll"
Delete "$INSTDIR\QtSvg4.dll"
Delete "$INSTDIR\QtGui4.dll"
Delete "$INSTDIR\QtNetwork4.dll"
Delete "$INSTDIR\QtWebKit4.dll"
Delete "$INSTDIR\QtXml4.dll"
Delete "$INSTDIR\QtXmlPatterns4.dll"
Delete "$INSTDIR\libpng12.dll"
Delete "$INSTDIR\BPGviewer.exe"
Delete "$INSTDIR\LICENSE.txt"
Delete "$INSTDIR\libpng12.dll"
Delete "$INSTDIR\imageformats\qgif4.dll"
Delete "$INSTDIR\imageformats\qico4.dll"
Delete "$INSTDIR\imageformats\qjpeg4.dll"
Delete "$INSTDIR\imageformats\qmng4.dll"
Delete "$INSTDIR\imageformats\qsvg4.dll"
Delete "$INSTDIR\imageformats\qtiff4.dll"
DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\BPGviewer"

RMDir "$INSTDIR\imageformats"


Delete "$INSTDIR\uninstall.exe"

 # Delete desktop and start menu shortcuts
  SetShellVarContext all
  Delete "$DESKTOP\BPGviewer.lnk"
  RMDir /r "$SMPROGRAMS\${PRODUCT_STARTMENU_GROUP}"

SectionEnd


;--------------------------------
;Installer Functions

Function .onInit

ReadRegStr $R0 HKLM \
  "${BPGviewer_UNINST_KEY}" \
  "UninstallString"
  StrCmp $R0 "" done
 
  MessageBox MB_OKCANCEL|MB_ICONEXCLAMATION \
  "BPGviewer is already installed. $\n$\nClick `OK` to remove the \
  previous version or `Cancel` to cancel this upgrade." \
  IDOK uninst
  Abort
 
;Run the uninstaller
uninst:
  ClearErrors
  ExecWait '$R0 _?=$INSTDIR' ;Do not copy the uninstaller to a temp file
 
  IfErrors no_remove_uninstaller done
    ;You can either use Delete /REBOOTOK in the uninstaller or add some code
    ;here to remove the uninstaller. Use a registry key to check
    ;whether the user has chosen to uninstall. If you are using an uninstaller
    ;components page, make sure all sections are uninstalled.
  no_remove_uninstaller:
 
done:

System::Call 'kernel32::CreateMutexA(i 0, i 0, t "$(^Name)") i .r1 ?e'
 
 Pop $R0
 StrCmp $R0 0 +3
 MessageBox MB_OK|MB_ICONEXCLAMATION "The installer is already running."
 Abort

!insertmacro MUI_LANGDLL_DISPLAY
  
;LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

  ;${MementoSectionRestore}
 
FunctionEnd

;--------------------------------
;UnInstaller Functions
Function un.onInit
 ;Get the stored language preference
  !insertmacro MUI_UNGETLANGUAGE
  
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "Are you sure you want to completely remove $(^Name) and all of its components?" IDYES +2
   Abort
FunctionEnd

Function un.onUninstSuccess

  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) was successfully removed from your computer."

FunctionEnd

