/************************************************************************/
/*					IApp Header File													  	*/
/************************************************************************/
/* Function		Declarations used by the IApp functions.						*/
/* Author		(c) Copyright Infoline AG 1990-1995								*/
/*					Schaffhauserstrasse 121												*/
/*					CH-8302 Kloten - Switzerland										*/
/*					Phone: +41 1 803 07 06 / Fax: +41 1 881 17 55				*/
/* Last Update	V3.00 01/Mar/1995 Andy Brunner 	Chg: Commercial release	*/
/************************************************************************/

/*----------------------------------------------------------------------*/
/*					32Bit Compiler: Definition for 32->16 bit thunking layer	*/
/*----------------------------------------------------------------------*/

#ifdef	IAPP32
	#define	IAPP_SEG16	_Seg16
	#define	IAPP_API		_Far16 _Pascal
	#define	IAPP_API_C	_Far16 _Cdecl
#endif

#ifndef	IAPP32
	#define	IAPP_SEG16
	#define	IAPP_API		far pascal _loadds
	#define	IAPP_API_C	far cdecl _loadds
#endif

#define	IAPP_BOOL	USHORT

/************************************************************************/
/*					Base Functions	 													 	*/ 
/************************************************************************/

/*----------------------------------------------------------------------*/
/* IAppAbortProgram					Abort process with full-screen popup  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppAbortProgram(	/* No return value							*/
		PSZ		pszMessage);		/* Popup message or NULL  					*/

/*----------------------------------------------------------------------*/
/* IAppAllocMemory					Allocate storage from memory pool		*/
/*----------------------------------------------------------------------*/

IAPP_SEG16 PVOID IAPP_API IAppAllocMemory( /* Pointer to memory			*/
		USHORT	usSize,				/* Size of block or 0 for full 64KB		*/
		USHORT	usType);				/* Type (0=Private, 1=System-Shared)	*/

/*----------------------------------------------------------------------*/
/* IAppBeep								Sound speeker									*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppBeep(				/* No return value							*/
		VOID);							/* No parameters supported				  	*/

/*----------------------------------------------------------------------*/
/* IAppDateConversion				Convert date to various formats	 	  	*/
/*----------------------------------------------------------------------*/

typedef struct _IAPP_DATE
{
	ULONG		ulJulianDay;			/* Returned julian day						*/
	USHORT	usDayOfYear;			/* Returned day of year						*/
	UCHAR		ucDayOfWeek;			/* Returned day of week (0 = Sun)		*/
} IAPP_DATE;

typedef IAPP_DATE FAR *P_IAPP_DATE;

BOOL IAPP_API IAppDateConversion(
		USHORT	usYear,				/* Passed year									*/
		UCHAR		ucMonth,				/* Passed month								*/
		UCHAR		ucDay,				/* Passed day									*/
		P_IAPP_DATE	pxDate);			/* Structure with returned data			*/

/*----------------------------------------------------------------------*/
/* IAppDateFromJulian				Convert date from julian day		 	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppDateFromJulian( /* TRUE=Success or FALSE=Invalid date	*/
		ULONG		ulJulian,			/* Passed julian day							*/
		PUSHORT	pusYear,				/* Returned year	 							*/
		PUCHAR	pucMonth, 			/* Returned month	  							*/
		PUCHAR	pucDay);				/* Returned day  								*/

/*----------------------------------------------------------------------*/
/* IAppDateTime						Format system date and system time 	  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppDateTime(		/* No return value							*/
		PUCHAR	pszDate,				/* Date buffer (11 chars) or NULL 		*/
		PUCHAR	pszTime);			/* Time buffer (9 chars) or NULL	 		*/

/*----------------------------------------------------------------------*/
/* IAppDisableBreak					Disable or enable Ctrl-Break/Ctrl-C		*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppDisableBreak(	/* No return value							*/
		IAPP_BOOL fFlag);				/* TRUE=Disable or FALSE=Enable		  	*/

/*----------------------------------------------------------------------*/
/* IAppDisableKill					Disable or enable process kill			*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppDisableKill(	/* No return value							*/
		IAPP_BOOL fFlag);				/* TRUE=Disable or FALSE=Enable		  	*/

/*----------------------------------------------------------------------*/
/* IAppFileClose						Close file										*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppFileClose(		/* No return value							*/
		HFILE		hFile);				/* File handle								  	*/

/*----------------------------------------------------------------------*/
/* IAppFileCommit						Flush file buffer(s)							*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppFileCommit(		/* No return value							*/
		HFILE		hFile);				/* File handle or 0xffff for all files	*/

/*----------------------------------------------------------------------*/
/* IAppFileDelete						Delete file										*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppFileDelete(		/* No return value							*/
		PUCHAR	pszFileName);		/* File name									*/

/*----------------------------------------------------------------------*/
/* IAppFileInformation				Obtain file information						*/
/*----------------------------------------------------------------------*/

