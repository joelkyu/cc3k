#include "floor.h"
#include "movement.h"

#include <iostream>
#include <memory>
#include <vector>
using namespace std;

bool Floor::init(ifstream& mapFile, bool isMapProvided) {
    char initCommand;
    PlayerRace playerRace;
    bool initScreen = true;
    cin.exceptions(ios::eofbit | ios::failbit);

    cout << "Enter xXx_cc3k_xXx!" << endl;
    cout << "Cut down your enemies and bathe in their blood and tears!!!" << endl;
    cout << "For max enjoyment, please open and play music.wav since" << endl;
    cout << "the linux server doens't play audio files with the play command :/" << endl;

    // ------------------- initiate game --------------------
    try {
        while (initScreen) {
            cout << "Pick a race: (s)hade, (d)row, (v)ampire, (g)oblin, (t)roll" << endl;
            cin >> initCommand;

            switch (initCommand) {
            case 'q':                                      // quit game
                cout << "Quitting? Pathetic." << endl;
                return false;

            case 's':                                      // shade
                playerRace = PlayerRace::Shade;
                cout << "Throw some SHADE at your foes!" << endl;
                initScreen = false;
                break;

            case 'd':                                      // drow
                playerRace = PlayerRace::Drow;
                cout << "Rule the Underdark as a DROW!" << endl;
                initScreen = false;
                break;

            case 'v':                                      // vampire
                playerRace = PlayerRace::Vampire;
                cout << "Feast on your foes as a VAMPIRE!" << endl;
                initScreen = false;
                break;

            case 'g':                                      // goblin
                playerRace = PlayerRace::Goblin;
                cout << "GOBLIN, the ultimate gremlin!" << endl;
                initScreen = false;
                break;

            case 't':                                      // troll
                playerRace = PlayerRace::Troll;
                cout << "TROLL your enemies with your fighting prowess!" << endl;
                initScreen = false;
                break;
            }
        }
    }
    catch (ios::failure&) {
        return false; 
    } // quits with any I/O failure

     // creating the new fields
    display = make_shared<Display>(ROW_DIMENSION, COL_DIMENSION); // makes display with our row and col dimensions
    initCells();
    /*for (int i = 0; i < 5; ++i) {
        auto chamberptr = make_shared<Chamber>(ROW_DIMENSION, COL_DIMENSION);
        chambers.push_back(chamberptr);
    }*/

    floorLevel = 0; // resets floor count 
    PLAYER_RACE = playerRace; // sets the player race

     // calling next floor to make the maps
    nextFloor(mapFile, isMapProvided);

    display->update(cells);

    return true; // returns true if inializtion is successful
}

void Floor::initCells()
{
    for (int r = 0; r < ROW_DIMENSION; ++r) {
        vector<shared_ptr<Cell>> row;
        for (int c = 0; c < COL_DIMENSION; ++c) {
            auto cellptr = make_shared<Cell>(r, c);
            row.push_back(cellptr);
        }
        cells.push_back(row);
    }
}

void clearCells(vector<vector<shared_ptr<Cell>>> cells) {
    for (auto row : cells) {
        for (auto aCell : row) {
            aCell->setEntity(nullptr);
            aCell->getGold()->clear();
            aCell->setTerrain(nullptr);
        }
    }
}

void Floor::nextFloor(ifstream& mapFile, bool isMapProvided) 
{
    if (floorLevel == 5) // 5 being after the 5th floor
    {
        // call the player score/death method to generate score screen
    }
    else {
        // reset cells
        clearCells(cells);

        readFloor(mapFile);
        if (!isMapProvided) { randomSpawn(); }
        ++floorLevel;
    }
}


// constructor
Floor::Floor() {
    // make movement classes with dummy value
    movement = make_shared<Movement>(Direction::North);
    attack = make_shared<Attack>(Direction::North);
}

// ----------------- readFloor() and friends ----------------------------

