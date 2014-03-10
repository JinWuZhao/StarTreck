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

cocos2d::CCNode* StageManager::loadStage(const std::string& name)
{
	CCNode* ret = NULL;
	ret = SceneReader::sharedSceneReader()->createNodeWithSceneFile(name.c_str());
	if (!ret)
	{
		CCLOG("Failed to create scene:%s.", name.c_str());
	}
	return ret;
}

bool StageManager::readStageData(std::vector<StageInfo>& stageData)
{
	bool ret = false;
	do
	{
		rapidjson::Document stageDoc;
		CC_BREAK_IF(!readStageConfig("StageDef.json", stageDoc));
		CC_BREAK_IF(!parseStageData(stageDoc, stageData));
		ret = true;
	} while (0);

	return ret;
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

bool StageManager::parseStageData(rapidjson::Value& parsedDoc, std::vector<StageInfo>& data)
{
	data.clear();
	bool ret = false;
	do 
	{
		CC_BREAK_IF(!DICTOOL->checkObjectExist_json(parsedDoc, "Stages"));
		int stageNum = DICTOOL->getArrayCount_json(parsedDoc, "Stages");
		CC_BREAK_IF(stageNum <= 0);
		int i = 0;
		do 
		{
			const rapidjson::Value& stageDict = DICTOOL->getDictionaryFromArray_json(parsedDoc, "Stages", i);
			int level = DICTOOL->getIntValue_json(stageDict, "Level", -1);
			CC_BREAK_IF(level < 0);
			std::string name = DICTOOL->getStringValue_json(stageDict, "Name");
			CC_BREAK_IF(name.size() == 0);
			StageInfo info;
			info.level = level;
			info.name = name;
			data.push_back(info);
			CCLOG("Parse Stage:%s successfully.", name.c_str());
			i++;
		} while (i < stageNum);
		CC_BREAK_IF(i < stageNum);
		ret = true;
	} while (0);

	if (!ret)
	{
		CCLOG("Failed to parse stage data.");
		data.clear();
	}

	return ret;
}
