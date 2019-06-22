//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2019 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#include "JoyHatMap.hxx"

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
JoyHatMap::JoyHatMap(void)
{
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void JoyHatMap::add(const Event::Type event, const JoyHatMapping& mapping)
{
  myMap[mapping] = event;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void JoyHatMap::add(const Event::Type event, const EventMode mode,
                    const int button, const int hat, const JoyHat hdir)
{
  add(event, JoyHatMapping(mode, button, hat, hdir));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void JoyHatMap::erase(const JoyHatMapping& mapping)
{
  myMap.erase(mapping);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void JoyHatMap::erase(const EventMode mode,
                      const int button, const int hat, const JoyHat hdir)
{
  erase(JoyHatMapping(mode, button, hat, hdir));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Event::Type JoyHatMap::get(const JoyHatMapping& mapping) const
{
  auto find = myMap.find(mapping);
  if (find != myMap.end())
    return find->second;

  // try without button as modifier
  JoyHatMapping m = mapping;

  m.button = JOY_CTRL_NONE;

  find = myMap.find(m);
  if (find != myMap.end())
    return find->second;

  return Event::Type::NoType;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
Event::Type JoyHatMap::get(const EventMode mode,
                           const int button, const int hat, const JoyHat hdir) const
{
  return get(JoyHatMapping(mode, button, hat, hdir));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool JoyHatMap::check(const JoyHatMapping & mapping) const
{
  auto find = myMap.find(mapping);

  return (find != myMap.end());
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
bool JoyHatMap::check(const EventMode mode,
                      const int button, const int hat, const JoyHat hdir) const
{
  return check(JoyHatMapping(mode, button, hat, hdir));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string JoyHatMap::getDesc(const Event::Type event, const JoyHatMapping & mapping) const
{
  ostringstream buf;

  // hat description
  if (mapping.hat != JOY_CTRL_NONE)
  {
    buf << "/H" << mapping.hat;
    switch (mapping.hdir)
    {
      case JoyHat::UP:    buf << "/up";    break;
      case JoyHat::DOWN:  buf << "/down";  break;
      case JoyHat::LEFT:  buf << "/left";  break;
      case JoyHat::RIGHT: buf << "/right"; break;
      default:                             break;
    }
  }


  return buf.str();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string JoyHatMap::getDesc(const Event::Type event, const EventMode mode,
                          const int button, const int hat, const JoyHat hdir) const
{
  return getDesc(event, JoyHatMapping(mode, button, hat, hdir));
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string JoyHatMap::getEventMappingDesc(const int stick, const Event::Type event, const EventMode mode) const
{
  ostringstream buf;

  for (auto item : myMap)
  {
    if (item.second == event && item.first.mode == mode)
    {
      if (buf.str() != "")
        buf << ", ";
      buf << "J" << stick << getDesc(event, item.first);
    }
  }
  return buf.str();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
JoyHatMap::JoyHatMappingArray JoyHatMap::getEventMapping(const Event::Type event, const EventMode mode) const
{
  JoyHatMappingArray map;

  for (auto item : myMap)
    if (item.second == event && item.first.mode == mode)
      map.push_back(item.first);

  return map;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
string JoyHatMap::saveMapping(const EventMode mode) const
{
  ostringstream buf;

  for (auto item : myMap)
  {
    if (item.first.mode == mode)
    {
      if (buf.str() != "")
        buf << "|";
      buf << item.second << ":" << item.first.button << "," <<
        item.first.hat << "," << int(item.first.hdir);
    }
  }
  return buf.str();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
int JoyHatMap::loadMapping(string & list, const EventMode mode)
{
  // Since istringstream swallows whitespace, we have to make the
  // delimiters be spaces
  std::replace(list.begin(), list.end(), '|', ' ');
  std::replace(list.begin(), list.end(), ':', ' ');
  std::replace(list.begin(), list.end(), ',', ' ');
  istringstream buf(list);
  int event, button, hat, hdir, i = 0;

  while (buf >> event && buf >> button && buf >> hat && buf >> hdir && ++i)
    add(Event::Type(event), EventMode(mode), button, hat, JoyHat(hdir));

  return i;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void JoyHatMap::eraseMode(const EventMode mode)
{
  for (auto item = myMap.begin(); item != myMap.end();)
    if (item->first.mode == mode) {
      auto _item = item++;
      erase(_item->first);
    }
    else item++;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
void JoyHatMap::eraseEvent(const Event::Type event, const EventMode mode)
{
  for (auto item = myMap.begin(); item != myMap.end();)
    if (item->second == event && item->first.mode == mode) {
      auto _item = item++;
      erase(_item->first);
    }
    else item++;
}