typedef struct _IAPP_FILE_INFO
{
	ULONG		ulAllocated;			/* Allocated file size	 					*/
	ULONG		ulSize;					/* Used file size			 					*/
	USHORT	usAttribute;			/* File attributes		 					*/
									
	struct
	{
		USHORT	usYear;				/* Year of creation			 				*/
		UCHAR		ucMonth;				/* Month of creation			 				*/
		UCHAR		ucDay;	 			/* Day of creation			 				*/
		UCHAR		ucHours;				/* Hours of creation							*/
		UCHAR		ucMinutes;			/* Minutes of creation						*/
		UCHAR		ucSeconds;			/* Seconds of creation						*/
	} Create;

	struct
	{
		USHORT	usYear;				/* Year of last write			  			*/
		UCHAR		ucMonth;				/* Month of last write			  			*/
		UCHAR		ucDay;				/* Day of last write				  			*/
		UCHAR		ucHours;				/* Hours of last write			  			*/
		UCHAR		ucMinutes;			/* Minutes of last write		  			*/
		UCHAR		ucSeconds;			/* Seconds of last write		  			*/
	} Write;

	struct
	{
		USHORT	usYear;				/* Year of last access				  		*/
		UCHAR		ucMonth;				/* Month of last access				  		*/
		UCHAR		ucDay; 				/* Day of last access				  		*/
		UCHAR		ucHours;				/* Hours of last access			 	  		*/
		UCHAR		ucMinutes;			/* Minutes of last access		 	  		*/
		UCHAR		ucSeconds;			/* Seconds of last access		 	  		*/
	} Access;

} IAPP_FILE_INFO;

typedef IAPP_FILE_INFO FAR *P_IAPP_FILE_INFO;

BOOL IAPP_API IAppFileInformation( /* TRUE=Success or FALSE=Not found	*/
		PUCHAR	pszFileName,		/* File name		 							*/
		P_IAPP_FILE_INFO pInf);		/* File information							*/

/*----------------------------------------------------------------------*/
/* IAppFileOpen						Open file										*/
/*----------------------------------------------------------------------*/

HFILE IAPP_API IAppFileOpen(		/* Handle or -1 if flag = FALSE			*/
		PUCHAR	pszFileName,		/* File name  									*/
		UCHAR		cType);				/* (R)ead, (W)rite, (A)ppend, (U)pdate	*/
											/* or (N) for deny-none read.				*/

/*----------------------------------------------------------------------*/
/* IAppFileRead						Read file										*/
/*----------------------------------------------------------------------*/

USHORT IAPP_API IAppFileRead(		/* Length of block read or 0 for EOF	*/
		HFILE		hFile,				/* File handle		 							*/
		PVOID		bBuffer,				/* Buffer			 							*/
		USHORT	usBufferSize);		/* Size of buffer	 							*/

/*----------------------------------------------------------------------*/
/* IAppFileSearch						Search file (current dir and DPATH)		*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppFileSearch(		/* TRUE=Success or FALSE=Not found		*/
		PUCHAR	pszFileName,		/* File name  									*/
		PUCHAR	pszFoundPath);		/* Found path (260 characters)			*/

/*----------------------------------------------------------------------*/
/* IAppFileSetPosition				Set file position								*/
/*----------------------------------------------------------------------*/

#define	IAPP_FILE_BEGIN	0L
#define	IAPP_FILE_END	  -1L

VOID IAPP_API IAppFileSetPosition( /* No return value							*/
		HFILE		hFile,				/* File handle	  								*/
		LONG		lPosition);			/* File position 								*/

/*----------------------------------------------------------------------*/
/* IAppFileWrite						Write file										*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppFileWrite(		/* No return value							*/
		HFILE		hFile,				/* File handle		 							*/
		PVOID		bBuffer,				/* Buffer			 							*/
		USHORT	usBufferSize);		/* Size of buffer	 							*/

/*----------------------------------------------------------------------*/
/* IAppFreeMemory						Free allocated memory from pool			*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppFreeMemory(		/* No return value							*/
		PVOID		pbMemory);			/* Address address to be freed			*/

/*----------------------------------------------------------------------*/
/* IAppGetCurrentPath				Get current path information 				*/
/*----------------------------------------------------------------------*/

PUCHAR IAPP_API IAppGetCurrentPath(	/* Complete path							*/
		PUCHAR	pszPath);			/* Complete path								*/

/*----------------------------------------------------------------------*/
/* IAppGetLogicalDrives				Get valid logical drives 					*/
/*----------------------------------------------------------------------*/

PUCHAR IAPP_API IAppGetLogicalDrives( /* Drive buffer							*/
		PUCHAR	pszDrives);			/* Drive buffer (27 characters)			*/

/*----------------------------------------------------------------------*/
/* IAppGetMessage						Retrieve message from message library 	*/
/*----------------------------------------------------------------------*/

IAPP_SEG16 PUCHAR IAPP_API IAppGetMessage(	/* Address of buffer			*/
		PUCHAR	pszMsgFile,			/* Message library file						*/
		USHORT	usMessageNmbr,		/* Message number								*/
		PUCHAR	pszBuffer,			/* Message buffer 							*/
		USHORT	usBufferSize);		/* Size of message buffer					*/

/*----------------------------------------------------------------------*/
/*	IAppGetToken						Return next token from file 				*/
/*----------------------------------------------------------------------*/

typedef struct _IAPP_GET_TOKEN
{
	UCHAR		szFileName[257]; 		/* Input file name							*/
	UCHAR		szErrorMsg[257];		/* Error message or "\0" if EOF			*/
	UCHAR		szToken[257];			/* Returned token								*/
	ULONG		ulCurrentLine;			/* Current line number						*/
	IAPP_BOOL fEnableComment;		/* Comment flag 								*/
} IAPP_GET_TOKEN;