// recursive helpers for setChamberVector
bool isNewChamber(vector<vector<bool>> &array, int row, int col, int maxRow, int maxCol)
{
    if (row < 0 || col < 0 || row >= maxRow || col >= maxCol) return false;
    if (array[row][col] == false) return false;
    
    // replace true with false
    array[row][col] = false;

    // recure north, south, east, west
    isNewChamber(array, row - 1, col, maxRow, maxCol);
    isNewChamber(array, row + 1, col, maxRow, maxCol);
    isNewChamber(array, row, col - 1, maxRow, maxCol);
    isNewChamber(array, row, col + 1, maxRow, maxCol);
    return true;

}

void getChamberBlock(vector<vector<bool>>& cellArray, Chamber& chamber,
    int row, int col, int maxRow, int maxCol)
{
    if (row < 0 || col < 0 || row >= maxRow || col >= maxCol) return;
    if (cellArray[row][col] == true)
    {
        chamber.setChamberValue(row, col);
        cellArray[row][col] = false;
        getChamberBlock(cellArray, chamber, row - 1, col, maxRow, maxCol);
        getChamberBlock(cellArray, chamber, row + 1, col, maxRow, maxCol);
        getChamberBlock(cellArray, chamber,row, col - 1, maxRow, maxCol);
        getChamberBlock(cellArray, chamber, row, col + 1, maxRow, maxCol);
    }
}

// helper function for readFloor that alters chambers field
void Floor::setChamberVector() {
    vector<vector<bool>> findNewChambers(ROW_DIMENSION, 
        vector<bool>(COL_DIMENSION, false));        // 2D vector of false

    // get a 2D vector of bools that map all chambers in one vector
    for (int r = 0; r < ROW_DIMENSION; ++r) {
        for (int c = 0; c < COL_DIMENSION; ++c) {

            if (cells[r][c]->getTerrain() != nullptr) {
                if (cells[r][c]->getTerrain()->enemyCanAccess()) {  // if chamber tile

                    findNewChambers[r][c] = true;
                }
            }
        }
    }

    vector<vector<bool>> findChamberBlock;

    // copy findNewChambers into findChamberBlock
    for (int r = 0; r < ROW_DIMENSION; ++r) {
        vector<bool> newRow;
        for (int c = 0; c < COL_DIMENSION; ++c) {
            newRow.push_back(findNewChambers[r][c]);
        }
        findChamberBlock.push_back(newRow);
    }

    // put each block of true in its own chamber object
    for (int r = 0; r < ROW_DIMENSION; ++r) {
        for (int c = 0; c < COL_DIMENSION; ++c) {

            if (isNewChamber(findNewChambers, r, c, ROW_DIMENSION, COL_DIMENSION)) {
                auto newChamber = make_shared<Chamber>(ROW_DIMENSION, COL_DIMENSION);
                getChamberBlock(findChamberBlock, *newChamber, r, c, ROW_DIMENSION, COL_DIMENSION);

                chambers.push_back(newChamber);
            }

        }
    }
}

// helper for readFloor to reduce dupe code
// set an empty chamber tile in the cell pointer
void setEmptyChamberTile(shared_ptr<Cell> currCell) {
    TerrainFactory makeTerrain('.');
    auto terrainToSet = dynamic_pointer_cast<Terrain>(makeTerrain.spawnObject(0, 0));
    currCell->setTerrain(terrainToSet);
}

