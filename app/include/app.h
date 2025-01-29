#ifndef APP_H
#define APP_H

#include "logbook.h"
#include <iostream>
#include <algorithm>
#include <thread>

const int levelsCnt = 3;
const std::string levelsStr[levelsCnt] {"LOW", "MEDIUM", "HIGH"};
const Level levels[levelsCnt] {LOW, MEDIUM, HIGH};
const std::string curLevels = "Доступные уровни: LOW, MEDIUM, HIGH\n";

void AddMessage(Logbook&, const std::string, Level);

class App {
 public:
  App(const std::string&, Level);

  static bool IsLevel(std::string);
  static Level GetLevelByStr(std::string);

 private:
  void Run();

  Logbook logbook_;
};

#endif