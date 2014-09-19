#ifndef SCENES_H
#define SCENES_H

// Enumeration of scenes, giving name for each scene number
enum SceneName
{
	DEFAULT = UTHDefaultScene,
	GAME,
	COUNT // Keep this last, it tells how many scenes there are
};

#endif //SCENES_H

#ifdef NEWSCENEFUNC
#undef NEWSCENEFUNC

#include "BattleScene.h"

// Create function for a new scene, having a case for every user made scene
uth::Scene* NewSceneFunc(int SceneID)
{
	switch (SceneID)
	{
	case GAME:		return new /*Game*/BattleScene();
	default:		return nullptr;
	}
}

#endif // NEWSCENEFUNC