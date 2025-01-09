#pragma once

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(HelloWorld);

private:
    cocos2d::Sprite* playerRef;
    cocos2d::Sprite* ground;

    int currentScore; // Déclaration de la variable de score
    int bestScore; // Déclaration de la variable pour le meilleur score
    cocos2d::Label* scoreLabel;
    cocos2d::Label* bestScoreLabel;

    void updateScore();
    void loadBestScore();

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    bool onContactBegin(cocos2d::PhysicsContact& contact);
};