typedef IAPP_GET_TOKEN FAR *P_IAPP_GET_TOKEN;

BOOL IAPP_API IAppGetToken(		/* TRUE=Success or FALSE=EOF or error	*/
		P_IAPP_GET_TOKEN pBuf);		/* Token structure							*/

/*----------------------------------------------------------------------*/
/* IAppIniClose						Close application .INI file				*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppIniClose(	 	/* No return value							*/
		PVOID		hIniFile);			/* Handle of .INI file						*/

/*----------------------------------------------------------------------*/
/* IAppIniOpen							Create or open application .INI			*/
/*----------------------------------------------------------------------*/

PVOID IAPP_API IAppIniOpen(		/* Handle of .INI file						*/
		HAB		habUser,				/* Existing PM anchor block or NULL		*/
		PUCHAR	pszIniFile);		/* File name									*/

/*----------------------------------------------------------------------*/
/* IAppIniRead							Read from .INI file							*/
/*----------------------------------------------------------------------*/

#define	IAPP_USRINI		(PVOID) (-1L)
#define	IAPP_SYSINI		(PVOID) (-2L)

ULONG IAPP_API IAppIniRead( 		/* Address of buffer							*/
		PVOID		hIniFile,			/* IAPP_SYSINI, IAPP_USRINI or handle	*/
		PUCHAR	pszApplName,		/* Application name							*/
		PUCHAR	pszKeyName,			/* Key name										*/
		PBYTE		pbBuffer,			/* Address of buffer to hold data		*/
		ULONG		ulBufferLength);	/* Length of buffer							*/

/*----------------------------------------------------------------------*/
/* IAppIniWrite						Write to .INI file							*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppIniWrite(		/* No return value							*/
		PVOID		hIniFile,			/* IAPP_SYSINI, IAPP_USRINI or handle	*/
		PUCHAR	pszApplName,		/* Application name							*/
		PUCHAR	pszKeyName,			/* Key name or NULL to delete all keys	*/
		PBYTE		pbBuffer,			/* Address of buffer							*/
		ULONG		ulBufferLength);	/* Length of buffer							*/

/*----------------------------------------------------------------------*/
/* IAppKeyboardFlush					Flush keyboard buffer 			    	  	*/
/*----------------------------------------------------------------------*/

#define IAPP_KBD_BKSP	0x0008
#define IAPP_KBD_RTAB	0x0009
#define IAPP_KBD_ENTER	0x000d
#define IAPP_KBD_ESC		0x001b

#define IAPP_KBD_F1		0xf001
#define IAPP_KBD_F2		0xf002
#define IAPP_KBD_F3		0xf003
#define IAPP_KBD_F4		0xf004
#define IAPP_KBD_F5		0xf005
#define IAPP_KBD_F6		0xf006
#define IAPP_KBD_F7		0xf007
#define IAPP_KBD_F8		0xf008
#define IAPP_KBD_F9		0xf009
#define IAPP_KBD_F10		0xf00a
#define IAPP_KBD_F11		0xf00b
#define IAPP_KBD_F12		0xf00c

#define IAPP_KBD_SF1		0xf011
#define IAPP_KBD_SF2		0xf012
#define IAPP_KBD_SF3		0xf013
#define IAPP_KBD_SF4		0xf014
#define IAPP_KBD_SF5		0xf015
#define IAPP_KBD_SF6		0xf016
#define IAPP_KBD_SF7		0xf017
#define IAPP_KBD_SF8		0xf018
#define IAPP_KBD_SF9		0xf019
#define IAPP_KBD_SF10	0xf01a
#define IAPP_KBD_SF11	0xf01b
#define IAPP_KBD_SF12	0xf01c

#define IAPP_KBD_AF1		0xf021
#define IAPP_KBD_AF2		0xf022
#define IAPP_KBD_AF3		0xf023
#define IAPP_KBD_AF4		0xf024
#define IAPP_KBD_AF5		0xf025
#define IAPP_KBD_AF6		0xf026
#define IAPP_KBD_AF7		0xf027
#define IAPP_KBD_AF8		0xf028
#define IAPP_KBD_AF9		0xf029
#define IAPP_KBD_AF10	0xf02a
#define IAPP_KBD_AF11	0xf02b
#define IAPP_KBD_AF12	0xf02c

#define IAPP_KBD_CENTER	0x0a

#define IAPP_KBD_CF1		0xf031
#define IAPP_KBD_CF2		0xf032
#define IAPP_KBD_CF3		0xf033
#define IAPP_KBD_CF4		0xf034
#define IAPP_KBD_CF5		0xf035
#define IAPP_KBD_CF6		0xf036
#define IAPP_KBD_CF7		0xf037
#define IAPP_KBD_CF8		0xf038
#define IAPP_KBD_CF9		0xf039
#define IAPP_KBD_CF10	0xf03a
#define IAPP_KBD_CF11	0xf03b
#define IAPP_KBD_CF12	0xf03c

