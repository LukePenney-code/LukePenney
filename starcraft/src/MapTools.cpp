#include "MapTools.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <array>
#include <map>

// constructor for MapTools
MapTools::MapTools()
{
    
}

void MapTools::onStart()
{
    m_width          = BWAPI::Broodwar->mapWidth();
    m_height         = BWAPI::Broodwar->mapHeight();
    m_walkable       = Grid<int>(m_width, m_height, 1);
    m_buildable      = Grid<int>(m_width, m_height, 0);
    m_depotBuildable = Grid<int>(m_width, m_height, 0);
    m_lastSeen       = Grid<int>(m_width, m_height, 0);

    // Set the boolean grid data from the Map
    for (int x(0); x < m_width; ++x)
    {
        for (int y(0); y < m_height; ++y)
        {
            m_buildable.set(x, y, canBuild(x, y));
            m_depotBuildable.set(x, y, canBuild(x, y));
            m_walkable.set(x, y, m_buildable.get(x,y) || canWalk(x, y));
        }
    }

    // set tiles that static resources are on as unbuildable
    for (auto & resource : BWAPI::Broodwar->getStaticNeutralUnits())
    {
        if (!resource->getType().isResourceContainer())
        {
            continue;
        }

        const int tileX = resource->getTilePosition().x;
        const int tileY = resource->getTilePosition().y;

        for (int x=tileX; x<tileX+resource->getType().tileWidth(); ++x)
        {
            for (int y=tileY; y<tileY+resource->getType().tileHeight(); ++y)
            {
                m_buildable.set(x, y, false);

                // depots can't be built within 3 tiles of any resource
                for (int rx=-3; rx<=3; rx++)
                {
                    for (int ry=-3; ry<=3; ry++)
                    {
                        if (!BWAPI::TilePosition(x+rx, y+ry).isValid())
                        {
                            continue;
                        }

                        m_depotBuildable.set(x+rx, y+ry, 0);
                    }
                }
            }
        }
    }
}

void MapTools::onFrame()
{
    for (int x=0; x<m_width; ++x)
    {
        for (int y=0; y<m_height; ++y)
        {
            if (isVisible(x, y))
            {
                m_lastSeen.set(x, y, BWAPI::Broodwar->getFrameCount());
            }
        }
    }

    if (m_drawMap)
    {
        draw();
    }
}

void MapTools::toggleDraw()
{
    m_drawMap = !m_drawMap;
}


bool MapTools::isExplored(const BWAPI::TilePosition & pos) const
{
    return isExplored(pos.x, pos.y);
}

bool MapTools::isExplored(const BWAPI::Position & pos) const
{
    return isExplored(BWAPI::TilePosition(pos));
}

bool MapTools::isExplored(int tileX, int tileY) const
{
    if (!isValidTile(tileX, tileY)) { return false; }

    return BWAPI::Broodwar->isExplored(tileX, tileY);
}

bool MapTools::isVisible(int tileX, int tileY) const
{
    if (!isValidTile(tileX, tileY)) { return false; }

    return BWAPI::Broodwar->isVisible(BWAPI::TilePosition(tileX, tileY));
}

bool MapTools::isPowered(int tileX, int tileY) const
{
    return BWAPI::Broodwar->hasPower(BWAPI::TilePosition(tileX, tileY));
}

bool MapTools::isValidTile(int tileX, int tileY) const
{
    return tileX >= 0 && tileY >= 0 && tileX < m_width && tileY < m_height;
}

bool MapTools::isValidTile(const BWAPI::TilePosition & tile) const
{
    return isValidTile(tile.x, tile.y);
}

bool MapTools::isValidPosition(const BWAPI::Position & pos) const
{
    return isValidTile(BWAPI::TilePosition(pos));
}

bool MapTools::isBuildable(int tileX, int tileY) const
{
    if (!isValidTile(tileX, tileY))
    {
        return false;
    }

    return m_buildable.get(tileX, tileY);
}

bool MapTools::isBuildable(const BWAPI::TilePosition & tile) const
{
    return isBuildable(tile.x, tile.y);
}

void MapTools::printMap() const
{
    std::stringstream ss;
    for (int y(0); y < m_height; ++y)
    {
        for (int x(0); x < m_width; ++x)
        {
            ss << isWalkable(x, y);
        }

        ss << "\n";
    }

    std::ofstream out("map.txt");
    out << ss.str();
    out.close();
}

BWAPI::TilePosition MapTools::getNatural()
{
    for (BWAPI::Unit u : BWAPI::Broodwar->getMinerals())
    {
        if (!u->isBeingGathered() && u->getTilePosition().isValid())
        {
            return u->getTilePosition();
        }
    }
}

bool MapTools::isDepotBuildableTile(int tileX, int tileY) const
{
    if (!isValidTile(tileX, tileY))
    {
        return false;
    }

    return m_depotBuildable.get(tileX, tileY);
}

bool MapTools::isWalkable(int tileX, int tileY) const
{
    if (!isValidTile(tileX, tileY))
    {
        return false;
    }

    return m_walkable.get(tileX, tileY);
}

int MapTools::distanceMapIndex(BWAPI::TilePosition tile, Grid<int> distanceMap)
{
    return distanceMap.get(tile.x, tile.y);

}

