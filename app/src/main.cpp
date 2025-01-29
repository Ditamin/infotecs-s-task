#include "app.h"

int main(int argc, char* argv[]) {
  if (argc < 3) {
    std::cerr << "Необходимо ввести параметры запуска (имя файла, уровень по умолчанию)\n";
    return 0;
  }
  
  std::string filename;
  Level defaultLevel;

  // Получаем имя файла из аргументов
  filename = argv[1];

  if (argc >= 3) {
    // Получаем уровень по умолчанию из аргументов
    std::string levelStr = argv[2];

    // Проверяем уровень на корректность
    if (!App::IsLevel(levelStr)) {
      std::cerr << "Некорректный уровень важности по умолчанию\n" + curLevels;
      return 0;
    }

    defaultLevel = App::GetLevelByStr(levelStr);
  }

  // Запускаем приложение
  App app(filename, defaultLevel);
  return 0;
}