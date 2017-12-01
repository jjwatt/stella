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
// Copyright (c) 1995-2017 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef SOUND_NULL_HXX
#define SOUND_NULL_HXX

#include "bspf.hxx"
#include "Sound.hxx"
#include "OSystem.hxx"

/**
  This class implements a Null sound object, where-by sound generation
  is completely disabled.

  @author Stephen Anthony
*/
class SoundNull : public Sound
{
  public:
    /**
      Create a new sound object.  The init method must be invoked before
      using the object.
    */
    SoundNull(OSystem& osystem) : Sound(osystem)
    {
      myOSystem.logMessage("Sound disabled.\n", 1);
    }

    /**
      Destructor
    */
    virtual ~SoundNull() = default;

  public:
    /**
      Enables/disables the sound subsystem.

      @param state  True or false, to enable or disable the sound system
    */
    void setEnabled(bool state) override { }

    /**
      Initializes the sound device.  This must be called before any
      calls are made to derived methods.
    */
    void open() override { }

    /**
      Should be called to close the sound device.  Once called the sound
      device can be started again using the initialize method.
    */
    void close() override { }

    /**
      Set the mute state of the sound object.  While muted no sound is played.

      @param state Mutes sound if true, unmute if false
    */
    void mute(bool state) override { }

    /**
      Reset the sound device.
    */
    void reset() override { }

    /**
      Sets the volume of the sound device to the specified level.  The
      volume is given as a percentage from 0 to 100.  Values outside
      this range indicate that the volume shouldn't be changed at all.

      @param percent The new volume percentage level for the sound device
    */
    void setVolume(Int32 percent) override { }

    /**
      Adjusts the volume of the sound device based on the given direction.

      @param direction  Increase or decrease the current volume by a predefined
                        amount based on the direction (1 = increase, -1 =decrease)
    */
    void adjustVolume(Int8 direction) override { }

  private:
    // Following constructors and assignment operators not supported
    SoundNull() = delete;
    SoundNull(const SoundNull&) = delete;
    SoundNull(SoundNull&&) = delete;
    SoundNull& operator=(const SoundNull&) = delete;
    SoundNull& operator=(SoundNull&&) = delete;
};

#endif
