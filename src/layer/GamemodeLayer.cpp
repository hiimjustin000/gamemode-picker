#include "GamemodeLayer.h"
#include <Geode/modify/GJBaseGameLayer.hpp>

using namespace geode::prelude;

class $modify(GJBaseGameLayer) {
    void update(float p0) {
        GJBaseGameLayer::update(p0);
        static_cast<PlayerObjectExt*>(this->m_player1)->updateSpeedVar();
        static_cast<PlayerObjectExt*>(this->m_player2)->updateSpeedVar();
    }
};

bool GamemodeLayer::setup(std::string const& value) {
    auto playLayer = GameManager::sharedState()->m_playLayer;
    auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);
    auto player2 = static_cast<PlayerObjectExt*>(playLayer->m_player2);

    m_title = CCLabelBMFont::create(value.c_str(), "bigFont.fnt");
    m_bgSprite->addChildAtPosition(m_title, Anchor::Top, ccp(0, -22));
    m_selectMenu = CCMenu::create();
    m_combineMenu = CCMenu::create();
    m_speedMenu = CCMenu::create();
    m_togglesMenu = CCMenu::create();
    m_mainLayer->addChildAtPosition(m_combineMenu, Anchor::Center, ccp(0, -10), false);

    auto onMode = menu_selector(GamemodeLayer::onMode);
    m_cubeBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_iconBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_iconBtn_on_001.png"), this, onMode);
    m_cubeBtn->setTag(0);
    m_shipBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_shipBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_shipBtn_on_001.png"), this, onMode);
    m_shipBtn->setTag(1);
    m_ballBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_ballBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_ballBtn_on_001.png"), this, onMode);
    m_ballBtn->setTag(2);
    m_birdBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_birdBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_birdBtn_on_001.png"), this, onMode);
    m_birdBtn->setTag(3);
    m_dartBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_dartBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_dartBtn_on_001.png"), this, onMode);
    m_dartBtn->setTag(4);
    m_robotBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_robotBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_robotBtn_on_001.png"), this, onMode);
    m_robotBtn->setTag(5);
    m_spiderBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_spiderBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_spiderBtn_on_001.png"), this, onMode);
    m_spiderBtn->setTag(6);
    m_swingBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gj_swingBtn_off_001.png"), CCSprite::createWithSpriteFrameName("gj_swingBtn_on_001.png"), this, onMode);
    m_swingBtn->setTag(7);

    m_selectMenu->addChild(m_cubeBtn);
    m_selectMenu->addChild(m_shipBtn);
    m_selectMenu->addChild(m_ballBtn);
    m_selectMenu->addChild(m_birdBtn);
    m_selectMenu->addChild(m_dartBtn);
    m_selectMenu->addChild(m_robotBtn);
    m_selectMenu->addChild(m_spiderBtn);
    m_selectMenu->addChild(m_swingBtn);
    m_selectMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(5));

    auto onSpeed = menu_selector(GamemodeLayer::onSpeed);
    m_halfBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("halfOff.png"_spr), CCSprite::createWithSpriteFrameName("halfOn.png"_spr), this, onSpeed);
    m_halfBtn->setTag(0);
    m_normalBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("normalOff.png"_spr), CCSprite::createWithSpriteFrameName("normalOn.png"_spr), this, onSpeed);
    m_normalBtn->setTag(1);
    m_doubleBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("doubleOff.png"_spr), CCSprite::createWithSpriteFrameName("doubleOn.png"_spr), this, onSpeed);
    m_doubleBtn->setTag(2);
    m_threeBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("threeOff.png"_spr), CCSprite::createWithSpriteFrameName("threeOn.png"_spr), this, onSpeed);
    m_threeBtn->setTag(3);
    m_fourBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("fourOff.png"_spr), CCSprite::createWithSpriteFrameName("fourOn.png"_spr), this, onSpeed);
    m_fourBtn->setTag(4);

    m_speedMenu->addChild(m_halfBtn);
    m_speedMenu->addChild(m_normalBtn);
    m_speedMenu->addChild(m_doubleBtn);
    m_speedMenu->addChild(m_threeBtn);
    m_speedMenu->addChild(m_fourBtn);
    m_speedMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(5));

    CCMenuItemToggler* platBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("platOff.png"_spr), CCSprite::createWithSpriteFrameName("platOn.png"_spr), this, onMode);
    platBtn->setTag(8);
    platBtn->toggle(player1->m_isPlatformer);
    CCMenuItemToggler* sizeBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("sizeOff.png"_spr), CCSprite::createWithSpriteFrameName("sizeOn.png"_spr), this, onMode);
    sizeBtn->setTag(9);
    sizeBtn->toggle(static_cast<PlayerObjectExt*>(player1)->m_fields->m_scale);
    m_flipBtn = CCMenuItemToggler::create(CCSprite::createWithSpriteFrameName("gravOff.png"_spr), CCSprite::createWithSpriteFrameName("gravOn.png"_spr), this, onSpeed);
    m_flipBtn->setTag(5);

    m_togglesMenu->addChild(platBtn);
    m_togglesMenu->addChild(sizeBtn);
    m_togglesMenu->addChild(m_flipBtn);
    m_togglesMenu->setLayout(AxisLayout::create(Axis::Row)->setGap(6));

    beginButtons(player1);
    m_combineMenu->addChild(m_togglesMenu);
    m_combineMenu->addChild(m_speedMenu);
    m_combineMenu->addChild(m_selectMenu);
    m_combineMenu->setLayout(AxisLayout::create(Axis::Column)->setGap(1));
    m_speedMenu->setScale(0.80);
    m_selectMenu->setScale(0.75);
    m_togglesMenu->setScale(0.85);

    this->setID("GamemodeLayer");
    m_combineMenu->setID("combined-menu");
    m_speedMenu->setID("speed-buttons-menu");
    m_selectMenu->setID("gamemode-buttons-menu");
    m_togglesMenu->setID("toggle-buttons-menu");
    m_title->setID("title");
    m_cubeBtn->setID("cube-button");
    m_shipBtn->setID("ship-button");
    m_ballBtn->setID("ball-button");
    m_birdBtn->setID("ufo-button");
    m_dartBtn->setID("wave-button");
    m_robotBtn->setID("robot-button");
    m_spiderBtn->setID("spider-button");
    m_swingBtn->setID("swing-button");
    m_halfBtn->setID("half-speed-button");
    m_normalBtn->setID("normal-speed-button");
    m_doubleBtn->setID("2x-speed-button");
    m_threeBtn->setID("3x-speed-button");
    m_fourBtn->setID("4x-speed-button");
    sizeBtn->setID("size-toggle-button");
    platBtn->setID("platformer-toggle-button");
    m_flipBtn->setID("gravity-toggle-button");
    m_mainLayer->setID("main-layer");
    m_buttonMenu->setID("close-button-menu");
    m_closeBtn->setID("close-button");
    m_bgSprite->setID("background");

    setTouchPriority(2);
    handleTouchPriority(this);

    return true;
}

