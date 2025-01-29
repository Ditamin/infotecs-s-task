#include "logbook.h"

Logbook::Logbook(const std::string& fileName, Level defaultLevel) {
  defaultLevel_ = defaultLevel;
  writer_ = std::ofstream(fileName, std::ios::app); 
}

Logbook::~Logbook() {
  writer_.close();
}

Level Logbook::GetDefaultLevel() const {
  return defaultLevel_;
}

void Logbook::SetDefaultLevel(Level newLevel) {
  defaultLevel_ = newLevel;
}

void Logbook::AddMessage(const std::string message) {
  AddMessage(message, defaultLevel_);
}

void Logbook::AddMessage(const std::string message, Level level) {
  if (writer_.bad()) {
    throw std::runtime_error("Could not open file");
  }

  if (level < defaultLevel_) {
    return;
  }

  std::string log = getCurTime() + " " + levelToStr(level) + " " + message;
  WriteLog(log);
}

void Logbook::WriteLog(std::string message) {
  // захватываем mutex во избежании ошибок многопоточности
  std::lock_guard<std::mutex> guard(logMutex);
  writer_ << message << std::endl;
}

std::string Logbook::levelToStr(Level level) const {
  return levels_[level];
}

std::string Logbook::getCurTime() const {
  time_t rawTime = time(NULL);
  struct tm* timeInfo = localtime(&rawTime);
  char time[20];
  strftime(time, sizeof(time), "%T", timeInfo);

  return time;
}
