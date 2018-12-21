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
// Copyright (c) 1995-2018 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef OSYSTEM_MACOS_HXX
#define OSYSTEM_MACOS_HXX

#include "OSystem.hxx"

/**
  This class defines UNIX-like OS's (macOS) system-specific settings.

  @author  Mark Grebe, Stephen Anthony
*/
class OSystemMACOS : public OSystem
{
  public:
    /**
      Create a new macOS-specific operating system object
    */
    OSystemMACOS();
    virtual ~OSystemMACOS() = default;

    /**
      Returns the default paths for loading/saving files.
    */
    string defaultSaveDir() const override;
    string defaultLoadDir() const override;

  private:
    // Following constructors and assignment operators not supported
    OSystemMACOS(const OSystemMACOS&) = delete;
    OSystemMACOS(OSystemMACOS&&) = delete;
    OSystemMACOS& operator=(const OSystemMACOS&) = delete;
    OSystemMACOS& operator=(OSystemMACOS&&) = delete;
};

#endif