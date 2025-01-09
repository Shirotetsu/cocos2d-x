#include "GraphicsScene.h"

USING_NS_CC;

Scene* GraphicsScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GraphicsScene::create();
    scene->addChild(layer);

    return scene;
}

bool GraphicsScene::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto sonicSprite = Sprite::create("shadow.png");
    auto shadowSprite = Sprite::create("shadow.png");
    shadowSprite->setAnchorPoint(Vec2(0, 0));
    sonicSprite->setAnchorPoint(Vec2(0, 0));

    sonicSprite->addChild(shadowSprite);

	//sonicSprite->setAnchorPoint(Vec2(0.5, 0.5)); // middle of the sonicSprite pos
    shadowSprite->setPosition(100, 100);
    sonicSprite->setPosition(0, 0);

    this->addChild(sonicSprite, 0);

    return true;
}