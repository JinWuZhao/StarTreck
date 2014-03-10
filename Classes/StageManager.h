#ifndef __STAGEMANAGER_H__
#define __STAGEMANAGER_H__

#include "cocos2d.h"
#include "cocos-ext.h"

struct StageInfo
{
	int level;
	std::string name;
};

class StageManager :
	public cocos2d::CCObject
{
private:
	StageManager();
public:
	virtual ~StageManager();

	static StageManager* sharedStageManager();

	//载入关卡
	cocos2d::CCNode* loadStage(const std::string& name);

	//读取关卡数据
	bool readStageData(std::vector<StageInfo>& stageData);

private:
	//读取并解析关卡文件
	bool readStageConfig(const char* fileName, rapidjson::Document& parsedDoc);

	//分析关卡数据
	bool parseStageData(rapidjson::Value& parsedDoc, std::vector<StageInfo>& data);
};

#endif