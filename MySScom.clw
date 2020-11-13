; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMySScomDlg
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "MySScom.h"

ClassCount=5
Class1=CMySScomApp
Class2=CMySScomDlg

ResourceCount=7
Resource2=IDD_DIALOG_ABOUT
Resource3=IDD_MYSSCOM_DIALOG
Resource1=IDR_MAINFRAME
Resource4=IDR_MENU_TRAY
Class3=CDialogAbout
Resource5=IDD_DIALOG_SRSEND
Class4=CDialogSrSend
Resource6=IDD_DIALOG_EXFUNCT
Class5=CDialogExfunct
Resource7=IDR_MENU_EDIT

[CLS:CMySScomApp]
Type=0
HeaderFile=MySScom.h
ImplementationFile=MySScom.cpp
Filter=N

[CLS:CMySScomDlg]
Type=0
HeaderFile=MySScomDlg.h
ImplementationFile=MySScomDlg.cpp
Filter=D
LastObject=CMySScomDlg
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_MYSSCOM_DIALOG]
Type=1
Class=CMySScomDlg
ControlCount=45
Control1=IDC_COMBO_COMNO,combobox,1344339971
Control2=IDC_COMBO_BAUD,combobox,1344339971
Control3=IDC_COMBO_DATA,combobox,1344339971
Control4=IDC_COMBO_STOP,combobox,1344339971
Control5=IDC_BUTTON_ONOFF,button,1342242817
Control6=IDC_BUTTON_PAUSE,button,1342242816
Control7=IDC_BUTTON_SAVE,button,1342242816
Control8=IDC_BUTTON_CLEAR,button,1342242816
Control9=IDC_CHECK_HEXDSPL,button,1342246147
Control10=IDC_CHECK_AUTOCLEAR,button,1342246147
Control11=IDC_EDIT_LINES,edit,1350639617
Control12=IDC_CHECK_AUTOSAVE,button,1342246147
Control13=IDC_BUTTON_SRSEND,button,1342242816
Control14=IDC_BUTTON_COUNT,button,1342242816
Control15=IDC_CHECK_HEXSEND,button,1342246147
Control16=IDC_EDIT_TIMER,edit,1350639617
Control17=IDC_CHECK_RETURN,button,1342242819
Control18=IDC_EDIT_SEND,edit,1350635648
Control19=IDC_BUTTON_SEND,button,1342242816
Control20=IDC_EDIT_RECV,RICHEDIT,1352742916
Control21=IDC_CHECK_AUTOSEND,button,1342246147
Control22=IDC_STATIC_CONTROL,button,1342177287
Control23=IDC_STATIC_RECEIVE,button,1342177287
Control24=IDC_STATIC_SEND,button,1342177287
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC_MS,static,1342308352
Control30=IDC_STATIC_DEVIDE,static,1342177296
Control31=IDC_STATIC_OVER,static,1342308352
Control32=IDC_STATIC_LINES,static,1342308352
Control33=IDC_CHECK_SHOWTIME,button,1342242819
Control34=IDC_STATIC,static,1342308352
Control35=IDC_COMBO_CHECK,combobox,1344339971
Control36=IDC_CHECK_FRAMEDSPL,button,1342242819
Control37=IDC_CHECK_SHOWDIREC,button,1342242819
Control38=IDC_CHECK_SHOWSDATA,button,1342242819
Control39=IDC_BUTTON_EXFUNCT,button,1342242816
Control40=IDC_BUTTON_ABOUTME,button,1342242816
Control41=IDC_EDIT_FILEPATH,edit,1350631424
Control42=IDC_BUTTON_OPENFILE,button,1342242816
Control43=IDC_BUTTON_SENDFILE,button,1342242816
Control44=IDC_STATIC_FILE,button,1342177287
Control45=IDC_PROGRESS_SENDFILE,msctls_progress32,1350565889

[MNU:IDR_MENU_TRAY]
Type=1
Class=CMySScomDlg
Command1=IDC_MENU_TRAY_ABOUT
Command2=IDC_MENU_TRAY_SHOW
Command3=IDC_MENU_TRAY_HIDE
Command4=IDC_MENU_TRAY_EXIT
CommandCount=4

[MNU:IDR_MENU_EDIT]
Type=1
Class=?
Command1=IDC_MENU_EDIT_CUT
Command2=IDC_MENU_EDIT_COPY
Command3=IDC_MENU_EDIT_PASTE
Command4=IDC_MENU_EDIT_SELALL
Command5=IDC_MENU_EDIT_CLEAR
CommandCount=5

