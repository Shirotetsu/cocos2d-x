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
        glview->setFrameSize(960, 720);
        director->setOpenGLView(glview);
    }

    auto helloWorld = HelloWorld::createScene();
    auto graphicsScene = GraphicsScene::createScene();
    auto touchScene = TouchScene::createScene();

    director->runWithScene(helloWorld);

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
}

void AppDelegate::applicationWillEnterForeground() {
}