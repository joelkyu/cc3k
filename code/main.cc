#include "floor.h"
#include "movement.h"
#include "attack.h"
#include "merchant.h"

#include <string>
#include <iostream>
#include <iomanip>


using namespace std;

enum class PlayerCommand {NO, SO, EA, WE, NE, NW, SE, SW, U, A, F, R, Q, NONE};

string printRace(Race race) {
    string raceString = "";
    switch (race) {
    case Race::Shade :
        raceString = "Shade";
        break;

    case Race::Drow:
        raceString = "Drow";
        break;

    case Race::Goblin:
        raceString = "Goblin";
        break;

    case Race::Troll:
        raceString = "Troll";
        break;

    case Race::Vampire:
        raceString = "Vampire";
        break;

    default :
        break;
    }
    return raceString;
}

PlayerCommand processCommand(const string& command) {
    PlayerCommand enumCom;

    if (command == "no") enumCom = PlayerCommand::NO;
    else if (command == "so") enumCom = PlayerCommand::SO;
    else if (command == "ea") enumCom = PlayerCommand::EA;
    else if (command == "we") enumCom = PlayerCommand::WE;
    else if (command == "ne") enumCom = PlayerCommand::NE;
    else if (command == "nw") enumCom = PlayerCommand::NW;
    else if (command == "se") enumCom = PlayerCommand::SE;
    else if (command == "sw") enumCom = PlayerCommand::SW;
    else if (command == "u") enumCom = PlayerCommand::U;
    else if (command == "a") enumCom = PlayerCommand::A;
    else if (command == "f") enumCom = PlayerCommand::F;
    else if (command == "r") enumCom = PlayerCommand::R;
    else if (command == "q") enumCom = PlayerCommand::Q;
    else enumCom = PlayerCommand::NONE;

    return enumCom;
}

// merchant hostile status
bool Merchant::isHostile = false;


