#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1D_05_宇田川滉太_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	typedef struct Vector2 {
		float x;
		float y;
	};
	struct MUSI {
		Vector2 pos;
		Vector2 speed;
		float radius;
		unsigned int color;
	};
	struct SCORP {
		Vector2 pos;
		float radius;
		unsigned int color;
	};
	struct TATAKI {
		Vector2 pos;
		float radius;
		unsigned int color;
	};

	//虫始まり↓
	MUSI musi[4] = {
		{1216.0f,360.0f,
		 -3.0f,0.0f,
		64,BLUE },

		{640.0f,0.0f,
		 0.0f,2.0f,
		64,WHITE },

		{0.0f,360.0f,
		 -6.0f,0.0f,
		64,GREEN },

		{640.0f,656.0f,
		 0.0f,1.0f,
		64,RED },
	};

	//虫終わり↑

	//判定↓
	SCORP scorp = {
		{640.0f,360.0f},
		64,WHITE
	};
	TATAKI tataki = {
		{640.0f,360.0f},
		64,WHITE
	};
	int isPlayerAlive = true;


	int isTataki = false;
	int HaeTataki = Novice::LoadTexture("./tataki.png");
	int TarGet = Novice::LoadTexture("./target.png");
	int Gokiburi = Novice::LoadTexture("./gokiburi.png");
	int Spider = Novice::LoadTexture("./kumo.png");

	//判定↑

	//敵の復活↓
	int RespawnTimer = 60;
	int RespawnTimer1 = 60;
	int RespawnTimer2 = 60;
	int RespawnTimer3 = 60;
	//敵の復活↑



	//敵が生きているか死んでいるか↓
	int isEnemyAlive = true;
	int isEnemyAlive1 = true;
	int isEnemyAlive2 = true;
	int isEnemyAlive3 = true;
	//敵が生きているか死んでいるか↑



	//倒したら別の敵が登場↓
	/*Vector2 Musi{
		1000,360
	};*/
	int musiDeathCount = 0;
	int musiDeathCount1 = 0;
	int musiDeathCount2 = 0;
	int musiDeathCount3 = 0;
	//倒したら別の敵が登場↑



	//爆発↓
	int explosion = Novice::LoadTexture("./Explosion.png");
	//爆発↑


	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///



		//上下左右に動かす↓
		if (isEnemyAlive)
		{
			//右
			musi[0].pos.x += musi[0].speed.x;
			musi[0].pos.y += musi[0].speed.y;
		}

		if (isEnemyAlive1)
		{
			//下
			musi[1].pos.y += musi[1].speed.y;
			musi[1].pos.x += musi[1].speed.x;
		}

		if (isEnemyAlive2)
		{
			//左
			musi[2].pos.x -= musi[2].speed.x;
			musi[2].pos.y += musi[2].speed.y;
		}

		if (isEnemyAlive3)
		{
			//上
			musi[3].pos.y -= musi[3].speed.y;
			musi[3].pos.x += musi[3].speed.x;
		}
		//上下左右に動かす↑



		//衝突判定 虫↓
		int e2bX = musi[0].pos.x - scorp.pos.x;
		int e2bY = musi[0].pos.y - scorp.pos.y;
		int e2bR = musi[0].radius + scorp.radius;

		int e2bX1 = musi[1].pos.x - scorp.pos.x;
		int e2bY1 = musi[1].pos.y - scorp.pos.y;
		int e2bR1 = musi[1].radius + scorp.radius;

		int e2bX2 = musi[2].pos.x - scorp.pos.x;
		int e2bY2 = musi[2].pos.y - scorp.pos.y;
		int e2bR2 = musi[2].radius + scorp.radius;

		int e2bX3 = musi[3].pos.x - scorp.pos.x;
		int e2bY3 = musi[3].pos.y - scorp.pos.y;
		int e2bR3 = musi[3].radius + scorp.radius;
		//衝突判定 虫↑



		//衝突判定 自機↓
		int PosbX = tataki.pos.x - musi[0].pos.x;
		int PosbY = tataki.pos.y - musi[0].pos.y;
		int PosbR = tataki.radius + musi[0].radius;

		int PosbX1 = tataki.pos.x - musi[1].pos.x;
		int PosbY1 = tataki.pos.y - musi[1].pos.y;
		int PosbR1 = tataki.radius + musi[1].radius;

		int PosbX2 = tataki.pos.x - musi[2].pos.x;
		int PosbY2 = tataki.pos.y - musi[2].pos.y;
		int PosbR2 = tataki.radius + musi[2].radius;

		int PosbX3 = tataki.pos.x - musi[3].pos.x;
		int PosbY3 = tataki.pos.y - musi[3].pos.y;
		int PosbR3 = tataki.radius + musi[3].radius;
		//衝突判定 自機↑

		// ハエたたきの移動処理
		/*if (keys[DIK_W]) {
			scorp.pos.y -= 3.0f;
			tataki.pos.y -= 3.0f;
		}
		if (keys[DIK_A]) {
			scorp.pos.x -= 3.0f;
			tataki.pos.x -= 3.0f;
		}
		if (keys[DIK_S]) {
			scorp.pos.y += 3.0f;
			tataki.pos.y += 3.0f;
		}
		if (keys[DIK_D]) {
			scorp.pos.x += 3.0f;
			tataki.pos.x += 3.0f;
		}*/



		//アタック↓
		if (!keys[DIK_SPACE] && preKeys[DIK_SPACE])
		{
			////自機と敵が接触↓
			//if (PosbR * PosbR >= PosbX * PosbX + PosbY * PosbY)
			//{
			//	isPlayerAlive = true;
			//}
			//if (PosbR1 * PosbR1 >= PosbX1 * PosbX1 + PosbY1 * PosbY1)
			//{
			//	isPlayerAlive = true;
			//}
			//if (PosbR2 * PosbR2 >= PosbX2 * PosbX2 + PosbY2 * PosbY2)
			//{
			//	isPlayerAlive = true;
			//}
			//if (PosbR3 * PosbR3 >= PosbX3 * PosbX3 + PosbY3 * PosbY3)
			//{
			//	isPlayerAlive = true;
			//}
			////自機と敵が接触↑


			isTataki = true;

			if (isTataki)
			{
				Novice::DrawSprite(tataki.pos.x - 360 / 2, tataki.pos.y - 410 / 2, HaeTataki, 1.0f, 1.0f, 0.0f, WHITE);
			}


			//もし自機と敵が接していたら、交わっていたら↓
			if (e2bR * e2bR >= e2bX * e2bX + e2bY * e2bY)
			{
				isEnemyAlive = false;
			}

			if (e2bR1 * e2bR1 >= e2bX1 * e2bX1 + e2bY1 * e2bY1)
			{
				isEnemyAlive1 = false;
			}

			if (e2bR2 * e2bR2 >= e2bX2 * e2bX2 + e2bY2 * e2bY2)
			{
				isEnemyAlive2 = false;
			}

			if (e2bR3 * e2bR3 >= e2bX3 * e2bX3 + e2bY3 * e2bY3)
			{
				isEnemyAlive3 = false;
			}
			//もし自機と敵が接していたら、交わっていたら↑


			//アタック↑
		}
		//もし、敵が死んでいたら↓
		if (isEnemyAlive == false)
		{
			RespawnTimer--;
		}

		if (isEnemyAlive1 == false)
		{
			RespawnTimer1--;
		}

		if (isEnemyAlive2 == false)
		{
			RespawnTimer2--;
		}

		if (isEnemyAlive3 == false)
		{
			RespawnTimer3--;
		}
		//もし、敵が死んでいたら↑


		//別の敵を出す↓
		if (RespawnTimer <= 0)
		{
			++musiDeathCount;
			RespawnTimer = 60;
			isEnemyAlive = true;
		}

		if (RespawnTimer1 <= 0)
		{
			++musiDeathCount1;
			RespawnTimer1 = 60;
			isEnemyAlive1 = true;
		}

		if (RespawnTimer2 <= 0)
		{
			++musiDeathCount2;
			RespawnTimer2 = 60;
			isEnemyAlive2 = true;
		}

		if (RespawnTimer3 <= 0)
		{
			++musiDeathCount3;
			RespawnTimer3 = 60;
			isEnemyAlive3 = true;
		}
		//別の敵を出す↑


		if (!isEnemyAlive)
		{
			if (RespawnTimer <= 9) {
				if (musiDeathCount % 2 == 0)
				{
					musi[0].pos.x = 1216;
					musi[0].pos.y = 360;
					musi[0].speed.x = -3.0f;
				}
				if (musiDeathCount % 2 == 1)
				{
					musi[0].pos.x = 0;
					musi[0].pos.y = 360;
					musi[0].speed.x = 9.0f;
				}
				/*if (musiDeathCount % 3 == 2)
				{
					musi[0].pos.x = musi[0].radius;
					musi[0].pos.y = musi[0].radius;
					musi[0].speed.x = 3.0f;
					musi[0].speed.y = 3.0f;
				}*/
			}
		}
		/// % 2 == 0の時は宣言時のスピード、% 2 == 1なら符号を変える


		if (!isEnemyAlive1)
		{
			if (RespawnTimer1 <= 9){
				if (musiDeathCount1 % 2 == 0)
				{
					musi[1].pos.x = 640;
					musi[1].pos.y = 0;
					musi[1].speed.y = 2.0f;
				}
				if (musiDeathCount1 % 2 == 1)
				{
					musi[1].pos.x = 640;
					musi[1].pos.y = 700;
					musi[1].speed.y = -10.0f;
				}
			}
		}

		if (!isEnemyAlive2)
		{
			if (RespawnTimer2 <= 9) {
				if (musiDeathCount2 % 2 == 0)
				{
					musi[2].pos.x = 0;
					musi[2].pos.y = 360;
					musi[2].speed.x = -6.0f;
				}
				if (musiDeathCount2 % 2 == 1)
				{
					musi[2].pos.x = 0;
					musi[2].pos.y = 360;
					musi[2].speed.x = -9.0f;
				}
			}
		}

		if (!isEnemyAlive3)
		{
			if (RespawnTimer3 <= 9) {

				if (musiDeathCount3 % 2 == 0)
				{
					musi[3].pos.x = 640;
					musi[3].pos.y = 656;
					musi[3].speed.y = 1.0f;
				}
				if (musiDeathCount3 % 2 == 1)
				{
					musi[3].pos.x = 0;
					musi[3].pos.y = 640;
					musi[3].speed.y = 8.0f;
				}
			}
		}



		if (musi[0].pos.x + musi[0].radius <= 0)
		{
			musi[0].pos.x = 1280;
		}
		if (musi[0].pos.x - musi[0].radius >= 1281)
		{
			musi[0].pos.x = 0;
		}

		if (musi[1].pos.y + musi[1].radius <= 0)
		{
			musi[1].pos.y = 720;
		}
		if (musi[1].pos.y - musi[1].radius >= 721)
		{
			musi[1].pos.y = 0;
		}

		if (musi[2].pos.x + musi[2].radius <= 0)
		{
			musi[2].pos.x = 1280;
		}
		if (musi[2].pos.x - musi[2].radius >= 1281)
		{
			musi[2].pos.x = 0;
		}

		if (musi[3].pos.y + musi[3].radius <= 0)
		{
			musi[3].pos.y = 1280;
		}
		if (musi[3].pos.y - musi[3].radius >= 1281)
		{
			musi[3].pos.y = 0;
		}





		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (isEnemyAlive == true)
		{
			Novice::DrawBox(musi[0].pos.x - 64 / 2, musi[0].pos.y - 64 / 2, musi[0].radius, musi[0].radius, 0.0f, BLUE, kFillModeSolid);
		}
		if (isEnemyAlive1 == true)
		{
			Novice::DrawBox(musi[1].pos.x - 64 / 2, musi[1].pos.y - 64 / 2, musi[1].radius, musi[1].radius, 0.0f, WHITE, kFillModeSolid);
		}
		if (isEnemyAlive2 == true)
		{
			Novice::DrawBox(musi[2].pos.x - 64 / 2, musi[2].pos.y - 64 / 2, musi[2].radius, musi[2].radius, 0.0f, GREEN, kFillModeSolid);
		}
		if (isEnemyAlive3 == true)
		{
			Novice::DrawBox(musi[3].pos.x - 64 / 2, musi[3].pos.y - 64 / 2, musi[3].radius, musi[3].radius, 0.0f, RED, kFillModeSolid);
		}


		//虫爆発↓
		if (isEnemyAlive == false)
		{
			if (RespawnTimer >= 10)
			{
				Novice::DrawSprite(musi[0].pos.x - 90 / 2, musi[0].pos.y - 90 / 2, explosion, 1, 1, 0.0f, BLUE);
			}
		}

		if (isEnemyAlive1 == false)
		{
			if (RespawnTimer1 >= 10)
			{
				Novice::DrawSprite(musi[1].pos.x - 90 / 2, musi[1].pos.y - 90 / 2, explosion, 1, 1, 0.0f, WHITE);
			}
		}

		if (isEnemyAlive2 == false)
		{
			if (RespawnTimer2 >= 10)
			{
				Novice::DrawSprite(musi[2].pos.x - 90 / 2, musi[2].pos.y - 90 / 2, explosion, 1, 1, 0.0f, GREEN);
			}
		}

		if (isEnemyAlive3 == false)
		{
			if (RespawnTimer3 >= 10)
			{
				Novice::DrawSprite(musi[3].pos.x - 90 / 2, musi[3].pos.y - 90 / 2, explosion, 1, 1, 0.0f, RED);
			}
		}
		//虫爆発↑


		//スコープ
		Novice::DrawSprite(scorp.pos.x - 120 / 2, scorp.pos.y - 120 / 2, TarGet, 1.0f, 1.0f, 0.0f, WHITE);

		Novice::ScreenPrintf(0, 100, "%d", musiDeathCount);




		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