[DLG:IDD_DIALOG_ABOUT]
Type=1
Class=CDialogAbout
ControlCount=5
Control1=IDC_STATIC_MAINFRAME,static,1342177294
Control2=IDC_BUTTON_SWITCH,button,1342242816
Control3=IDC_BUTTON_READOK,button,1342242816
Control4=IDC_STATIC_ABOUT,button,1342177287
Control5=IDC_EDIT_ABOUT,edit,1344342084

[CLS:CDialogAbout]
Type=0
HeaderFile=DialogAbout.h
ImplementationFile=DialogAbout.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_SWITCH
VirtualFilter=dWC

[DLG:IDD_DIALOG_SRSEND]
Type=1
Class=CDialogSrSend
ControlCount=168
Control1=IDC_RADIO_SENDALL,button,1342311433
Control2=IDC_EDIT_AUTOTIME,edit,1350639745
Control3=IDC_RADIO_SENDEACH,button,1342180361
Control4=IDC_BUTTON_EXPAND,button,1342242816
Control5=IDC_CHECK_01,button,1342242819
Control6=IDC_EDIT_01,edit,1350631552
Control7=IDC_BUTTON_SEND01,button,1342242816
Control8=IDC_CHECK_02,button,1342242819
Control9=IDC_EDIT_02,edit,1350631552
Control10=IDC_BUTTON_SEND02,button,1342242816
Control11=IDC_CHECK_03,button,1342242819
Control12=IDC_EDIT_03,edit,1350631552
Control13=IDC_BUTTON_SEND03,button,1342242816
Control14=IDC_CHECK_04,button,1342242819
Control15=IDC_EDIT_04,edit,1350631552
Control16=IDC_BUTTON_SEND04,button,1342242816
Control17=IDC_CHECK_05,button,1342242819
Control18=IDC_EDIT_05,edit,1350631552
Control19=IDC_BUTTON_SEND05,button,1342242816
Control20=IDC_CHECK_06,button,1342242819
Control21=IDC_EDIT_06,edit,1350631552
Control22=IDC_BUTTON_SEND06,button,1342242816
Control23=IDC_CHECK_07,button,1342242819
Control24=IDC_EDIT_07,edit,1350631552
Control25=IDC_BUTTON_SEND07,button,1342242816
Control26=IDC_CHECK_08,button,1342242819
Control27=IDC_EDIT_08,edit,1350631552
Control28=IDC_BUTTON_SEND08,button,1342242816
Control29=IDC_CHECK_09,button,1342242819
Control30=IDC_EDIT_09,edit,1350631552
Control31=IDC_BUTTON_SEND09,button,1342242816
Control32=IDC_CHECK_10,button,1342242819
Control33=IDC_EDIT_10,edit,1350631552
Control34=IDC_BUTTON_SEND10,button,1342242816
Control35=IDC_CHECK_11,button,1342242819
Control36=IDC_EDIT_11,edit,1350631552
Control37=IDC_BUTTON_SEND11,button,1342242816
Control38=IDC_CHECK_12,button,1342242819
Control39=IDC_EDIT_12,edit,1350631552
Control40=IDC_BUTTON_SEND12,button,1342242816
Control41=IDC_CHECK_13,button,1342242819
Control42=IDC_EDIT_13,edit,1350631552
Control43=IDC_BUTTON_SEND13,button,1342242816
Control44=IDC_CHECK_14,button,1342242819
Control45=IDC_EDIT_14,edit,1350631552
Control46=IDC_BUTTON_SEND14,button,1342242816
Control47=IDC_CHECK_15,button,1342242819
Control48=IDC_EDIT_15,edit,1350631552
Control49=IDC_BUTTON_SEND15,button,1342242816
Control50=IDC_CHECK_16,button,1342242819
Control51=IDC_EDIT_16,edit,1350631552
Control52=IDC_BUTTON_SEND16,button,1342242816
Control53=IDC_CHECK_17,button,1342242819
Control54=IDC_EDIT_17,edit,1350631552
Control55=IDC_BUTTON_SEND17,button,1342242816
Control56=IDC_CHECK_18,button,1342242819
Control57=IDC_EDIT_18,edit,1350631552
Control58=IDC_BUTTON_SEND18,button,1342242816
Control59=IDC_STATIC,static,1342308352
Control60=IDC_CHECK_19,button,1342242819
Control61=IDC_EDIT_19,edit,1350631552
Control62=IDC_BUTTON_SEND19,button,1342242816
Control63=IDC_CHECK_20,button,1342242819
Control64=IDC_EDIT_20,edit,1350631552
Control65=IDC_BUTTON_SEND20,button,1342242816
Control66=IDC_CHECK_21,button,1342242819
Control67=IDC_EDIT_21,edit,1350631552
Control68=IDC_BUTTON_SEND21,button,1342242816
Control69=IDC_CHECK_22,button,1342242819
Control70=IDC_EDIT_22,edit,1350631552
Control71=IDC_BUTTON_SEND22,button,1342242816
Control72=IDC_CHECK_23,button,1342242819
Control73=IDC_EDIT_23,edit,1350631552
Control74=IDC_BUTTON_SEND23,button,1342242816
Control75=IDC_CHECK_24,button,1342242819
Control76=IDC_EDIT_24,edit,1350631552
Control77=IDC_BUTTON_SEND24,button,1342242816
Control78=IDC_CHECK_25,button,1342242819
Control79=IDC_EDIT_25,edit,1350631552
Control80=IDC_BUTTON_SEND25,button,1342242816
Control81=IDC_CHECK_26,button,1342242819
Control82=IDC_EDIT_26,edit,1350631552
Control83=IDC_BUTTON_SEND26,button,1342242816
Control84=IDC_CHECK_27,button,1342242819
Control85=IDC_EDIT_27,edit,1350631552
Control86=IDC_BUTTON_SEND27,button,1342242816
Control87=IDC_CHECK_28,button,1342242819
Control88=IDC_EDIT_28,edit,1350631552
Control89=IDC_BUTTON_SEND28,button,1342242816
Control90=IDC_CHECK_29,button,1342242819
Control91=IDC_EDIT_29,edit,1350631552
Control92=IDC_BUTTON_SEND29,button,1342242816
Control93=IDC_CHECK_30,button,1342242819
Control94=IDC_EDIT_30,edit,1350631552
Control95=IDC_BUTTON_SEND30,button,1342242816
Control96=IDC_CHECK_31,button,1342242819
Control97=IDC_EDIT_31,edit,1350631552
Control98=IDC_BUTTON_SEND31,button,1342242816
Control99=IDC_CHECK_32,button,1342242819
Control100=IDC_EDIT_32,edit,1350631552
Control101=IDC_BUTTON_SEND32,button,1342242816
Control102=IDC_CHECK_33,button,1342242819
Control103=IDC_EDIT_33,edit,1350631552
Control104=IDC_BUTTON_SEND33,button,1342242816
Control105=IDC_CHECK_34,button,1342242819
Control106=IDC_EDIT_34,edit,1350631552
Control107=IDC_BUTTON_SEND34,button,1342242816
Control108=IDC_CHECK_35,button,1342242819
Control109=IDC_EDIT_35,edit,1350631552
Control110=IDC_BUTTON_SEND35,button,1342242816
Control111=IDC_CHECK_36,button,1342242819
Control112=IDC_EDIT_36,edit,1350631552
Control113=IDC_BUTTON_SEND36,button,1342242816
Control114=IDC_CHECK_37,button,1342242819
Control115=IDC_EDIT_37,edit,1350631552
Control116=IDC_BUTTON_SEND37,button,1342242816
Control117=IDC_CHECK_38,button,1342242819
Control118=IDC_EDIT_38,edit,1350631552
Control119=IDC_BUTTON_SEND38,button,1342242816
Control120=IDC_CHECK_39,button,1342242819
Control121=IDC_EDIT_39,edit,1350631552
Control122=IDC_BUTTON_SEND39,button,1342242816
Control123=IDC_CHECK_40,button,1342242819
Control124=IDC_EDIT_40,edit,1350631552
Control125=IDC_BUTTON_SEND40,button,1342242816
Control126=IDC_STATIC,static,1342177296
Control127=IDC_EDIT_T01,edit,1350639745
Control128=IDC_EDIT_T02,edit,1350639745
Control129=IDC_EDIT_T03,edit,1350639745
Control130=IDC_EDIT_T04,edit,1350639745
Control131=IDC_EDIT_T05,edit,1350639745
Control132=IDC_EDIT_T06,edit,1350639745
Control133=IDC_EDIT_T07,edit,1350639745
Control134=IDC_EDIT_T08,edit,1350639745
Control135=IDC_EDIT_T09,edit,1350639745
Control136=IDC_EDIT_T10,edit,1350639745
Control137=IDC_EDIT_T11,edit,1350639745
Control138=IDC_EDIT_T12,edit,1350639745
Control139=IDC_EDIT_T13,edit,1350639745
Control140=IDC_EDIT_T14,edit,1350639745
Control141=IDC_EDIT_T15,edit,1350639745
Control142=IDC_EDIT_T16,edit,1350639745
Control143=IDC_EDIT_T17,edit,1350639745
Control144=IDC_EDIT_T18,edit,1350639745
Control145=IDC_EDIT_T19,edit,1350639745
Control146=IDC_EDIT_T20,edit,1350639745
Control147=IDC_EDIT_T21,edit,1350639745
Control148=IDC_EDIT_T22,edit,1350639745
Control149=IDC_EDIT_T23,edit,1350639745
Control150=IDC_EDIT_T24,edit,1350639745
Control151=IDC_EDIT_T25,edit,1350639745
Control152=IDC_EDIT_T26,edit,1350639745
Control153=IDC_EDIT_T27,edit,1350639745
Control154=IDC_EDIT_T28,edit,1350639745
Control155=IDC_EDIT_T29,edit,1350639745
Control156=IDC_EDIT_T30,edit,1350639745
Control157=IDC_EDIT_T31,edit,1350639745
Control158=IDC_EDIT_T32,edit,1350639745
Control159=IDC_EDIT_T33,edit,1350639745
Control160=IDC_EDIT_T34,edit,1350639745
Control161=IDC_EDIT_T35,edit,1350639745
Control162=IDC_EDIT_T36,edit,1350639745
Control163=IDC_EDIT_T37,edit,1350639745
Control164=IDC_EDIT_T38,edit,1350639745
Control165=IDC_EDIT_T39,edit,1350639745
Control166=IDC_EDIT_T40,edit,1350639745
Control167=IDC_BUTTON_STARTSEND,button,1342242816
Control168=IDC_STATIC,static,1342177297

