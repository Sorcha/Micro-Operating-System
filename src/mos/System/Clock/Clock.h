/*
 * Clock.h
 *
 *  Created on: Aug 8, 2011
 *      Author: DVD
 */

#pragma once

#include "SystemTypes.h"
#include "Debug.h"
#include "List.h"

///
///	The types of clock events that are generated by the system.
///
enum ClockEventType{EVENT_TYPE_CLOCK, EVENT_TYPE_PERIPHERALS_CLOCK};


///
///	The function prototype to be called when an clock event occurs.
///
typedef void (*ClockEventFunction)(U16 oldClock, U16 newClock);



///
///	An instance that represents an hook to be connected to the clock event system.
///
class ClockChangeListener
{
	///
	///	Which clock event type this listener should hook.
	///
	ClockEventType _type;

	///
	///	The function to be called when an clock event occurs.
	///
	ClockEventFunction _onClockChange;

	///
	///	A general purpose node.
	///
	Node<ClockChangeListener> _node;


public:
	ClockChangeListener(ClockEventType type,ClockEventFunction onClockChange ) : _type(type),
																				 _onClockChange(onClockChange)
	{
		DebugAssertNotNull(_onClockChange);
	}

	///
	///	Returns the event type that this listener is sensible to.s
	///
	ClockEventType GetEventType(){return _type;}

	///
	///	Returns the function to be called when an event is triggered.
	///
	ClockEventFunction GetEventFunction(){return _onClockChange;}

	///
	///	Returns a general purpose node, used to save this instance in the hook list.
	///
	Node<ClockChangeListener>& GetNode(){return _node;}

};

///
///	This class is responsible for all clock frequency adjustments.
///		WARNING: This class is not thread-safe.
///
class Clock
{
	///
	///	An list of all listeners registered on clock events.
	///
	static List<ClockChangeListener> _hooks;

	///
	///	Triggers all listeners registered for the @eventType.
	///
	static void TriggerAllEvents(ClockEventType eventType,U16 oldClock, U16 newClock);

public:

	///
	///	Adds an event listener to the clock events;
	///
	static void SetEventListener(ClockChangeListener listener);
	///
	///	Returns the crystal frequency.
	///
	PORT_SPECIFIC static U16 GetCrystalFrequency();

	///
	///	Returns the current clock frequency.
	///
	PORT_SPECIFIC static U16 GetClockFrequency();

	///
	///	Returns the current peripherals clock frequency.
	///
	PORT_SPECIFIC static U16 GetPeripheralsClockFrequency();

	///
	///	Sets the clock frequency to @newClock, this methods returns true if the clock
	///	was successfully change, false otherwise. This method should trigger a clock change event.
	///		NOTE: @newClock value must be in MHz.
	///
	PORT_SPECIFIC static bool SetClockFrequency(U16 newClock);

	///
	///	Sets the peripherals clock frequency to @newClock, this methods returns true if the clock
	///	was successfully change, false otherwise. This method should trigger a clock change event.
	///		NOTE: @newClock value must be in MHz.
	///
	PORT_SPECIFIC static bool SetPeripheralsClockFrequency(U16 newClock);

	///
	///	Sets the clock frequency to its maximum value.
	///
	PORT_SPECIFIC static void SetClockAtMaxFrequency();

	///
	///	Sets the peripherals clock frequency to its maximum value.
	///
	PORT_SPECIFIC static void SetClockAtMinFrequency();

	///
	///	Sets the clock frequency to its minimum value.
	///
	PORT_SPECIFIC static bool SetPeripheralsClockAtMaxFrequency();

	///
	///	Sets the peripherals clock frequency to its minimum value.
	///
	PORT_SPECIFIC static bool SetPeripheralsClockAtMinFrequency();
};
