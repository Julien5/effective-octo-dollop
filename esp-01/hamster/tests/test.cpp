#include <iostream>
#include "parse.h"
#include "eeprom.h"
#include "nstring.h"
#include "clock.h"
#include "tickscounter.h"
#include "ui.h"

#include <vector>
#include <algorithm>

#include "application.h"

int display_exit_code(int exitcode) {
  if (exitcode!=0)
    std::cout << "bad.\n";
  else
    std::cout << "good.\n";
  if (exitcode!=0)
    exit(exitcode);
  return exitcode;
}

std::vector<std::string> args(int argc, char ** argv) {
  return std::vector<std::string>(argv,argv+argc);
}

int main(int argc, char ** argv) {
  std::cout << "test\n";
  const auto A = args(argc,argv);
  if (std::find(A.begin(),A.end(),std::string("main"))==A.end()) {
    display_exit_code(eeprom::test());
    //display_exit_code(parse::test());
    //display_exit_code(nstring::test());
    //display_exit_code(Clock::test());
    //display_exit_code(tickscounter::test());
    //display_exit_code(ui::test());
  } else {
    application::setup();
    while(true) {
      application::loop();
    }
  }
  return 0;
}