#ifndef H_ZURAPCE_APP_
#define H_ZURAPCE_APP_

/**
	@file アプリケーション関連
*/

/**
	初期化処理.
	@param period pceAppProc を呼び出す周期 (ms)
*/
void app_Init( int period );

/**
	終了時処理.
*/
void app_Exit();

#endif // H_ZURAPCE_APP_

