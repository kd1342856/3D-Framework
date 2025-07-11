#pragma once
#include "Framework/Direct3D/KdTexture.h"

namespace EngineCore {

	class Engine {
	public:
		static Engine& Instance() 
		{
			static Engine instance;
			return instance;
		}

		bool Init();         // 初期化
		void Shutdown();     // 終了処理
		void Update();       // 毎フレーム更新
		void Draw();         // 毎フレーム描画
		void Release();

		std::shared_ptr<KdTexture> m_gameViewRT;
	private:
		Engine(){}
		~Engine() { Release(); }
	};
}