#define IAPP_KBD_HOME	0xf041
#define IAPP_KBD_END		0xf042
#define IAPP_KBD_PGUP	0xf043
#define IAPP_KBD_PGDN	0xf044
#define IAPP_KBD_LEFT	0xf045
#define IAPP_KBD_RIGHT	0xf046
#define IAPP_KBD_UP		0xf047
#define IAPP_KBD_DOWN	0xf048
		  						  
#define IAPP_KBD_INS		0xf051
#define IAPP_KBD_DEL		0xf052
#define IAPP_KBD_LTAB	0xf053

#define IAPP_KBD_CHOME	0xf060
#define IAPP_KBD_CEND	0xf061
#define IAPP_KBD_CPGUP	0xf062
#define IAPP_KBD_CPGDN	0xf063
#define IAPP_KBD_CLEFT	0xf064
#define IAPP_KBD_CRIGHT	0xf065
#define IAPP_KBD_CUP		0xf066
#define IAPP_KBD_CDOWN	0xf067

VOID IAPP_API IAppKeyboardFlush(	/* No return value							*/
		VOID);					  		/* No arguments supported					*/

/*----------------------------------------------------------------------*/
/* IAppKeyboardRead					Read character from keyboard	    	  	*/
/*----------------------------------------------------------------------*/

USHORT IAPP_API IAppKeyboardRead( /* Key value									*/
		VOID);					  		/* No arguments supported				 	*/

/*----------------------------------------------------------------------*/
/* IAppMMFClose						Close memory mapped file				  	*/
/*----------------------------------------------------------------------*/

typedef VOID FAR *IAPP_MMF;		/* Memory mapped file handle				*/

VOID IAPP_API IAppMMFClose(		/* No return value							*/
		IAPP_MMF	hHandle);			/* Memory mapped file handle				*/

/*----------------------------------------------------------------------*/
/* IAppMMFDelete						Delete memory mapped file 				  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppMMFDelete(		/* No return value							*/
		PUCHAR	pszFileName);		/* Name of memory mapped file				*/

/*----------------------------------------------------------------------*/
/* IAppMMFOpen							Open memory mapped file						*/
/*----------------------------------------------------------------------*/

IAPP_MMF IAPP_API IAppMMFOpen(	/* File handle									*/
		PUCHAR	pszFileName,		/* Name of memory mapped file			 	*/
		UCHAR		ucOpenType);		/* 'W' Write, 'R' Read or 'A' Append 	*/

/*----------------------------------------------------------------------*/
/* IAppMMFRead							Read memory mapped file					  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppMMFRead(			/* TRUE=Success or FALSE=End of file	*/
		IAPP_MMF	hHandle,				/* Memory mapped file handle				*/
		PBYTE		*pbBuffer,			/* Pointer to buffer			 				*/
		PUSHORT	pusLength);			/* Length of buffer or 0 if EOF			*/

/*----------------------------------------------------------------------*/
/* IAppMMFSeek							Set position in memory mapped file		*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppMMFSeek(			/* TRUE=Success or FALSE=Wrong Record#	*/
		IAPP_MMF	hHandle,				/* Memory mapped file handle 				*/
		ULONG		ulRecord);			/* Next record number to read				*/

/*----------------------------------------------------------------------*/
/* IAppMMFWrite						Write memory mapped file  				  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppMMFWrite(		/* No return value							*/
		IAPP_MMF	hHandle,				/* Memory mapped file handle				*/
		PBYTE		pbBuffer,			/* Buffer to write			 				*/
		USHORT	usLength);			/* Length of buffer				 			*/

/*----------------------------------------------------------------------*/
/* IAppPrintClose						Close printer 						    	  	*/
/*----------------------------------------------------------------------*/

typedef struct _IAPP_PRINT
{
	/*-------------------------------------------------------------------*/
	/*	The following fields must be set before calling IAppPrintOpen.		*/
	/*	They must not be altered afterwards. The optional header and 		*/
	/* footer line(s) may contain tags for date, time or page numbers.	*/
	/* Those fields must be formatted according to the C sprintf syntax,	*/
	/* e.g. #hu (page), @s (date) or s (time).									*/
	/*-------------------------------------------------------------------*/
	UCHAR		ucPaperLength;	 		/* Paper length in number of lines	 	*/
	UCHAR		ucPaperWidth;			/* Paper width in number of characters	*/
	UCHAR		ucTopMargin;			/* Top margin in number of lines		  	*/
	UCHAR		ucBottonMargin;		/* Botton margin in number of lines	  	*/
	UCHAR		ucLeftMargin;			/* Left margin in number of characters	*/
	UCHAR		ucPreHeaderLine;		/* Character for line before header(s)	*/
	UCHAR		szHeader[5][256];		/* 0 to 5 header line(s)				  	*/
	UCHAR		ucPostHeaderLine;		/* Character for line after header(s) 	*/
	UCHAR		ucPreFooterLine;		/* Character for line before footer(s)	*/
	UCHAR		szFooter[5][256];		/* 0 to 5 footer line(s) 				  	*/
	UCHAR		ucPostFooterLine;		/* Character for line after footer(s) 	*/
	/*-------------------------------------------------------------------*/
	/*	The following fields must not be set or modified by the caller.	*/
	/*	They may be read anytime by the application for reference.			*/
	/*-------------------------------------------------------------------*/
	USHORT	usCurrentPage;			/* Current page number				  		*/
	UCHAR		ucCurrentLine;			/* Current line number				  		*/
	UCHAR		ucTotalLines;			/* Maximum number of lines per page		*/
	UCHAR		ucLinesLeft;			/* Number of lines left on this page	*/
	HFILE		hPrinter;				/* Device or file handle			  		*/
	IAPP_MMF	hMMFile;					/* Memory mapped file handle		  		*/
	PUCHAR	pMMFBuffer;				/* Memory mapped file buffer		  		*/
} IAPP_PRINT;