void Floor::readFloor(ifstream& mapFile) 
{
    cin.exceptions(ios::eofbit | ios::failbit);


    try {
        string rowString;
        char tile;

        TerrainFactory makeTerrain('.');                // factories
        PlayerFactory makePlayer(PLAYER_RACE);
        ItemFactory makeItem('p');
        EnemyFactory makeEnemy(Race::Human);


        for (int rowIndex = 0; rowIndex < ROW_DIMENSION; ++rowIndex) {
            getline(mapFile, rowString);                // get rows of map in a string

            for (int colIndex = 0; colIndex < COL_DIMENSION; ++colIndex) {
                auto currCell = cells[rowIndex][colIndex];  // current cell pointer
                tile = rowString[colIndex];                 // get each char in the row

                shared_ptr<Terrain> terrainToSet;               // putting these in cells
                shared_ptr<Entity> entityToSet;
                shared_ptr<Gold> goldToSet;

                switch (tile) {

                // ----------- terrain -------------
                case '.' :                                      // chamber tile
                    setEmptyChamberTile(currCell);
                    break;

                case '-' :                                      // horizontal wall or
                    [[fallthrough]];
                case '|' :                                      // vertical wall or
                    [[fallthrough]];
                case '+' :                                      // door or
                    [[fallthrough]];
                case '#' :                                      // passage or
                    [[fallthrough]];
                case '\\' :                                     // stairs 
                    // make object and place it in currCell
                    makeTerrain.setTerrainMade(tile);
                    terrainToSet = dynamic_pointer_cast<Terrain>(makeTerrain.spawnObject(rowIndex, colIndex));
                    currCell->setTerrain(terrainToSet);
                    break;

                case ' ' :                                      // empty space
                    currCell->setTerrain(nullptr);
                    break;

                // ----------- player --------------
                case '@' :
                    // if first floor
                    if (floorLevel == 0) {
                        auto thePlayer = dynamic_pointer_cast<Player>(makePlayer.spawnObject(rowIndex, colIndex));
                        // set THE_PLAYER field
                        THE_PLAYER = thePlayer;
                    }
                    currCell->setEntity(THE_PLAYER);
                    THE_PLAYER->setCoords(rowIndex, colIndex);

                    setEmptyChamberTile(currCell);
                    break;

                // ------------ enemy ---------------
                case 'H' :
                    makeEnemy.setRaceMade(Race::Human);
                    entityToSet = dynamic_pointer_cast<Entity>(makeEnemy.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case 'W' :
                    makeEnemy.setRaceMade(Race::Dwarf);
                    entityToSet = dynamic_pointer_cast<Entity>(makeEnemy.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case 'E' :
                    makeEnemy.setRaceMade(Race::Elf);
                    entityToSet = dynamic_pointer_cast<Entity>(makeEnemy.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case 'O' :
                    makeEnemy.setRaceMade(Race::Orc);
                    entityToSet = dynamic_pointer_cast<Entity>(makeEnemy.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case 'M' :
                    makeEnemy.setRaceMade(Race::Merchant);
                    entityToSet = dynamic_pointer_cast<Entity>(makeEnemy.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case 'D' :                                  // gotta set hoard coordinates somehow
                    makeEnemy.setRaceMade(Race::Dragon);
                    entityToSet = dynamic_pointer_cast<Entity>(makeEnemy.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case 'L' :
                    makeEnemy.setRaceMade(Race::Halfling);
                    entityToSet = dynamic_pointer_cast<Entity>(makeEnemy.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                // ------------ potion ---------------
                case '0' :                                      // HpUp
                    makeItem.setPotionType(PotionType::HpUp);
                    entityToSet = dynamic_pointer_cast<Entity>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '1' :                                      // AtkUp
                    makeItem.setPotionType(PotionType::AtkUp);
                    entityToSet = dynamic_pointer_cast<Entity>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '2' :                                      // DefUp
                    makeItem.setPotionType(PotionType::DefUp);
                    entityToSet = dynamic_pointer_cast<Entity>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '3' :                                      // HpDown
                    makeItem.setPotionType(PotionType::HpDown);
                    entityToSet = dynamic_pointer_cast<Entity>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '4' :                                      // AtkDown
                    makeItem.setPotionType(PotionType::AtkDown);
                    entityToSet = dynamic_pointer_cast<Entity>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '5' :                                      // DefDown
                    makeItem.setPotionType(PotionType::DefDown);
                    entityToSet = dynamic_pointer_cast<Entity>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setEntity(entityToSet);

                    setEmptyChamberTile(currCell);
                    break;

                // ------------- gold ------------------
                case '6' :                                      // normal
                    makeItem.setGoldType(GoldType::Normal);
                    goldToSet = dynamic_pointer_cast<Gold>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setGold(goldToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '7' :                                      // small
                    makeItem.setGoldType(GoldType::Normal);
                    goldToSet = dynamic_pointer_cast<Gold>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setGold(goldToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '8' :                                      // merchant hoard
                    makeItem.setGoldType(GoldType::Normal);
                    goldToSet = dynamic_pointer_cast<Gold>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setGold(goldToSet);

                    setEmptyChamberTile(currCell);
                    break;

                case '9' :                                      // dragon hoard, copy coords to dragon somehow
                    makeItem.setGoldType(GoldType::Normal);
                    goldToSet = dynamic_pointer_cast<Gold>(makeItem.spawnObject(rowIndex, colIndex));
                    currCell->setGold(goldToSet);

                    setEmptyChamberTile(currCell);
                    break;

                } // big ass switch end

            } // column for loop end
        } // row for loop end

        setChamberVector();

    }
    catch (ios::failure&) {} // quits with any I/O failure
}

// ------------------ end of readFloor() and friends ---------------------------

// Yingying will do
void Floor::randomSpawn()
{
    int numOfChambers = (int)chambers.size();

    // factories and their dummy values
    EnemyFactory makeEnemy(Race::Human);    // i 22 to 41
    ItemFactory makeItem('p');              // i 2 to 21, 10 for potions 10 for gold
    PlayerFactory makePlayer(PLAYER_RACE);  // i 0
    TerrainFactory makeStairs('\\');        // i 1


    for (int i = 0; i < 42; ++i) {
        int row = 0;
        int col = 0;

        // try random again if entity occupies cell
        bool tryAgain = false;

                                         // pick chamber
        int chamberIndex = rand() % numOfChambers;
        shared_ptr<Chamber> currChamber = chambers[chamberIndex];

        int numOfTiles = currChamber->getNumOfTiles();  // pick tile
        
        int randTile = rand() % numOfTiles;

        int currTile = 0;
        for (; row < ROW_DIMENSION; ++row) {
            col = 0;
            if (tryAgain) break;

            for (; col < COL_DIMENSION; ++col) {
                if (tryAgain) break;

                // if random tile is picked
                if (currTile == randTile && currChamber->getChamberValue(row, col)) {

                    // if something occupying cell
                    if (cells[row][col]->getEntity() != nullptr ||
                        !cells[row][col]->getGold()->empty() ||
                        cells[row][col]->getTerrain()->areStairs()) {
                        --i;
                        tryAgain = true;
                        break;
                    }

                    // spawn enemy
                    if (i >= 22 && i < 42) {
                        auto randomEnemy = dynamic_pointer_cast<Entity>(makeEnemy.randomObject(row, col));
                        cells[row][col]->setEntity(randomEnemy);
                    }
                    // spawn potion
                    else if (i >= 2 && i < 12) {
                        makeItem.setItemType('p');
                        auto randomPotion = dynamic_pointer_cast<Entity>(makeItem.randomObject(row, col));
                        cells[row][col]->setEntity(randomPotion);
                    }
                    // spawn gold
                    else if (i >= 12 && i < 22) {
                        makeItem.setItemType('g');
                        auto randomGold = dynamic_pointer_cast<Gold>(makeItem.randomObject(row, col));
                        cells[row][col]->setGold(randomGold);

                        /*if (randomGold->getType() == GoldType::DragonHoard) {
                            makeEnemy.setRaceMade(Race::Dragon);
                            auto makeDragon = dynamic_pointer_cast<Entity>(makeItem.spawnObject(row, col));
                            cells[row][col]->setEntity(makeDragon);                 // spawn dragon on top of hoard
                        }  */                                                             // for now
                    }
                    // spawn player
                    else if (i == 0) {                  // spawn player
                        
                        // if first floor
                        if (floorLevel == 0) {
                            auto thePlayer = dynamic_pointer_cast<Player>(makePlayer.spawnObject(row, col));
                            // set THE_PLAYER field
                            THE_PLAYER = thePlayer;
                        }
                        cells[row][col]->setEntity(THE_PLAYER);
                        THE_PLAYER->setCoords(row, col);
                        
                    }

                    // spawn stairs
                    else if (i == 1) {
                        auto theStairs = dynamic_pointer_cast<Terrain>(makeStairs.spawnObject(row, col));
                        cells[row][col]->setTerrain(theStairs);
                    }

                    // successfully spawned enemy
                    tryAgain = true;
                }
                // if not at randomtile yet then increment tile
                if (currTile < randTile && currChamber->getChamberValue(row, col)) ++currTile;
            }
        }
    }
}

void Floor::tick() {
    //calls attack for every enemy entity
   
    for (auto r = 0; r < ROW_DIMENSION; ++r) {
        for (auto c = 0; c < COL_DIMENSION; ++c) {
            attack->enemyAttack(cells[r][c]->getEntity(), THE_PLAYER, *this);
        }
    }

    // if has moved flag is false, 
    for (auto r = 0; r < ROW_DIMENSION; ++r) {
        for (auto c = 0; c < COL_DIMENSION; ++c) {
            movement->randomMove(cells[r][c]->getEntity(), *this);
        }
    }

    // update the display for all cells
    display->update(cells);

    // sets hasMoved for all entities back to false
    for (auto r = 0; r < ROW_DIMENSION; ++r) {
        for (auto c = 0; c < COL_DIMENSION; ++c) {
            auto entity = cells[r][c]->getEntity(); // it is fine if it returns a nullptr as dynamic cast will take care of it
            auto enemy = dynamic_pointer_cast<Enemy>(entity);	// checking if it is an enemy
            if (enemy) { enemy->setHasMoved(false); }

        }
    }
}

// ========== getters ============
PlayerRace Floor::getPlayerRace() { return PLAYER_RACE; } 

shared_ptr<Player> Floor::getPlayer() { return THE_PLAYER; }

int Floor::getROWDIMENSION() { return ROW_DIMENSION; }

int Floor::getCOLDIMENSION() { return COL_DIMENSION; }

bool Floor::getChambers(int chamber, int x, int y) { return chambers[chamber]->getChamberValue(x, y); }

bool Floor::cellsEntityExists(int x, int y) { return cells[x][y]->entityExists(); }

bool Floor::enemyCanAccessCell(int x, int y)
{
    if (cells[x][y]->getTerrain() == nullptr) return false;
   return cells[x][y]->getTerrain()->enemyCanAccess();
}

bool Floor::playerCanAccessCell(int x, int y)
{
    if (cells[x][y]->getTerrain() == nullptr) return false;
    return cells[x][y]->getTerrain()->playerCanAccess();
}

bool Floor::cellAreStairs(int x, int y)
{
    if (cells[x][y]->getTerrain() == nullptr) return false;
    return cells[x][y]->getTerrain()->areStairs();
}

bool Floor::cellHasPotion(int x, int y)
{
    auto testPotion = dynamic_pointer_cast<Potion>(cells[x][y]->getEntity());
    return (testPotion != nullptr);
}

PotionType Floor::getCellPotiontype(int x, int y)
{
    auto potion = dynamic_pointer_cast<Potion>(cells[x][y]->getEntity());
    return potion->getPotionType();
}

shared_ptr<Enemy> Floor::getEnemy(int x, int y)
{
    auto enemy = dynamic_pointer_cast<Enemy>(cells[x][y]->getEntity());
    return enemy;
}

int Floor::getFloor() { return floorLevel;  }

shared_ptr<vector<shared_ptr<Gold>>> Floor::getGoldVector(int x, int y)
{
    return cells[x][y]->getGold();
}

shared_ptr<Movement> Floor::getMovement()
{
    return movement;
}


// ========== setters ============
void Floor::setCellsEntity(int x, int y, shared_ptr<Entity> entity) { cells[x][y]->setEntity(entity); }

void Floor::setGold(int x, int y, GoldType gold)
{
    ItemFactory makeItem('g');
    makeItem.setGoldType(gold);
    auto newGold = dynamic_pointer_cast<Gold>(makeItem.spawnObject(0, 0));
    cells[x][y]->setGold(newGold);
}

void Floor::toggleEnemyMovement()
{
    movement->toggleEnemiesCanMove();
}

// ========== override ============
ostream& operator<<(ostream& out, const Floor& f)
{
    out << *f.display;
    return out;
}
