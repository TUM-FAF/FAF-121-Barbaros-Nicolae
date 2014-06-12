using UnityEngine;
using System.Collections;



public class UnityDebugerClass
{
	public class InnerClass
	{
		public struct dataHolder
		{
			int t;
			public string s;
			float f;
			
			public dataHolder(int t)
			{
				this.t = t;
				s = "faflabsers";
				f = 121.2014f;
			}
		}
		
		public dataHolder holder = new dataHolder(123456);
		private string className = "im not a class, im a structure";
	}
	
	public InnerClass innerClass = new InnerClass();
	public string className = "UnityDebuggerClass";
}
public class DebugginUI : MonoBehaviour {

	private string theString = "Im a string";
	private bool isTrue = true;
	private int bigNumber = 2342342;
	protected UnityDebugerClass unitydebuggerClass = new UnityDebugerClass();

	void OnGUI()
	{
		float _yPos = 5.0f;
		float _xPos = 5.0f;
		float _width = (Screen.width >= 960 || Screen.height >=960) ? 320 : 160;
		float _height = (Screen.width >= 960 || Screen.height >=960) ? 80 : 40;
		float _heightPlus = _height + 10.0f;

		if(GUI.Button(new Rect(_xPos, _yPos, _width, _height), "Log, warn and error"))
		{
			D.log("This is a log with formatting: (0:0.0)", 12.123213);
			D.warn("warning! warning!" );
			D.error("errort time. the vaue of gnarly.innerClass.hoder.s is: {0}", unitydebuggerClass.innerClass.holder.s);
		}

		if(GUI.Button(new Rect(_xPos, _yPos += _heightPlus, _width, _height), "Call with a null sting"))
		{
			protectMyInput(null, 140);
		}

		if(GUI.Button(new Rect(_xPos, _yPos += _heightPlus, _width, _height), "Call with a low number"))
		{
			protectMyInput(string.Empty, 50);
		}

		if(GUI.Button(new Rect(_xPos, _yPos += _heightPlus, _width, _height), "Call with valid input"))
		{
			protectMyInput(string.Empty, 400);
		}
	}

	//this is useful to check values in the inspector to be as you expacted7
	//that is an extremily useful little class for debugging!
	public void protectMyInput(string shouldNeverBeNull, int shouldBeAboveOneHundred)
	{
		D.assert( shouldNeverBeNull != null, "shouldNeverBeNull is null, that's not good");
		D.assert( shouldBeAboveOneHundred > 100, "shouldBeAboveOneHundred is less than 100", true);
	}
}

//Unity Debuger
