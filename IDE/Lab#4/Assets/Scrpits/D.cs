#define DEBUG_LEVEL_LOG
#define DEBUG_LEVEL_WARN
#define DEBUG_LEVEL_ERROR


using UnityEngine;
using System.Collections;

//Debug Class, that will help us with debugging 
//If we define some Debug warning, errors, logging my activating this methods we can actualy 
//setting the contidional to the platform of choice wlll only compile the method for that platform
public class D : MonoBehaviour 
{
	[System.Diagnostics.Conditional("DEBUG_LEVEL_LOG")]	
	public static void log(string format, params object[] paramList)
	{
		Debug.Log(string.Format(format, paramList));
	}

	[System.Diagnostics.Conditional("DEBUG_LEVEL_WARN")]	
	public static void warn(string format, params object[] paramList)
	{
		Debug.LogWarning(string.Format(format, paramList));
	}

	[System.Diagnostics.Conditional("DEBUG_LEVEL_ERROR")]	
	public static void error(string format, params object[] paramList)
	{
		Debug.LogError(string.Format(format, paramList));
	}


	//assert is verifing your input, for example assert in a string is to be a string not a null, so we verify
	[System.Diagnostics.Conditional( "UNITY_EDITOR" )]
	[System.Diagnostics.Conditional( "DEBUG_LEVEL_LOG" )]
	public static void assert(bool condition)
	{
		assert ( condition, string.Empty, false);
	}

	[System.Diagnostics.Conditional( "UNITY_EDITOR" )]
	[System.Diagnostics.Conditional( "DEBUG_LEVEL_LOG" )]
	public static void assert(bool condition, string assertString)
	{
		assert ( condition, assertString, false);
	}

	[System.Diagnostics.Conditional( "UNITY_EDITOR" )]
	[System.Diagnostics.Conditional( "DEBUG_LEVEL_LOG" )]
	public static void assert(bool condition, string assertString, bool pauseOnFail)
	{
		if(!condition)
		{
			Debug.LogError( "assert failed! " + assertString);

			if(pauseOnFail)
				Debug.Break();
		}
	}
}
