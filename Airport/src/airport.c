/**************************************************************************
 File name:  airport.c
 Author:     Ellysia Li
 Date:		   Oct 30, 2019
 Class:		   CS300
 Assignment: Airport Simulator
 Purpose:    Implementation of an Airport Simulator
 *************************************************************************/

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/airport.h"
#include "../../GenericDynamicList/include/list.h"
#include "../../GenericDynamicPriorityQ/include/pqueue.h"
#include "../../GenericDynamicQ/include/queue.h"

char gszAirportErrors[NUMBER_OF_AIRPORT_ERRORS][MAX_ERROR_AIRPORT_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszAirportErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	airportCreate

 Description: Initializes the airport queues and the statistic values

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportCreate (AirportPtr psAirport)
{
	int i;
	if (NULL == psAirport)
	{
		processError ("airportCreate", ERROR_NO_AIRPORT_CREATE);
	}
	pqueueCreate (&psAirport->sLandingQueue);
	queueCreate (&psAirport->sTakeoffQueue);

	for (i = 0; i < NUMBER_OF_RUNWAYS; i++)
	{
		psAirport->ezRunways[i] = EMPTY;
	}

	psAirport->clock = 0;

	psAirport->sAirportStats.numCrashes =
			psAirport->sAirportStats.numEmergencyLandings =
					psAirport->sAirportStats.numLandings =
							psAirport->sAirportStats.numTakeoffs =
									psAirport->sAirportStats.totalFlyingTimeRemaining =
											psAirport->sAirportStats.totalLandingTime =
													psAirport->sAirportStats.totalTakeoffTime = 0;
}

/**************************************************************************
 Function: 	 	airportTerminate

 Description: Terminates the airport queues and the statistic values

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportTerminate (AirportPtr psAirport)
{
	int i;
	if (NULL == psAirport)
	{
		processError ("airportTerminate", ERROR_NO_AIRPORT_TERMINATE);
	}
	pqueueTerminate (&psAirport->sLandingQueue);
	queueTerminate (&psAirport->sTakeoffQueue);

	for (i = 0; i < NUMBER_OF_RUNWAYS; i++)
	{
		psAirport->ezRunways[i] = EMPTY;
	}

	psAirport->clock = 0;

	psAirport->sAirportStats.numCrashes =
			psAirport->sAirportStats.numEmergencyLandings =
					psAirport->sAirportStats.numLandings =
							psAirport->sAirportStats.numTakeoffs =
									psAirport->sAirportStats.totalFlyingTimeRemaining =
											psAirport->sAirportStats.totalLandingTime =
													psAirport->sAirportStats.totalTakeoffTime = 0;
}

/**************************************************************************
 Function: 	 	airportLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void airportLoadErrorMessages ()
{
	queueLoadErrorMessages ();
	LOAD_AIRPORT_ERRORS
}

/**************************************************************************
 Function: 	 	airportLandingQSize

 Description: Returns the size of the landing queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	Size of the landing queue
 *************************************************************************/
int airportLandingQSize (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportLandingQSize", ERROR_INVALID_AIRPORT);
	}
	return pqueueSize (&psAirport->sLandingQueue);
}

/**************************************************************************
 Function: 	 	airportTakeoffQSize

 Description: Returns the size of the takeoff queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	Size of the takeoff queue
 *************************************************************************/
int airportTakeoffQSize (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportTakeoffQSize", ERROR_INVALID_AIRPORT);
	}
	return queueSize (&psAirport->sTakeoffQueue);
}

/**************************************************************************
 Function: 	 	airportQsAreEmpty

 Description: Checks if both queues are empty

 Parameters:	psAirport - pointer to the airport

 Returned:	 	True if both are empty; false otherwise
 *************************************************************************/
bool airportQsAreEmpty (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportQsAreEmpty", ERROR_INVALID_AIRPORT);
	}
	return 0 == pqueueSize (&psAirport->sLandingQueue) &&
			   0 == queueSize (&psAirport->sTakeoffQueue);
}

/**************************************************************************
 Function: 	 	airportAddLandingPlane

 Description: Adds a landing plane to the landing queue

 Parameters:	psAirport - pointer to the airport
 	 	 	 	 	 	 	fuel 		  - fuel (time) remaining for plane

 Returned:	 	None
 *************************************************************************/
void airportAddLandingPlane (AirportPtr psAirport, const int fuel)
{
	if (NULL == psAirport)
	{
		processError ("airportAddLandingPlane", ERROR_INVALID_AIRPORT);
	}
	pqueueEnqueue (&psAirport->sLandingQueue, &psAirport->clock, sizeof (int),
																															 fuel);
}

