#include<iostream>
#include<string>
#include "json.hpp"
#include<fstream>
#include<thread>
#include<mutex>
#include<vector>
#include<random>

using json = nlohmann::json;
using namespace std;
using mutex = std:: mutex;
using thread = std:: thread;
// class entity storing atrributes of player and enemy class.
class Entity {
public:
    string name;
    double health;
    double attack;
    double defense;
    double heal;
    
};
// inheritnce of child class player in  parent class entity.
class player : public Entity {
public:
    player(string name, double health, double attack, double defense, double heal){
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        this->heal = heal;
    }
  // for serialization  of data
    json to_json() const {
        return {
            {"name", name},
            {"health", health},
            {"attack", attack},
            {"defense", defense},
            {"heal", heal}
        };
    }
   // for deserialization of data.
    static player from_json(const json& j) {
        return player(
            j.at("name").get<string>(),
            j.at("health").get<double>(),
            j.at("attack").get<double>(),
            j.at("defense").get<double>(),
            j.at("heal").get<double>()
        );
    }
};
// inheritnce of child class enemy in  parent class entity.
class enemy : public Entity {
public:
    enemy(string name, double health, double attack, double defense, double heal) {
        this->name = name;
        this->health = health;
        this->attack = attack;
        this->defense = defense;
        this->heal = heal;
    }
    // Advanced AI logic for enemy decisions .
    string enemyDecision(const player& p) {
        if (health < 30 && heal > 20) {
            return "heal";
        } else if (p.defense > attack) {
            return "attack";
        } else if (p.attack > defense) {
            return "defense";
        } else {
            return "heal";
        }

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(1, 100);
        int roll = dis(gen);

        if (roll <= 40) return "attack";
        else if (roll <= 70) return "defense";
        else return "heal";
    }
     // serialization of data .
    json to_json() const {
        return {
            {"name", name},
            {"health", health},
            {"attack", attack},
            {"defense", defense},
            {"heal", heal}
        };
    }
    // deserialization of data 
    static enemy from_json(const json& j) {
        return enemy(
            j.at("name").get<string>(),
            j.at("health").get<double>(),
            j.at("attack").get<double>(),
            j.at("defense").get<double>(),
            j.at("heal").get<double>()
        );
    }
};
// mutex for running one thread at a time.
mutex mtx;
int playerWin = 0, enemyWin = 0;

void simulateGame(int count) {
    player p1("pokemon", 80, 70, 90, 100);
    enemy e1("doremon", 80, 80, 90, 100);

    double damagePlayer = p1.health + (e1.health - p1.health) / 2;
    double damageEnemy = p1.health + (e1.health - p1.health) / 2;

    if (p1.defense > e1.attack) {
        damageEnemy -= 10;
        e1.health = damageEnemy;
    } else {
        damagePlayer -= 10;
        p1.health = damagePlayer;
    }
     // loack guard for locking current thread and gets unloked whe one thread task  is completed
    lock_guard<mutex> lock(mtx);
    if (p1.health > e1.health && damagePlayer > 0) {
        playerWin++;
    } else {
        enemyWin++;
    }
}
 // helper function to avoid negtive values 
