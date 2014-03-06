#ifndef BFILEPARSER_HH
#define BFILEPARSER_HH

#include <string>
#include <ostream>
#include <istream>
#include <vector>

#include "BFileItem.hh"

class BFileParser
{
public:
  BFileParser();
  bool loadDef( const std::string& name);
  bool loadDef( std::istream& is);
  bool loadFile( const std::string& name);
  bool loadFile( std::istream& is);
  bool saveFile( const std::string& name);
  bool saveFile( std::ostream& os);

  void printDef( std::ostream& os) const;
  char separator() const;
  void setSeparator( const char c);
private:
  std::vector<BFileItem> _items;
  char                   _separator;
  bool                   _debug;
};

#endif