/**************************************************************************
 Function: 	 	airportAddTakeoffPlane

 Description: Adds a takeoff plane to the takeoff queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportAddTakeoffPlane (AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportAddTakeoffPlane", ERROR_INVALID_AIRPORT);
	}
	queueEnqueue (&psAirport->sTakeoffQueue, &psAirport->clock, sizeof (int));
}

/**************************************************************************
 Function: 	 	airportLandPlane

 Description: Land a plane from the landing queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportLandPlane (AirportPtr psAirport)
{
	int time, fuel;
	if (NULL == psAirport)
	{
		processError ("airportLandPlane", ERROR_INVALID_AIRPORT);
	}
	if (pqueueIsEmpty (&psAirport->sLandingQueue))
	{
		processError ("airportLandPlane", ERROR_EMPTY_AIRPORT);
	}
	pqueueDequeue (&psAirport->sLandingQueue, &time, sizeof (int), &fuel);

	if (0 == fuel)
	{
		psAirport->sAirportStats.numEmergencyLandings++;
		airportUpdateRunwayStatus (psAirport, EMERGENCY);
	}
	else
	{
		airportUpdateRunwayStatus (psAirport, LANDING);
	}
	psAirport->sAirportStats.numLandings++;
	psAirport->sAirportStats.totalFlyingTimeRemaining += fuel;
	psAirport->sAirportStats.totalLandingTime += psAirport->clock - time;
}

/**************************************************************************
 Function: 	 	airportTakeoffPlane

 Description: Land a plane from the landing queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportTakeoffPlane (AirportPtr psAirport)
{
	int time;
	if (NULL == psAirport)
	{
		processError ("airportTakeoffPlane", ERROR_INVALID_AIRPORT);
	}
	if (queueIsEmpty (&psAirport->sTakeoffQueue))
	{
		processError ("airportTakeoffPlane", ERROR_EMPTY_AIRPORT);
	}
	queueDequeue (&psAirport->sTakeoffQueue, &time, sizeof (int));
	psAirport->sAirportStats.numTakeoffs++;
	psAirport->sAirportStats.totalTakeoffTime += psAirport->clock - time;
	airportUpdateRunwayStatus (psAirport, TAKEOFF);
}

/**************************************************************************
 Function: 	 	airportCrashPlane

 Description: Crash a plane from the landing queue

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportCrashPlane (AirportPtr psAirport)
{
	int time, fuel;
	if (NULL == psAirport)
	{
		processError ("airportCrashPlane", ERROR_INVALID_AIRPORT);
	}
	if (pqueueIsEmpty (&psAirport->sLandingQueue))
	{
		processError ("airportCrashPlane", ERROR_EMPTY_AIRPORT);
	}
	pqueueDequeue (&psAirport->sLandingQueue, &time, sizeof (int), &fuel);
	psAirport->sAirportStats.numCrashes++;
}

/**************************************************************************
 Function: 	 	airportAssignRunways

 Description: Assign planes to the runways until runways full or queues empty

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportAssignRunways (AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("airportAssignRunways", ERROR_INVALID_AIRPORT);
	}
	while (airportRunwayHasOpen (psAirport) && !airportQsAreEmpty (psAirport))
	{
		if (airportHasEmergency (psAirport)
				|| pqueueSize (&psAirport->sLandingQueue)
						>= queueSize (&psAirport->sTakeoffQueue))
		{
			airportLandPlane (psAirport);
		}
		else
		{
			airportTakeoffPlane (psAirport);
		}
	}
}

/**************************************************************************
 Function: 	 	airportUpdateRunwayStatus

 Description: Updates the first empty runway to the appropriate status

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
extern void airportUpdateRunwayStatus (AirportPtr psAirport, int status)
{
	int i = 0;
	if (NULL == psAirport)
	{
		processError ("airportUpdateRunwayStatus", ERROR_INVALID_AIRPORT);
	}
	if (!airportRunwayHasOpen (psAirport))
	{
		processError ("airportUpdateRunwayStatus", ERROR_FULL_RUNWAY);
	}

	while (EMPTY != airportGetRunwayStatus (psAirport, i))
	{
		i++;
	}
	psAirport->ezRunways[i] = status;
}

/**************************************************************************
 Function: 	 	airportResetRunways

 Description: Resets all runways to empty

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
extern void airportResetRunways (AirportPtr psAirport)
{
	int i;
	if (NULL == psAirport)
	{
		processError ("airportResetRunways", ERROR_INVALID_AIRPORT);
	}
	for (i = 0; i < NUMBER_OF_RUNWAYS; i++)
	{
		psAirport->ezRunways[i] = EMPTY;
	}
}

/**************************************************************************
 Function: 	 	airportDecrementFuel

 Description: Decrement fuel in landing planes (and increment airport's clock)

 Parameters:	psAirport - pointer to the airport

 Returned:	 	None
 *************************************************************************/
