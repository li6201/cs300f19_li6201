/**************************************************************************
 File name:  list.c
 Author:     Ellysia Li
 Date:		 	 9.24.2019
 Class:		 	 CS300
 Assignment: GenericDynamicList
 Purpose:    Implementation for a dynamic list of generic elements
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "../include/list.h"

char gszListErrors[NUMBER_OF_LIST_ERRORS][MAX_ERROR_LIST_CHARS];

/**************************************************************************
 Function: 	 	processError

 Description: Process the error code passed to this routine

 Parameters:	pszFunctionName - function causing the error
 	 	 	 	 	 	 	errorCode 	    - identifies the stack error

 Returned:	 	None
 *************************************************************************/
static void processError (const char *pszFunctionName, int errorCode)
{
	printf ("Function: %s %s \n ", pszFunctionName, gszListErrors[errorCode]);
	exit (EXIT_FAILURE);
}

/**************************************************************************
 Function: 	 	lstCreate

 Description: Initializes psHead, psTail, psCurrent to NULL (the list is empty)

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstCreate (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstCreate", ERROR_NO_LIST_CREATE);
	}
	psList->psCurrent = psList->psFirst = psList->psLast = NULL;
	psList->numElements = 0;
}

/**************************************************************************
 Function: 	 	lstTerminate

 Description: Sets psHead, psTail, psCurrent to NULL

 Parameters:	psList - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstTerminate (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstTerminate", ERROR_NO_LIST_TERMINATE);
	}

	psList->psCurrent = psList->psFirst;
	while (0 < psList->numElements)
	{
		free (psList->psCurrent->pData);
		psList->psFirst = psList->psCurrent;
		psList->psCurrent = psList->psCurrent->psNext;
		free (psList->psFirst);
		psList->numElements--;
	}
}

/**************************************************************************
 Function: 	 	stkLoadErrorMessages

 Description: Initializes the string of error messages. LOAD_ERRORS is a
 	 	 	 	 	 	 	macro defined in the header file.

 Parameters:	None

 Returned:	 	None
 *************************************************************************/
void lstLoadErrorMessages ()
{
	LOAD_LIST_ERRORS
}

/**************************************************************************
 Function: 	 	lstSize

 Description: Returns the number of elements on the list

 Parameters:	psList - pointer to a list

 Returned:	 	Number of elements in the list
 *************************************************************************/
int lstSize (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstSize", ERROR_INVALID_LIST);
	}
	return (psList->numElements);
}

/**************************************************************************
 Function: 	 	lstIsEmpty

 Description: Checks if the list is empty

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if list is empty otherwise false
 *************************************************************************/
bool lstIsEmpty (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstIsEmpty", ERROR_INVALID_LIST);
	}
	return (0 == psList->numElements);
}

/**************************************************************************
 Function: 	 	lstHasCurrent

 Description: Checks if psCurrent is NULL

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if psCurrent is NULL otherwise false
 *************************************************************************/
bool lstHasCurrent (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstHasCurrent", ERROR_INVALID_LIST);
	}
	// results: Returns true if the current node is not NULL; otherwise, false
	//					is returned
	return (true);
}

/**************************************************************************
 Function: 	 	lstHasNext

 Description: Checks if psCurrent has a successor

 Parameters:	psList - pointer to a list

 Returned:	 	Returns true if psCurrent has a successor otherwise false
 *************************************************************************/
bool lstHasNext (const ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstHasNext", ERROR_INVALID_LIST);
	}
	// results: Returns true if the current node has a successor; otherwise,
	//					 false is returned
	return (true);
}

/**************************************************************************
 Function: 	 	lstPeek

 Description: Looks at the value psCurrent is pointing to in the list

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	 	pBuffer - void pointer used to store the value
 	 	 	 	 	 	 	size    - size of value

 Returned:	 	Pointer to the buffer of the peek value
 *************************************************************************/
