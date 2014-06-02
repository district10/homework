; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CSzsyView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "szsy.h"
LastPage=0

ClassCount=7
Class1=CSzsyApp
Class2=CSzsyDoc
Class3=CSzsyView
Class4=CMainFrame

ResourceCount=4
Resource1=IDR_MAINFRAME
Resource2=IDD_ABOUTBOX
Class5=CAboutDlg
Class6=CMoravec
Resource3=IDD_DIALOG_moravec
Class7=CForstner
Resource4=IDD_DIALOG_Forstner

[CLS:CSzsyApp]
Type=0
HeaderFile=szsy.h
ImplementationFile=szsy.cpp
Filter=N

[CLS:CSzsyDoc]
Type=0
HeaderFile=szsyDoc.h
ImplementationFile=szsyDoc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC

[CLS:CSzsyView]
Type=0
HeaderFile=szsyView.h
ImplementationFile=szsyView.cpp
Filter=C
LastObject=ID_Forstner
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=szsy.cpp
ImplementationFile=szsy.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_rgbtohui
Command15=ID_Moravec
Command16=ID_Forstner
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[DLG:IDD_DIALOG_moravec]
Type=1
Class=CMoravec
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT_size,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT_value,edit,1350631552

[CLS:CMoravec]
Type=0
HeaderFile=Moravec.h
ImplementationFile=Moravec.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CMoravec

[DLG:IDD_DIALOG_Forstner]
Type=1
Class=CForstner
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_EDIT_l1,edit,1350631552
Control6=IDC_EDIT_l2,edit,1350631552

[CLS:CForstner]
Type=0
HeaderFile=Forstner.h
ImplementationFile=Forstner.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT_l1

