//
// Created by F.Moitzi on 02.12.2021.
//

#ifndef ISING_SETTINGS_HPP
#define ISING_SETTINGS_HPP

#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <initializer_list>

namespace ising {


  class Config {

    /**
     * everything is stored internally as std::strings
     *  usually read from a configuration file
     */
    using prop_map = std::map<std::string, std::string>;

    prop_map props;

  public:

    /**
     * example constructor. Normally I have a method to read the
     * values in from a file
     */
    Config(std::initializer_list<std::pair<std::string, std::string>>
    list) {
      for (const auto &p: list)
        props[p.first] = p.second;
    }

    // values are converted as they are requested to whatever types
    // they need to be. Also a default may be given in case the value
    // was missing from the configuration file
    template<typename T>
    T get(const std::string &s, const T &dflt = T()) const {
      auto found = props.find(s);

      if (found == props.end())
        return dflt;

      T t;
      std::istringstream(found->second) >> std::boolalpha >> t;
      return t;
    }

    // std::strings need special handling (no conversion)
    std::string get(const std::string &s, const std::string &dflt = "") const {
      auto found = props.find(s);
      return found != props.end() ? found->second : dflt;
    }

  };


}

/*
int main()
{
  const config cfg =
      {
      {"OutputFile", "/tmp/out.txt"}
      , {"CaptureFPS", "25.0"}
      , {"RetryDelaySeconds", "5"}
      };

  std::string s;
  float f;
  int i;

  s = cfg.get("OutputFile");
  f = cfg.get<float>("CaptureFPS");
  i = cfg.get<int>("RetryDelaySeconds");

  std::cout << "s: " << s << '\n';
  std::cout << "f: " << f << '\n';
  std::cout << "i: " << i << '\n';
}
 */


#endif //ISING_SETTINGS_HPP
