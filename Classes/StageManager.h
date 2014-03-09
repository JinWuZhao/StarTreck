#ifndef __STAGEMANAGER_H__
#define __STAGEMANAGER_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include <map>

class StageManager :
	public cocos2d::CCObject
{
private:
	StageManager();
public:
	virtual ~StageManager();

	static StageManager* sharedStageManager();

	//载入关卡
	bool loadStage(void);

	//根据等级随机获取一个关卡节点prefab
	cocos2d::CCNode* getPrefabWithLevel(int level);

	//清除关卡数据
	void clearStage(void);

private:
	//读取并解析关卡文件
	bool readStageConfig(const char* fileName, rapidjson::Document& parsedDoc);

	//根据解析的文档创建节点，该节点作为关卡中的prefab使用
	bool createPrefabsWithDoc(rapidjson::Value& parsedDoc);

	//保存prefab节点的map
	std::multimap<int, cocos2d::CCNode* >		m_PrefabMap;
};

#endif