bool MapTools::isWalkable(const BWAPI::TilePosition & tile) const
{
    return isWalkable(tile.x, tile.y);
}
Grid<int> MapTools::computeDistanceMap(const BWAPI::TilePosition& startTile)
{
    // Closed List
    std::vector<BWAPI::TilePosition> closed;
    closed.reserve(BWAPI::Broodwar->mapWidth() * BWAPI::Broodwar->mapHeight());

    // The 4 dimensional legal actions to be used by our BFS
    const size_t cardinal_actions = 4;
    const int x_actions[cardinal_actions] = { 1, -1, 0, 0 };
    const int y_actions[cardinal_actions] = { 0, 0, 1, -1 };

    Grid<int> distance = Grid<int>(BWAPI::Broodwar->mapWidth(), BWAPI::Broodwar->mapHeight(), -1);

    // Creating open list
    std::vector<BWAPI::TilePosition> open;
    open.reserve(BWAPI::Broodwar->mapWidth() * BWAPI::Broodwar->mapHeight());


    // Checking if the start tile is valid 
    if (isValidTile(startTile))
    {
        // Pushing the start tile into the open and closed lists
        open.push_back(startTile);
        closed.push_back(startTile);

        // Setting start tile to a distance of 0
        distance.set(startTile.x, startTile.y, 0);

        // Breadth First searching throughout the map and computing each
        // tile positions distance from the start tile
        for (size_t openIndex = 0; openIndex < open.size(); openIndex++)
        {
            const auto& tile = open[openIndex];

            // check every possible child of this tile
            for (size_t a = 0; a < cardinal_actions; a++)
            {
                const BWAPI::TilePosition nextTile(tile.x + x_actions[a], tile.y + y_actions[a]);

                // if the new tile is inside the map bounds, is walkable, and has not been visited yet, set the distance of its parent + 1
                if (isWalkable(nextTile) && distance.get(nextTile.x, nextTile.y) == -1)
                {
                    distance.set(nextTile.x, nextTile.y, distance.get(tile.x, tile.y) + 1);
                    open.push_back(nextTile);
                    closed.push_back(nextTile);
                }
            }
        }
        return distance;

    }
    else {
        return Grid<int>();
        std::cout << "Invalid Starting Tile" << std::endl;
    }
}




int MapTools::width() const
{
    return m_width;
}

int MapTools::height() const
{
    return m_height;
}


void MapTools::drawTile(int tileX, int tileY, const BWAPI::Color & color) const
{
    const int padding   = 2;
    const int px        = tileX*32 + padding;
    const int py        = tileY*32 + padding;
    const int d         = 32 - 2*padding;

    BWAPI::Broodwar->drawLineMap(px,     py,     px + d, py,     color);
    BWAPI::Broodwar->drawLineMap(px + d, py,     px + d, py + d, color);
    BWAPI::Broodwar->drawLineMap(px + d, py + d, px,     py + d, color);
    BWAPI::Broodwar->drawLineMap(px,     py + d, px,     py,     color);
}

bool MapTools::canWalk(int tileX, int tileY) const
{
    for (int i=0; i<4; ++i)
    {
        for (int j=0; j<4; ++j)
        {
            if (!BWAPI::Broodwar->isWalkable(tileX*4 + i, tileY*4 + j))
            {
                return false;
            }
        }
    }

    return true;
}

bool MapTools::canBuild(int tileX, int tileY) const
{
    return BWAPI::Broodwar->isBuildable(BWAPI::TilePosition(tileX, tileY));
}




void MapTools::draw() const
{
    const BWAPI::TilePosition screen(BWAPI::Broodwar->getScreenPosition());
    const int sx = screen.x;
    const int sy = screen.y;
    const int ex = sx + 20;
    const int ey = sy + 15;

    for (int x = sx; x < ex; ++x)
    {
        for (int y = sy; y < ey; y++)
        {
            const BWAPI::TilePosition tilePos(x,y);
            if (!tilePos.isValid()) { continue; }

            if (true)
            {
                BWAPI::Color color = isWalkable(x, y) ? BWAPI::Color(0, 255, 0) : BWAPI::Color(255, 0, 0);
                if (isWalkable(x, y) && !isBuildable(x, y)) { color = BWAPI::Color(255, 255, 0); }
                if (isBuildable(x, y) && !isDepotBuildableTile(x, y)) { color = BWAPI::Color(127, 255, 255); }
                drawTile(x, y, color);
            }
        }
    }

    const char red = '\x08';
    const char green = '\x07';
    const char white = '\x04';
    const char yellow = '\x03';

    BWAPI::Broodwar->drawBoxScreen(0, 0, 200, 100, BWAPI::Colors::Black, true);
    BWAPI::Broodwar->setTextSize(BWAPI::Text::Size::Huge);
    BWAPI::Broodwar->drawTextScreen(10, 5, "%cMap Legend", white);
    BWAPI::Broodwar->setTextSize(BWAPI::Text::Size::Default);
    BWAPI::Broodwar->drawTextScreen(10, 30, "%cRed: ", red);
    BWAPI::Broodwar->drawTextScreen(60, 30, "%cCan't Walk or Build", white);
    BWAPI::Broodwar->drawTextScreen(10, 45, "%cGreen:", green);
    BWAPI::Broodwar->drawTextScreen(60, 45, "%cCan Walk and Build", white);
    BWAPI::Broodwar->drawTextScreen(10, 60, "%cYellow:", yellow);
    BWAPI::Broodwar->drawTextScreen(60, 60, "%cResource Tile, Can't Build", white);
    BWAPI::Broodwar->drawTextScreen(10, 75, "Teal:");
    BWAPI::Broodwar->drawTextScreen(60, 75, "%cCan't Build Depot", white);

    
}