[CLS:CDialogSrSend]
Type=0
HeaderFile=DialogSrSend.h
ImplementationFile=DialogSrSend.cpp
BaseClass=CDialog
Filter=D
LastObject=CDialogSrSend
VirtualFilter=dWC

[DLG:IDD_DIALOG_EXFUNCT]
Type=1
Class=CDialogExfunct
ControlCount=35
Control1=IDC_EDIT_CHECKSUM,edit,1352728652
Control2=IDC_EDIT_CHANGE,edit,1352728644
Control3=IDC_EDIT_BFRAME,edit,1352728652
Control4=IDC_EDIT_AFRAME,edit,1352728652
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,button,1342177287
Control7=IDC_STATIC,button,1342177287
Control8=IDC_RADIO_CHECKADDO,button,1342308361
Control9=IDC_RADIO_CHECKADDN,button,1342177289
Control10=IDC_RADIO_CHECKXOR,button,1342177289
Control11=IDC_BUTTON_GETCHKSUM,button,1342242816
Control12=IDC_EDIT_CHKSUM10,edit,1350641673
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_EDIT_CHKSUM16,edit,1350633481
Control16=IDC_RADIO_DISPMODE,button,1342308361
Control17=IDC_RADIO_DispChar,button,1342177289
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_EDIT_HEAD1,edit,1350631561
Control21=IDC_EDIT_HEAD2,edit,1350631561
Control22=IDC_EDIT_KEY,edit,1350633609
Control23=IDC_EDIT_CHAR1,edit,1350631561
Control24=IDC_EDIT_CHAR2,edit,1350631561
Control25=IDC_STATIC,static,1342308353
Control26=IDC_STATIC,static,1342308353
Control27=IDC_STATIC,static,1342308353
Control28=IDC_STATIC,static,1342308353
Control29=IDC_RADIO_ASSEMBLE,button,1342308361
Control30=IDC_RADIO_DISASMBLE,button,1342177289
Control31=IDC_BUTTON_FRAME,button,1342242816
Control32=IDC_BUTTON_UNFRAME,button,1342242816
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342177297
Control35=IDC_STATIC,static,1342177296

[CLS:CDialogExfunct]
Type=0
HeaderFile=DialogExfunct.h
ImplementationFile=DialogExfunct.cpp
BaseClass=CDialog
Filter=D
LastObject=CDialogExfunct
VirtualFilter=dWC