double clamp(double value, double min = 0.0, double max = 100.0) {
    return std::max(min, std::min(max, value));
}
// here ai is deciding if player 1 health is low , player 2 will come in play and vice versa similar for enemy.
void AiCharacterBehaviour(){
    int teamPlayerScore  = 0, teamEnemyScore = 0;
    
    json teamfight = json:: array();
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(60, 100);
    cout<<"Fight between team player  and  team enemy "<<endl;
    for(int i = 0;i<1000;i++){
        player p1("player1",dis(gen),dis(gen),dis(gen),dis(gen));
        player p2("player2", dis(gen), dis(gen), dis(gen), dis(gen));
        enemy e1("enemy1", dis(gen), dis(gen), dis(gen), dis(gen));
        enemy e2("enemy2", dis(gen), dis(gen), dis(gen), dis(gen));
    if(p1.defense>e1.attack){
        p1.health -= 5;
        p1.heal += 10;
        e1.defense -= 5;
        e1.heal += 10;
        teamPlayerScore += 10;
    } 
    else if(p1.attack>e1.defense){
        p1.attack -= 5;
        p1.heal += 10;
        e1.attack -= 5;
        e1.heal += 10;
        teamEnemyScore += 10;
    }
    else if(p1.health <= 0){
        if(p1.heal<=20){
            if(p2.defense>e1.attack){
                p2.health -= 5;
                p2.heal += 10;
                e1.defense -= 5;
                e1.heal += 10;
                teamPlayerScore -= 5;
                teamEnemyScore += 5;
            }
            else {
                p2.attack -= 5;
                p2.heal += 10;
                e1.attack -= 5;
                e1.heal -= 5;
                teamPlayerScore -= 5;
                teamEnemyScore += 5;
            }
        }
        else {
            if(p1.defense>e2.attack){
                p1.health -= 5;
                p1.heal += 10;
                e2.defense -= 5;
                e2.heal += 10;
                teamPlayerScore += 5;
                teamEnemyScore -= 5;
            }
            else {
                p1.attack -= 5;
                p1.heal += 10;
                e2.attack -= 5;
                e2.heal += 10;
                teamPlayerScore += 5;
                teamEnemyScore -= 5;
            }
        }
    }
    json gameAiResult = {
        {"teamPlayerScore", teamPlayerScore},
        {"teamEnemyScore", teamEnemyScore}
    };
    teamfight.push_back(gameAiResult);
}
ofstream outFile("teamfight.json");
outFile << teamfight.dump(4);
outFile.close();
cout<<" successfully saved in teamfight.json ."<<endl;
}
int main() {
    // call for constructor
    player p1("pokemon", 80, 70, 90, 100);
    enemy e1("doremon", 80, 80, 90, 100);
    player p2("pikachu",90,78,91,100);
    enemy e2("charizard", 90, 80, 90, 100);
    AiCharacterBehaviour();
    // Serialize player and enemy
    ofstream outFile("player.json");
    outFile << p1.to_json().dump(4);
    outFile.close();

    ofstream outFile2("enemy.json");
    outFile2 << e1.to_json().dump(4);
    outFile2.close();

    // Deserialize
    ifstream inFile("player.json");
    json jread;
    inFile >> jread;
    

    
    ifstream inFile2("enemy.json");
    json kread;
    inFile2 >> kread;
    
   player loadedPlayer = player::from_json(jread);
    cout<<"\n\nplayer loaded from file\n";
    cout<<"Name : "<<loadedPlayer.name<<"\n";
    cout<<"Health : "<<loadedPlayer.health<<"\n";
    cout<<"Attack : "<<loadedPlayer.attack<<"\n";
    cout<<"Defense : "<<loadedPlayer.defense<<"\n";
    enemy loadedEnemy = enemy::from_json(kread);
    cout<<"\n\nenemy loaded from file\n";
    cout<<"Name : "<<loadedEnemy.name<<"\n";
    cout<<"Health : "<<loadedEnemy.health<<"\n";
    cout<<"Attack : "<<loadedEnemy.attack<<"\n";
    cout<<"Defense : "<<loadedEnemy.defense<<"\n";
    // Threads
    const int games = 1000;
    const int threads = 4;
    const int totalThread = games / threads;
    vector<thread> threadpool;
    for (int i = 0; i < threads; i++) {
        threadpool.emplace_back(simulateGame, totalThread);
    }
    for (auto& t : threadpool) {
        t.join();
    }

    // Game Simulation with AI decisions
    json results = json::array();
    double damagePlayer = p1.health + (e1.health - p1.health) / 2;
    double damageEnemy = p1.health + (e1.health - p1.health) / 2;

    for (int i = 0; i < 1000; i++) {
        p1.health = clamp(p1.health);
        p1.attack = clamp(p1.attack);
        p1.defense = clamp(p1.defense);
        p1.heal = clamp(p1.heal);

        e1.health = clamp(e1.health);
        e1.attack = clamp(e1.attack);
        e1.defense = clamp(e1.defense);
        e1.heal = clamp(e1.heal);

        string decision = e1.enemyDecision(p1);

        if (decision == "attack") {
            p1.defense += 5;
            p1.attack -= 5;
            e1.attack += 10;
            damagePlayer -= 15;
            p1.health = damagePlayer;
            e1.health += 5;
            p1.heal -= 30;
            e1.heal -= 10;
        } else if (decision == "defense") {
            p1.attack += 5;
            p1.defense -= 5;
            damageEnemy -= 10;
            e1.health = damageEnemy;
            e1.defense += 10;
            e1.heal -= 30;
            p1.heal -= 10;
        } else {
            p1.health -= 10;
            e1.health -= 10;
            p1.heal += 10;
            e1.heal += 10;
        }

        json gameresult = {
            {"game", i + 1},
            {"player heal", p1.heal},
            {"enemy heal", e1.heal},
            {"player health", p1.health},
            {"enemy health", e1.health},
            {"player attack", p1.attack},
            {"enemy attack", e1.attack},
            {"player defense", p1.defense},
            {"enemy defense", e1.defense},
            {"decision", decision}
        };

        results.push_back(gameresult);

        if (p1.health <= 0 && e1.health <= 0) {
            break;
        }
    }

    ofstream resultFile("results.json");
    resultFile << results.dump(4);
    resultFile.close();

    cout << "AI logic applied and results saved to results.json.\n";
    return 0;
}