typedef IAPP_PRINT FAR *P_IAPP_PRINT;

VOID IAPP_API IAppPrintClose(		/* No return value							*/
		P_IAPP_PRINT xControl,		/* Control structure				  			*/
		PBYTE		pTermCmd,	  		/* Termination string (not for MMF)		*/
		USHORT	usTermLength);		/* Length of termination string			*/

/*----------------------------------------------------------------------*/
/* IAppPrintLine						Print line 							    	  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppPrintLine(		/* No return value							*/
		P_IAPP_PRINT xControl,		/* Control structure							*/
		PUCHAR	pszLine);	  		/* Print line or NULL for empty line	*/

/*----------------------------------------------------------------------*/
/* IAppPrintNewPage					Force skip to new page 			    	  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppPrintNewPage(	/* No return value							*/
		P_IAPP_PRINT xControl);		/* Control structure							*/

/*----------------------------------------------------------------------*/
/* IAppPrintOpen						Open printer 						    	  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppPrintOpen(		/* No return value							*/
		P_IAPP_PRINT xControl,		/* Control structure							*/
		PUCHAR	pszName,		  		/* Device/file name or "*MMFName"		*/
		PBYTE		pInitCmd,	  		/* Initialization string (not for MMF)	*/
		USHORT	usInitLength);		/* Length of initialization string		*/

/*----------------------------------------------------------------------*/
/* IAppPrintQuery						Query available printers		    	  	*/
/*----------------------------------------------------------------------*/

typedef struct _IAPP_PRINT_QUERY
{
	UCHAR		szName[13]; 			/* Queue or printer name 				 	*/
	UCHAR		szServer[16];			/* Server name if remote queue		 	*/
	UCHAR		szDevice[9];			/* Printer device name					 	*/
	UCHAR		szDriver[33];			/* Printer driver name					 	*/
	IAPP_BOOL fDefault;				/* Default printer (TRUE/FALSE)		 	*/
} IAPP_PRINT_QUERY;

typedef IAPP_PRINT_QUERY FAR *P_IAPP_PRINT_QUERY;

VOID IAPP_API IAppPrintQuery(		/* No return value							*/
		PSZ		pszMMFName);		/* Name of resulting MMF file				*/

/*----------------------------------------------------------------------*/
/* IAppProtect							Lock or unlock process resource	 	  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppProtect(			/* No return value							*/
		IAPP_BOOL fType);				/* TRUE=Lock or FALSE=Unlock 				*/

/*----------------------------------------------------------------------*/
/* IAppRoundSwiss						Round value using swiss rounding roule	*/
/*----------------------------------------------------------------------*/

double IAPP_API IAppRoundSwiss(	/* Rounded value								*/
		double	dValue);				/* Value to be rounded						*/

/*----------------------------------------------------------------------*/
/* 	IAppRPNCalc						Calculate RPN calculation expression	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppRPNCalc(			/* TRUE=Success or FALSE=Error			*/
		PUCHAR	pszCalcString,		/* String to be evaluated/calculated	*/
		double	*dResultValue,		/* Resulting value							*/
		PUCHAR	pszErrorMsg);		/* Error message (80 chars) if errors	*/

/*----------------------------------------------------------------------*/
/* IAppScanEnvironment				Return environment variable string	   */
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppScanEnvironment( /* TRUE=Success or FALSE=Not found	*/
		PUCHAR	pszEnvVar,			/* Variable to search, e.g. "DPATH"		*/
		PUCHAR	*pszEnvStr); 		/* Pointer to found string	 		  		*/

/*----------------------------------------------------------------------*/
/* IAppScreenClear					Clear part of the screen 				  	*/
/*----------------------------------------------------------------------*/

#define IAPP_COLOR_WHITE_ON_BLUE		0x17
#define IAPP_COLOR_WHITE$_ON_BLUE	0x1f
#define IAPP_COLOR_YELLOW_ON_BLUE	0x1e
#define IAPP_COLOR_GREEN$_ON_BLUE	0x1a
#define IAPP_COLOR_RED$_ON_BLUE		0x1c

VOID IAPP_API IAppScreenClear(	/* No return value							*/
		USHORT	usRowTop,			/* Top left row position					*/
		USHORT	usColumnTop,		/* Top left column position				*/
		USHORT	usRowBottom,		/* Bottom right row position				*/
		USHORT	usColumnBottom,	/* Upper left corner							*/
		UCHAR		ucAttribute);		/*	Character attribute						*/

/*----------------------------------------------------------------------*/
/* IAppScreenSetCursor				Set cursor position						  	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppScreenSetCursor( /* No return value							*/
		USHORT	usRow,				/* Row position								*/
		USHORT	usColumn);			/* Column position							*/

