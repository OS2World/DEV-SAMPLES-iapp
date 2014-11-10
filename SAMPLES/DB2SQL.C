/************************************************************************/
/*					DB2/2 SQL Sample Program											*/
/************************************************************************/
/* Function		Display the names of all DB2/2 system tables.	 			*/
/* Author		(c) Copyright Infoline AG 1995									*/
/*					Schaffhauserstrasse 121												*/
/*					CH-8302 Kloten - Switzerland										*/
/*					Phone: +41 1 803 07 06 / Fax: +41 1 881 17 55				*/
/* History		V3.00 01/Mar/1995 Andy Brunner	Initial program version	*/
/************************************************************************/

#define	INCL_BASE
#define	USER_OS2

#include "user.h"								/* Include the necessary files	*/
#include "iapp.h"								/* Include IAPP user file			*/

/*----------------------------------------------------------------------*/
/*	Function prototypes																	*/
/*----------------------------------------------------------------------*/

VOID TerminateProgram(PUCHAR pszErrorMessage);

/*======================================================================*/
/*	Function: main																		 	*/ 
/*======================================================================*/

SHORT main(SHORT sArgCounter, PUCHAR *pszArgVariables)
{
	/*-------------------------------------------------------------------*/
	/* Automatic variables																*/
	/*-------------------------------------------------------------------*/

	typedef struct
	{
		UCHAR		szCreator[9];
		UCHAR		szName[20];
		UCHAR		szType[2];
		UCHAR		szRemarks[41];
	} RESULT_TABLE;

	typedef RESULT_TABLE FAR *P_RESULT_TABLE;

	P_RESULT_TABLE		pxResultTable						= NULL;

	PUCHAR				pszSqlMessage						= NULL;
	PUCHAR				pszSqlStatement					= NULL;

	ULONG					ulRowsProcessed					= 0L;

	/*-------------------------------------------------------------------*/
	/* Display program title															*/
	/*-------------------------------------------------------------------*/

	printf("DB2/2 SQL Sample Program Version 3.00 - (c) Copyright Infoline AG 1995\n");
	printf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");
	printf("\n");

	/*-------------------------------------------------------------------*/
	/* Check program arguments															*/
	/*-------------------------------------------------------------------*/

	if (sArgCounter != 2)
		TerminateProgram("Usage: DB2SQL DatabaseName");

	/*-------------------------------------------------------------------*/
	/* Allocate memory for data structure											*/
	/*-------------------------------------------------------------------*/

	pszSqlMessage		= IAppAllocMemory(512, 0);
	pszSqlStatement	= IAppAllocMemory(32768, 0);
	pxResultTable		= IAppAllocMemory(sizeof(RESULT_TABLE), 0);

	/*-------------------------------------------------------------------*/
	/* Open the database																	*/
	/*-------------------------------------------------------------------*/

	if (IAppSqlOpen(pszArgVariables[1]) != 0L)
		TerminateProgram(IAppSqlMessage(pszSqlMessage));

	/*-------------------------------------------------------------------*/
	/* Display column title and prepare dynamic SQL statement				*/
	/*-------------------------------------------------------------------*/

	printf("Creator  Name               Type  Remarks\n");
	printf("컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴컴\n");

	strcpy(pszSqlStatement, "SELECT Creator, Name, Type, SUBSTR(Remarks,1,40) "\
									"FROM Sysibm.Systables "\
									"WHERE Type = 'T' "\
									"ORDER BY Creator, Name");

	/*-------------------------------------------------------------------*/
	/* Execute SQL statement to display all DB2/2 system tables				*/
	/*-------------------------------------------------------------------*/

	for (;;)
	{
		/*----------------------------------------------------------------*/
		/* Fetch next row in result table											*/
		/*----------------------------------------------------------------*/

		if (IAppSqlExec(1, pszSqlStatement, pxResultTable, 1L, &ulRowsProcessed) != 0L)
			TerminateProgram(IAppSqlMessage(pszSqlMessage));

		if (ulRowsProcessed == 0L)
			break;

		/*----------------------------------------------------------------*/
		/* Format and display the fetched row										*/
		/*----------------------------------------------------------------*/

		printf("%-8s %-18s %-5s %-40s\n",
			pxResultTable->szCreator,
			pxResultTable->szName,
			(pxResultTable->szType[0] == 'T') ? "Table" : "View",
			pxResultTable->szRemarks);
	}

	printf("\n");

	/*-------------------------------------------------------------------*/
	/* Commit the transaction															*/
	/*-------------------------------------------------------------------*/

	if (IAppSqlCommit() != 0L)
		TerminateProgram(IAppSqlMessage(pszSqlMessage));

	/*-------------------------------------------------------------------*/
	/* Close the database																*/
	/*-------------------------------------------------------------------*/

	if (IAppSqlClose() != 0L)
		TerminateProgram(IAppSqlMessage(pszSqlMessage));

	/*-------------------------------------------------------------------*/
	/* Free the memory of the data structures										*/
	/*-------------------------------------------------------------------*/

	IAppFreeMemory(pszSqlMessage);
	IAppFreeMemory(pszSqlStatement);
	IAppFreeMemory(pxResultTable);

	pszSqlMessage		= NULL;
	pszSqlStatement	= NULL;
	pxResultTable		= NULL;

	/*-------------------------------------------------------------------*/
	/* Return to the caller																*/
	/*-------------------------------------------------------------------*/

	return (0);
}

/*======================================================================*/
/*	Function: TerminateProgram														 	*/ 
/*======================================================================*/

VOID TerminateProgram(PUCHAR pszErrorMessage)
{
	/*-------------------------------------------------------------------*/
	/* Display error message and terminate program								*/
	/*-------------------------------------------------------------------*/

	puts(pszErrorMessage);

	exit(4);
}


