# PolledTimeout

Class in C++ that encapsulates checking that a time window has elapsed.

## Introduction

The logic is split into several separate policy clases in addition to the main logic class:
- TimeSource: represents a source of time. Examples of a time source are: reading Real Time Clock hardware, calling some time function like POXIX's time()/gettimeofday() or Arduino's millis(), reading a hardware timer like a CPU clock counter. The unit of the time source is part of this policy as well.
- TimeUnit: represents the unit of time to be used by the PolledTimeout class. This policy class converts the unit of the time source to the unit that the polled timeout class offers. The internals are mostly constexpr methods. All math is integer to keep it simple.
- YieldPolicy: implements what to do every time the time gets polled. Example actions are: nothing, yield() context, sleep(), delay(), etc.
- PolledTimeout: the main class to use. This is a template class that builds the needed logic to poll a time. It requires policy classes as template arguments and a timeout value as a constructor argument.

In addition, there is one template bool parameter to define at compile time whether the class's logic will work as a one-shot poll (i.e.: once expired it must be manually reset) or periodic poll (i.e.: once expired the internals automatically reset).
Of note, the periodic logic is implemented with:
- the assurance that there is zero drift, so if the timeout value is e.g.: 10, the timouts are assured to be at T0 + i*10
- the possibility of jitter. Given that this is a polled implementation, the time of polling can't be assured and is in fact platform-dependant. That means that, in the best case, a poll could be done at exactly the timeout time, but due to the involved calculations, the returned decision will be just a few cycles/instructions later. In addition, for multitasking environments, the OS may choose to take the CPU away from the polling thread during the actual calculation.

## Why

The logic that this class encapsulates is a classic: get some initial time marker T0, then keep polling until some timeout has elapsed.
Example:

    unsigned int start = millis();
    unsigned int timeout = 1000; //ms
    while(millis() - start < timeout) //1-shot
    {
      trySomething();
    }

And yet the number of developers who get the above code wrong is staggering.

## Example use:

    using oneShotMs = polledTimeout::timeoutTemplate<false, YieldPolicy::DoNothing, TimePolicy::TimeMillis>;
    oneShotMS timeout(1000); //1-second one-shot

    while(!timeout)
    {
      trySomething();
    }

## Related links
[PolledTimeout at ESP8266's Arduino repo](https://github.com/esp8266/Arduino/blob/master/cores/esp8266/PolledTimeout.h)


## Disclaimers
This is a work in progress, i.e.: not a finished implementation. 
There are zero guarantees about whether this works as advertised, or even whether this fits your needs. If it works for you, yay. If not, you're free to adapt it.

# Contribution Policy
This is primarily a personal project.

If you want to contribute, sure, I'll take a look at your PR.

If you want to discuss and work together, sure, open an issue.

If you want me to use time to help you, or to fix your specific use case, you're in the wrong place.