/*----------------------------------------------------------------------*/
/* IAppScreenWrite					Write string to the screen	 				*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppScreenWrite(	/* No return value							*/
		USHORT	usRow,				/* Row position								*/
		USHORT	usColumn,			/* Column position							*/
		PUCHAR	szString,			/* String to write							*/
		UCHAR		ucAttribute);		/*	Character attribute 						*/

/*----------------------------------------------------------------------*/
/* IAppService							Perform special IAPP services		  		*/
/*----------------------------------------------------------------------*/

#define IAPP_POPUP_NOWAIT	0x0001	/* Don't wait for ENTER at error		*/
#define IAPP_POPUP_WAIT		0x0002	/* Wait for ENTER at error				*/
#define IAPP_SQL_ROW_SIZE	0x0003	/* Return ULONG with SQL row size	*/
#define IAPP_SQL_DATA_AREA	0x0004	/* Return PVOID to SQL data area		*/
#define IAPP_LANG_CODE		0x0005	/* Return PUCHAR to language code	*/
#define IAPP_FOPEN_ABORT	0x0006	/* Abort if file open failed			*/
#define IAPP_FOPEN_NOABORT	0x0007	/* Return -1 if file open failed		*/
#define IAPP_LICENSE_NBR	0x0008	/* Return PUCHAR to license string	*/

IAPP_SEG16 PVOID IAPP_API IAppService( /* Value according to function	*/
		USHORT	usFunction);		/* Function to be performed 				*/

/*----------------------------------------------------------------------*/
/* IAppStrip							Strip blanks in string		 				*/
/*----------------------------------------------------------------------*/

IAPP_SEG16 PUCHAR IAPP_API IAppStrip( /* Address of string 					*/
		PUCHAR	pszString,			/* String to be stripped					*/
		UCHAR		ucAction);			/* 'L' Leading, 'T' Trailing, 'B' Both	*/

/*----------------------------------------------------------------------*/
/* IAppThreadCreate					Create thread					 				*/
/*----------------------------------------------------------------------*/

typedef struct _IAPP_THREAD
{
	/*-------------------------------------------------------------------*/
	/*	The following fields must not be set or modified by the caller.	*/
	/*	They may be read anytime by the application for reference.			*/
	/*-------------------------------------------------------------------*/
	HSEM			hsemWait; 			/* Wait semaphore								*/
	HSEM			hsemRun;				/* Run semaphore								*/
	IAPP_BOOL	fRunning;			/* TRUE=Running, FALSE=Waiting			*/
	PBYTE			pStack;				/* Thread stack								*/
	IAPP_BOOL	fWinCalls;			/* TRUE=WinCalls, FALSE=No WinCalls		*/
#ifdef IAPP32
	PVOID			pfnFunction;		/* Function to be executed					*/
#else
	VOID (far pascal *pfnFunction)(); /* Function to be executed		  	*/
#endif
	PVOID			pArgument;			/* Function argument							*/
} IAPP_THREAD;

typedef IAPP_THREAD FAR *P_IAPP_THREAD;

P_IAPP_THREAD IAPP_API IAppThreadCreate(	/* Return thread structure		*/
		IAPP_BOOL fWinCalls); 		/* TRUE=WinCalls, FALSE=No WinCalls		*/

/*----------------------------------------------------------------------*/
/* IAppThreadDestroy					Destroy thread					 				*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppThreadDestroy(	/* No return value							*/
		P_IAPP_THREAD	xControl);	/* Thread control structure				*/

/*----------------------------------------------------------------------*/
/* IAppThreadExecute					Execute thread					 				*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppThreadExecute(	/* No return value							*/
		P_IAPP_THREAD	hHandle,		/* Thread handle								*/
		PFN		pfnFunction,		/* Function to be executed					*/
		PVOID		pArgument);			/* Function argument or NULL				*/

/*----------------------------------------------------------------------*/
/* IAppTrace							Write trace record							*/
/*----------------------------------------------------------------------*/

VOID IAPP_API_C IAppTrace(
		PUCHAR	pszFunction,	/* Function name								  	*/
		IAPP_BOOL fType,			/* TRUE = Call, FALSE = Return or -1 for	*/
										/* normal (intermediate) call					*/
		PUCHAR	pszFormat,		/* Format string ($i = USHORT, $I = SHORT,*/
										/*	$l = ULONG, $L = LONG, $c = UCHAR,		*/
										/*	$C = CHAR, $s = PUCHAR, $p = PVOID,		*/
										/* $d = double, $b = hexadecimal)			*/
		...);							/* Optional parameters							*/
		
/*----------------------------------------------------------------------*/
/* IAppUpperCase						Fold string to uppercase 					*/
/*----------------------------------------------------------------------*/

IAPP_SEG16 PUCHAR IAPP_API IAppUpperCase(	/* Address of string				*/
		PUCHAR	pszString);			/* String to uppercase 						*/

/*----------------------------------------------------------------------*/
/* IAppWait								Wait the specified number of seconds	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppWait(				/* No return value							*/
		USHORT	usSeconds);			/* Wait time in seconds						*/

/*----------------------------------------------------------------------*/
/* IAppWaitMSec  						Wait specified number of Milliseconds	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppWaitMSec(		/* No return value							*/
		USHORT	usMilliSeconds);	/* Wait time in milliseconds 				*/

