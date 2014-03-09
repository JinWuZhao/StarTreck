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

	//����ؿ�
	bool loadStage(void);

	//���ݵȼ������ȡһ���ؿ��ڵ�prefab
	cocos2d::CCNode* getPrefabWithLevel(int level);

	//����ؿ�����
	void clearStage(void);

private:
	//��ȡ�������ؿ��ļ�
	bool readStageConfig(const char* fileName, rapidjson::Document& parsedDoc);

	//���ݽ������ĵ������ڵ㣬�ýڵ���Ϊ�ؿ��е�prefabʹ��
	bool createPrefabsWithDoc(rapidjson::Value& parsedDoc);

	//����prefab�ڵ��map
	std::multimap<int, cocos2d::CCNode* >		m_PrefabMap;
};

#endif