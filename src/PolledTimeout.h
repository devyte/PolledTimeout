#ifndef __POLLEDTIMEOUT_H__
#define __POLLEDTIMEOUT_H__


/*
 PolledTimeout.h - Encapsulation of a polled Timeout
 Copyright (c) 2018 Daniel Salazar. All rights reserved.
 This file is part of the esp8266 core for Arduino environment.
 This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.
 This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 Lesser General Public License for more details.
 You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __POLLEDTIMEOUT_H__
#define __POLLEDTIMEOUT_H__



#include <PolledTimeoutPolicies.h>

namespace TimePolicy
{

  using TimeMillis = TimeUnit< TimeSourcePolicy::TimeSourceMillis, 1000 >;

} //TimePolicy



namespace PolledTimeout
{
  //Construction of types using the policies

  // legacy type names, deprecated (unit is milliseconds)
  using oneShot = TimeoutTemplate<false, YieldPolicy::DoNothing, TimePolicy::TimeMillis>;
  using periodic = TimeoutTemplate<true, YieldPolicy::DoNothing, TimePolicy::TimeMillis>;

  // standard versions (based on millis())
  // timeMax() is 49.7 days ((2^32)-2 ms)
  using oneShotMs = TimeoutTemplate<false, YieldPolicy::DoNothing, TimePolicy::TimeMillis>;
  using periodicMs = TimeoutTemplate<true, YieldPolicy::DoNothing, TimePolicy::TimeMillis>;

} //PolledTimeout





#include <PolledTimeoutPolicies_esp8266.h>

namespace TimePolicy
{
  
  using TimeFastMillis = TimeUnit< TimeSourcePolicy::TimeSourceCycles,       1000 >;
  using TimeFastMicros = TimeUnit< TimeSourcePolicy::TimeSourceCycles,    1000000 >;
  using TimeFastNanos  = TimeUnit< TimeSourcePolicy::TimeSourceCycles, 1000000000 >;

} //TimePolicy




namespace PolledTimeout
{
  //Construction of types using the policies


  // Time policy based on esp_get_cycle_count(), and intended to be called very often:
  // "Fast" versions sacrifices time range for improved precision and reduced execution time (by 86%)
  // (cpu cycles for ::expired(): 372 (millis()) vs 52 (esp_get_cycle_count()))
  // timeMax() values:
  // Ms: max is 26843       ms (26.8  s)
  // Us: max is 26843545    us (26.8  s)
  // Ns: max is  1073741823 ns ( 1.07 s)
  // (time policy based on esp_get_cycle_count() is intended to be called very often)

  using oneShotFastMs = TimeoutTemplate<false, YieldPolicy::DoNothing, TimePolicy::TimeFastMillis>;
  using periodicFastMs = TimeoutTemplate<true, YieldPolicy::DoNothing, TimePolicy::TimeFastMillis>;
  
  using oneShotFastUs = TimeoutTemplate<false, YieldPolicy::DoNothing, TimePolicy::TimeFastMicros>;
  using periodicFastUs = TimeoutTemplate<true, YieldPolicy::DoNothing, TimePolicy::TimeFastMicros>;

  using oneShotFastNs = TimeoutTemplate<false, YieldPolicy::DoNothing, TimePolicy::TimeFastNanos>;
  using periodicFastNs = TimeoutTemplate<true, YieldPolicy::DoNothing, TimePolicy::TimeFastNanos>;

} //polledTimeout


/* A 1-shot timeout that auto-yields when in CONT can be built as follows:
 * using oneShotYieldMs = PolledTimeout::TimeoutTemplate<false, PolledTimeout::YieldPolicy::YieldOrSkip>;
 *
 * Other policies can be implemented by the user, e.g.: simple yield that panics in SYS, and the polledTimeout types built as needed as shown above, without modifying this file.
 */




#endif
