#include <cassert>
#include <stdio.h>
#include <iostream>
#include "logbook.h"

extern "C" {

  const std::string fileName = "test_file.txt";

  std::string getFileText() {
    std::ifstream reader(fileName);
    std::string text;
    std::string line;

    while (std::getline(reader, line)) {
      text += line + "\n";
    }

    reader.close();
    return text;
  }

  void AddMessageWithoutLevelTest() {
    Logbook logbook(fileName, HIGH);
    std::string message = "message";
    std::string log = " HIGH  message";

    logbook.AddMessage(message);
    std::string fileText = getFileText();
    bool isContain = fileText.find(log) != std::string::npos;

    assert(isContain);
    remove(fileName.c_str());
  }

  void AddMessageWithLowerLevelTest() {
    Logbook logbook(fileName, HIGH);
    std::string message = "message";

    logbook.AddMessage(message, LOW);
    logbook.AddMessage(message, MEDIUM);
    std::string fileText = getFileText();
    bool isFileEmpty = fileText.empty();

    assert(isFileEmpty);
    remove(fileName.c_str());
  }

  void AddMessageManyTimesTest() {
    Logbook logbook(fileName, LOW);
    std::string message1 = "message1";
    std::string message2 = "message2";
    std::string log1 = "MEDIUM message1";
    std::string log2 = " HIGH  message2";

    logbook.AddMessage(message1, MEDIUM);
    logbook.AddMessage(message2, HIGH);
    std::string fileText = getFileText();
    bool isContain1 = fileText.find(log1) != std::string::npos;
    bool isContain2 = fileText.find(log2) != std::string::npos;
    bool isContainAll = isContain1 && isContain2;

    assert(isContainAll);
    remove(fileName.c_str());
  }

  void DefaultLevelChangeTest() {
    Logbook logbook(fileName, HIGH);
    
    logbook.SetDefaultLevel(LOW);
    Level curLevel = logbook.GetDefaultLevel();

    assert(curLevel == LOW);
    remove(fileName.c_str());
  }

  int main() {
    remove(fileName.c_str());

    AddMessageWithoutLevelTest();
    AddMessageWithLowerLevelTest();
    AddMessageManyTimesTest();
    
    DefaultLevelChangeTest();

    std::cout << "Tests passed" << std::endl;
  }

}