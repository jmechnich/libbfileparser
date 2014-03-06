#include "BFileParser.hh"

#include <fstream>
#include <sstream>
#include <iostream>

BFileParser::BFileParser()
        : _separator(';')
        , _debug( false)
{}

bool
BFileParser::loadDef( const std::string& name)
{
  std::ifstream is(name.c_str());
  return loadDef( is);
}

bool
BFileParser::loadDef( std::istream& is)
{
  if(!is.good())
      return false;
  
  _items.clear();
  std::string buf;
  std::vector<std::string> list;
  while( is.good())
  {
    list.clear();
    std::getline( is, buf);
    size_t lastpos=0, pos=0;
    while( (pos = buf.find(_separator,lastpos)) != std::string::npos)
    {
      list.push_back(buf.substr( lastpos, pos-lastpos));
      lastpos=pos+1;
    }
    if( lastpos < buf.size())
    {
      list.push_back(buf.substr( lastpos, pos-lastpos));
    }
    if( list.size() < 4)
    {
      break;
    }
    
    BFileItem item;
    std::istringstream iss;
    std::vector<std::string>::const_iterator it = list.begin();
    iss.clear(); iss.str(*(it++));
    iss >> item._offset;
    iss.clear();
    iss.str(*(it++));
    iss >> item._length;
    item._type = *(it++);
    item._name = *(it++);
    if( it != list.end())
    {
      std::ostringstream oss;
      oss << *(it++);
      while( it != list.end())
      {
        oss << _separator << *(it++);
      }
      item._extra_data = oss.str();
    }
                
    _items.push_back( item);
  }
  
  if( _debug)
      printDef(std::cout);
  
  return true;
}

bool
BFileParser::loadFile( const std::string& name)
{
  std::ifstream is(name.c_str());
  if(!is.good())
      return false;
  
  return loadFile( is);
}

bool
BFileParser::loadFile( std::istream& is)
{
  if(!is.good()) return false;
  
  if( _items.size() == 0)
  {
    return false;
  }

  size_t size_expected=0;
  std::vector<BFileItem>::const_iterator cit=_items.begin();
  for( ; cit!=_items.end(); ++cit)
  {
    size_expected+=cit->_length;
  }
  
  if( _debug)
      std::cout << "Expected size: " << size_expected << std::endl;

  size_t size_delivered=0;
  std::vector<BFileItem>::iterator it=_items.begin();
  for( it=_items.begin(); it!=_items.end(); ++it)
  {
    if(it->_data)
        delete[] it->_data;
    it->_data = new char[it->_length];
    is.read( it->_data, it->_length);
    size_delivered += it->_length;
    if(!is.good()) return false;
  }
  
  if( _debug)
      std::cout << "Delivered size: " << size_delivered << std::endl;

  if( size_delivered != size_expected)
      return false;
  
  if( _debug)
      printDef( std::cout);
  
  return true;
}

bool
BFileParser::saveFile( const std::string& name)
{
  std::ofstream os(name.c_str());
  if(!os.good())
      return false;
  return saveFile( os);
}

bool
BFileParser::saveFile( std::ostream& os)
{
  if(!os.good()) return false;
  
  if( _items.size() == 0)
  {
    return false;
  }

  size_t size_delivered=0;
  std::vector<BFileItem>::const_iterator it=_items.begin();
  for( it=_items.begin(); it!=_items.end(); ++it)
  {
    os.write( it->_data, it->_length);
    size_delivered += it->_length;
    if(!os.good()) return false;
  }
  
  if( _debug)
      std::cout << "Delivered size: " << size_delivered << std::endl;

  if( _debug)
      printDef( std::cout);
  
  return true;
}

void
BFileParser::printDef( std::ostream& os) const
{
  os << "Number of items: " << _items.size() << std::endl << std::endl;
  std::vector<BFileItem>::const_iterator it=_items.begin();
  for( ; it!=_items.end(); ++it)
  {
    it->print(os);
    os << std::endl;
  }
}