void *lstPeek (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstPeek", ERROR_INVALID_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstPeek", ERROR_NULL_PTR);
	}
	if (0 == psList->numElements)
	{
		processError ("lstPeek", ERROR_EMPTY_LIST);
	}
	if (NULL == psList->psCurrent)
	{
		processError ("lstPeek", ERROR_NO_CURRENT);
	}
	memcpy (pBuffer, psList->psCurrent->pData, size);
	return (pBuffer);
}

/**************************************************************************
 Function: 	 	lstPeekNext

 Description: Looks at the value psCurrent's successor is pointing to in the
 list

 Parameters:	psList  - pointer to a list
 	 	 	 	 	 	 	pBuffer - void pointer used to store the value
 	 	 	 	 	 	 	size    - size of value

 Returned:	 	Pointer to the buffer of the peek value
 *************************************************************************/
void *lstPeekNext (const ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstPeekNext", ERROR_INVALID_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstPeekNext", ERROR_NULL_PTR);
	}
	if (0 == psList->numElements)
	{
		processError ("lstPeekNext", ERROR_EMPTY_LIST);
	}
	if (NULL == psList->psCurrent)
	{
		processError ("lstPeekNext", ERROR_NO_CURRENT);
	}
	if (NULL == psList->psCurrent->psNext)
	{
		processError ("lstPeekNext", ERROR_NO_NEXT);
	}
	// requires:  List contains two or more elements and current is not last
	// results:   The data value of current's successor is returned
	return (pBuffer);
}

/**************************************************************************
 Function: 	 	lstFirst

 Description: Changes psCurrent to the first element in the list

 Parameters:	psList  - pointer to a list
						 	pBuffer - void pointer used to store the value
						 	size    - size of value

 Returned:	 	Pointer to the buffer with the first element's value
 *************************************************************************/
void lstFirst (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstFirst", ERROR_INVALID_LIST);
	}
	if (0 == psList->numElements)
	{
		processError ("lstFirst", ERROR_EMPTY_LIST);
	}
	psList->psCurrent = psList->psFirst;
}

/**************************************************************************
 Function: 	 	lstNext

 Description: Changes psCurrent to the next element in the list

 Parameters:	psList  - pointer to a list
							pBuffer - void pointer used to store the value
							size    - size of value

 Returned:	 	Pointer to the buffer with the former psCurrent's value
 *************************************************************************/
void lstNext (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstNext", ERROR_INVALID_LIST);
	}
	if (0 == psList->numElements)
	{
		processError ("lstNext", ERROR_EMPTY_LIST);
	}
	if (NULL == psList->psCurrent)
	{
		processError ("lstNext", ERROR_NO_CURRENT);
	}
	psList->psCurrent = psList->psCurrent->psNext;
}

/**************************************************************************
 Function: 	 	lstLast

 Description: Changes psCurrent to the last element in the list

 Parameters:	psList  - pointer to a list
							pBuffer - void pointer used to store the value
							size    - size of value

 Returned:	 	Pointer to the buffer with the last element's value
 *************************************************************************/
void lstLast (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstLast", ERROR_INVALID_LIST);
	}
	if (0 == psList->numElements)
	{
		processError ("lstLast", ERROR_EMPTY_LIST);
	}
	// requires:  List is not empty
	// results:   If the list is not empty, current is changed to last
	//						if it exists
}

/**************************************************************************
 Function: 	 	lstInsertAfter

 Description: Insert the new element as the successor of the current element
 (and make the inserted element the current element)

 Parameters:	psList  - pointer to a list
							pBuffer - void pointer used to store the value
							size    - size of value

 Returned:	 	None
 *************************************************************************/
