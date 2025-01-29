#include "app.h"

App::App(const std::string& fileName, Level level) : logbook_(fileName, level) {
  Run();
}

void App::Run() {
  while (true) {
    std::string message;
    std::cout << "Введите сообщение: ";
    getline(std::cin, message);

    if (message == "exit") {
      return;
    }

    std::string levelStr;
    std::cout << "Введите уровень сообщения (LOW, MEDIUM, HIGH) или нажмите Enter: ";
    getline(std::cin, levelStr);

    // пока уровень не пустой или неправильно написан, просим ввести
    while (!(levelStr.empty() || IsLevel(levelStr))) {
      std::cout << "Некорректный уровень сообщения\n";
      std::cout << "Введите уровень сообщения (LOW, MEDIUM, HIGH) или нажмите Enter: ";
      getline(std::cin, levelStr);
    }

    Level level;

    if (levelStr.empty()) {
      // присваиваем уровень по умолчанию
      level = logbook_.GetDefaultLevel();
    } else {
      // конвертируем строку уровень в тип Level
      level = GetLevelByStr(levelStr);
    }

    try {
      // создаем поток для записи нового сообщения
      std::thread logThread(AddMessage, std::ref(logbook_), message, level);
      // отделяем поток для параллельной обработки
      logThread.detach();
    } catch (std::runtime_error const& e) {
      std::cout << "Не удалось записать сообщение: " << e.what();
    }
  }
}

void AddMessage(Logbook& logbook, const std::string message, Level level) {
  logbook.AddMessage(message, level);
}

bool App::IsLevel(std::string level) {
  // Перевод строки level в верхний регистр
  std::transform(begin(level), end(level), begin(level), ::toupper);  
  return std::find(begin(levelsStr), end(levelsStr), level) != end(levelsStr);
}

Level App::GetLevelByStr(std::string level) {
  // Перевод строки level в верхний регистр
  std::transform(begin(level), end(level), begin(level), ::toupper);
  int idxOfLevel = std::find(begin(levelsStr), end(levelsStr), level) - begin(levelsStr);
  return levels[idxOfLevel];
}