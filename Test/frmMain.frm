VERSION 5.00
Begin VB.Form frmMain 
   Caption         =   "测试"
   ClientHeight    =   3990
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   8580
   LinkTopic       =   "Form1"
   ScaleHeight     =   3990
   ScaleWidth      =   8580
   StartUpPosition =   2  '屏幕中心
   Begin VB.CommandButton Command1 
      Caption         =   "UnHook"
      Height          =   555
      Left            =   6960
      TabIndex        =   3
      Top             =   1080
      Width           =   1215
   End
   Begin VB.TextBox Text3 
      Height          =   375
      Left            =   1410
      TabIndex        =   2
      Text            =   "Text3"
      Top             =   2400
      Width           =   4785
   End
   Begin VB.TextBox Text2 
      Height          =   345
      Left            =   1410
      TabIndex        =   1
      Text            =   "Text1"
      Top             =   1740
      Width           =   4755
   End
   Begin VB.TextBox Text1 
      Height          =   345
      Left            =   1410
      TabIndex        =   0
      Text            =   "Text1"
      Top             =   1110
      Width           =   4755
   End
End
Attribute VB_Name = "frmMain"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

Private Const WM_RBUTTONDOWN As Long = &H204
Private Const WM_RBUTTONUP As Long = &H205

Private WithEvents mclsSubClass As TSubclass.Subclass
Attribute mclsSubClass.VB_VarHelpID = -1
Private WithEvents mclsWinHook As TSubclass.WinHook
Attribute mclsWinHook.VB_VarHelpID = -1

Private WithEvents mclsMouseHook1 As TSubclass.MouseHook
Attribute mclsMouseHook1.VB_VarHelpID = -1
Private WithEvents mclsMouseHook2 As TSubclass.MouseHook
Attribute mclsMouseHook2.VB_VarHelpID = -1

Private Sub Command1_Click()
    
    mclsMouseHook2.UnHook
    Set mclsMouseHook2 = Nothing
    
End Sub

Private Sub Form_Load()
    
    Set mclsSubClass = New TSubclass.Subclass
    mclsSubClass.hWnd = Text3.hWnd

    Set mclsWinHook = New TSubclass.WinHook
    Debug.Print mclsWinHook.Hook(Text1.hWnd)
  
    Set mclsMouseHook1 = New TSubclass.MouseHook
    Debug.Print mclsMouseHook1.Hook
 
    Set mclsMouseHook2 = New TSubclass.MouseHook
    Debug.Print mclsMouseHook2.Hook
    
End Sub

Private Sub Form_Unload(Cancel As Integer)

    Set mclsSubClass = Nothing
    Set mclsWinHook = Nothing
    Set mclsMouseHook1 = Nothing
    Set mclsMouseHook2 = Nothing
    
End Sub

Private Function mclsSubClass_OnMessage(ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long, ByRef bEatIt As Boolean) As Long

    Select Case uMsg
    Case WM_RBUTTONDOWN, WM_RBUTTONUP

        bEatIt = True '吃掉这个消息
        mclsSubClass_OnMessage = 12 '返回自定义数据给窗口

    End Select
    
End Function

Private Sub mclsSubClass_AfterMessage(ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long)
    
    Debug.Print uMsg & "," & wParam & "," & lParam
    
End Sub

Private Sub mclsMouseHook1_OnMessage(ByVal hWnd As Long, ByVal uMsg As Long, ByVal x As Long, ByVal y As Long, ByVal wMouseData As Long, ByRef bEatIt As Boolean)
    
    Text1.Text = "MouseHook1: " & hWnd & "," & uMsg & "," & x & "," & y & "," & wMouseData
    
    Debug.Print Text1.Text, Timer
    
    Select Case uMsg
    Case WM_RBUTTONDOWN, WM_RBUTTONUP
        
        If hWnd = Text1.hWnd Then
            bEatIt = True
        End If
        
    End Select
    
End Sub

Private Sub mclsMouseHook2_OnMessage(ByVal hWnd As Long, ByVal uMsg As Long, ByVal x As Long, ByVal y As Long, ByVal wMouseData As Long, ByRef bEatIt As Boolean)
    
    Text2.Text = "MouseHook2: " & hWnd & "," & uMsg & "," & x & "," & y & "," & wMouseData
    
    Debug.Print Text2.Text, Timer
    
    Select Case uMsg
    Case WM_RBUTTONDOWN, WM_RBUTTONUP
        
        If hWnd = Text1.hWnd Then
            bEatIt = True
        End If
        
    End Select
    
End Sub

Private Sub mclsWinHook_OnMessage(ByVal hWnd As Long, ByVal uMsg As Long, ByVal wParam As Long, ByVal lParam As Long, ByRef bEatIt As Boolean)
    
    Text2.Text = hWnd & "," & uMsg & "," & wParam & "," & lParam
    
    'Debug.Print Text2.Text, Timer
    
    Select Case uMsg
    Case WM_RBUTTONDOWN, WM_RBUTTONUP
    
        bEatIt = True
        
    End Select
    
End Sub
