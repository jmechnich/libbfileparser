#ifndef BFILEITEM_HH
#define BFILEITEM_HH

#include <string>
#include <ostream>

class BFileItem
{
public:
  BFileItem();
  ~BFileItem();
  
  void print( std::ostream& os) const;
  
  unsigned long  _offset;
  unsigned long  _length;
  std::string    _type;
  std::string    _name;
  std::string    _extra_data;
  char* _data;
};

#endif