void lstInsertAfter (ListPtr psList, const void *pBuffer, int size)
{
	ListElementPtr psElementBuffer;

	if (NULL == psList)
	{
		processError ("lstInsertAfter", ERROR_INVALID_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstInsertAfter", ERROR_NULL_PTR);
	}
	if (0 != psList->numElements && NULL == psList->psCurrent)
	{
		processError ("lstInsertAfter", ERROR_NO_CURRENT);
	}

	psElementBuffer = (ListElementPtr) malloc (sizeof(ListElement));
	psElementBuffer->pData = malloc (size);
	memcpy (psElementBuffer->pData, pBuffer, size);

	if (NULL == psList->psCurrent)
	{
		psElementBuffer->psNext = NULL;
		psList->psFirst = psElementBuffer;
		psList->psLast = psElementBuffer;
	}
	else
	{
		psElementBuffer->psNext = psList->psCurrent->psNext;
		psList->psCurrent->psNext = psElementBuffer;
		if (psList->psCurrent == psList->psLast)
		{
			psList->psLast = psElementBuffer;
		}
	}
	psList->psCurrent = psElementBuffer;
	psList->numElements++;
}

/**************************************************************************
 Function: 	 	lstDeleteCurrent

 Description: Deletes the current element and adjusts successor and predecessor

 Parameters:	psList  - pointer to a list
							pBuffer - void pointer used to store the value
							size    - size of value

 Returned:	 	Pointer to the buffer with the last element's value
 *************************************************************************/
void *lstDeleteCurrent (ListPtr psList, void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstDeleteCurrent", ERROR_INVALID_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstDeleteCurrent", ERROR_NULL_PTR);
	}
	if (0 == psList->numElements)
	{
		processError ("lstDeleteCurrent", ERROR_EMPTY_LIST);
	}
	if (0 != psList->numElements && NULL == psList->psCurrent)
	{
		processError ("lstDeleteCurrent", ERROR_NO_CURRENT);
	}
	// requires: List is not empty
	// results: The current element is deleted and its successor and
	//				  predecessor become each others successor and predecessor. If
	//					the deleted element had a predecessor, then make it the new
	// 					current element; otherwise, make the first element current if
	// 					it exists. The value of the deleted element is returned.
	return (pBuffer);
}

/**************************************************************************
 Function: 	 	lstInsertBefore

 Description: Insert the new element as the predecessor of the current element
 (and make the inserted element the current element)

 Parameters:	psList  - pointer to a list
							pBuffer - void pointer used to store the value
							size    - size of value

 Returned:	 	Pointer to the buffer with the last element's value
 *************************************************************************/
void lstInsertBefore (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstInsertBefore", ERROR_INVALID_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstInsertBefore", ERROR_NULL_PTR);
	}
	if (0 != psList->numElements && NULL == psList->psCurrent)
	{
		processError ("lstInsertBefore", ERROR_NO_CURRENT);
	}
	// requires: List is not full
	// results:  If the list is not empty, insert the new element as the
	//           predecessor of the current element and make the inserted
	//           element the current element; otherwise, insert element
	//           and make it current.
}

/**************************************************************************
 Function: 	 	lstUpdateCurrent

 Description: Update the current element's value to the value of pBuffer

 Parameters:	psList  - pointer to a list
							pBuffer - void pointer used to store the value
							size    - size of value

 Returned:	 	None
 *************************************************************************/
void lstUpdateCurrent (ListPtr psList, const void *pBuffer, int size)
{
	if (NULL == psList)
	{
		processError ("lstUpdateCurrent", ERROR_INVALID_LIST);
	}
	if (NULL == pBuffer)
	{
		processError ("lstUpdateCurrent", ERROR_NULL_PTR);
	}
	if (0 == psList->numElements)
	{
		processError ("lstUpdateCurrent", ERROR_EMPTY_LIST);
	}
	if (0 != psList->numElements && NULL == psList->psCurrent)
	{
		processError ("lstUpdateCurrent", ERROR_NO_CURRENT);
	}
	// requires: List is not empty
	// results:  The value of pBuffer is copied into the current element
	// IMPORTANT: user could update with smaller, larger, or the same size data
	//					  so free data, then reallocate based on size before updating
}

/**************************************************************************
 Function: 	 	lstReverse

 Description: Reverse the order of the list

 Parameters:	psList  - pointer to a list

 Returned:	 	None
 *************************************************************************/
void lstReverse (ListPtr psList)
{
	if (NULL == psList)
	{
		processError ("lstUpdateCurrent", ERROR_INVALID_LIST);
	}
}