/************************************************************************/
/*					Dialog Manager Functions											*/ 
/************************************************************************/

/*----------------------------------------------------------------------*/
/* IAppDmCall							General call to OS/2 Dialog Manager		*/
/*----------------------------------------------------------------------*/

#define	IAPP_DM_ERROR	30001		/* Returned error (User code or GML)	*/
#define	IAPP_DM_ENTER	30002		/* Returned ENTER command 					*/
#define	IAPP_DM_CANCEL	30003		/* Returned ESC, ALT-F4 or CANCEL		*/
#define	IAPP_DM_EXIT	30004		/* Returned F3 or EXIT						*/
#define	IAPP_DM_FORCE	30005		/* Returned FORCEXIT							*/
#define	IAPP_DM_YES		30011		/* Returned 'Yes' (IAppDmQuestion)		*/
#define	IAPP_DM_NO		30012		/* Returned 'No' (IAppDmQuestion)		*/

BOOL IAPP_API IAppDmCall(			/* TRUE=Success or FALSE=Error			*/
		PUCHAR	pszDmCommand, 		/* DM service call command string 		*/
		USHORT	usVarCounter,		/* Size of variable or 0				  	*/
		PVOID		pbDmVariable, 		/* DM variables or NULL					  	*/
		PUSHORT	pszDmReturn); 		/* Returned command or NULL 				*/

/*----------------------------------------------------------------------*/
/* IAppDmMessage						Display message thru OS/2 DM			 	*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppDmMessage(		/* No return value							*/
		PUCHAR	pszMessage,		  	/* Message (max. 32767 chars)				*/
		IAPP_BOOL fTermFlag);  		/* TRUE=Terminate or FALSE=Continue 	*/

/*----------------------------------------------------------------------*/
/* IAppDmQuestion						Display question thru OS/2 DM				*/
/*----------------------------------------------------------------------*/

VOID IAPP_API IAppDmQuestion(		/* No return value							*/
		PUCHAR	pszMessage,	  		/* Message (max. 32767 chars)				*/
		PUSHORT	pusDmReturn);		/* Returned command 							*/

/************************************************************************/
/*					DB2/2 Functions		 											 	*/ 
/************************************************************************/

/*----------------------------------------------------------------------*/
/* IAppSqlClose						Close SQL database  				    	  	*/
/*----------------------------------------------------------------------*/

LONG IAPP_API IAppSqlClose(		/* 0 or SQL error code						*/
		VOID);					  		/* No arguments supported					*/

/*----------------------------------------------------------------------*/
/* IAppSqlCommit						Execute SQL "COMMIT" statement    	  	*/
/*----------------------------------------------------------------------*/

LONG IAPP_API IAppSqlCommit(		/* 0 or SQL error code						*/
		VOID);					  		/* No arguments supported					*/

/*----------------------------------------------------------------------*/
/* IAppSqlExec							Execute SQL statement			    	  	*/
/*----------------------------------------------------------------------*/

LONG IAPP_API IAppSqlExec(			/* 0 or SQL error code						*/
		USHORT	usSqlCursor,		/* SQL cursor (1-25 or 0 to close all)	*/
		PUCHAR	pszSqlStmt,			/* SQL statement or NULL=Close current	*/
		PVOID		pbTableAdr,			/* Result table address or NULL 			*/
		ULONG		ulTableSize, 		/* Number of rows in result table or 0L*/
		PULONG	pulRowsDone);		/* Number or rows processed or NULL		*/

/*----------------------------------------------------------------------*/
/* IAppSqlExecMMF						Perform IAppSqlExec into MMF File		*/
/*----------------------------------------------------------------------*/

LONG IAPP_API IAppSqlExecMMF(		/* 0 or SQL error code						*/
		USHORT	usSqlCursor,		/* SQL cursor (1-25 or 0 to close all)	*/
		PUCHAR	pszSqlStmt,			/* SQL statement								*/
		PUCHAR	pszMMFName,			/* Name of memory mapped file				*/
		USHORT	usRowSize,			/* Size of each result table row			*/
		ULONG		ulMaxRows, 			/* Maximum number of rows or 0 for all	*/
		PULONG	pulRowsDone);		/* Number or rows processed or NULL		*/

/*----------------------------------------------------------------------*/
/* IAppSqlMessage						Retrieve last error message  	    	  	*/
/*----------------------------------------------------------------------*/

IAPP_SEG16 PUCHAR IAPP_API IAppSqlMessage( /* Address of message buffer	*/
		PUCHAR	pszBuffer);		  	/* Message buffer (512 chars)		 		*/

/*----------------------------------------------------------------------*/
/* IAppSqlOpen							Open SQL database					    	  	*/
/*----------------------------------------------------------------------*/

LONG IAPP_API IAppSqlOpen(			/* 0 or SQL error code						*/
		PUCHAR	pszDataBase);		/* Database name 								*/

/*----------------------------------------------------------------------*/
/* IAppSqlQuote						Format SQL string (NULL or 'xxxx')    	*/
/*----------------------------------------------------------------------*/

IAPP_SEG16 PUCHAR IAPP_API IAppSqlQuote( /* Address of return buffer		*/
		PUCHAR	pszInput,	  		/* Input string buffer						*/
		PUCHAR	pszOutput);  		/* Output buffer or NULL					*/