int main(int argc, char* argv[]) {
    srand((unsigned int)time(0));

    // ============== MAP FILE INITIATION ==================

    // default map name
    const string DEFAULT_MAP = "__defaultMap__.txt";

    string fileName = DEFAULT_MAP;

    // check if default map exists
    ifstream mapFile{ DEFAULT_MAP };       // store all map layouts in mapFile

    if (!mapFile.is_open()) {
        cout << "No default map." << endl;
        return 0;
    }

    // read commandline argument, get filename
    if (argc == 2) {
        fileName = "";
        int i = 0;
        while (argv[1][i]) {
            fileName += argv[1][i];       // read arg into fileName
            ++i;
        }
        mapFile.close();                  // store all map layouts in mapFile
        mapFile.open(fileName);

        // open default map if file specified doesn't exist
        if (!mapFile.is_open()) {
            fileName = DEFAULT_MAP;
            mapFile.open(fileName);
        }
    }

    bool isMapProvided = fileName != DEFAULT_MAP;

    
    // =================== GAME LOOP ========================

    string command;
    bool gameLoop = true;

    // making an empty floor, placeholder race
    Floor theFloor;
     
    // movement, attack classes and dummy direction
    Movement movement(Direction::North);
    Attack attack(Direction::North);

    // player encounters stairs
    bool atStairs = false;

    // action statement
    string action = "";
    
    // call init to generate map or quit
    if (!theFloor.init(mapFile, isMapProvided)) return 0;

    // making a player pointer to track the player
    shared_ptr<Player> thePlayer = theFloor.getPlayer();

    if (thePlayer == nullptr) cout << "no player" << endl;

    //cout << mapFile;

    // print beginning map
    cout << theFloor;

    // printing player information
    cout << setfill(' ');
    cout << left << "Race: " << printRace(thePlayer->getRace()) << " Gold: " << thePlayer->getGold();
    cout << right << setw(55) << "Floor: " << theFloor.getFloor() << endl;

    cout << "HP: " << setw(4) << thePlayer->getCurrHP() << endl;
    cout << "Atk: " << setw(3) << thePlayer->getAtk() << endl;
    cout << "Def: " << setw(3) << thePlayer->getDef() << endl;
    cout << "Action: " << "Preparing for battle!" << endl;

    cin.exceptions(ios::eofbit | ios::failbit);
    while (gameLoop) {

        // accepts player input
        cout << "Waddya gonna do next?" << endl;

        try {                                           // try and catch io errors
            cin >> command;

            switch (processCommand(command)) {

            case PlayerCommand::NO:                        // move north
                movement.setDirection(Direction::North);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves North.";
                break;

            case PlayerCommand::SO:                        // move south
                movement.setDirection(Direction::South);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves South.";
                break;

            case PlayerCommand::EA:                        // move east
                movement.setDirection(Direction::East);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves East.";
                break;

            case PlayerCommand::WE:                        // move west
                movement.setDirection(Direction::West);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves West.";
                break;

            case PlayerCommand::NE:                        // move northeast
                movement.setDirection(Direction::Northeast);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves Northeast.";
                break;

            case PlayerCommand::NW:                        // move northwest
                movement.setDirection(Direction::Northwest);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves Northwest.";
                break;

            case PlayerCommand::SE:                        // move southeast
                movement.setDirection(Direction::Southeast);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves Southeast.";
                break;

            case PlayerCommand::SW:                        // move southwest
                movement.setDirection(Direction::Southwest);
                atStairs = movement.moveInDirection(thePlayer, theFloor);
                action = "PC moves Southwest.";
                break;

            case PlayerCommand::U:                         // use potion
            {
                cin >> command;
                action = "PC attempts to use potion.";
                PlayerCommand direction = processCommand(command);

                switch (direction) {                            // use potion in direction
                case PlayerCommand::NO:
                    movement.setDirection(Direction::North);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                case PlayerCommand::SO:
                    movement.setDirection(Direction::South);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                case PlayerCommand::EA:
                    movement.setDirection(Direction::East);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                case PlayerCommand::WE:
                    movement.setDirection(Direction::West);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                case PlayerCommand::NE:
                    movement.setDirection(Direction::Northeast);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                case PlayerCommand::NW:
                    movement.setDirection(Direction::Northwest);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                case PlayerCommand::SE:
                    movement.setDirection(Direction::Southeast);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                case PlayerCommand::SW:
                    movement.setDirection(Direction::Southwest);
                    movement.pickUpPotion(*thePlayer, theFloor);
                    break;

                default:
                    break;
                }
                break;
            }

            case PlayerCommand::A :                         // attack
            {
                cin >> command;
                action = "PC attacks!";
                PlayerCommand direction = processCommand(command);

                switch (direction) {                            // attack in direction
                case PlayerCommand::NO:
                    attack.setDirection(Direction::North);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                case PlayerCommand::SO:
                    attack.setDirection(Direction::South);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                case PlayerCommand::EA:
                    attack.setDirection(Direction::East);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                case PlayerCommand::WE:
                    attack.setDirection(Direction::West);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                case PlayerCommand::NE:
                    attack.setDirection(Direction::Northeast);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                case PlayerCommand::NW:
                    attack.setDirection(Direction::Northwest);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                case PlayerCommand::SE:
                    attack.setDirection(Direction::Southeast);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                case PlayerCommand::SW:
                    attack.setDirection(Direction::Southwest);
                    attack.playerAttack(thePlayer, theFloor);
                    break;

                default :
                    break;
                }
                break;
            }

            case PlayerCommand::F:                         // stop enemy movement
                theFloor.toggleEnemyMovement();
                action = "ZA WARUDO TOKI WO TOMARE"; 
                break;

            case PlayerCommand::R:                         // restart game
            {
                action = "You used KILLER QUEEN BITES ZA DUSTO to go back in time!!!";
                mapFile.close();                                        // refresh ifstream
                mapFile.open(fileName);
                if (!theFloor.init(mapFile, isMapProvided)) return 0;   // init map
                thePlayer = theFloor.getPlayer();
                break;
            }

            case PlayerCommand::Q:                         // quit game
            {
                cout << "Already? Pathetic." << endl;
                gameLoop = false;
                break;
            }
            default :
                break;
            }

            // if stairs are reached
            if (atStairs) {
                theFloor.nextFloor(mapFile, isMapProvided);
                atStairs = false;

                // if end is reached
                if (theFloor.getFloor() == 5) {
                    gameLoop = false;
                    cout << "You have successfully bathed in the blood of your enemies!" << endl;
                    cout << "You've collected " << thePlayer->getScore() << " in this tryst." << endl;
                }
            }

            theFloor.tick();// tick runs after every action the player makes.

            if (thePlayer->getCurrHP() == 0) {
                gameLoop = false;
                cout << "Your villainy was thwarted once again..." << endl;
                cout << "You've collected " << thePlayer->getScore() << " in this tryst." << endl;
                cout << "Now GET OUT!!!!!!!" << endl;
            }

            if (!gameLoop) break;                          // exit

            std::cout << theFloor;

            // printing player information
            cout << setfill(' ');
            cout << left << "Race: " << printRace(thePlayer->getRace()) << " Gold: " << thePlayer->getGold();
            cout << right << setw(55) << "Floor: " << theFloor.getFloor() << endl;

            cout << "HP: " << setw(4) << thePlayer->getCurrHP() << endl;
            cout << "Atk: " << setw(3) << thePlayer->getAtk() << endl;
            cout << "Def: " << setw(3) << thePlayer->getDef() << endl;
            cout << "Action: " << action << endl;
        }
        catch (ios::failure&) {}
    }
}


