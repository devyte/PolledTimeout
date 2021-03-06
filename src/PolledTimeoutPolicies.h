
#ifndef __POLLEDTIMEOUTYIELDPOLICIES_H__
#define __POLLEDTIMEOUTYIELDPOLICIES_H__


/*
 PolledTimeoutPolicies.h - Policy classes meant for use with polledTimeout
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

#include <PolledTimeoutTemplate.h>

#include <core_esp8266_features.h>

namespace YieldPolicy
{

  struct DoNothing
  {
    static void execute() {}
  };


  template <unsigned long delayMs>
  struct YieldAndDelayMs
  {
    static void execute() {delay(delayMs);} //yield is implied in delay
  };

} //YieldPolicy
