object PlotterForm: TPlotterForm
  Left = 268
  Top = 241
  Width = 1088
  Height = 750
  Caption = 'Funktionsplotter'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 13
  object PaintBox: TPaintBox
    Left = 0
    Top = 129
    Width = 1080
    Height = 594
    Align = alClient
    Color = clWhite
    ParentColor = False
    OnPaint = PaintBoxPaint
  end
  object Panel1: TPanel
    Left = 0
    Top = 0
    Width = 1080
    Height = 129
    Align = alTop
    TabOrder = 0
    object Label1: TLabel
      Left = 8
      Top = 16
      Width = 50
      Height = 13
      Caption = 'X-Intervall:'
    end
    object Label2: TLabel
      Left = 344
      Top = 16
      Width = 50
      Height = 13
      Caption = 'Y-Intervall:'
    end
    object Label3: TLabel
      Left = 8
      Top = 48
      Width = 20
      Height = 13
      Caption = 'f(x)='
    end
    object EditXmin: TEdit
      Left = 72
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 0
      Text = '-5'
    end
    object EditXmax: TEdit
      Left = 200
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 1
      Text = '+5'
    end
    object EditYmin: TEdit
      Left = 408
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 2
      Text = '-5'
    end
    object EditYmax: TEdit
      Left = 536
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 3
      Text = '+5'
    end
    object EditFunction1: TEdit
      Left = 72
      Top = 48
      Width = 585
      Height = 21
      TabOrder = 4
      Text = 'sin(x)'
    end
    object ButtonRefresh: TButton
      Left = 664
      Top = 16
      Width = 75
      Height = 25
      Caption = 'Aktualisieren'
      Default = True
      TabOrder = 7
      OnClick = ButtonRefreshClick
    end
    object EditFunction2: TEdit
      Left = 72
      Top = 72
      Width = 585
      Height = 21
      TabOrder = 5
      Text = 'cos(x)'
    end
    object EditFunction3: TEdit
      Left = 72
      Top = 96
      Width = 585
      Height = 21
      TabOrder = 6
      Text = 'tan(x)'
    end
  end
end
