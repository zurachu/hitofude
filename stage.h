#ifndef H_HITOFUDE_STAGE_
#define H_HITOFUDE_STAGE_

#include <piece.h>

/// リトライ判定
BOOL IsRetry();

/// 終了判定
BOOL IsEnd();

/// 画像の初期化
void InitImage();

/// ステージ初期化
void InitStage( char* data );

/// ステージ状態更新
void UpdateStage();

/// ステージ描画
void DrawStage();

#endif //  H_HITOFUDE_STAGE_

