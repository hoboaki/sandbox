# 文字コード：UTF-8

## ロムの名前

意識するポイント
- ファイル名順＝歴史順でソートされる。
- ファイル名はできる範囲で短く。

変えられるようにする。（GitだとVcsVersionが手前にくるとファイル名順＝歴史順ではなくなるため）

svn
```
$(ProjectName)_$(VcsVersion)_$(BuildVersionShortName)_$(BuildTargetName)_$(BuildDateAndTime)

MyProject_r12345_Td_PC-Product_170401-1230
MyProject_r12345_Td_PC-Trial_170401-1230
```

git その１
```
$(ProjectName)_$(VcsLastModifiedDateAndTime)_$(BuildVersionShortName)_$(BuildTargetName)

MyProject_170401-1120_Td_PC-Product
MyProject_170401-1120_Td_PC-Trial
```

git その２
```
$(ProjectName)_$(VcsLastModifiedDateAndTime)_$(BuildVersionShortName)_$(BuildTargetName_$(VcsVersion)

MyProject_170401-1120_Td_PC-Product_AB0926
MyProject_170401-1120_Td_PC-Trial_AB0926
```

## 名前空間

公式コードの名前空間。予約名扱いのためユーザーコードではこの名前空間以下にコードを書いてはいけない。

- ae:: Ae. 共通コード層。いかなる環境でも通るコードを書くことを意識する層。
- ap:: Ap. プラグインコード層。特定の環境で通るコードを書く層。
- apf:: Apf. プラグイン共通コード層。プラグインコードで使い回される共通コードを書く層。（例：OpenGLの実装など）


C#DLL

- Ae  : スクリプトコードから参照できるコード置き場。
- Adk : スクリプトコードをのぞくC#コードから参照できるコード置き場。

- ae   adel engine
- ap   adel engine plugin
- apf  adel engine plugin foundation
- adk  adel engine development kit

## 名前検討欄

- Platform
    - win-dx11
    - ios-gles300
- Build Target
- Build System
    - Win-VisualStudio Ios-Xcode Mac-Xcode
- Build Version
    - Debug(Db)
    - LocalDevelop(Ld) 
    - TeamDevelop(Td)
    - Review(Rv)
    - Final(Fn)
- Version Control System (Vcs)
- DirectX
    - dx11
- OpenGL
    - gl330 (version 3.3) gles300(version 3.0)

## アセットのバイナリタイプ

- Universal （OS・デバイス非依存）
    - エンディアンだけ変わる。32bit64bitはひとまず64bit固定とする。
    - UniversalLE
    - UniversalBE
- GraphicsResouce（Shader・Texture・VertexAttribute）
    - CoreGfxのタイプによって生成物が変わりそう。
    - WinDx11
    - WinVk
    - WinGl330
    - IosGles300
    - IosMtl
    - MacGl330
    - MacMtl
    
## グラフィックスアセットの検討

- .fbx .dae
    - Ae.Gfx.ResMdl
    - Ae.Gfx.ResMdlAnimSkl
- .aemat .aematanim MaterialEditor
    - Ae.Gfx.ResMat
    - Ae.Gfx.ResMatAnim
- .aepfx PosteffectEditor
    - Ae.Gfx.ResPfx Ae.Gfx.ResPfxAnim
- .aevfx VfxEditor
    - Ae.Gfx.ResVfx
- .tga .dds
    - Ae.Gfx.ResTexture
- シェーダーリソース
    - Ae.Gfx.ResShader

```c#
Adk.Engine.ActivePlatform.Gfx.Binarizer.FbxToResMdl()
Adk.Engine.ActivePlatform.Gfx.Binarizer.TgaToResTex()
Adk.Engine.ActivePlatform.Gfx.Binarizer.GlslToResShader(geom,vert,frag,comp)

// class Gl330 : Adk.PluginInterface.ICoreLibGfx
Ap.DevkitWin.Gl330.Binarizer.GlslToResShader(...)
```

## プラグインでできること

- BuildSystem の追加
- CoreLib の追加
- Vcs の追加
- ネイティブコード の追加
- スクリプトコード の追加
- アセットタイプ の追加
- 既存アセットタイプに独自パラメータの追加
- エディタツールバーのメニュー追加


# 用語

- ネイティブコード
    - 製品にのるコード。c++ objective-c などのコード。
- スクリプトコード
    - 製品にのるコード。エディタモード・アプリケーションモードの両方で動作するコード。限定されたC#コード。
- コマンドラインモード
    - ビルドやVcs、各アセットの変更などコマンドラインから各種操作するモード。
- エディタモード
    - エディタと通信しながらゲームを実行する実行モードの1種。
- アプリケーションモード
    - エディタと通信せずゲームを実行する実行モードの1種。

