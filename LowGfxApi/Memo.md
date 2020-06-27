# 3D  グラフィックス低レベルAPI に関するメモ

## Vulkan 

## DX12

### コマンドリストで設定する単位

★マークがあるところは他の箇所と値を一致させる必要がありそう。

- パイプラインステート
  - ルートシグネチャのポインタ（★）
  - ラスタライズステート
    - FillMode (フィル・ワイヤーフレーム)
    - 面カリング
    - 表面とみなす回転方向
    - DepthBias
    - DepthBiasClamp
    - SlopeScaledDepthBias
    - DepthClipEnable
    - MultisampleEnable
    - AntialisedLineEnable
    - ForcedSampleCount
    - ConservativeRaster 
  - ブレンドステート
  - デプスステンシルステート
  - 頂点バッファレイアウト
  - 頂点シェーダー
  - ピクセルシェーダー
  - プリミティブトポロジ
  - レンダーターゲットビューのフォーマット（★）
  - アンチエイリアス設定
- ルートシグネチャ（★）
  - シェーダーリソースビュー（テクスチャビュー）
  - コンスタントバッファビュー 
  - サンプラー
  - UAV（unordered access view）
- 直接
  - レンダーターゲット設定（★）
  - ビューポートとシザー矩形
  - プリミティブトポロジ
  - 頂点バッファ
  - インデックスバッファ

### パイプラインステートのシリアライズ

https://shobomaru.wordpress.com/2015/07/22/d3d12-pipeline-state/

ルートシグネチャへのポインタがありますけどシリアライズとは・・・？