/*----------------------------------------------------------------------*/
/* IAppSqlRollback					Execute SQL "ROLLBACK" statement    	*/
/*----------------------------------------------------------------------*/

LONG IAPP_API IAppSqlRollback(	/* 0 or SQL error code						*/
		VOID);					  		/* No arguments supported	 				*/

/************************************************************************/
/*					TCP/IP Socket Functions												*/ 
/************************************************************************/

typedef struct _IAPP_SOCKET
{
	LONG		hSocket;					/* Socket descriptor							*/
	LONG		lReturnCode;			/* Return code of socket interface		*/
	UCHAR		szErrorMessage[256];	/* Formatted message if FALSE returned	*/
} IAPP_SOCKET;

typedef IAPP_SOCKET FAR *P_IAPP_SOCKET;

/*----------------------------------------------------------------------*/
/* IAppSocketClose 					Close the TCP/IP socket	 		    	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppSocketClose( 	/* TRUE=Success or FALSE=Error			*/
		P_IAPP_SOCKET pxControl);	/* Control block								*/

/*----------------------------------------------------------------------*/
/* IAppSocketOpen	 					Open the TCP/IP socket 			    	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppSocketOpen(		/* TRUE=Success or FALSE=Error			*/
		P_IAPP_SOCKET *pxControl,	/* Address of control block pointer		*/
		PUCHAR	pszCallName,		/* Calling host name (NULL for server)	*/
		PUCHAR	pszServiceName);	/* Service name (defined in SERVICES)	*/

/*----------------------------------------------------------------------*/
/* IAppSocketRead						Read from the TCP/IP socket 	    	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppSocketRead( 	/* TRUE=Success or FALSE=Error			*/
		P_IAPP_SOCKET pxControl,	/* Control block								*/
		PVOID		bBuffer,				/* Buffer address 							*/
		PUSHORT	pusBufferSize);	/* Size of buffer read						*/

/*----------------------------------------------------------------------*/
/* IAppSocketWrite					Write to the TCP/IP socket		    	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppSocketWrite( 	/* TRUE=Success or FALSE=Error			*/
		P_IAPP_SOCKET pxControl,	/* Control block								*/
		PVOID		bBuffer,				/* Buffer address 							*/
		USHORT	usBufferSize);		/* Size of buffer	 							*/

/************************************************************************/
/*					CM/2 X.25 Functions	  											 	*/ 
/************************************************************************/

/*----------------------------------------------------------------------*/
/* IAppX25Close						Close X.25 link  					    	  	*/
/*----------------------------------------------------------------------*/

typedef struct _IAPP_X25
{
	UCHAR		ucChannelType;	 		/* X.25 channel type (S=SVC, P=PVC)	  	*/
	UCHAR		szRouteTable[9];		/* X.25 call routing table entry		  	*/
	LONG		lConnectionId;			/* X.25 channel connection identifier 	*/
	UCHAR		szErrorMsg[256];		/* Formatted message if FALSE returned	*/
} IAPP_X25;

typedef IAPP_X25 FAR *P_IAPP_X25;

BOOL IAPP_API IAppX25Close(		/* TRUE=Success or FALSE=Error			*/
		P_IAPP_X25 pxControl);		/* IApp X.25 control block				 	*/

/*----------------------------------------------------------------------*/
/* IAppX25Open							Open X.25 link						    	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppX25Open(			/* TRUE=Success or FALSE=Error			*/
		P_IAPP_X25 pxControl,		/* IApp X.25 control block				  	*/
		PSZ		pszCallAddr,		/* "nnnn" for SVC outgoing CALL (Link)	*/
											/* "*"    for SVC incoming CALL (Route)*/
											/* ""     for PVC channel       (Name)	*/
		PSZ		pszName);			/* X.25 SVC link, SVC route or PVC name*/

/*----------------------------------------------------------------------*/
/* IAppX25Read							Read X.25 link	 					    	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppX25Read(			/* TRUE=Success or FALSE=Error			*/
		P_IAPP_X25 pxControl, 		/* IApp X.25 control block	  				*/
		PUSHORT	pusLength,	 		/* Buffer length	 							*/
		PVOID		pBuffer);	 		/* Buffer 			 							*/

/*----------------------------------------------------------------------*/
/* IAppX25Write						Write X.25 link 					    	  	*/
/*----------------------------------------------------------------------*/

BOOL IAPP_API IAppX25Write(		/* TRUE=Success or FALSE=Error			*/
		P_IAPP_X25 pxControl,		/* IApp X.25 control block					*/
		PUSHORT	pusLength,	 		/* Buffer length								*/
		PVOID		pBuffer);	 		/* Buffer 										*/

/************************************************************************/
/*					Compiler Macros		  											 	*/ 
/************************************************************************/

/*----------------------------------------------------------------------*/
/* IAPPDEBUG							Write data to file				    	  	*/
/*----------------------------------------------------------------------*/

#define	IAPPDEBUG(f,b,l)			{	\
												HFILE hFile;\
												hFile = IAppFileOpen(f, 'a');\
												IAppFileWrite(hFile, (PVOID) b, l);\
												IAppFileWrite(hFile, "\r\n", 2);\
												IAppFileClose(hFile);\
											}

/************************************************************************/
/*			End of IAPP																		*/
/************************************************************************/

