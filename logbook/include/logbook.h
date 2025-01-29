#ifndef LOGBOOK_H
#define LOGBOOK_H

#include <string>
#include <fstream>
#include <time.h>
#include <mutex>

extern "C" {

  enum Level {
    LOW, MEDIUM, HIGH
  }; 

  class Logbook {
  public:
    Logbook(const std::string&, Level);
    ~Logbook();

    Level GetDefaultLevel() const;
    void SetDefaultLevel(Level);

    void AddMessage(const std::string);
    void AddMessage(const std::string, Level);

  private:
    void WriteLog(std::string);
    std::string getCurTime() const;
    std::string levelToStr(Level level) const;

    const std::string levels_[3] {"  LOW ", "MEDIUM", " HIGH "};

    Level defaultLevel_;
    std::ofstream writer_;
    std::mutex logMutex;
  };

}

#endif