void GamemodeLayer::updateToggleButtons() {
    m_cubeBtn->setEnabled(!m_cubeBtn->m_toggled);
    m_shipBtn->setEnabled(!m_shipBtn->m_toggled);
    m_ballBtn->setEnabled(!m_ballBtn->m_toggled);
    m_birdBtn->setEnabled(!m_birdBtn->m_toggled);
    m_dartBtn->setEnabled(!m_dartBtn->m_toggled);
    m_robotBtn->setEnabled(!m_robotBtn->m_toggled);
    m_spiderBtn->setEnabled(!m_spiderBtn->m_toggled);
    m_swingBtn->setEnabled(!m_swingBtn->m_toggled);

    m_halfBtn->setEnabled(!m_halfBtn->m_toggled);
    m_normalBtn->setEnabled(!m_normalBtn->m_toggled);
    m_doubleBtn->setEnabled(!m_doubleBtn->m_toggled);
    m_threeBtn->setEnabled(!m_threeBtn->m_toggled);
    m_fourBtn->setEnabled(!m_fourBtn->m_toggled);
}

void GamemodeLayer::onSpeed(CCObject* sender) {
    int tag = sender->getTag();
    auto playLayer = GameManager::sharedState()->m_playLayer;
    auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);
    auto player2 = static_cast<PlayerObjectExt*>(playLayer->m_player2);
    switch(tag) {
        case 0: player1->changePlayerSpeed(GJPlayerSpeed::Half); break;
        case 1: player1->changePlayerSpeed(GJPlayerSpeed::Default); break;
        case 2: player1->changePlayerSpeed(GJPlayerSpeed::Double); break;
        case 3: player1->changePlayerSpeed(GJPlayerSpeed::Three); break;
        case 4: player1->changePlayerSpeed(GJPlayerSpeed::Four); break;
        case 5: player1->flipGravity(!player1->m_fields->m_flipped, true); break;
    }
    updateButtons(player1);
    updateToggleButtons();
}

