#include "StarterBot.h"
#include "Tools.h"
#include "iostream"

StarterBot::StarterBot()
{
    
}

// Called when the bot starts!
void StarterBot::onStart()
{
    // Set our BWAPI options here    
	BWAPI::Broodwar->setLocalSpeed(10);
    BWAPI::Broodwar->setFrameSkip(0);
    
    // Enable the flag that tells BWAPI top let users enter input while bot plays
    BWAPI::Broodwar->enableFlag(BWAPI::Flag::UserInput);

    // Call MapTools OnStart
    m_mapTools.onStart();
    m_bases.addBase(Tools::GetUnitOfType(BWAPI::UnitTypes::Protoss_Nexus));
    m_bases.assignWorkers();


    m_army.setup(&m_bases);

    Grid<int> grid = m_mapTools.computeDistanceMap(BWAPI::Broodwar->self()->getStartLocation());
}

// Called whenever the game ends and tells you if you won or not
void StarterBot::onEnd(bool isWinner) 
{
    std::cout << "We " << (isWinner ? "won!" : "lost!") << "\n";
}

// Called on each frame of the game
void StarterBot::onFrame()
{
    // Update our MapTools information
    m_mapTools.onFrame();
    m_bases.onFrame();
    m_army.onFrame();

    // Build more supply if we are going to run out soon
    buildAdditionalSupply();

    // Send our scout out 
    manageScout();

    // Draw unit health bars, which brood war unfortunately does not do
    Tools::DrawUnitHealthBars();

    // Draw some relevent information to the screen to help us debug the bot
    drawDebugInformation();
}

void StarterBot::manageScout()
{
    if (m_scout.isAlive())
    {
        m_scout.onFrame();
    }
}

// Build more supply if we are going to run out soon
void StarterBot::buildAdditionalSupply()
{
    // Get the amount of supply supply we currently have unused
    const int unusedSupply = Tools::GetTotalSupply(true) - BWAPI::Broodwar->self()->supplyUsed();

    // If we have a sufficient amount of supply, we don't need to do anything
    if (unusedSupply >= 4) { return; }

    // Otherwise, we are going to build a supply provider
    bool startedBuilding = m_bases.getMain().buildStructure(BWAPI::UnitTypes::Protoss_Pylon);
    if (startedBuilding)
    {
        BWAPI::Unitset set;
        auto sc = m_bases.getMain().getWorker();
        set.insert(sc);
        m_bases.getMain().removeWorker(sc);
        m_scout.set(set, BWAPI::Broodwar->getStartLocations());
    }
}

// Draw some relevent information to the screen to help us debug the bot
void StarterBot::drawDebugInformation()
{
    //BWAPI::Broodwar->drawTextScreen(BWAPI::Position(10, 10), "Hello, World!\n");
    Tools::DrawUnitCommands();
    Tools::DrawUnitBoundingBoxes();
}

// Called whenever a unit is destroyed, with a pointer to the unit
void StarterBot::onUnitDestroy(BWAPI::Unit unit)
{
    if (unit->getPlayer() == BWAPI::Broodwar->enemy())
    {
        m_army.removeEnemy(unit);
    }
    else if (unit->getPlayer() == BWAPI::Broodwar->self())
    {
        m_army.remove(unit);
    }
}

// Called whenever a unit is morphed, with a pointer to the unit
// Zerg units morph when they turn into other units
void StarterBot::onUnitMorph(BWAPI::Unit unit)
{
	
}

// Called whenever a text is sent to the game by a user
void StarterBot::onSendText(std::string text) 
{ 
    if (text == "/map")
    {
        m_mapTools.toggleDraw();
    }
    //if (text == "/distance")
    //{
    //    m_mapTools.toggleDistanceMap();
    //}
}

// Called whenever a unit is created, with a pointer to the destroyed unit
// Units are created in buildings like barracks before they are visible, 
// so this will trigger when you issue the build command for most units
void StarterBot::onUnitCreate(BWAPI::Unit unit)
{ 
    m_army.built(unit->getType());

    if (unit->getType() == BWAPI::UnitTypes::Protoss_Pylon && !m_scout.isAlive())
    {
        m_scout.start();
    }
    else if (unit->getType() == WorkerType)
    {
        m_bases.assignWorker(unit);
       
    }
    
}

// Called whenever a unit finished construction, with a pointer to the unit
void StarterBot::onUnitComplete(BWAPI::Unit unit)
{
    if (unit->getPlayer() == BWAPI::Broodwar->self())
    {
        BWAPI::Broodwar->printf("Unit Completed");
        m_army.add(unit);
    }
}

// Called whenever a unit appears, with a pointer to the destroyed unit
// This is usually triggered when units appear from fog of war and become visible
void StarterBot::onUnitShow(BWAPI::Unit unit)
{ 
    if (unit->getPlayer() == BWAPI::Broodwar->enemy())
    {
        BWAPI::Broodwar->printf("Enemy Spotted");
        m_army.addEnemy(unit);

        if (unit->getType().isBuilding())
        {
            if (!m_scout.isEnemyFound())
            {
                m_scout.enemyFound();
                
            }

            m_scout.addTargets(unit->getTilePosition());
            m_scout.addTargetTypes(unit->getType());
        }
    }
}

// Called whenever a unit gets hidden, with a pointer to the destroyed unit
// This is usually triggered when units enter the fog of war and are no longer visible
void StarterBot::onUnitHide(BWAPI::Unit unit)
{ 
    if (unit->getPlayer() == BWAPI::Broodwar->enemy())
    {
        //m_opponent.remove(unit);
    }
}

// Called whenever a unit switches player control
// This usually happens when a dark archon takes control of a unit
void StarterBot::onUnitRenegade(BWAPI::Unit unit)
{ 
	
}