void airportDecrementFuel (AirportPtr psAirport)
{
	const int DECREMENT = -1;
	if (NULL == psAirport)
	{
		processError ("airportIncrementClock", ERROR_INVALID_AIRPORT);
	}
	psAirport->clock++;
	pqueueChangePriority (&psAirport->sLandingQueue, DECREMENT);
}

/**************************************************************************
 Function: 	 	airportGetRunwayStatus

 Description: Increment/decrement all planes in queues appropriately

 Parameters:	psAirport - pointer to the airport
 	 	 	 	 	 	  number	  - number of the runway to return

 Returned:	 	An int representing the status of the runway
 *************************************************************************/
int airportGetRunwayStatus (const AirportPtr psAirport, const int number)
{
	if (NULL == psAirport)
	{
		processError ("airportGetRunwayStatus", ERROR_INVALID_AIRPORT);
	}
	return psAirport->ezRunways[number];
}

/**************************************************************************
 Function: 	 	airportHasEmergency

 Description: Checks if a landing plane needs an emergency landing

 Parameters:	psAirport - pointer to the airport

 Returned:	 	True if a landing plane has no fuel; false otherwise
 *************************************************************************/
bool airportHasEmergency (const AirportPtr psAirport)
{
	int time = 0, fuel = 0;
	if (NULL == psAirport)
	{
		processError ("airportHasEmergency", ERROR_INVALID_AIRPORT);
	}
	if (pqueueIsEmpty (&psAirport->sLandingQueue))
	{
		return false;
	}
	else
	{
		pqueuePeek (&psAirport->sLandingQueue, &time, sizeof (int), &fuel);
		return 0 == fuel;
	}
}

/**************************************************************************
 Function: 	 	airportRunwayHasOpen

 Description: Checks if at least one runway is empty/open

 Parameters:	psAirport - pointer to the airport

 Returned:	 	True if a runway is open; false otherwise
 *************************************************************************/
bool airportRunwayHasOpen (const AirportPtr psAirport)
{
	const int THIRD = 2;
	if (NULL == psAirport)
	{
		processError ("airportRunwayHasOpen", ERROR_INVALID_AIRPORT);
	}
	return EMPTY == psAirport->ezRunways[THIRD];
}

/**************************************************************************
 Function: 	 	getAverageLandingTime

 Description: Return the average landing waiting time

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The average landing waiting time
 *************************************************************************/
float getAverageLandingTime (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("getAverageLandingTime", ERROR_INVALID_AIRPORT);
	}
	return (float) psAirport->sAirportStats.totalLandingTime
				 / psAirport->sAirportStats.numLandings;
}

/**************************************************************************
 Function: 	 	getAverageTakeoffTime

 Description: Return the average takeoff waiting time

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The average takeoff waiting time
 *************************************************************************/
float getAverageTakeoffTime (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("getAverageTakeoffTime", ERROR_INVALID_AIRPORT);
	}
	return (float) psAirport->sAirportStats.totalTakeoffTime
				 / psAirport->sAirportStats.numTakeoffs;
}

/**************************************************************************
 Function: 	 	getAverageFlyingTimeRemaining

 Description: Return the average flying time remaining

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The average flying time remaining
 *************************************************************************/
float getAverageFlyingTimeRemaining (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("getAverageFlyingTimeRemaining", ERROR_INVALID_AIRPORT);
	}
	return (float) psAirport->sAirportStats.totalFlyingTimeRemaining
				 / psAirport->sAirportStats.numLandings;}

/**************************************************************************
 Function: 	 	getNumEmergencyLandings

 Description: Return the number of emergency landings

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The number of emergency landings
 *************************************************************************/
int getNumEmergencyLandings (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("getNumEmergencyLandings", ERROR_INVALID_AIRPORT);
	}
	return psAirport->sAirportStats.numEmergencyLandings;
}

/**************************************************************************
 Function: 	 	getNumCrashes

 Description: Return the number of crashes

 Parameters:	psAirport - pointer to the airport

 Returned:	 	The number of crashes
 *************************************************************************/
int getNumCrashes (const AirportPtr psAirport)
{
	if (NULL == psAirport)
	{
		processError ("getNumCrashes", ERROR_INVALID_AIRPORT);
	}
	return psAirport->sAirportStats.numCrashes;
}