void GamemodeLayer::onMode(CCObject* sender) {
    int tag = sender->getTag();
    auto playLayer = GameManager::sharedState()->m_playLayer;
    auto player1 = static_cast<PlayerObjectExt*>(playLayer->m_player1);
    switch(tag) {
        case 0:
        player1->toggleFlyMode(false, false);
        player1->toggleRollMode(false, false);
        player1->toggleBirdMode(false, false);
        player1->toggleDartMode(false, false);
        player1->toggleRobotMode(false, false);
        player1->toggleSpiderMode(false, false);
        player1->toggleSwingMode(false, false);
        break;
        case 1: player1->toggleFlyMode(true, true); break; 
        case 2: player1->toggleRollMode(true, true); break;
        case 3: player1->toggleBirdMode(true, true); break;
        case 4: player1->toggleDartMode(true, true); break;
        case 5: player1->toggleRobotMode(true, true); break;
        case 6: player1->toggleSpiderMode(true, true); break;
        case 7: player1->toggleSwingMode(true, true); break;
        case 8: 
            player1->m_isPlatformer = !player1->m_isPlatformer;
            #ifdef GEODE_IS_ANDROID
                playLayer->m_uiLayer->togglePlatformerMode(player1->m_isPlatformer);
            #endif
            break;
        case 9: player1->togglePlayerScale(!static_cast<CCMenuItemToggler*>(sender)->m_toggled, true); break;
    }
    // log::info("player speed: {}", player1->m_playerSpeed);
    auto obj = TeleportPortalObject::create("edit_eGameRotBtn_001.png", true);
    obj->m_cameraIsFreeMode = true;
    playLayer->updateCameraMode(obj, false);
    updateButtons(player1);
    updateToggleButtons();
}

void GamemodeLayer::updateButtons(PlayerObject* player1) {

    PlayerObjectExt* playerExt1 = static_cast<PlayerObjectExt*>(player1);

    if(!player1->isInNormalMode()) m_cubeBtn->toggle(false);
    if(!player1->m_isShip) m_shipBtn->toggle(false);
    if(!player1->m_isBall) m_ballBtn->toggle(false);
    if(!player1->m_isBird) m_birdBtn->toggle(false);
    if(!player1->m_isDart) m_dartBtn->toggle(false);
    if(!player1->m_isRobot) m_robotBtn->toggle(false);
    if(!player1->m_isSpider) m_spiderBtn->toggle(false);
    if(!player1->m_isSwing) m_swingBtn->toggle(false);

    if(!playerExt1->isSpeed(GJPlayerSpeed::Half)) m_halfBtn->toggle(false);
    if(!playerExt1->isSpeed(GJPlayerSpeed::Default)) m_normalBtn->toggle(false);
    if(!playerExt1->isSpeed(GJPlayerSpeed::Double)) m_doubleBtn->toggle(false);
    if(!playerExt1->isSpeed(GJPlayerSpeed::Three)) m_threeBtn->toggle(false);
    if(!playerExt1->isSpeed(GJPlayerSpeed::Four)) m_fourBtn->toggle(false);
    if(!playerExt1->m_fields->m_flipped) m_flipBtn->toggle(false);
}

void GamemodeLayer::beginButtons(PlayerObject* player1) {

    PlayerObjectExt* playerExt1 = static_cast<PlayerObjectExt*>(player1);

    m_cubeBtn->toggle(playerExt1->isInNormalMode());
    m_shipBtn->toggle(playerExt1->m_isShip);
    m_ballBtn->toggle(playerExt1->m_isBall);
    m_birdBtn->toggle(playerExt1->m_isBird);
    m_dartBtn->toggle(playerExt1->m_isDart);
    m_robotBtn->toggle(playerExt1->m_isRobot);
    m_spiderBtn->toggle(playerExt1->m_isSpider);
    m_swingBtn->toggle(playerExt1->m_isSwing);

    m_halfBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Half));
    m_normalBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Default));
    m_doubleBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Double));
    m_threeBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Three));
    m_fourBtn->toggle(playerExt1->isSpeed(GJPlayerSpeed::Four));
    m_flipBtn->toggle(playerExt1->m_fields->m_flipped);
}

GamemodeLayer* GamemodeLayer::create(std::string const& text) {
    auto ret = new GamemodeLayer();
    if (ret && ret->initAnchored(360.f, 170.f, text, "GJ_square02.png")) {
        ret->autorelease();
        return ret;
    }
    CC_SAFE_DELETE(ret);
    return nullptr;
}
