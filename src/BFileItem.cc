#include "BFileItem.hh"

BFileItem::BFileItem()
        : _offset( 0)
        , _length( 0)
        , _data( 0)
{}

BFileItem::~BFileItem()
{
  if(_data) delete[] _data;
}

void
BFileItem::print(std::ostream& os) const
{
  os << "Offset: " << _offset << std::endl;
  os << "Length: " << _length << std::endl;
  os << "Type  : " << _type << std::endl;
  os << "Name  : " << _name << std::endl;
  os << "Extra data: " << _extra_data << std::endl;
  if( _data)
  {
    os << "Data: '";
    os.write( _data, _length);
    os << "'" << std::endl;
  }
}

