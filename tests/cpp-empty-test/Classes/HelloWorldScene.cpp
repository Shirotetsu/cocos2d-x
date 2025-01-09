#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    auto layer = HelloWorld::create();

    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
    if (!Layer::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    currentScore = 0;
    bestScore = UserDefault::getInstance()->getIntegerForKey("BEST_SCORE", 0);

    // Player shadow
    auto player = Sprite::create("shadow.png");
    player->setPosition(Vec2(origin.x + player->getContentSize().width / 2,
        origin.y + visibleSize.height / 2));
    auto playerBody = PhysicsBody::createBox(player->getContentSize());

    player->setScale(0.3f);
	player->setPhysicsBody(playerBody);

    playerBody->setRotationEnable(false);
    playerBody->setContactTestBitmask(true);
    //playerBody->setGravityEnable(false);

    playerRef = player;
    this->addChild(player, 1);

    // keyboard event listeners
    auto keyboardListener = EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(HelloWorld::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // Add obstacles
    this->schedule([this, origin, visibleSize](float) 
        {
        auto obstacle = Sprite::create("ring.png");
        float xPos = visibleSize.width + obstacle->getContentSize().width / 2;
        float yPos = CCRANDOM_0_1() * visibleSize.height * 0.9f + 100;

        obstacle->setPosition(Vec2(xPos, yPos));

        auto obstacleBody = PhysicsBody::createBox(obstacle->getContentSize());

        obstacleBody->setContactTestBitmask(true);
        obstacleBody->setGravityEnable(false);

        obstacle->setPhysicsBody(obstacleBody);
        obstacle->setScale(0.1f);

        this->addChild(obstacle);

        auto moveAction = MoveBy::create(3.0f, Vec2(-visibleSize.width - obstacle->getContentSize().width, 0));
        obstacle->runAction(moveAction);

        obstacle->setTag(1);
        }, 1.0f, "add_obstacle_key");

    // ground
    ground = Sprite::create("ground.png");
    ground->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y - 50));
    auto groundBody = PhysicsBody::createBox(ground->getContentSize());
    groundBody->setDynamic(false);
    groundBody->setContactTestBitmask(true);
    ground->setPhysicsBody(groundBody);
    ground->setTag(2);
    this->addChild(ground, 1);


    // collision detection
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

    // Scores
    scoreLabel = Label::createWithTTF("Score: 0", "fonts/Marker Felt.ttf", 24);
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width - scoreLabel->getContentSize().width,
        origin.y + visibleSize.height - scoreLabel->getContentSize().height));
    this->addChild(scoreLabel, 1);

    bestScoreLabel = Label::createWithTTF("Best Score:" + std::to_string(bestScore), "fonts/Marker Felt.ttf", 24);
    bestScoreLabel->setPosition(Vec2(origin.x + visibleSize.width - bestScoreLabel->getContentSize().width,
        origin.y + visibleSize.height - bestScoreLabel->getContentSize().height - 50));
    this->addChild(bestScoreLabel, 1);

    return true;
}
void HelloWorld::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
    Vec2 currentPos = playerRef->getPosition();
    float moveAmount = 100.0f; // Adjust the movement amount as needed
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    switch (keyCode) {
    case EventKeyboard::KeyCode::KEY_W:
        if (currentPos.y + moveAmount < visibleSize.height)
        {
            playerRef->setPosition(currentPos.x, currentPos.y + moveAmount);
        }
        break;
    case EventKeyboard::KeyCode::KEY_S:
        if (currentPos.y - moveAmount > origin.y)
        {
            playerRef->setPosition(currentPos.x, currentPos.y - moveAmount);
        }
        break;
    case EventKeyboard::KeyCode::KEY_A:
        if (currentPos.x - moveAmount > origin.x) 
        {
            playerRef->setPosition(currentPos.x - moveAmount, currentPos.y);
        }
        break;
    case EventKeyboard::KeyCode::KEY_D:
        if (currentPos.x + moveAmount < visibleSize.width) 
        {
            playerRef->setPosition(currentPos.x + moveAmount, currentPos.y);
        }
        break;
    default:
        break;
    }
}

bool HelloWorld::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();

    if ((nodeA == playerRef && nodeB->getTag() == 1) || (nodeB == playerRef && nodeA->getTag() == 1)) 
    {
        updateScore();

        // Handle collision: destroy the obstacle
        if (nodeA->getTag() == 1) 
        {
            nodeA->removeFromParentAndCleanup(true);
        }
        else if (nodeB->getTag() == 1) 
        {
            nodeB->removeFromParentAndCleanup(true);
        }
    }
    return true;
}

void HelloWorld::updateScore()
{
    currentScore++;
    scoreLabel->setString("Score: " + std::to_string(currentScore));

    if (currentScore > bestScore)
    {
        bestScore = currentScore;
        UserDefault::getInstance()->setIntegerForKey("BEST_SCORE", bestScore);
        UserDefault::getInstance()->flush();
    }
}

void HelloWorld::loadBestScore()
{
    bestScore = UserDefault::getInstance()->getIntegerForKey("BEST_SCORE", 0);
}