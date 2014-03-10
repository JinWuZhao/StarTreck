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

	//����ؿ�
	cocos2d::CCNode* loadStage(const std::string& name);

	//��ȡ�ؿ�����
	bool readStageData(std::vector<StageInfo>& stageData);

private:
	//��ȡ�������ؿ��ļ�
	bool readStageConfig(const char* fileName, rapidjson::Document& parsedDoc);

	//�����ؿ�����
	bool parseStageData(rapidjson::Value& parsedDoc, std::vector<StageInfo>& data);
};

#endif