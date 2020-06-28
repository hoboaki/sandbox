# 3D  グラフィックス低レベルAPI に関するメモ

## Vulkan 

★マークがあるところは他の箇所と値を一致させる必要あり。

### コマンドバッファで設定する単位

- RenderPassBegin（レンダーターゲットクリアのトリガーも担う）
  - レンダーパス（★2）
    - レンダーターゲットのフォーマット（★1）
    - loadOp storeOp
  - レンダーターゲット（★1）
  - レンダーエリア
    - https://qiita.com/Pctg-x8/items/2b3d5c8a861f42aa533f
  - レンダーターゲットクリアカラー
- パイプライン（※マークがあるものは直接設定のAPIもある）
  - レンダーパス（★2）
  - シェーダー
  - 頂点バッファレイアウト
  - プリミティブトポロジ
  - ビューポート※
  - シザー矩形※
  - ラスタライズステート
    - FillMode
    - CullMode
    - FrontFace
    - DepthBias系
  - マルチサンプリングオプション
  - デプスステンシルステート
  - ブレントステート
  - ブレンド係数カラー値※
  - パイプラインレイアウト（シェーダーバインド宣言）（★3）
    - ディスクリプタセットレイアウト配列（★4）
      - コンスタントバッファビュー（ユニフォームバッファ）の宣言
      - ストレージバッファビューの宣言
      - サンプラーの宣言
    - インラインコンスタントデータの宣言（PushConstant）（★5）
- ディスプリプタセット配列（シェーダーバインド実体）（★4）
  - コンスタントバッファビュー（ユニフォームバッファ）
  - テクスチャビュー（イメージビュー）
  - ストレージバッファビュー
  - サンプラー
  - パイプラインレイアウト（★3）
- その他の直接設定
  - ビューポート（VK_DYNAMIC_STATE_VIEWPORT が有効なパイプラインの場合）
  - シザー矩形（VK_DYNAMIC_STATE_SCISSOR が有効なパイプラインの場合）
  - ステンシルテスト参照値  
  - ブレンド係数カラー値
  - プリミティブトポロジ（VK_DYNAMIC_STATE_PRIMITIVE_TOPOLOGY_EXT が有効なパイプラインの場合）
  - 頂点バッファ・インデックスバッファ
  - インラインコンスタントデータ（PushConstants）（★5）
  - 他にも DYNAMIC_STATE で指定されたものが設定可能
- トリガー
  - 描画系
  - コンピュート

## ネストコマンドバッファ

- 普通の仕様。 
- https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCmdExecuteCommands.html

## インダイレクト引数描画

- [vkCmdDrawIndexedIndirect](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/man/html/vkCmdDrawIndexedIndirect.html)

## 非同期コンピュート

- メイン Queue とは別の専用の Queue を用意することで実現。
- [優先度設定](https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/vkspec.html#devsandqueues-priority)もあり。メイン Queue より低い優先度で実行といったことも可能。0.0f〜1.0fで指定し値が大きい方が高優先。

## DirectX 12

### コマンドバッファ（コマンドリスト）で設定する単位

★マークがあるところは他の箇所と値を一致させる必要あり。

- パイプラインステート
  - ルートシグネチャのポインタ（★1）
  - ラスタライズステート
    - FillMode
    - CullMode
    - FrontFace
    - DepthBias系
  - マルチサンプリングオプション
  - デプスステンシルステート
  - ブレンドステート
  - 頂点バッファレイアウト
  - 頂点シェーダー
  - ピクセルシェーダー
  - プリミティブトポロジタイプ（点, 線, 三角形）（★3）
  - レンダーターゲットのフォーマット（★2）
- ルートシグネチャ（=シェーダーバインド宣言＆実体）（★1）
  - コンスタントバッファビュー 
  - テクスチャビュー（シェーダーリソースビュー）
  - サンプラー
  - ストレージバッファビュー（UAV:unordered access view）
- その他の直接設定
  - レンダーターゲット設定（★2）
  - ビューポート
  - シザー矩形
  - ブレンド係数カラー値
  - ステンシルテスト参照値
  - プリミティブトポロジ（★3）
  - 頂点バッファ・インデックスバッファ
- トリガー
  - レンダーターゲットのクリア
  - 描画系

**パイプラインステートのシリアライズ**

https://shobomaru.wordpress.com/2015/07/22/d3d12-pipeline-state/

ルートシグネチャへのポインタがありますけどシリアライズとは・・・？


## ネストコマンドバッファ

- 一部制約があるがだいたい普通。
- [ID3D12GraphicsCommandList::ExecuteBundle](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12graphicscommandlist-executebundle)

## インダイレクト引数描画

- [ID3D12GraphicsCommandList::ExecuteIndirect](https://docs.microsoft.com/en-us/windows/win32/api/d3d12/nf-d3d12-id3d12graphicscommandlist-executeindirect)


## 非同期コンピュート

- Vulkan と同様。
- 優先度は NORMAL と HIGH に２種類のみ。

## Metal

### コマンドバッファ（コマンドエンコーダ）で設定する単位

- レンダーパス（これを引数にコマンドエンコーダを作成・レンダーターゲットクリアのトリガーも担う）
  - レンダーターゲット
  - loadOp storeOp
  - レンダーターゲットクリアカラー
- パイプラインステート（RenderPipeline/ComputePipeline）
  - シェーダー
  - 頂点バッファレイアウト
  - レンダーターゲットのフォーマット
  - マルチサンプリングオプション
  - コンスタントバッファビューの書き込み可能属性指定（なにこれ？）
- アーギュメントバッファ（全部指定する必要なし・シェーダーバインド宣言＆実体として扱い可能）
  - コンスタントバッファビュー（MTLBuffer : MTLResource）
  - テクスチャビュー（MTLTexture : MTLResource）
  - サンプラー（MTLSamplerState）
  - インラインコンスタントデータ
- その他の直接設定
  - ラスタライズステート
    - FillMode
    - CullMode
    - FrontFace
    - DepthBias系
  - デプスステンシルステート
  - ブレントステート
  - アーギュメントバッファで指定できる各パラメータ
  - ビューポート
  - シザー矩形
  - ブレンド係数カラー値
  - ステンシルテスト参照値
  - 頂点バッファ・インデックスバッファ
- トリガー
  - 描画系（プリミティブトポロジは引数で指定）
  - コンピュート

## ネストコマンドバッファ

- 通常のコマンドバッファと区別化されている。IndirectCommandBuffer。
- IndirectCommandBuffer 内から IndirectCommandBuffer はコールできない。
- RenderCommandEncoder/ComputeCommandEncoder に生成済の IndirectCommandBuffer を挿入できる。
- IndirectCommandBuffer で扱える設定項目も限定的。デプスステンシルステートやブレンドステートなどは扱えない。他2種APIと比べると扱いづらそう。

## インダイレクト引数描画

- https://developer.apple.com/documentation/metal/mtlrendercommandencoder/specifying_drawing_and_dispatch_arguments_indirectly

## 非同期コンピュート

## 要調査

- 共通
  - 非同期コンピュート
  - 複数Queue

## 参考

- [A Comparison of Modern Graphics APIs](https://alain.xyz/blog/comparison-of-modern-graphics-apis)

