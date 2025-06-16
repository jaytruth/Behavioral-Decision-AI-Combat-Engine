# Behavioral - Decision C++ AI Combat Engine

🎮 A high-level AI-powered combat simulation engine written in modern C++.  
🧠 Features decision-making AI logic for enemy behavior, player adaptability, and team-based battle systems.

---

## 🚀 Features

- ✅ Object-Oriented Design using `Entity`, `Player`, and `Enemy` classes
- ✅ Multithreading with `std::thread`, `std::mutex`, and `lock_guard`
- ✅ AI behavior modeling and decision-making system
- ✅ JSON Serialization & Deserialization (using `nlohmann/json`)
- ✅ Team vs Team simulation (1000+ battles)
- ✅ Result logging into `.json` files (`results.json`, `teamfight.json`)
- ✅ Advanced use of randomness (`std::random_device`, `mt19937`, etc.)
- ✅ Portable & lightweight C++ code

---

## 🧠 AI Logic Summary

The AI engine makes dynamic decisions during combat, especially for enemies, based on:

- 📊 Player’s current **health**, **attack**, and **defense**
- 🧠 Enemy’s own **health**, **attack**, **defense**, and **heal capacity**
- 🧑‍🤝‍🧑 Teammate’s **health** and **heal** status
- 🎲 Random probability to simulate unpredictability and strategic variation

Based on this data, the enemy decides to:
- **Attack** the player
- **Defend** to reduce damage
- **Heal** when weak

This creates a believable and challenging combat simulation, where AI behaves strategically instead of randomly.

## 🧪 How to Run

1. ✅ Make sure you have a C++ compiler with C++11+ support.
   Example: `g++`, `clang++`, or MSVC

2. ✅ Compile the code:


3. ✅ Run the executable:


4. 📝 Check the generated files:
   - `results.json`: AI battle logs
   - `teamfight.json`: Team fight results
   - `player.json`, `enemy.json`: Serialized character data
 Sample code for json :- 
  1. enemy.json
     {
    "attack": 80.0,
    "defense": 90.0,
    "heal": 100.0,
    "health": 80.0,
    "name": "doremon"
}
  2. player.json
     {
    "attack": 70.0,
    "defense": 90.0,
    "heal": 100.0,
    "health": 80.0,
    "name": "pokemon"
}
   3. teamfight.json 
      [
    {
        "teamEnemyScore": 10,
        "teamPlayerScore": 0
    },
    {
        "teamEnemyScore": 10,
        "teamPlayerScore": 0
    },
   , .......]
   4. results.json
     [
    {
        "decision": "attack",
        "enemy attack": 90.0,
        "enemy defense": 90.0,
        "enemy heal": 90.0,
        "enemy health": 85.0,
        "game": 1,
        "player attack": 65.0,
        "player defense": 95.0,
        "player heal": 70.0,
        "player health": 65.0
    }, ...... ]

## 🎯 Purpose

This project simulates intelligent character behavior in combat scenarios. It demonstrates:
- Use of AI decision trees for dynamic decision-making
- Object-oriented programming in C++
- Multithreading with race-condition safety
- Serialization and deserialization using JSON
- Realistic combat behavior simulation
 
## 🧩 Dependencies

- C++11 or newer
- [nlohmann/json](https://github.com/nlohmann/json): Used for reading and writing `.json` files

## 📁 Project Structure
Behavioral-Decision-AI-Combat-Engine/
│
├── main.cpp # Main C++ simulation engine
├── player.json # Serialized player data
├── enemy.json # Serialized enemy data
├── results.json # 1000+ battle AI simulation results
├── teamfight.json # Team-vs-Team AI simulation results
├── README.md # Project documentation
└── .gitignore # Files to ignore in Git
