#include "StageManager.h"

USING_NS_CC;
USING_NS_CC_EXT;

static StageManager* _sharedStageManager = NULL;

StageManager::StageManager()
:CCObject()
{
}


StageManager::~StageManager()
{
}

StageManager* StageManager::sharedStageManager()
{
	if (!_sharedStageManager)
	{
		_sharedStageManager = new StageManager();
	}
	return _sharedStageManager;
}

bool StageManager::loadStage(void)
{
	bool ret = false;
	do 
	{
		rapidjson::Document stageDoc;
		CC_BREAK_IF(readStageConfig("StageDef.json", stageDoc));
		CC_BREAK_IF(createPrefabsWithDoc(stageDoc));
		ret = true;
	} while (0);

	return ret;
}

CCNode* StageManager::getPrefabWithLevel(int level)
{

	return NULL;
}

void StageManager::clearStage(void)
{
	m_PrefabMap.clear();
}

bool StageManager::readStageConfig(const char* fileName, rapidjson::Document& parsedDoc)
{
	bool ret = false;
	do 
	{
		CCFileUtils* fileUtile = CCFileUtils::sharedFileUtils();
		unsigned long fileSize = 0;
		std::string filePath = fileUtile->fullPathForFilename(fileName);
		byte* fileContent = fileUtile->getFileData(filePath.c_str(), "r", &fileSize);
		CC_BREAK_IF(fileContent == NULL || strcmp(((char*)fileContent), " ") == 0);
		std::string load_str((const char*)fileContent, fileSize);
		CC_SAFE_DELETE_ARRAY(fileContent);
		parsedDoc.Parse<0>(load_str.c_str());
		CC_BREAK_IF(parsedDoc.HasParseError());
		ret = true;
	} while (0);

	if (!ret)
	{
		CCLOG("Parse StageFile:%s failed.", fileName);
	}

	return ret;
}

bool StageManager::createPrefabsWithDoc(rapidjson::Value& parsedDoc)
{
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!DICTOOL->checkObjectExist_json(parsedDoc, "Prefabs"));
		int prefabSize = DICTOOL->getArrayCount_json(parsedDoc, "Prefabs");
		CC_BREAK_IF(prefabSize <= 0);
		int i = 0;
		do 
		{
			const rapidjson::Value& prefabDef = DICTOOL->getDictionaryFromArray_json(parsedDoc, "Prefabs", i);
			int prefabLevel = DICTOOL->getIntValue_json(prefabDef, "Level", -1);
			CC_BREAK_IF(prefabLevel < 0);
			std::string prefabName = DICTOOL->getStringValue_json(prefabDef, "Name");
			CC_BREAK_IF(prefabName.size() == 0);
			//load scenenodes
			CCNode* prefabNode = SceneReader::sharedSceneReader()->createNodeWithSceneFile(prefabName.c_str());
			CC_BREAK_IF(!prefabNode);
			m_PrefabMap.insert(std::pair<int, CCNode*>(prefabLevel, prefabNode));
			CCLOG("Create Prefab:%s successfully.", prefabName.c_str());
		} while (i < prefabSize);
		ret = true;
	} while (0);

	if (!ret)
	{
		CCLOG("Create Prefabs failed.");
		m_PrefabMap.clear();
	}

	return ret;
}
