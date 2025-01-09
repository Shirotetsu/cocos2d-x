#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GraphicsScene.h"
#include "TouchScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if (!glview) {
        glview = GLViewImpl::create("Hello World");
        glview->setFrameSize(640, 480);
        director->setOpenGLView(glview);
    }

    //auto scene = HelloWorld::createScene();
    auto graphicsScene = GraphicsScene::createScene();
    auto touchScene = TouchScene::createScene();
    director->runWithScene(touchScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}