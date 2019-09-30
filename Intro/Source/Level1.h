#ifndef Proj1_Beta_LV1_HEADER
#define Proj1_Beta_LV1_HEADER
#include <BetaObject.h>

namespace levels {
	class Level1 : public Beta::BetaObject {
	public:

		Level1();
		~Level1();


		void Load();
		void Initialize();
		void Update(float dt);
		void FixedUpdate(float dt);
		void Shutdown();
		void Unload();

	private:



	};
}

#endif